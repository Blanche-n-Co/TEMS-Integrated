#include <p18cxxx.h>
#include <p18f46k22.h>
#include <delays.h>

#include "1wire.h"
#include "../OS/hardware.h"


//FOR DEBUG
//#include "My_USART.h"
/******************************************************************
** 	ENUMERATIONS - DEFINITIONS (inside the file) 		 **
******************************************************************/

#define DQ_LOW			TRISBbits.TRISB5 = OUTPUT_PORT; PORTBbits.RB5 = 0
#define DQ_RELEASE		TRISBbits.TRISB5 = INPUT_PORT
#define DQ_READ			PORTBbits.RB5

/******************************************************************
** 	        GLOBAL VARIABLES (inside the file)		 **
******************************************************************/

/******************************************************************
** 	                 MAIN FUNCTIONS 	  		 **
******************************************************************/


int OWInit (void) {
    /****					LOCAL VARIABLES					  ****/
    int state;

    /****     				    FUNCTION           			  ****/
    DQ_LOW;

    Delay10TCYx(200);	//500탎

    DQ_RELEASE;

    Delay10TCYx(40);	//100탎

    state = DQ_READ;

    Delay10TCYx(160);	//400탎

    return state;
}

void OWWriteBit (int My_bit) {
    /****					LOCAL VARIABLES					  ****/

    /****     				    FUNCTION           			  ****/
    DQ_LOW;

    if (My_bit)
            Delay10TCYx(4);			//10탎
    else
            Delay10TCYx(40);		//100탎

    DQ_RELEASE;

    if (My_bit)
            Delay10TCYx(24);		//60탎

    Delay10TCYx(4);				//10탎 (recovery) (time obliged between 2 writes)
}

int OWReadBit (void) {
    /****					LOCAL VARIABLES					  ****/
    int My_bit;

    /****     				    FUNCTION           			  ****/
    DQ_LOW;

    Nop();Nop();Nop();Nop();	//1탎

    DQ_RELEASE;

    Delay10TCYx(4);				//10탎

    My_bit = (int)DQ_READ;

    Delay10TCYx(24);			//60탎

    Delay10TCYx(4);				//10탎 (recovery) (time obliged between 2 reads)

    return My_bit;
}

void OWWriteByte (int byte) {
    /****					LOCAL VARIABLES					  ****/
    int i;

    /****     				    FUNCTION           			  ****/
    // Loop to write each bit in the byte, LS-bit first
    for (i = 0; i < 8; i++)	{
            OWWriteBit(byte & 0x01);

            // Shifts the data byte for the next bit
            byte >>= 1;
    }
}	

int OWReadByte (void) {
    /****					LOCAL VARIABLES					  ****/
    int i, byte = 0;

    /****     				    FUNCTION           			  ****/
    for (i = 0; i < 8; i++)
    {
            // Shifts the result to get it ready for the next bit
            byte >>= 1;

            // If result is one, then set MS bit
            if (OWReadBit())
                    byte |= 0x80;
    }
    return byte;
}

void Convert_Temperature (void) {
    /****		LOCAL VARIABLES         		  ****/

    /****     	 FUNCTION           			  ****/
    OWInit();			// Master resets bus
    OWWriteByte(0xCC);		// Skips the ROM
    OWWriteByte(0x44);		// Converts temperature

    // Delay of 800탎
    //Delay10KTCYx(200);
    //Delay10KTCYx(120);
}

float Read_Temperature (void) {
    /****					LOCAL VARIABLES					  ****/
    unsigned char scratchpad[10];
    int i, msb, lsb, result;
    float temperature;
    //FOR DEBUG
    unsigned char _result;

    /****     				    FUNCTION           			  ****/
    OWInit();				// Master resets bus
    OWWriteByte(0xCC);		// Skips the ROM
    OWWriteByte(0xBE);		// Reads scratch pad

    for (i = 0; i < 9; i++)				// Reads 9 bytes from scratchpad
            scratchpad[i] = OWReadByte();

    msb = scratchpad[1] & 0x7;			// Loads 3 bits of the MSB, masking any sign bits
    msb = msb << 8;						// Shifts the MSB left 8 bits
    lsb = scratchpad[0];
    result = (msb | lsb);				// Loads all 8 bits of the LSB

    if (msb & 0x80)						// Sign bit set, temp is negative
            result *= -1;
    //FOR DEBUG
    /*
    _result = ((char)(result & 0xF0))/256;
    USART1_TX(_result);
    _result = (char)(result & 0x0F);
    USART1_TX(_result);*/
    temperature = (float)result * 0.0625;

    return temperature;
}