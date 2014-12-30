// =======================================================================
//   Dérives de compilations
// =======================================================================
#include <p18cxxx.h>
#include <p18f46k22.h>
#include <delays.h>
#include <string.h>

#include "TIOS.h"
#include "fcts/LCD/xlcd.h"
#include "fcts/OS/hardware.h"
#include "fcts/OS/My_TIMERS.h"
#include "fcts/Temperature/ftoa.h"

#include "pconfig.h"
#include "TCPIPConfig.h"
#include "HardwareProfile.h"
#include "TCPIP Stack/StackTsk.h"
#include "TCPIP Stack/TCPIP.h"



// =======================================================================
//   Déclaration des fonctions d'interruption
// =======================================================================
void MyInterruptLow(void);          //Fonction d'interruptions basses
void MyInterruptHight(void);        //Fonction d'interruptions hautes



// =======================================================================
//   Prérequis fonctionnement interruptions (Requis MCC18)
// =======================================================================
#pragma code lowVector=0x0018
void atInterruptLow(void){
  _asm GOTO MyInterruptLow _endasm}
#pragma code

#pragma code hightVector=0x0008
void atInterruptHight(void){
  _asm GOTO MyInterruptHight _endasm}
#pragma code



// =======================================================================
//   Déclaration des variables globales
// =======================================================================
volatile unsigned char BP_read_state = 0;
volatile unsigned char CPT_TIMER1 = 0;

/* ETHERNET */
#define EthernetPort    30302
#define MaxLenghtRX     30

APP_CONFIG      AppConfig;              // Structure déclarée dans StackTsk.h
                                        //(utiliser ds la fonction init_appconfig)
WORD ok         = 0;
WORD nbrRecu    = 0;
unsigned char i = 0;

BYTE DonneRecue[MaxLenghtRX];
static TCP_SOCKET sendSocket = INVALID_SOCKET;



// =======================================================================
//   Déclaration des fonctions
// =======================================================================
static void InitAppConfig(void);
static void DisplayIPValue(IP_ADDR);
static void DisplayMacValue(MAC_ADDR);



// =======================================================================
//   Déclaration des fonctions de callback
// =======================================================================
void (*MaCB[MAXCALLBACKCHRONO])(void);          //Callback chrono
unsigned int TempsCB[MAXCALLBACKCHRONO];
volatile unsigned int TickCB[MAXCALLBACKCHRONO];





// ****************  TIOSInitialiser ******************************
// Initialise l'OS: initialise les variables et démarre le Timer
// ****************************************************************
void TIOSInitialiser(void)
{
    unsigned char i;
    //Initialisation pour variables CallBack Chrono
    for (i=0 ; i<MAXCALLBACKCHRONO ; i++){
        MaCB[i] = 0;
        TempsCB[i] = 0;
    }
} 


// ****************  EnregistrerFonctionDeRappel ******************************
// Sauve l'adresse de la fonction à rappeler. Lorsque le nombre d'interruptions
// aura atteint temps millisecondes, le système rappellera la fonction
// *************************************************************************
unsigned char TIOSEnregistrerCB_TIMER(void(*ptFonction)(void), unsigned int tps)
{
    unsigned int i = 0;
    while (MaCB[i]!=0 && i<MAXCALLBACKCHRONO) i++;
     //S'il reste de la place on enregistre et on retourne 0 (opération réussie)
    if (i<MAXCALLBACKCHRONO)
    {
        MaCB[i]    = ptFonction;
        TempsCB[i] = tps;
        TickCB[i]  = 0;             //Initialiser le compteur à 0;
        return i;                   // ID du call back
    }
    else return 255;                //Il n'y a plus de place pour enregistrer un callback
}


// ****************  Retirer fonction de rappel ******************************
// Libère l'emplacement de la callback
// *************************************************************************
void TIOSRetirerCB_TIMER(unsigned char IDCB)
{
     if ((IDCB >=0) && IDCB<MAXCALLBACKCHRONO)
     {
        MaCB[IDCB] = 0;
        TempsCB[IDCB] = 0;
     }
}



// ****************  Boucle principale de l'OS ******************************
// Boucle infinie qui attend des événement liés aux interruptions pour 
// appeler les fonctions enregistrées
// *************************************************************************
void TIOSStart()
{
    unsigned char idx;

    InitHardware();

    /*************************************
    *-> Configuration des interruptions
    **************************************/
    INTCONbits.GIE      = 1;		// Active les interruptions générales
    INTCONbits.PEIE     = 1;		// Active les interruptions des peripheriques
    RCONbits.IPEN       = 1;		// Active les priorite des interruptions (indispensable pour les basses)

    //USART1
    IPR1bits.RC1IP      = 1;

    //TIMER1
    TIMER1_100ms();                     // Interruptions toutes les ms par Timer1
    PIE1bits.TMR1IE     = 1;		// Activation interruption Timer1 en overflow
    IPR1bits.TMR1IP     = 1;		// Activation interruption en Haute Priorité



    /*************************************
    *-> Configuration de l'affichage LCD
    **************************************/
    OpenXLCD(FOUR_BIT & LINES_5X7);

    while(BusyXLCD());                  // Configuration du splash screen
    putrsXLCD("     T E M S    ");
    while(BusyXLCD());
    SetDDRamAddr(0x40);


    /*************************************
    *-> Configuration de l'ADC
    **************************************/
    ANSELDbits.ANSD4    = 1;
    TRISDbits.TRISD4    = 1;

    ADCON0bits.ADON     = 1;
    ADCON0bits.CHS      = 0b11000;
    ADCON1bits.PVCFG    = 0b00;
    ADCON1bits.NVCFG    = 0b00;
    ADCON2bits.ADCS     = 0b101;
    ADCON2bits.ADFM     = 1;


    /*************************************
    *-> Configuration de la pile TCP/IP
    **************************************/
    ENC_CS_TRIS         = 0;                // On définit le module utilisé sur le bus SPI
    ENC_CS_IO           = 1;                // même si dans notre cas, il n'y en a qu'un

    TickInit();                             // Initialise l'horloge de la pile TCPIP (Timer0)
    InitAppConfig();                        // Configuration des adresses et masque
    StackInit();                            // Initialise la pile

    StackTask();
    StackApplications();


    //client = émet (port: 30302)
    sendSocket = TCPOpen((DWORD)(PTR_BASE)"192.168.0.200",
                         TCP_OPEN_IP_ADDRESS, EthernetPort, TCP_PURPOSE_DEFAULT);

    while(BusyXLCD());
    if(sendSocket==INVALID_SOCKET)
        putrsXLCD("ETH: Socket Failed");
    else
        putrsXLCD("ETH: Connected... ");

    Delay10KTCYx(200);                          //0.5sec
    Delay10KTCYx(200);                          //0.5sec

    DisplayIPValue(AppConfig.MyIPAddr);


    /*************************************
    *-> Boucle principale
    **************************************/
    while(1){
        for (idx = 0; idx < MAXCALLBACKCHRONO; idx++){      //Check les conditions pour rappeler les fonctions liées au temps
            if (MaCB[idx])                                  //Si on a l'adresse d'une fonction CB à cet index
                if (TickCB[idx] >= TempsCB[idx])            //Si on est arrivé au nombre de mS demandé, on appelle la fonction
                {
                    TickCB[idx] = 0;
                    MaCB[idx]();                            //Rappel de la fonction enregistrée!
                }
         }
     }
}



// =======================================================================
//   Fonctions interruptions BASSES
// =======================================================================
#pragma interrupt MyInterruptLow
void MyInterruptLow(void)
{
    if(INTCONbits.TMR0IF){
        TickUpdate();                           //Reset Timer0 et flag
    }
}



// =======================================================================
//   Fonctions interruptions HAUTES
// =======================================================================
#pragma interrupt MyInterruptHight
void MyInterruptHight(void)
{
    //Flag interruption sur boutons
    if(INTCONbits.INT0IF == 1){
        Delay10KTCYx(2);                        //Delay of 5ms
        if(BP_UP == 0)
            BP_read_state = 1;
        if(BP_MIDDLE == 0)
            BP_read_state = 2;
        if(BP_DOWN == 0)
            BP_read_state = 3;
        if(BP_LEFT == 0)
            BP_read_state = 4;
        if(BP_RIGHT == 0)
            BP_read_state = 5;
        INTCONbits.INT0IF = 0;
    }

    //Flag interruption sur TIMER1
    if (PIR1bits.TMR1IF){
        unsigned char i;

        for (i = 0; i < MAXCALLBACKCHRONO; i++) // Ajourne tous les ticks
            TickCB[i]++;

        TMR1H = 0xF0;
        TMR1L = 0x60;
        
	PIR1bits.TMR1IF = 0;
    }
}



// =======================================================================
//   Prérequis fonctionnement LCD
// =======================================================================
void DelayFor18TCY(void){
    Nop(); Nop(); Nop(); Nop(); Nop(); Nop();
    Nop(); Nop(); Nop(); Nop(); Nop(); Nop();
    Nop(); Nop(); Nop(); Nop(); Nop(); Nop();
}

void DelayPORXLCD(void){
    Delay10KTCYx(6);}           // 15ms

void DelayXLCD(void){
    Delay10KTCYx(2);}           //  5ms



// =======================================================================
//   Function:        void InitAppConfig(void)
// =======================================================================
static ROM BYTE SerializedMACAddress[6] = {MY_DEFAULT_MAC_BYTE1, MY_DEFAULT_MAC_BYTE2, MY_DEFAULT_MAC_BYTE3, MY_DEFAULT_MAC_BYTE4, MY_DEFAULT_MAC_BYTE5, MY_DEFAULT_MAC_BYTE6};

static void InitAppConfig(void){
#if defined(EEPROM_CS_TRIS) || defined(SPIFLASH_CS_TRIS)
	unsigned char vNeedToSaveDefaults = 0;
#endif

	while(1)
	{
		// Start out zeroing all AppConfig bytes to ensure all fields are
		// deterministic for checksum generation
		memset((void*)&AppConfig, 0x00, sizeof(AppConfig));

		AppConfig.Flags.bIsDHCPEnabled  = TRUE;
		AppConfig.Flags.bInConfigMode   = TRUE;
		memcpypgm2ram((void*)&AppConfig.MyMACAddr, (ROM void*)SerializedMACAddress, sizeof(AppConfig.MyMACAddr));

		AppConfig.MyIPAddr.Val      = MY_DEFAULT_IP_ADDR_BYTE1 | MY_DEFAULT_IP_ADDR_BYTE2<<8ul | MY_DEFAULT_IP_ADDR_BYTE3<<16ul | MY_DEFAULT_IP_ADDR_BYTE4<<24ul;
		AppConfig.DefaultIPAddr.Val = AppConfig.MyIPAddr.Val;
		AppConfig.MyMask.Val        = MY_DEFAULT_MASK_BYTE1 | MY_DEFAULT_MASK_BYTE2<<8ul | MY_DEFAULT_MASK_BYTE3<<16ul | MY_DEFAULT_MASK_BYTE4<<24ul;
		AppConfig.DefaultMask.Val   = AppConfig.MyMask.Val;
		AppConfig.MyGateway.Val     = MY_DEFAULT_GATE_BYTE1 | MY_DEFAULT_GATE_BYTE2<<8ul | MY_DEFAULT_GATE_BYTE3<<16ul | MY_DEFAULT_GATE_BYTE4<<24ul;
		AppConfig.PrimaryDNSServer.Val  = MY_DEFAULT_PRIMARY_DNS_BYTE1 | MY_DEFAULT_PRIMARY_DNS_BYTE2<<8ul  | MY_DEFAULT_PRIMARY_DNS_BYTE3<<16ul  | MY_DEFAULT_PRIMARY_DNS_BYTE4<<24ul;
		AppConfig.SecondaryDNSServer.Val= MY_DEFAULT_SECONDARY_DNS_BYTE1 | MY_DEFAULT_SECONDARY_DNS_BYTE2<<8ul  | MY_DEFAULT_SECONDARY_DNS_BYTE3<<16ul  | MY_DEFAULT_SECONDARY_DNS_BYTE4<<24ul;


		// Load the default NetBIOS Host Name
		memcpypgm2ram(AppConfig.NetBIOSName, (ROM void*)MY_DEFAULT_HOST_NAME, 16);
		FormatNetBIOSName(AppConfig.NetBIOSName);

		#if defined(WF_CS_TRIS)
			// Load the default SSID Name
			WF_ASSERT(sizeof(MY_DEFAULT_SSID_NAME) <= sizeof(AppConfig.MySSID));
			memcpypgm2ram(AppConfig.MySSID, (ROM void*)MY_DEFAULT_SSID_NAME, sizeof(MY_DEFAULT_SSID_NAME));
			AppConfig.SsidLength = sizeof(MY_DEFAULT_SSID_NAME) - 1;

	        AppConfig.SecurityMode = MY_DEFAULT_WIFI_SECURITY_MODE;
	        AppConfig.WepKeyIndex  = MY_DEFAULT_WEP_KEY_INDEX;

	        #if (MY_DEFAULT_WIFI_SECURITY_MODE == WF_SECURITY_OPEN)
	            memset(AppConfig.SecurityKey, 0x00, sizeof(AppConfig.SecurityKey));
	            AppConfig.SecurityKeyLength = 0;

	        #elif MY_DEFAULT_WIFI_SECURITY_MODE == WF_SECURITY_WEP_40
	            memcpypgm2ram(AppConfig.SecurityKey, (ROM void*)MY_DEFAULT_WEP_KEYS_40, sizeof(MY_DEFAULT_WEP_KEYS_40) - 1);
	            AppConfig.SecurityKeyLength = sizeof(MY_DEFAULT_WEP_KEYS_40) - 1;

	        #elif MY_DEFAULT_WIFI_SECURITY_MODE == WF_SECURITY_WEP_104
			    memcpypgm2ram(AppConfig.SecurityKey, (ROM void*)MY_DEFAULT_WEP_KEYS_104, sizeof(MY_DEFAULT_WEP_KEYS_104) - 1);
			    AppConfig.SecurityKeyLength = sizeof(MY_DEFAULT_WEP_KEYS_104) - 1;

	        #elif (MY_DEFAULT_WIFI_SECURITY_MODE == WF_SECURITY_WPA_WITH_KEY)       || \
	              (MY_DEFAULT_WIFI_SECURITY_MODE == WF_SECURITY_WPA2_WITH_KEY)      || \
	              (MY_DEFAULT_WIFI_SECURITY_MODE == WF_SECURITY_WPA_AUTO_WITH_KEY)
			    memcpypgm2ram(AppConfig.SecurityKey, (ROM void*)MY_DEFAULT_PSK, sizeof(MY_DEFAULT_PSK) - 1);
			    AppConfig.SecurityKeyLength = sizeof(MY_DEFAULT_PSK) - 1;

	        #elif (MY_DEFAULT_WIFI_SECURITY_MODE == WF_SECURITY_WPA_WITH_PASS_PHRASE)     || \
	              (MY_DEFAULT_WIFI_SECURITY_MODE == WF_SECURITY_WPA2_WITH_PASS_PHRASE)    || \
	              (MY_DEFAULT_WIFI_SECURITY_MODE == WF_SECURITY_WPA_AUTO_WITH_PASS_PHRASE)
	            memcpypgm2ram(AppConfig.SecurityKey, (ROM void*)MY_DEFAULT_PSK_PHRASE, sizeof(MY_DEFAULT_PSK_PHRASE) - 1);
	            AppConfig.SecurityKeyLength = sizeof(MY_DEFAULT_PSK_PHRASE) - 1;

	        #else
	            #error "No security defined"
	        #endif /* MY_DEFAULT_WIFI_SECURITY_MODE */

		#endif

		// Compute the checksum of the AppConfig defaults as loaded from ROM
//		wOriginalAppConfigChecksum = CalcIPChecksum((BYTE*)&AppConfig, sizeof(AppConfig));

		#if defined(EEPROM_CS_TRIS) || defined(SPIFLASH_CS_TRIS)
		{
			NVM_VALIDATION_STRUCT NVMValidationStruct;

			// Check to see if we have a flag set indicating that we need to
			// save the ROM default AppConfig values.
			if(vNeedToSaveDefaults)
				SaveAppConfig(&AppConfig);

			// Read the NVMValidation record and AppConfig struct out of EEPROM/Flash
			#if defined(EEPROM_CS_TRIS)
			{
				XEEReadArray(0x0000, (BYTE*)&NVMValidationStruct, sizeof(NVMValidationStruct));
				XEEReadArray(sizeof(NVMValidationStruct), (BYTE*)&AppConfig, sizeof(AppConfig));
			}
			#elif defined(SPIFLASH_CS_TRIS)
			{
				SPIFlashReadArray(0x0000, (BYTE*)&NVMValidationStruct, sizeof(NVMValidationStruct));
				SPIFlashReadArray(sizeof(NVMValidationStruct), (BYTE*)&AppConfig, sizeof(AppConfig));
			}
			#endif

			// Check EEPROM/Flash validitity.  If it isn't valid, set a flag so
			// that we will save the ROM default values on the next loop
			// iteration.
			if((NVMValidationStruct.wConfigurationLength != sizeof(AppConfig)) ||
			   (NVMValidationStruct.wOriginalChecksum != wOriginalAppConfigChecksum) ||
			   (NVMValidationStruct.wCurrentChecksum != CalcIPChecksum((BYTE*)&AppConfig, sizeof(AppConfig))))
			{
				// Check to ensure that the vNeedToSaveDefaults flag is zero,
				// indicating that this is the first iteration through the do
				// loop.  If we have already saved the defaults once and the
				// EEPROM/Flash still doesn't pass the validity check, then it
				// means we aren't successfully reading or writing to the
				// EEPROM/Flash.  This means you have a hardware error and/or
				// SPI configuration error.
				if(vNeedToSaveDefaults)
				{
					while(1);
				}

				// Set flag and restart loop to load ROM defaults and save them
				vNeedToSaveDefaults = 1;
				continue;
			}

			// If we get down here, it means the EEPROM/Flash has valid contents
			// and either matches the ROM defaults or previously matched and
			// was run-time reconfigured by the user.  In this case, we shall
			// use the contents loaded from EEPROM/Flash.
			break;
		}
		#endif
		break;
	}
}


static void DisplayIPValue(IP_ADDR IPVal)
{
    //	printf("%u.%u.%u.%u", IPVal.v[0], IPVal.v[1], IPVal.v[2], IPVal.v[3]);
    BYTE IPDigit[4];
    BYTE i;

    while(BusyXLCD());
    SetDDRamAddr(0x40);
    while(BusyXLCD());
    putrsXLCD("ETH: ");

    for(i = 0 ; i < sizeof(IP_ADDR) ; i++){
        uitoa((WORD)IPVal.v[i], IPDigit);       //Converts to a null-terminated string

        while(BusyXLCD());
        putsXLCD(IPDigit);

        if(i == sizeof(IP_ADDR)-1)
            break;

        while(BusyXLCD());
        putrsXLCD(".");
    }
}