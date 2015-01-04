#include <p18cxxx.h>
#include <p18lf46k22.h>

#include "My_USART.h"

// USART1
void USART1_TX_RX_9600(void){
    //Conf USART
    ANSELCbits.ANSC6    = 0;        // Broche C6 (TX) en Numérique
    TRISCbits.TRISC6	= 1;        //                en entrée
    ANSELCbits.ANSC7    = 0;        // Broche C7 (RX) en Numérique
    TRISCbits.TRISC7	= 1;        //                en entrée

    //Conf Baud Rate
    BAUDCON1bits.BRG16	= 1;
    TXSTA1bits.BRGH     = 1;
    SPBRGH1:SPBRG1      = 416;
    TXSTA1bits.SYNC     = 0;        // Mode asynchrone
    RCSTA1bits.SPEN     = 1;        // Serial Peripherical Enable

    //Config émission
    TXSTA1bits.TXEN	= 1;        // Emission activée
    TXSTA1bits.TX9	= 0;
    PIE1bits.TX1IE	= 0;

    //Config réception
    RCSTA1bits.CREN	= 1;        // Réception activée
    RCSTA1bits.RX9	= 0;
    PIE1bits.RC1IE	= 1;
    PIR1bits.RC1IF	= 0;
    IPR1bits.RC1IP	= 1;
}

char Busy1_USART(void){
  if(!TXSTA1bits.TRMT)              // Is the transmit shift register empty
    return 1;                       // No, return FALSE
    return 0;                       // Return TRUE
}

void USART1_TX(char data){
    while(Busy1_USART());
    TXREG1 = data;
}

// Envoi un string se termine par 0
void Usart1_TX_String(char *String){
    char Continue = 1;

    while (Continue){
        if (*String == 0)
            Continue = 0;
        else
            USART1_TX(*String++);
    }
}

// USART2
void USART2_TX_RX_9600(void){
    //Conf USART
    ANSELDbits.ANSD6    = 0;        // Broche D6 (TX) en Numérique
    TRISDbits.TRISD6	= 1;        //                en entrée
    ANSELDbits.ANSD7    = 0;        // Broche D7 (RX) en Numérique
    TRISDbits.TRISD7	= 1;        //                en entrée

    //Conf Baud Rate
    BAUDCON2bits.BRG16	= 1;
    TXSTA2bits.BRGH     = 1;
    SPBRGH2:SPBRG2      = 416;
    TXSTA2bits.SYNC     = 0;        // Mode asynchrone
    RCSTA2bits.SPEN     = 1;        // Serial Peripherical Enable

    //Config émission
    TXSTA2bits.TXEN	= 1;        // Emission activée
    TXSTA2bits.TX9	= 0;
    PIE3bits.TX2IE	= 0;

    //Config réception
    RCSTA2bits.CREN	= 0;        // Réception activée
}

// Envoi un string se termine par 0
void Usart2_TX_String(char *String){
    char Continue = 1;

    while (Continue){
        if (*String == 0)
            Continue = 0;
        else
            USART2_TX(*String++);
    }
}

// Fonction qui envoie le caractère défini dans l'argument
void USART2_TX(char data){
    while(TXSTA2bits.TRMT==0);
    TXREG2 = data;
}
