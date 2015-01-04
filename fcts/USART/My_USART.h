#ifndef __USART_H
#define __USART_H

/******************************************************************
** 	        		  FUNCTION PROTOTYPES	    	 **
******************************************************************/


// Configuration USART1 en mode Emission et Réception 9600 baud
void USART1_TX_RX_9600(void);

// Fonction qui retourne l'état (available /busy) de l'USART1
char Busy1_USART(void);

// Fonction qui envoie le caractère défini dans l'argument
void USART1_TX(char data);

// Envoi d'une variable string qui se termine par 0, l'argument est le pointeur du premier caractère de la string
void Usart1_TX_String(char *String);

// Configuration USART2 en mode Emission 9600 baud
void USART2_TX_RX_9600(void);

// Envoi un string se termine par 0
void Usart2_TX_String(char *String);

// Fonction qui envoie le caractère défini dans l'argument
void USART2_TX(char data);

#endif

