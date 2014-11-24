#include "My_TIMERS.h"
#include <p18cxxx.h>
#include <p18lf46k22.h>

void TIMER1_1ms(void)
{
	//Overflow toutes les ms
	//Utilisation des 16 bits du TIMER1
	T1CONbits.T1RD16 = 1;		//(voir DS page 172)
	//Une incrémentation du TIMER1 dure 4 x période d'horlode (instruction machine)
	T1CONbits.TMR1CS = 0b00;		//(voir DS page 172)
	/* Une période d'horlode dure 62.5nS --> une opération machine dure 4 x 62.5nS = 250nS
	Il faut 1000000 nS --> 1000000/250nS = 4000 incrémentation du TIMER1
	4000 incrémentations < 65536 (nbr total d'incrémentation sur 16 bits) --> pas besoin de diviser la clock */
	T1CONbits.T1CKPS = 0b00; 	//(voir DS page 172)
	//Valeur initiale du TIMER1 = 65536 - 4000 = 61536 (0XF060)
	TMR1H = 0xF0;
	TMR1L = 0x60;
	//Activation du TIMER1
	T1CONbits.TMR1ON = 1;		//(voir DS page 172)
}


void TIMER1_10ms(void)
{
	//Overflow toutes les 10 ms
	//Utilisation des 16 bits du TIMER1
	T1CONbits.T1RD16 = 1;		//(voir DS page 172)
	//Une incrémentation du TIMER1 dure 4 x période d'horlode (instruction machine)
	T1CONbits.TMR1CS = 0b00;		//(voir DS page 172)
	/* Une période d'horlode dure 62.5nS --> une opération machine dure 4 x 62.5nS = 250nS
	Il faut 10000000 nS --> 10000000/250nS = 40000 incrémentation du TIMER1
	40000 incrémentations < 65536 (nbr total d'incrémentation sur 16 bits) --> pas besoin de diviser la clock */
	T1CONbits.T1CKPS = 0b00; 	//(voir DS page 172)
	//Valeur initiale du TIMER1 = 65536 - 40000 =  25536 (0X63C0)
	TMR1H = 0x63;
	TMR1L = 0xC0;
	//Activation du TIMER1
	T1CONbits.TMR1ON = 1;		//(voir DS page 172)
}

void TIMER1_100ms(void)
{
	//Overflow toutes les ms
	//Utilisation des 16 bits du TIMER1
	T1CONbits.T1RD16 = 1;		//(voir DS page 172)
	//Une incrémentation du TIMER1 dure 4 x période d'horlode (instruction machine)
	T1CONbits.TMR1CS = 0b00;		//(voir DS page 172)
	/* Une période d'horlode dure 62.5nS --> une opération machine dure 4 x 62.5nS = 250nS
	Il faut 100000000 nS --> 100000000/250nS = 400000 incrémentation du TIMER1
	400000 incrémentations > 65536 (nbr total d'incrémentation sur 16 bits) --> il faut diviser la clock 
	Si diviseur par 8 --> incrémentation du TIMER1 dure 4 x 62.5 x 8 = 2000 ns = 2µs
	Il faut 100000 µs --> 100000/2µs = 50000 incrémentations du TIMER1
	50000 incrémentations < 65536 --> OK*/
	T1CONbits.T1CKPS = 0b11; 	// diviseur par 8 (voir DS page 172)
	//Valeur initiale du TIMER1 = 65536 - 50000 =  15536 (0X3CB0)
	TMR1H = 0x3C;
	TMR1L = 0xB0;
	//Activation du TIMER1
	T1CONbits.TMR1ON = 1;		//(voir DS page 172)
}