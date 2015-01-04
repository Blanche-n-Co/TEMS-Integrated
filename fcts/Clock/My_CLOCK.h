#ifndef __My_CLOCK_H
#define __My_CLOCK_H

/******************************************************************
**                    FUNCTION PROTOTYPES 			 **
******************************************************************/

void ClockInit(void);                   // Initialisation de l'I2C (+valeurs)
void ClockRead(void);                   // Lecture de l'horloge
void ClockShow(void);                   // Affichage de l'horloge
void BCD2ASC(unsigned char, char*);     // Conversion BCD vers ASCII

#endif

