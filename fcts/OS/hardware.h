#ifndef __HARDWARE_H
#define __HARDWARE_H


enum {OFF, ON};
enum {NUMERIC, ANALOGIC};
enum {OUTPUT_PORT, INPUT_PORT};


/*********************************************************************
 * Category:        Définition des ports utilisés
 ********************************************************************/
#define LED             PORTCbits.RC2
#define LED_TRI         TRISCbits.TRISC2
#define LED_ANS         ANSELCbits.ANSC2

#define BP_UP		PORTCbits.RC0
#define BP_UP_TRI  	TRISCbits.TRISC0
// RC0 est toujours numérique

#define BP_MIDDLE       PORTEbits.RE2
#define BP_MIDDLE_TRI   TRISEbits.TRISE2
#define BP_MIDDLE_ANS   ANSELEbits.ANSE2

#define BP_DOWN		PORTEbits.RE1
#define BP_DOWN_TRI 	TRISEbits.TRISE1
#define BP_DOWN_ANS     ANSELEbits.ANSE1

#define BP_LEFT		PORTAbits.RA6
#define BP_LEFT_TRI     TRISAbits.TRISA6
// RA6 est toujours numérique

#define BP_RIGHT        PORTAbits.RA7
#define BP_RIGHT_TRI    TRISAbits.TRISA7
// RA7 est toujours numérique

#define RELAIS          PORTBbits.RB4
#define RELAIS_TRI      TRISBbits.TRISB4
#define RELAIS_ANS      ANSELBbits.ANSB4

#define INT_BP          PORTBbits.RB0
#define INT_BP_TRI      TRISBbits.TRISB0
#define INT_BP_ANS      ANSELBbits.ANSB0

#define CANALPHOTODIODE	ADCON0bits.CHS=0b11000
#define CANALBORNIER    ADCON0bits.CHS=0b01000

#define DS18B20_ANS     ANSELBbits.ANSB5


/*********************************************************************
 * Category:        Prototype de fonction
 ********************************************************************/
void InitHardware(void);

#endif
