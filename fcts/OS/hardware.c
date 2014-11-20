#include <p18cxxx.h>
#include <p18f46k22.h>

#include "hardware.h"


void InitHardware(void)
{
    /*************************************
    *-> Horloge et registres
    **************************************/
    OSCCONbits.IRCF=0b111; // 16MhZ !!

    // Configurer par d�faut entr�es analogiques
    ANSELA  = NUMERIC;
    ANSELB  = NUMERIC;
    ANSELC  = NUMERIC;
    ANSELD  = NUMERIC;
    ANSELE  = NUMERIC;


    
    /*************************************
    *-> Init des p�riph�riques
    **************************************/
    // Configuration LED (RC2)
    LED_ANS         = NUMERIC;              // Led en Num�rique
    LED_TRI         = OUTPUT_PORT;          // Led en sortie
    LED             = OFF;                  // Led off au d�marrage

    // RA7 est toujours num�rique
    BP_UP_TRI       = INPUT_PORT;           //BP_UP en Entr�e (UP)

    BP_DOWN_ANS     = NUMERIC;              //BP_DOWN en Num�rique
    BP_DOWN_TRI     = INPUT_PORT;           //BP_DOWN en Entr�e

    BP_MIDDLE_ANS   = NUMERIC;              //BP_MIDDLE en Num�rique
    BP_MIDDLE_TRI   = INPUT_PORT;           //BP_MIDdLE en Entr�e

    // RA6 est toujours num�rique
    BP_RIGHT_TRI    = INPUT_PORT;           //BP_RIGHT en Entr�e

    // RC0 est toujours num�rique
    BP_LEFT_TRI     = INPUT_PORT;           //BP_LEFT en Entr�e

    // Configuration Broches INT0 (interruption bouton poussoir)
    INT_BP_ANS      = NUMERIC;              //INT_BP en Num�rique
    INT_BP_TRI      = INPUT_PORT;           //INT_BP en Entr�e

    // Configuration RELAIS (RB4)
    RELAIS_ANS      = NUMERIC;              //RELAIS_ANS en Num�rique
    RELAIS_TRI      = OUTPUT_PORT;          //RELAIS en sortie
    RELAIS          = OFF;                  //RELAIS non activ� au d�marrage

    // Configuration DS18B20
    DS18B20_ANS     = NUMERIC;              // DS18B20_TRI en num�rique

    //CONFIGURATION BROCHES LCD
    ANSELEbits.ANSE0= NUMERIC;              //RE0 (LCD R/W) en Num�rique
    // RA4 est toujours num�rique           //RA4 (LCD E) en Num�rique
    ANSELDbits.ANSD5= NUMERIC;              //RA0 (LCD0) en Num�rique
    ANSELAbits.ANSA1= NUMERIC;              //RA1 (LCD1) en Num�rique
    ANSELAbits.ANSA2= NUMERIC;              //RA2 (LCD2) en Num�rique
    ANSELAbits.ANSA3= NUMERIC;              //RA3 (LCD3) en Num�rique

    // Configuration Entr�es Anamogique (ADC)
    ANSELDbits.ANSD4= ANALOGIC;             //RD4 (Photo Diode , AN24) en Analogique
    ANSELBbits.ANSB2= ANALOGIC;             //RB2 (EXT_INT, AN8) en Analogique
}
