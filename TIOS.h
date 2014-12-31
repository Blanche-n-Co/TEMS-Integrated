#ifndef __TIOS_H
#define __TIOS_H

//Définit le nombre maximal de callback de type Chrono
#define	MAXCALLBACKCHRONO		10


//**********************************************************
//********** FONCTIONS POUR LE MOTEUR OS *******************
//**********************************************************

//Initialisation de TIOS
void TIOSInitialiser(void);

//Enregistrer des fonctions callback liées au temps
//Retourne un ID associé à l'enregistrement
unsigned char TIOSEnregistrerCB_TIMER(void(*ptFonction)(void), unsigned int temps);
//Retourne un ID associé à l'enregistrement de la Callback Button
void TIOSEnregistrerCB_Button(void(*ptFonction)(char*));

//Retirer des fonctions callback liées au temps, prend l'ID du CallBack comme argument
void TIOSRetirerCB_TIMER(unsigned char IDCB);
//Retirer la fonctions callback Button
void TIOSRetirerCB_Button(void);

//Démarrage de la boucle principale
void TIOSStart(void);


#endif //__TIOS_H
