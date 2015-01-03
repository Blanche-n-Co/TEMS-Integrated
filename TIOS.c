// =======================================================================
//   D�rives de compilations
// =======================================================================
#include <p18cxxx.h>
#include <p18f46k22.h>
#include <stdlib.h>
#include <delays.h>
#include <string.h>

#include "main.h"
#include "TIOS.h"
#include "fcts/LCD/xlcd.h"
#include "fcts/OS/hardware.h"
#include "fcts/OS/My_TIMERS.h"
#include "fcts/USART/My_USART.h"
#include "fcts/Temperature/ftoa.h"

#include "pconfig.h"
#include "TCPIPConfig.h"
#include "HardwareProfile.h"
#include "TCPIP Stack/StackTsk.h"
#include "TCPIP Stack/TCPIP.h"



// =======================================================================
//   D�claration des fonctions d'interruption
// =======================================================================
void MyInterruptLow(void);          //Fonction d'interruptions basses
void MyInterruptHight(void);        //Fonction d'interruptions hautes



// =======================================================================
//   Pr�requis fonctionnement interruptions (Requis MCC18)
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
//   D�claration des variables globales
// =======================================================================
volatile unsigned char BP_read_state        = 0;
volatile unsigned char CPT_TIMER1           = 0;



// =======================================================================
//   D�claration des varables pour Callback
// =======================================================================
//CallBack Chrono
void (*MaCB[MAXCALLBACKCHRONO])(void);
unsigned int TempsCB[MAXCALLBACKCHRONO];
volatile unsigned int TickCB[MAXCALLBACKCHRONO];

//CallBack Button
void(*MaCBButton)(char*);           // Pointeur de fonction pour la fonction "void Manage_Button(volatile unsigned char *ptr_Button)" (main.c)
volatile unsigned char Button;      // Variable qui indique le nom de la touche appuy�e (UP, DOWN, LEFT, RIGHT, ENTER)
char IDCB_ENABLE_INTERRUPT_BP = 0;  // ID de la callback utilis�e pour la gestion des rebonds
void ENABLE_INTERRUPT_BP(void);     // Fonction interne pour la gestion des rebonds

//Variables pour CallBack USART (r�ception d'un string)
void(*MaCBUSART1)(char*);               //Pointeur de fonction pour la fonction "void USART1_RX(char *Trame_RS232)" d�finie dans le main.c
volatile unsigned char USARTReception;  //Variable qui signale la r�cepption d'une trame compl�te
volatile char bufRS232[MAXBUFRS232];    //Buffer qui contient la trame re�ue (tableau de caract�res)
volatile unsigned char idxbufRS232 = 0; //Index du buffer qui contient la trame re�ue



// ****************  TIOSInitialiser ******************************
// Initialise l'OS: initialise les variables et d�marre le Timer
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

    //Initialisation pour variables USART
    MaCBUSART1 = 0;
    USARTReception = 0;
} 


// ****************  EnregistrerFonctionDeRappel ***************************
// Sauve l'adresse de la fonction � rappeler. Lorsque le nombre d'interruptions
// aura atteint temps millisecondes, le syst�me rappellera la fonction
// *************************************************************************
unsigned char TIOSEnregistrerCB_TIMER(void(*ptFonction)(void), unsigned int tps)
{
    unsigned int i = 0;
    while (MaCB[i]!=0 && i<MAXCALLBACKCHRONO) i++;
     //S'il reste de la place on enregistre et on retourne 0 (op�ration r�ussie)
    if (i<MAXCALLBACKCHRONO)
    {
        MaCB[i]    = ptFonction;
        TempsCB[i] = tps;
        TickCB[i]  = 0;             //Initialiser le compteur � 0;
        return i;                   // ID du call back
    }
    else return 255;                //Il n'y a plus de place pour enregistrer un callback
}

// ****************  Retirer fonction de rappel ***************************
void TIOSRetirerCB_TIMER(unsigned char IDCB){
    if ((IDCB >=0) && IDCB<MAXCALLBACKCHRONO)  //Lib�re l'emplacement de la Callabck
    {
        MaCB[IDCB] = 0;
        TempsCB[IDCB] = 0;
    }
}



// ****************  Enregistrer CallBack Button****************************
// Sauve l'adresse de la fonction � rappeler
// *************************************************************************
void TIOSEnregistrerCB_Button(void(*ptFonction)(char*)){
    //Sauver l'adresse de la fonction pour rappel
    MaCBButton = ptFonction;
}

// ****************  Retirer fonction de rappel Button**********************
void TIOSRetirerCB_Button(void){
    MaCBButton = 0;
}



// ****************  Enregistrer CallBack USART1 ******************************
// Sauve l'adresse de la fonction � rappeler
// *************************************************************************
void TIOSEnregistrerCB_USART1_RX(void(*ptFonction)(char*)){
    //Sauver l'adresse de la fonction pour rappel
    MaCBUSART1 = ptFonction;
}

// ****************  Retirer fonction de rappel USART1 **********************
void TIOSRetirerCB_USART1_RX(void){
    MaCBUSART1 = 0;
}



// ****************  Boucle principale de l'OS ******************************
// Boucle infinie qui attend des �v�nement li�s aux interruptions pour 
// appeler les fonctions enregistr�es
// *************************************************************************
void TIOSStart()
{
    unsigned char idx;
//    unsigned char cls;

    /*************************************
    *-> Configuration des interruptions
    **************************************/
    //USART1
    IPR1bits.RC1IP      = 1;

    //TIMER1
    TIMER1_1ms();                       // Interruptions toutes les ms par Timer1
    PIE1bits.TMR1IE     = 1;		// Activation interruption Timer1 en overflow
    IPR1bits.TMR1IP     = 1;		// Activation interruption en Haute Priorit�

    //INT0 (Buttons)
    INTCONbits.INT0IE = 1;              // Interruption INT0 activ�e
    INTCON2bits.INTEDG0 = 0;            // Interruption sur flanc descendant activ�e


    
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
        StackTask();
        StackApplications();

        for (idx = 0; idx < MAXCALLBACKCHRONO; idx++){      //Check les conditions pour rappeler les fonctions li�es au temps
            if (MaCB[idx])                                  //Si on a l'adresse d'une fonction CB � cet index
                if (TickCB[idx] >= TempsCB[idx])            //Si on est arriv� au nombre de mS demand�, on appelle la fonction
                {
                    TickCB[idx] = 0;
                    MaCB[idx]();                            //Rappel de la fonction enregistr�e!
                }
         }

        if (!(Button ==NONE))                               //Check les conditions pour rappeler la fonction Bouton
        {
            MaCBButton (&Button);
            Button = NONE;
        }

        if (USARTReception)
        {
            USARTReception = 0;

            if (MaCBUSART1)
                MaCBUSART1(bufRS232);                       //Rappel de la fonction enregistr�e!
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
        IDCB_ENABLE_INTERRUPT_BP = TIOSEnregistrerCB_TIMER(ENABLE_INTERRUPT_BP, 1000);  // INT_BP d�sactiv�es pour 500 ms

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

    //Flag interruption sur USART1 RX
    if(PIR1bits.RC1IF){
        bufRS232[idxbufRS232] = RCREG1;     //Lire le registre de r�ception, le charger dans le buffer
        
        if (bufRS232[idxbufRS232] == '*'){
            bufRS232[idxbufRS232] = 0;
            USARTReception =1;
            idxbufRS232 = 0;
            USART1_TX('\r');                //Transmettre retour charriot
            USART1_TX('\n');                //('\r' + '\n' pour Win32 !!!)
            USART1_TX('>');                 //Transmettre un prompt
        }
        else{
            USART1_TX(bufRS232[idxbufRS232]);   //Transmettre le caract�re en retour
            if (++idxbufRS232 >= MAXBUFRS232)   //Si on arrive au maximum du buffer, remettre � z�ro
                idxbufRS232 = 0;
        }
    }
}

void ENABLE_INTERRUPT_BP(void){
    //INTCONbits.INT0IE = 1;      // Interruption INT0 activ�e
    INT_BP_ANS = NUMERIC;
    TIOSRetirerCB_TIMER(IDCB_ENABLE_INTERRUPT_BP);
}
