// =======================================================================
//   Dérives de compilations
// =======================================================================
#include <p18cxxx.h>
#include <p18lf46k22.h>
#include <delays.h>
#include <string.h>

#include "main.h"
#include "fcts/LCD/xlcd.h"
#include "fcts/OS/hardware.h"
#include "fcts/Temperature/ftoa.h"

#include "pconfig.h"
#include "TCPIPConfig.h"
#include "HardwareProfile.h"
#include "TCPIP Stack/StackTsk.h"
#include "TCPIP Stack/TCPIP.h"






// =======================================================================
//   Instructions PRAGMA
// =======================================================================
#pragma config FOSC     = INTIO67       //Fosc=1000 Sélection oscillateur interne, I/O sur RA6 and RA7
#pragma config PLLCFG   = ON		//4xPLL
#pragma config PRICLKEN = ON            //primary clock
#pragma config FCMEN    = OFF		//Fail-Safe Clock Monitor

#pragma config LVP      = OFF           //Programmation in situ (ICSP) en basse tension
#pragma config PWRTEN   = OFF           //Timer de démarrage
#pragma config WDTEN    = OFF           //Chien de garde désactivé
#pragma config BOREN    = OFF           //Détection de fluctuation d'alimentation (Brown-out)
#pragma config IESO     = OFF           //apres PWRT et POR voir datasheet page42





// =======================================================================
//   Variables globales
// =======================================================================
volatile unsigned char BP_read_state = 0;
volatile unsigned char CPT_TIMER1 = 0;

/* Module Ethernet
 */
#define Port            30302
#define MaxLenghtRX	30

APP_CONFIG AppConfig;                   //structure déclarée dans StackTsk.h
                                        //(utiliser ds la fonction init_appconfig)
WORD ok         = 0;
WORD nbrRecu    = 0;
unsigned char i = 0;

BYTE DonneRecue[MaxLenghtRX];
static TCP_SOCKET sendSocket = INVALID_SOCKET;





// =======================================================================
//   Déclaration des fonctions
// =======================================================================
void MyInterruptLow(void);
void MyInterruptHight(void);

static void InitAppConfig(void);
static void DisplayIPValue(IP_ADDR);
static void DisplayMacValue(MAC_ADDR);




// =======================================================================
//   Programme principal
// =======================================================================
void main(void){
    InitHardware();
    
    /*************************************
    *-> Configuration des interruptions
    **************************************/
    INTCONbits.GIE      = 1;		//active les interruptions générales
    INTCONbits.PEIE     = 1;		//active les interruptions des peripheriques
    RCONbits.IPEN       = 1;		//active les priorite des interruptions (indispensable pour les basses)

    //USART1
    IPR1bits.RC1IP      = 1;


    /*************************************
    *-> Configuration de l'affichage LCD
    **************************************/
    OpenXLCD(FOUR_BIT & LINES_5X7);

    while(BusyXLCD());                  // Configuration du splash screen
    putrsXLCD("     T E M S    ");
    while(BusyXLCD());
    SetDDRamAddr(0x40);

    
    /*************************************
    *-> Configuration du timer 1 (envoi régulier des infos)
    **************************************/
    T1CONbits.TMR1ON    = 1;                // Active le timer1
    T1GCONbits.TMR1GE   = 0;                // Gate non utilisée
    T1CONbits.TMR1CS    = 0b00;             // Clock source = Instruction clock
    T1CONbits.T1CKPS    = 0b11;             // Prescaler de 8
    T1CONbits.T1RD16    = 1;                // Travaille sur 16 bits
    T1CONbits.T1SYNC    = 1;                // Valeur ignorée

    TMR1H:TMR1L         = 15535;            // Valeur de départ

    PIE1bits.TMR1IE     = 1;                // Active les interruptions
    IPR1bits.TMR1IP     = 1;                // en priorité HAUTE
    PIR1bits.TMR1IF     = 0;                // avec le FLAG à 0


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
                         TCP_OPEN_IP_ADDRESS, 30302, TCP_PURPOSE_DEFAULT);

    while(BusyXLCD());
    if(sendSocket==INVALID_SOCKET)
        putrsXLCD("ETH: Socket Failed");
    else
        putrsXLCD("ETH: Connected... ");

    Delay10KTCYx(200);                          //0.5sec
    Delay10KTCYx(200);                          //0.5sec

    DisplayIPValue(AppConfig.MyIPAddr);
    //DisplayMacValue(AppConfig.MyMACAddr);     // Encore quelques erreurs...
 
    
    /*************************************
    *-> Boucle principale
    **************************************/
    while(1){
        
	StackTask();
	StackApplications();

        if(TCPIsConnected(sendSocket)){

            nbrRecu = TCPIsGetReady(sendSocket);
            if(nbrRecu > 0){

                for(i=0;i<=MaxLenghtRX;i++)     // Remise à zéro du tableau des données
                        DonneRecue[i]=0;

                ok = TCPGetArray(sendSocket,&DonneRecue[0],nbrRecu);

                if(DonneRecue[0]==35)           // Commandes: 35 = #
                {
                    if(strcmppgm2ram(DonneRecue,"#Led")==0){
                        //Led;
                    }
                }
                StackTask();
                StackApplications();
            }

            //envoi au pc ce qui a ete recu une fois que c'est fini
            ok = TCPIsPutReady(sendSocket);
            if(ok > 0){
                    ok = TCPPutArray(sendSocket,&DonneRecue[0],11);
                    TCPFlush(sendSocket);
            }
        }
        // Gérer les boutons (int)
        //Gérer les converesions ADC (ext)
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
//   Prérequis fonctionnement interruptions
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
//   Fonctions interruptions
// =======================================================================
#pragma interrupt MyInterruptLow
void MyInterruptLow(void)
{
    if(INTCONbits.TMR0IF){
        TickUpdate();                       //Reset Timer0 et flag
    }
}


#pragma interrupt MyInterruptHight
void MyInterruptHight(void)
{
    if(INTCONbits.INT0IF == 1){
        Delay10KTCYx(2);                    //Delay of 5ms
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
    
    if(PIR1bits.TMR1IF == 1){
        TMR1H:TMR1L = 15535;
        CPT_TIMER1++;
        PIR1bits.TMR1IF=0;
    }
}





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


		// SNMP Community String configuration
		#if defined(STACK_USE_SNMP_SERVER)
		{
			BYTE i;
			static ROM char * ROM cReadCommunities[] = SNMP_READ_COMMUNITIES;
			static ROM char * ROM cWriteCommunities[] = SNMP_WRITE_COMMUNITIES;
			ROM char * strCommunity;

			for(i = 0; i < SNMP_MAX_COMMUNITY_SUPPORT; i++)
			{
				// Get a pointer to the next community string
				strCommunity = cReadCommunities[i];
				if(i >= sizeof(cReadCommunities)/sizeof(cReadCommunities[0]))
					strCommunity = "";

				// Ensure we don't buffer overflow.  If your code gets stuck here,
				// it means your SNMP_COMMUNITY_MAX_LEN definition in TCPIPConfig.h
				// is either too small or one of your community string lengths
				// (SNMP_READ_COMMUNITIES) are too large.  Fix either.
				if(strlenpgm(strCommunity) >= sizeof(AppConfig.readCommunity[0]))
					while(1);

				// Copy string into AppConfig
				strcpypgm2ram((char*)AppConfig.readCommunity[i], strCommunity);

				// Get a pointer to the next community string
				strCommunity = cWriteCommunities[i];
				if(i >= sizeof(cWriteCommunities)/sizeof(cWriteCommunities[0]))
					strCommunity = "";

				// Ensure we don't buffer overflow.  If your code gets stuck here,
				// it means your SNMP_COMMUNITY_MAX_LEN definition in TCPIPConfig.h
				// is either too small or one of your community string lengths
				// (SNMP_WRITE_COMMUNITIES) are too large.  Fix either.
				if(strlenpgm(strCommunity) >= sizeof(AppConfig.writeCommunity[0]))
					while(1);

				// Copy string into AppConfig
				strcpypgm2ram((char*)AppConfig.writeCommunity[i], strCommunity);
			}
		}
		#endif

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

//static void DisplayMacValue(MAC_ADDR MacVal)
//{
//    BYTE MacDigit[6];
//    BYTE i;
//
//    while(BusyXLCD());
//    SetDDRamAddr(0x40);
//
//    for(i = 0 ; i < sizeof(MAC_ADDR) ; i++){
//        itoa((WORD)MacVal.v[i], MacDigit);
//
//        while(BusyXLCD());
//        putsXLCD(MacDigit);
//
//        if(i == sizeof(MAC_ADDR)-1)
//            break;
//
//        while(BusyXLCD());
//        putrsXLCD("-");
//    }
//}
