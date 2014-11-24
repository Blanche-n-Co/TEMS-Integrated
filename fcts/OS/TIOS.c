/*********************************************************************
 * Category:        Dérives de compilations
 ********************************************************************/
#include <p18cxxx.h>
#include <p18f46k22.h>

#include "TIOS.h"
#include "hardware.h"
#include "My_TIMERS.h"
#include "../../main.h"





/*********************************************************************
 * Category:        Variables callback
 ********************************************************************/
void (*MaCB[MAXCALLBACKCHRONO])(void);              //Tableau qui contient les pointeurs de fonctions
unsigned int TempsCB[MAXCALLBACKCHRONO];            //Tableau qui contient les temps définis pour chaque callback
volatile unsigned int TickCB[MAXCALLBACKCHRONO];    //Tableau qui contient le compteur associé à chaque callback

void(*MaCBButton)(char*);                           //Variables pour CallBack Button

volatile unsigned char Button;                      //Variablres pour Gestion Touches
char IDCB_ENABLE_INTERRUPT_BP = 0;                  // ID de la callback utilisée pour la gestion des rebonds





/*********************************************************************
 * Category:        Déclaration des fonctions
 ********************************************************************/
void MyInterruptLow(void);
void MyInterruptHight(void);

void ENABLE_INTERRUPT_BP(void);                     // Fonction utilisée pour la gestion des rebonds





/*********************************************************************
 * Category:        Initialisation TIOS
 ********************************************************************/
void TIOSInitialiser(void){
    unsigned char i;

    for (i=0 ; i<MAXCALLBACKCHRONO ; i++){
             MaCB[i] = 0;
             TempsCB[i] = 0;
    }

    //Initialisation pour variable Button
     MaCBButton = 0;
} 





/*********************************************************************
 * Category:        Fonctions de rappel
 ********************************************************************/
unsigned char TIOSEnregistrerCB_TIMER(void(*ptFonction)(void), unsigned int tps){
    unsigned int i = 0;
    while (MaCB[i]!=0 && i<MAXCALLBACKCHRONO) i++;

    //S'il reste de la place on enregistre et on retourne 0 (opération réussie)
    if (i<MAXCALLBACKCHRONO){
         MaCB[i] = ptFonction;
         TempsCB[i] = tps;
         TickCB[i] = 0; //Initialiser le compteur à 0;
         return i; // ID du call back
    }

    else return 255; //Il n'y a plus de place pour enregistrer un callback
}

// ****************  Enregistrer CallBack Button****************************
// Sauve l'adresse de la fonction à rappeler
// *************************************************************************
void TIOSEnregistrerCB_Button(void(*ptFonction)(char*)){
    //Sauver l'adresse de la fonction pour rappel
    MaCBButton = ptFonction;
}


// ****************  Retirer fonction de rappel ******************************
// Libère l'emplacement de la callback
// *************************************************************************
void TIOSRetirerCB_TIMER(unsigned char IDCB){
     if ((IDCB >=0) && IDCB<MAXCALLBACKCHRONO){
            MaCB[IDCB] = 0;
            TempsCB[IDCB] = 0;
     }
}

// ****************  Retirer fonction de rappel Button**********************
void TIOSRetirerCB_Button(void){
     MaCBButton = 0;
}





/*********************************************************************
 * Category:        Boucle principale de l'OS
 ********************************************************************/
void TIOSStart(){
    unsigned char idx;

    //Initialisation des I/O
    InitHardware();

    //Création, configuration et démarrage de Timer1 pour générer une interruption toutes les mS en priorité haute
    TIMER1_1ms(); //A partir d'ici, interruption toutes les ms par Timer1

    
    /*************************************
    *-> Configuration des interruptions
    **************************************/
    INTCONbits.GIE  = 1;		//active les interruptions générales
    INTCONbits.PEIE = 1;		//active les interruptions des peripheriques
    RCONbits.IPEN   = 1;		//active les priorite des interruptions : indispensable pour les priorites basses

    //TIMER1
    PIE1bits.TMR1IE = 1;		// Activation interruption Timer1 en overflow

    //INT0
    INTCONbits.INT0IE = 1;              // Interruption INT0 activée
    INTCON2bits.INTEDG0 = 0;            // Interruption sur flanc descendant activée


    //Boucle principale de l'OS d'où on ne sort jamais
     while(1){
        // Check les conditions pour rappeler les fonctions liées au temps
        for (idx = 0; idx < MAXCALLBACKCHRONO; idx++){
            if (MaCB[idx]) //Si on a l'adresse d'une fonction CB à cet index
            //Si on est arrivé au nombre de mS demandé, on appelle la fonction
            if (TickCB[idx] >= TempsCB[idx])
            {
                TickCB[idx] = 0;
                MaCB[idx]();  //Rappel de la fonction enregistrée!
            }
         }
         // Check les conditions pour rappeler la fonction Bouton
        if (!(Button ==NONE)){
            MaCBButton (&Button);
            Button = NONE;
        }
      }
}





/*********************************************************************
 * Category:        Prérequis fonctionnement interruptions
 ********************************************************************/
#pragma code lowVector=0x0018
void atInterruptLow(void){
  _asm GOTO MyInterruptLow _endasm}
#pragma code

#pragma code hightVector=0x0008
void atInterruptHight(void){
  _asm GOTO MyInterruptHight _endasm}
#pragma code





/*********************************************************************
 * Category:        Fonctions d'interruptions
 ********************************************************************/
#pragma interrupt MyInterruptLow
void MyInterruptLow(void)
{
    if(INTCONbits.TMR0IF){
        TickUpdate();                       //Reset Timer0 et flag pour Ethernet
    }
}


#pragma interrupt MyInterruptHight
void MyInterruptHight(void)
{

    /*************************************
    *-> Interruption Timer1
    **************************************/
    if (PIR1bits.TMR1IF){
	// reconfiguration du Timer0
	// Ajourner tous les ticks
	unsigned char i;
  	for (i = 0; i < MAXCALLBACKCHRONO; i++) TickCB[i]++;
        TMR1H = 0xF0;
        TMR1L = 0x60;
	PIR1bits.TMR1IF = 0;
    }

    /*************************************
    *-> Interruption INT0 (Bouttons)
    **************************************/
    if(INTCONbits.INT0IF){
        //GESTION DES REBONDS
        //ON DESACTIVE L'INTERRUPTION DE INT_BP PENDANT 500 ms
        //INTCONbits.INT0IE = 0;      // Interruption INT0 désactivée
        INT_BP_ANS = ANALOGIC;
        IDCB_ENABLE_INTERRUPT_BP = TIOSEnregistrerCB_TIMER(ENABLE_INTERRUPT_BP, 1000);

        if (INT_BP == 0){       // MEMORISATION DU BOUTON POUSSOIR
            if(!BP_UP)
                Button = UP;
            else if(!BP_DOWN)
                Button = DOWN;
            else if(!BP_RIGHT)
                Button = RIGHT;
            else if(!BP_LEFT)
                Button = LEFT;
            else if(!BP_MIDDLE)
                Button = CENTER;
        }
        INTCONbits.INT0IF = 0;
    }
}


/*********************************************************************
 * Category:        Fonctions de gestion des rebonds
 ********************************************************************/
void ENABLE_INTERRUPT_BP(void){
    INT_BP_ANS = NUMERIC;
    TIOSRetirerCB_TIMER(IDCB_ENABLE_INTERRUPT_BP);
}