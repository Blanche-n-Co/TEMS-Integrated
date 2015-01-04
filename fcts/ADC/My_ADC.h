#ifndef __My_ADC_H
#define __My_ADC_H

/******************************************************************
**                    FUNCTION PROTOTYPES 			 **
******************************************************************/

extern char resConv[10];

void AdcInit(void);     // Initialisation des registres pour capteur de luminosité + ADC
void AdcConv(void);     // Lance une conversion et alimente une variable interne
void AdcShow(void);     // Affichage de la luminosité

#endif

