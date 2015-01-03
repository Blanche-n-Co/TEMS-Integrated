#include <p18cxxx.h>
#include <p18lf46k22.h>

// USART1
void USART1_TX_RX_9600(void){
    //SPBRG1 = 25;			// voir DS page 278

    //Conf USART
    ANSELCbits.ANSC6    = 0;        // Broche C6 (TX) en Num�rique
    TRISCbits.TRISC6	= 1;        //                en entr�e
    ANSELCbits.ANSC7    = 0;        // Broche C7 (RX) en Num�rique
    TRISCbits.TRISC7	= 1;        //                en entr�e

    //Conf Baud Rate
    BAUDCON1bits.BRG16	= 1;
    TXSTA1bits.BRGH     = 1;
    SPBRGH1:SPBRG1      = 416;
    TXSTA1bits.SYNC     = 0;        // Mode asynchrone
    RCSTA1bits.SPEN     = 1;        // Serial Peripherical Enable

    //Config �mission
    TXSTA1bits.TXEN	= 1;        // Emission activ�e
    TXSTA1bits.TX9	= 0;
    PIE1bits.TX1IE	= 0;

    //Config r�ception
    RCSTA1bits.CREN	= 1;        // R�ception activ�e
    RCSTA1bits.RX9	= 0;
    PIE1bits.RC1IE	= 1;
    PIR1bits.RC1IF	= 0;
    IPR1bits.RC1IP	= 1;
}

char Busy1_USART(void){
  if(!TXSTA1bits.TRMT)  // Is the transmit shift register empty
    return 1;          // No, return FALSE
    return 0;          // Return TRUE
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