// =======================================================================
//   D�rives de compilations
// =======================================================================
#include <p18cxxx.h>
#include <p18lf46k22.h>
#include <delays.h>

#include "My_ADC.h"
#include "../../main.h"
#include "../LCD/xlcd.h"
#include "../LCD/writeOnLCD.h"
#include "../Temperature/ftoa.h"



// =======================================================================
//   Variables globales
// =======================================================================
float res = 0;                              // R�sultat de la conversion ADC
char  resConv[10];                          // Conversion valeur r�sultante ADC



// =======================================================================
//   Initialisation des registres pour capteur de luminosit� et ADC
// =======================================================================
void AdcInit(void){
    ANSELDbits.ANSD4	= 1;                // Configuration de la PIN
    TRISDbits.TRISD4	= 1;
    ADCON2bits.ADFM	= 1;                // Formatage du r�sultat
    ADCON1bits.PVCFG	= 0b00;             // Tension de r�f�rence positive
    ADCON1bits.NVCFG	= 0b00;             // Tension de r�f�rence n�gative
    ADCON0bits.CHS	= 0b11000;          // S�lectionne le canal
    ADCON2bits.ADCS	= 0b101;            // S�lectionne l'horloge
    ADCON0bits.ADON	= 1;                // Active le module
    ADCON0bits.GO	= 1;                // Lance une conversion
}



// =======================================================================
//   Conversion ADC (Luminosit�)
// =======================================================================
void AdcConv(void){
    ADCON0bits.GO = 1;
    while(ADCON0bits.GO == 1);

    res = ((float)((ADRESH*256) + ADRESL)/1024)*5;
    ftoa(res,&resConv[0],2,'f');
}



// =======================================================================
//   Affichage de la luminosit�
// =======================================================================
void AdcShow(void){
    writeOnLCDS(FLUSH,0x00, "Luminosity: ");    
    putsXLCD(resConv);
}