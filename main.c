// =======================================================================
//   D�rives de compilations
// =======================================================================
#include <p18cxxx.h>
#include <p18f46k22.h>
#include <string.h>
#include <delays.h>

#include "main.h"
#include "TIOS.h"
#include "fcts/OS/hardware.h"

#include "fcts/i2c/i2c.h"
#include "fcts/LCD/xlcd.h"
#include "fcts/LCD/writeOnLCD.h"

#include "fcts/GSM/My_GSM.h"
#include "fcts/USART/My_USART.h"
#include "fcts/Temperature/ftoa.h"
#include "fcts/Temperature/1wire.h"

#include "pconfig.h"
#include "TCPIPConfig.h"
#include "HardwareProfile.h"
#include "TCPIP Stack/StackTsk.h"
#include "TCPIP Stack/TCPIP.h"



// =======================================================================
//   Instructions PRAGMA
// =======================================================================
#pragma config FOSC     = INTIO67       // Fosc=1000 S�lection oscillateur interne, I/O sur RA6 and RA7
#pragma config PLLCFG   = ON		// 4xPLL
#pragma config PRICLKEN = ON            // primary clock
#pragma config FCMEN    = OFF		// Fail-Safe Clock Monitor
#pragma config DEBUG    = ON

#pragma config LVP      = OFF           // Programmation in situ (ICSP) en basse tension
#pragma config PWRTEN   = OFF           // Timer de d�marrage
#pragma config WDTEN    = OFF           // Chien de garde d�sactiv�
#pragma config BOREN    = OFF           // D�tection de fluctuation d'alimentation (Brown-out)
#pragma config IESO     = OFF           // apres PWRT et POR voir datasheet page42



// =======================================================================
//   Variables globales
// =======================================================================
char StateUp                = ZERO;
unsigned char IDCB_LED      = 0;            // ID de la callback "LedModeBlink"
unsigned char IDCB_EthSoTX  = 0;            // ID de la callback "EthernetSocketTX"


/* TEMPERATURE */
float TempProbeValues[] = {0,-50,100};      // Temp�rature CURRENT(0), MAXIMUM(1), MINIMUM(2)


/* LUMINOSITY */
float res = 0;                              // R�sultat de la conversion ADC
char  resConv[10];                          // Conversion valeur r�sultante ADC


/* REAL TIME CLOCK */
unsigned char ClockReadBuffer[]={0,0,0,0,0,0,0,0};//Obligatoire pour faire init
unsigned char ClockConvBuffer[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
unsigned char ClockInitBuffer[]={
    0x05,   //   05 - Seconds (doit �tre de min 1 sec car ne peut commencer par 0)
    0x45,   //   45 - Minutes
    0x10,   //   10 - Hours format 24h
    0x02,   //Mardi - Days
    0x13,   //   13 - Date
    0x01,   //  Jan - Month
    0x15,   // 2015 - Year
    0x01,   // DOIT �tre d�finit � min 1 pour ne pas terminer avec un 0 (puts)
    0x00    // Arr�te la transmission avec puts
};


/* ETHERNET */
#define EthernetPort    8080
#define MaxLenghtRX     30
APP_CONFIG              AppConfig;      // Structure d�clar�e dans StackTsk.h
                                        //(utiliser ds la fonction init_appconfig)
WORD ok                 = 0;
WORD nbrRecu            = 0;
unsigned char i         = 0;
BYTE DonneRecue[MaxLenghtRX];
static TCP_SOCKET sendSocket = INVALID_SOCKET;



// =======================================================================
//   Fonctions internes
// =======================================================================
void LedModeBlink(void);                                        //Gestion clignotement LED
void ButtonsManagement(volatile unsigned char *ptr_Button);     //Gestion des touches

void TemperatureProbe(void);            // Gestion de la temp�rature

void ClockInit(void);                   // Initialisation de l'I2C (+valeurs)
void ClockRead(void);                   // Lecture de l'horloge
void ClockShow(void);                   // Affichage de l'horloge
void BCD2ASC(unsigned char, char*);     // Conversion BCD vers ASCII

void USART1_RX(char *);                 // Gestion des trames Usart re�ues

void EthernetSocketInit(void);          // Initialisation d'un socket (module Ethernet)
void EthernetSocketRX(void);            // Fonction de r�ception par Ethernet
void EthernetSocketTX(void);            // Fonction d'envoie par Ethernet
static void InitAppConfig(void);        // Fonction requise � la pile TCP/IP
static void DisplayIPValue(IP_ADDR);    // Affichage adresse IP initialis�e



// =======================================================================
//   Programme principal
// =======================================================================
void main(void){

    InitHardware();                         // Initialisation des valeurs syst�mes
    USART1_TX_RX_9600();                    // Initialisation des registres USART1
    USART2_TX_RX_9600();                    // Initialisation des registres USART2
    TIOSInitialiser();                      // Initialisation de l'OS (appel des Callbacks)


    /*************************************
    *-> Configuration LCD
    **************************************/
    OpenXLCD(FOUR_BIT & LINES_5X7);         // Configuration fonctionnement LCD
    while(BusyXLCD());                      // Configuration du splash screen
    putrsXLCD("     T E M S    ");
    while(BusyXLCD());
    SetDDRamAddr(0x40);


    /*************************************
    *-> Configuration temperature
    **************************************/
    INTCONbits.GIE  = 0;                    // D�sactive temporairement les interruptons
    Convert_Temperature();                  // Lance une premi�re conversion
    INTCONbits.GIE  = 1;                    // R�active les interruptons apr�s conversion



    /*************************************
    *-> Configuration ADC
    **************************************/
    ANSELDbits.ANSD4	= 1;
    TRISDbits.TRISD4	= 1;
    ADCON2bits.ADFM	= 1;
    ADCON1bits.PVCFG	= 0b00;
    ADCON1bits.NVCFG	= 0b00;
    ADCON0bits.CHS	= 0b11000;
    ADCON2bits.ADCS	= 0b101;
    ADCON0bits.ADON	= 1;
    ADCON0bits.GO	= 1;


    /*************************************
    *-> Configuration horloge
    **************************************/
    ClockInit();                            //Initialisation de l'horloge et valeur de d�part


    /*************************************
    *-> Configuration de la pile TCP/IP
    **************************************/
    ENC_CS_TRIS         = 0;                // On d�finit le module utilis� sur le bus SPI
    ENC_CS_IO           = 1;                // m�me si dans notre cas, il n'y en a qu'un

    TickInit();                             // Initialise l'horloge de la pile TCPIP (Timer0)
    InitAppConfig();                        // Configuration des adresses et masque
    StackInit();                            // Initialise la pile
    EthernetSocketInit();


    /*************************************
    *-> Enregistrement des Callbacks
    **************************************/
    TIOSEnregistrerCB_Button(ButtonsManagement);
    TIOSEnregistrerCB_USART1_RX(USART1_RX);

    TIOSEnregistrerCB_TIMER(LedModeBlink, 50);
    TIOSEnregistrerCB_TIMER(TemperatureProbe, 1000);
    TIOSEnregistrerCB_TIMER(EthernetSocketRX, 50);
    IDCB_EthSoTX = TIOSEnregistrerCB_TIMER(EthernetSocketTX, 5000);



    /*************************************
    *-> Lancement de l'OS (Boucle infinie)
    **************************************/
    TIOSStart();
}


void LedModeBlink(void){
    LED = !LED;
}

// =======================================================================
//   Fonction de gestion de bouttons
// =======================================================================
void ButtonsManagement(volatile unsigned char *ptr_Button){
    switch (*ptr_Button){
        case UP :
            writeOnLCDS(FLUSH,   0x00, "     T E M S    ");
            if (StateUp == ZERO){
                TIOSRetirerCB_TIMER(IDCB_EthSoTX);
                writeOnLCDS(NOFLUSH, 0x40, "Updates disabled");
                StateUp = ONE;
            }else
                if (StateUp == ONE){
                    IDCB_EthSoTX = TIOSEnregistrerCB_TIMER(EthernetSocketTX, 5000);
                    writeOnLCDS(NOFLUSH, 0x40, "Updates  enabled");
                    StateUp = ZERO;
                }
            break;
            
	case DOWN :
            writeOnLCDS(FLUSH,0x00, "Luminosity: ");
            while(ADCON0bits.GO == 1);
            res = ((float)((ADRESH*256) + ADRESL)/1024)*5;
            ftoa(res,&resConv[0],2,'f');
            putsXLCD(resConv);
            Delay10KTCYx(200);
            ADCON0bits.GO=1;
            break;

	case CENTER :
            writeOnLCDS(FLUSH,   0x00, "     T E M S    ");
            writeOnLCDS(NOFLUSH, 0x40, "Choose an option");
            break;

        case RIGHT :
            writeOnLCDS(FLUSH,   0x00, "Temperature:");
            writeOnLCDF(NOFLUSH, AFTER, TempProbeValues[0], 1);

            prepareLCD(NOFLUSH,  0x40);
            writeOnLCDS(NOFLUSH, AFTER,"MAX:");
            writeOnLCDF(NOFLUSH, AFTER, TempProbeValues[1], 1);
            writeOnLCDS(NOFLUSH, AFTER,"MIN:");
            writeOnLCDF(NOFLUSH, AFTER, TempProbeValues[2], 1);
            break;

	case LEFT :
            ClockRead();
            ClockShow();
            break;
    }
}


// =======================================================================
//   Fonction de gestion de temp�rature
// =======================================================================
void TemperatureProbe(void){
    INTCONbits.GIE = 0;
    TempProbeValues[0] = Read_Temperature();
    INTCONbits.GIE = 1;

    if (TempProbeValues[0] < TempProbeValues[2])
        TempProbeValues[2] = TempProbeValues[0];

    if (TempProbeValues[0] > TempProbeValues[1])
        TempProbeValues[1] = TempProbeValues[0];

    if (TempProbeValues[0] > TEMPERATURE_MAX){
        GsmCallExecution();
    }
    if (TempProbeValues[0] < TEMPERATURE_MIN){
        GsmCallExecution();
    }
    
    INTCONbits.GIE = 0;
    Convert_Temperature();
    INTCONbits.GIE = 1;
}


// =======================================================================
//   Fonction de lecture de l'heure
// =======================================================================
void ClockInit(void){
    //I2C State (Initialization)
    TRISDbits.TRISD0 = 1;
    TRISDbits.TRISD1 = 1;

    OpenI2C2( MASTER, SLEW_OFF);
    SSP2ADD = 0x27;             //Baud rate

    //Ecriture de l'heure
    IdleI2C2();
    StartI2C2();                //Condition de START �quivalent � SSP2CON2bits.SEN = 1;
    while(SSP2CON2bits.SEN);    //Attends qu'il soit pr�s
    WriteI2C2(0b11010000);      //Adresse du p�riph�rique et mode d'�criture (0)
    WriteI2C2(0b00000000);      //Envoie l'adresse de start dans laquelle on commence � �crire

    //On commence � �crire les donn�es en se rapportant au format BCD (DS1307)
    //On d�finit un tableau pour �viter de faire des write pour chaque valeurs
    putsI2C2(&ClockInitBuffer[0]);   //Le tableau s'incr�mente seul
    StopI2C2();
}


// =======================================================================
//   Fonction de lecture de l'heure
// =======================================================================
void ClockRead(void){
    int i = 0;
    int nbBytes = 7;                            //Conversion de la date et l'heure
    unsigned char *ptr = &ClockConvBuffer[0];

    Delay10KTCYx(200);
    Delay10KTCYx(200);

    IdleI2C2();
    StartI2C2();
    while(SSP2CON2bits.SEN);
    WriteI2C2(0b11010000);                      //On doit utiliser le rewrite
    WriteI2C2(0b00000000);

    RestartI2C2();
    while(SSP2CON2bits.RSEN);
    WriteI2C2(0b11010001);

    getsI2C2(&ClockReadBuffer[0],nbBytes);
    StopI2C2();

    for(i=0 ; i < nbBytes ; i++, ptr+=2){
        BCD2ASC(ClockReadBuffer[i], ptr);}
    *ptr = 0;

    ptr = &ClockConvBuffer[0];
}


// =======================================================================
//   Fonction d'affichage de l'heure
// =======================================================================
void ClockShow(void){
    int j = 0;
    //Lecture de l'heure
    ClockRead();

    //Affichage de la date
    // -  8 et  9 Affichage du jour de la date
    // - 10 et 11 Affichage du mois de la date
    // - 12 et 13 Affichage de l'ann�e de la date
    writeOnLCDS(FLUSH, 0x00,"Date: ");
    for(j=8 ; j<14 ; j+=2){
        while(BusyXLCD());
        WriteDataXLCD(ClockConvBuffer[j]);
        while(BusyXLCD());
        WriteDataXLCD(ClockConvBuffer[j+1]);

        if(j != 12){
            while(BusyXLCD());
            WriteDataXLCD('-');
        }
    }

    //Affichage de l'heure
    // - 4 et 5 Affichage de l'heure
    // - 2 et 3 Affichage des minutes
    // - 0 et 1 Affichage des secondes
    writeOnLCDS(NOFLUSH, 0x40,"Time: ");
    for(j=5 ; j>=0 ; j-=2){
        while(BusyXLCD());
        WriteDataXLCD(ClockConvBuffer[j-1]);
        while(BusyXLCD());
        WriteDataXLCD(ClockConvBuffer[j]);

        if(j != 1){
            while(BusyXLCD());
            WriteDataXLCD(':');
        }
    }
}


// =======================================================================
//   Fonction de conversion BCD to ASCII
// =======================================================================
void BCD2ASC(unsigned char src, char *dest){
    static const char outputs[] = "0123456789ABCDEF";
    *dest++ = outputs[src>>4];
    *dest++ = outputs[src&0x0f];
}


// =======================================================================
//   Fonction de gestion de r�ception RX USART1
// =======================================================================
void USART1_RX(char *Trame){
    LED = 1;
    if ((Trame[0] = '#')){
        switch (Trame[1]){
            case 'A' :
                RELAIS = 1;
                break;

            case 'B' :
                RELAIS = 0;
                break;

            default:
                break;
        }
    }
}


// =======================================================================
//   Fonctions de gestion de l'ethernet
// =======================================================================
void EthernetSocketInit(void){
    StackTask();
    StackApplications();

    //Socket Serveur (re�oit)
    sendSocket = TCPOpen(0,
                    TCP_OPEN_SERVER,
                    EthernetPort,
                    TCP_PURPOSE_DEFAULT);

    while(BusyXLCD());
    if(sendSocket == INVALID_SOCKET)
        putrsXLCD("ETH: Socket Fail");
    else{
        putrsXLCD("ETH: Connected  ");
        Delay10KTCYx(200); Delay10KTCYx(200);
        DisplayIPValue(AppConfig.MyIPAddr);
    }    
}

void EthernetSocketTX(void)
{
    char j = 0;
    char tmpCUR[6];

    StackTask();
    StackApplications();

    if(TCPIsConnected(sendSocket)){

        ok = TCPIsPutReady(sendSocket);

        if(ok > 0){
            ok = TCPPutArray(sendSocket,AppConfig.NetBIOSName, 16);
            TCPFlush(sendSocket);
        }
    }

    for(j=0 ; j<3 ; j++){
        StackTask();
        StackApplications();

        if(TCPIsConnected(sendSocket)){

            ok = TCPIsPutReady(sendSocket);

            if(ok > 0){
                ftoa(TempProbeValues[j], tmpCUR, 2, 'F');
                ok = TCPPutArray(sendSocket,&tmpCUR[0], sizeof(float));
                TCPFlush(sendSocket);
            }
        }
    }
}

void EthernetSocketRX(void)
{
    StackTask();
    StackApplications();

    if(TCPIsConnected(sendSocket)){

        nbrRecu = TCPIsGetReady(sendSocket);
        if(nbrRecu > 0){

            for(i=0 ; i<=MaxLenghtRX ; i++)     // Remise � z�ro du tableau des donn�es
                    DonneRecue[i]=0;

            ok = TCPGetArray(sendSocket,&DonneRecue[0], nbrRecu);

            if(DonneRecue[0] == 35)           // Commandes: 35 = #
            {
                //DoorOpened=DO / DoorClosed= DC
                if(strcmppgm2ram(DonneRecue,"#DO") == 0){
                    RELAIS = 1;}
                if(strcmppgm2ram(DonneRecue,"#DC") == 0){
                    RELAIS = 0;}
            }
        }
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
    putrsXLCD("IP: ");

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

/*********************************************************************
 * Function:        void InitAppConfig(void)
 ********************************************************************/
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