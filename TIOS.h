#ifndef __TIOS_H
#define __TIOS_H

//D�finit le nombre maximal de callback de type Chrono
#define	MAXCALLBACKCHRONO		10      // Nombre maximal de CallBack
#define MAXBUFRS232			 5      // Taille maximum du buffer USART

//**********************************************************
//********** FONCTIONS POUR LE MOTEUR OS *******************
//**********************************************************

//Initialisation de TIOS
void TIOSInitialiser(void);

//Enregistrer des fonctions callback li�es au temps
//Retourne un ID associ� � l'enregistrement
unsigned char TIOSEnregistrerCB_TIMER(void(*ptFonction)(void), unsigned int temps);
//Retirer des fonctions callback li�es au temps, prend l'ID du CallBack comme argument
void TIOSRetirerCB_TIMER(unsigned char IDCB);

//Retourne un ID associ� � l'enregistrement de la Callback Button
void TIOSEnregistrerCB_Button(void(*ptFonction)(char*));
//Retirer la fonctions callback Button
void TIOSRetirerCB_Button(void);

//Enregistrer une fonction callback li� � la r�ception d'une trame RS232
void TIOSEnregistrerCB_USART1_RX(void(*ptFonction)(char*));
//Retirer la fonctions callback USART1_RX
void TIOSRetirerCB_USART1_RX(void);

//D�marrage de la boucle principale
void TIOSStart(void);


#endif //__TIOS_H
