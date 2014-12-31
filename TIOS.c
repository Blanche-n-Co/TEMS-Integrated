// =======================================================================
//   Dérives de compilations
// =======================================================================
#include <p18cxxx.h>
#include <p18f46k22.h>
#include <delays.h>
#include <string.h>

#include "main.h"
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




// =======================================================================
//   Déclaration des varables pour Callback
// =======================================================================
//CallBack Chrono
void (*MaCB[MAXCALLBACKCHRONO])(void);
unsigned int TempsCB[MAXCALLBACKCHRONO];
volatile unsigned int TickCB[MAXCALLBACKCHRONO];

//CallBack Button
void(*MaCBButton)(char*);           // Pointeur de fonction pour la fonction "void Manage_Button(volatile unsigned char *ptr_Button)" (main.c)
volatile unsigned char Button;      // Variable qui indique le nom de la touche appuyée (UP, DOWN, LEFT, RIGHT, ENTER)
char IDCB_ENABLE_INTERRUPT_BP = 0;  // ID de la callback utilisée pour la gestion des rebonds
void ENABLE_INTERRUPT_BP(void);     // Fonction interne pour la gestion des rebonds



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
    
    //Initialisation pour variable Button
     MaCBButton = 0;
} 


// ****************  EnregistrerFonctionDeRappel ***************************
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



// ****************  Enregistrer CallBack Button****************************
// Sauve l'adresse de la fonction à rappeler
// *************************************************************************
void TIOSEnregistrerCB_Button(void(*ptFonction)(char*))
{
    //Sauver l'adresse de la fonction pour rappel
    MaCBButton = ptFonction;
}

// ****************  Retirer fonction de rappel Button**********************
void TIOSRetirerCB_Button(void)
{
    MaCBButton = 0;
}



// ****************  Retirer fonction de rappel ****************************
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

    //InitHardware();

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

    //INT0 (Buttons)
    INTCONbits.INT0IE = 1;              // Interruption INT0 activée
    INTCON2bits.INTEDG0 = 0;            // Interruption sur flanc descendant activée

    
    /*************************************
    *-> Configuration de l'affichage LCD
    **************************************/
//    while(BusyXLCD());                  // Configuration du splash screen
//    putrsXLCD("     T E M S    ");
//    while(BusyXLCD());
//    SetDDRamAddr(0x40);


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

        if (!(Button ==NONE))                               //Check les conditions pour rappeler la fonction Bouton
        {
            MaCBButton (&Button);
            Button = NONE;
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
    //Flag interruption sur TIMER1
    if (PIR1bits.TMR1IF){
        unsigned char i;

        for (i = 0; i < MAXCALLBACKCHRONO; i++) // Ajourne tous les ticks
            TickCB[i]++;

        TMR1H = 0xF0;
        TMR1L = 0x60;
        
	PIR1bits.TMR1IF = 0;
    }

    //Flag interruption sur boutons
    if(INTCONbits.INT0IF){
        INT_BP_ANS = ANALOGIC;                                                     // GESTION DES REBONDS
        IDCB_ENABLE_INTERRUPT_BP = TIOSEnregistrerCB_TIMER(ENABLE_INTERRUPT_BP, 1000);  // INT_BP désactivées pour 500 ms

        if (INT_BP == 0)
        {
            if(!BP_UP)              // MEMORISATION DU BOUTON POUSSOIR
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

void ENABLE_INTERRUPT_BP(void)
{
    //INTCONbits.INT0IE = 1;      // Interruption INT0 activée
    INT_BP_ANS = NUMERIC;
    TIOSRetirerCB_TIMER(IDCB_ENABLE_INTERRUPT_BP);
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



