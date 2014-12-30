// =======================================================================
//   Dérives de compilations
// =======================================================================
#include <p18cxxx.h>
#include <p18f46k22.h>

#include "TIOS.h"
#include "fcts/OS/hardware.h"



// =======================================================================
//   Instructions PRAGMA
// =======================================================================
#pragma config FOSC     = INTIO67       //Fosc=1000 Sélection oscillateur interne, I/O sur RA6 and RA7
#pragma config PLLCFG   = ON		//4xPLL
#pragma config PRICLKEN = ON            //primary clock
#pragma config FCMEN    = OFF		//Fail-Safe Clock Monitor
#pragma config DEBUG    = ON

#pragma config LVP      = OFF           //Programmation in situ (ICSP) en basse tension
#pragma config PWRTEN   = OFF           //Timer de démarrage
#pragma config WDTEN    = OFF           //Chien de garde désactivé
#pragma config BOREN    = OFF           //Détection de fluctuation d'alimentation (Brown-out)
#pragma config IESO     = OFF           //apres PWRT et POR voir datasheet page42



// =======================================================================
//   Variables ID Callback
// =======================================================================
unsigned char IDCB_LED  = 0; // mémorisation de l'identificateur créé lors de l'enregistrement de la Callback Clignote_LED


// =======================================================================
//   Fonctions callback
// =======================================================================
void Clignote_LED(void);


// =======================================================================
//   Programme principal
// =======================================================================
void main(void){
    TIOSInitialiser();                                          // Initialisation de l'OS (appel des Callbacks)

    IDCB_LED = TIOSEnregistrerCB_TIMER(Clignote_LED, 3);        // Initialisation des Callbacks

    TIOSStart();                                                // Lancement OS (Boucle infinie)
}


void Clignote_LED(void)
{
    LED = !LED;
}
