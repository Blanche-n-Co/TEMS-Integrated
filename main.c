// =======================================================================
//   Dérives de compilations
// =======================================================================
#include <p18cxxx.h>
#include <p18f46k22.h>
#include <string.h>
#include <delays.h>

#include "main.h"
#include "TIOS.h"

#include "fcts/LCD/xlcd.h"
#include "fcts/OS/hardware.h"
#include "fcts/LCD/writeOnLCD.h"
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
#pragma config FOSC     = INTIO67       // Fosc=1000 Sélection oscillateur interne, I/O sur RA6 and RA7
#pragma config PLLCFG   = ON		// 4xPLL
#pragma config PRICLKEN = ON            // primary clock
#pragma config FCMEN    = OFF		// Fail-Safe Clock Monitor
#pragma config DEBUG    = ON

#pragma config LVP      = OFF           // Programmation in situ (ICSP) en basse tension
#pragma config PWRTEN   = OFF           // Timer de démarrage
#pragma config WDTEN    = OFF           // Chien de garde désactivé
#pragma config BOREN    = OFF           // Détection de fluctuation d'alimentation (Brown-out)
#pragma config IESO     = OFF           // apres PWRT et POR voir datasheet page42



// =======================================================================
//   Variables globales
// =======================================================================
unsigned char IDCB_LED  = 0;            // ID de la callback "LedModeBlink"


/* TEMPERATURE */
float TemperatureCur =   0;             // Variable pour la température CURRENT
float TemperatureMin = 100;             // Variable pour la température MINIMUM
float TemperatureMax = -50;             // Variable pour la température MAXIMUM



/* ETHERNET */
#define EthernetPort    30302
#define MaxLenghtRX     30
APP_CONFIG              AppConfig;      // Structure déclarée dans StackTsk.h
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

void TemperatureProbe(void);            // Gestion de la température

void EthernetSocketInit(void);          // Initialisation d'un socket (module Ethernet)
void EthernetSocketTX(void);            // Fonction d'envoie par Ethernet
void EthernetSocketRX(void);            // Fonction de réception par Ethernet
static void InitAppConfig(void);        // Fonction requise à la pile TCP/IP
static void DisplayIPValue(IP_ADDR);    // Affichage adresse IP initialisée



// =======================================================================
//   Programme principal
// =======================================================================
void main(void){
    InitHardware();                         // Initialisation des valeurs systèmes
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
    *-> Configuration de la pile TCP/IP
    **************************************/
    ENC_CS_TRIS         = 0;                // On définit le module utilisé sur le bus SPI
    ENC_CS_IO           = 1;                // même si dans notre cas, il n'y en a qu'un

    TickInit();                             // Initialise l'horloge de la pile TCPIP (Timer0)
    InitAppConfig();                        // Configuration des adresses et masque
    StackInit();                            // Initialise la pile
    EthernetSocketInit();



    /*************************************
    *-> Configuration temperature
    **************************************/
    INTCONbits.GIE  = 0;                    // Désactive temporairement les interruptons
    Convert_Temperature();                  // Lance une première conversion
    INTCONbits.GIE  = 1;                    // Réactive les interruptons après conversion



    /*************************************
    *-> Enregistrement des Callbacks
    **************************************/
    TIOSEnregistrerCB_Button(ButtonsManagement);
    TIOSEnregistrerCB_TIMER(TemperatureProbe, 1000);
    TIOSEnregistrerCB_TIMER(EthernetSocketTX, 5000);


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
            break;
            
	case DOWN :
                IDCB_LED = TIOSEnregistrerCB_TIMER(LedModeBlink, 50);
            break;

	case CENTER :
                writeOnLCDS(FLUSH, 0x00,"");
            break;

        case RIGHT :
                writeOnLCDS(FLUSH, 0x00,"Temperature:");
                writeOnLCDF(NOFLUSH, AFTER, TemperatureCur, 1);
                
                prepareLCD(NOFLUSH, 0x40);
                writeOnLCDS(NOFLUSH, AFTER,"MIN:");
                writeOnLCDF(NOFLUSH, AFTER, TemperatureMin, 1);
                writeOnLCDS(NOFLUSH, AFTER,"MAX:");
                writeOnLCDF(NOFLUSH, AFTER, TemperatureMax, 1);
            break;

	case LEFT :
            break;
    }
}


// =======================================================================
//   Fonction de gestion de température
// =======================================================================
void TemperatureProbe(void){
    INTCONbits.GIE = 0;
    TemperatureCur = Read_Temperature();
    INTCONbits.GIE = 1;

    if (TemperatureCur < TemperatureMin)
        TemperatureMin = TemperatureCur;

    if (TemperatureCur > TemperatureMax)
        TemperatureMax = TemperatureCur;

    if (TemperatureCur > TEMPERATURE_MAX){
        //ACTION MODULE GSM
    }
    if (TemperatureCur < TEMPERATURE_MIN){
        //ACTION MODULE GSM
    }
    
    INTCONbits.GIE = 0;
    Convert_Temperature();
    INTCONbits.GIE = 1;
}


// =======================================================================
//   Fonctions de gestion de l'ethernet
// =======================================================================
void EthernetSocketInit(void){
    StackTask();
    StackApplications();

    //client = émet (port: 30302)
    sendSocket = TCPOpen((DWORD)(PTR_BASE)"10.10.10.3",
                         TCP_OPEN_IP_ADDRESS, EthernetPort, TCP_PURPOSE_DEFAULT);

    // sendSocket = TCPOpen(0,TCP_OPEN_SERVER,EthernetPort,TCP_PURPOSE_DEFAULT);

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
    char tmpCUR[6];
    
    StackTask();
    StackApplications();

    if(TCPIsConnected(sendSocket)){

        ok = TCPIsPutReady(sendSocket);

        if(ok > 0){
            ftoa(TemperatureCur, tmpCUR, 2, 'F');
            ok = TCPPutArray(sendSocket,&tmpCUR[0], 11);
            TCPFlush(sendSocket);
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

            for(i=0 ; i<=MaxLenghtRX ; i++)     // Remise à zéro du tableau des données
                    DonneRecue[i]=0;

            ok = TCPGetArray(sendSocket,&DonneRecue[0],nbrRecu);

            if(DonneRecue[0] == 35)           // Commandes: 35 = #
            {
                if(strcmppgm2ram(DonneRecue,"#Led")==0){
                    //Led;
                }
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