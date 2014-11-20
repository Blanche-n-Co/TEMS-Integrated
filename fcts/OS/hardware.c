#include <p18cxxx.h>
#include <p18f46k22.h>

#include "hardware.h"


void InitHardware(void)
{
    /*************************************
    *-> Horloge et registres
    **************************************/
    OSCCONbits.IRCF=0b111; // 16MhZ !!

    // Configurer par défaut entrées analogiques
    ANSELA  = NUMERIC;
    ANSELB  = NUMERIC;
    ANSELC  = NUMERIC;
    ANSELD  = NUMERIC;
    ANSELE  = NUMERIC;


    
    /*************************************
    *-> Init des périphériques
    **************************************/
    // Configuration LED (RC2)
    LED_ANS         = NUMERIC;              // Led en Numérique
    LED_TRI         = OUTPUT_PORT;          // Led en sortie
    LED             = OFF;                  // Led off au démarrage

    // RA7 est toujours numérique
    BP_UP_TRI       = INPUT_PORT;           //BP_UP en Entrée (UP)

    BP_DOWN_ANS     = NUMERIC;              //BP_DOWN en Numérique
    BP_DOWN_TRI     = INPUT_PORT;           //BP_DOWN en Entrée

    BP_MIDDLE_ANS   = NUMERIC;              //BP_MIDDLE en Numérique
    BP_MIDDLE_TRI   = INPUT_PORT;           //BP_MIDdLE en Entrée

    // RA6 est toujours numérique
    BP_RIGHT_TRI    = INPUT_PORT;           //BP_RIGHT en Entrée

    // RC0 est toujours numérique
    BP_LEFT_TRI     = INPUT_PORT;           //BP_LEFT en Entrée

    // Configuration Broches INT0 (interruption bouton poussoir)
    INT_BP_ANS      = NUMERIC;              //INT_BP en Numérique
    INT_BP_TRI      = INPUT_PORT;           //INT_BP en Entrée

    // Configuration RELAIS (RB4)
    RELAIS_ANS      = NUMERIC;              //RELAIS_ANS en Numérique
    RELAIS_TRI      = OUTPUT_PORT;          //RELAIS en sortie
    RELAIS          = OFF;                  //RELAIS non activé au démarrage

    // Configuration DS18B20
    DS18B20_ANS     = NUMERIC;              // DS18B20_TRI en numérique

    //CONFIGURATION BROCHES LCD
    ANSELEbits.ANSE0= NUMERIC;              //RE0 (LCD R/W) en Numérique
    // RA4 est toujours numérique           //RA4 (LCD E) en Numérique
    ANSELDbits.ANSD5= NUMERIC;              //RA0 (LCD0) en Numérique
    ANSELAbits.ANSA1= NUMERIC;              //RA1 (LCD1) en Numérique
    ANSELAbits.ANSA2= NUMERIC;              //RA2 (LCD2) en Numérique
    ANSELAbits.ANSA3= NUMERIC;              //RA3 (LCD3) en Numérique

    // Configuration Entrées Anamogique (ADC)
    ANSELDbits.ANSD4= ANALOGIC;             //RD4 (Photo Diode , AN24) en Analogique
    ANSELBbits.ANSB2= ANALOGIC;             //RB2 (EXT_INT, AN8) en Analogique
}
