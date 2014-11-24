#ifndef __TIOS_H
#define __TIOS_H

//D�finit le nombre maximal de callback de type Chrono
#define	MAXCALLBACKCHRONO		20      // Nombre maximum de callbacks (� mettre � jour en fct du prg)


//**********************************************************
//********** FONCTIONS POUR LE MOTEUR OS *******************
//**********************************************************

//Initialisation de TIOS
void TIOSInitialiser(void);

//Enregistrer des fonctions callback li�es au temps
//Retourne un ID associ� � l'enregistrement de la callback Timer
unsigned char TIOSEnregistrerCB_TIMER(void(*ptFonction)(void), unsigned int temps);
//Retourne un ID associ� � l'enregistrement de la Callback Button
void TIOSEnregistrerCB_Button(void(*ptFonction)(char*));
//Retirer des fonctions callback li�es au temps, prend l'ID du CallBack Timer comme argument
void TIOSRetirerCB_TIMER(unsigned char IDCB);
//Retirer la fonctions callback Button
void TIOSRetirerCB_Button(void);


//D�marrage de la boucle principale
void TIOSStart(void);


#endif //__TIOS_H
