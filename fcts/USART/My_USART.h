#ifndef __USART_H
#define __USART_H

/******************************************************************
** 	        		  FUNCTION PROTOTYPES	    	 **
******************************************************************/


// Configuration USART1 en mode Emission et R�ception 9600 baud ,les interruptions ne sont pas configur�es
void USART1_TX_RX_9600(void);

// Fonction qui retourne l'�tat (available /busy) de l'USART1
char Busy1_USART(void);

// Fonction qui envoie le caract�re d�fini dans l'argument
void USART1_TX(char data);

// Envoi d'une variable string qui se termine par 0, l'argument est le pointeur du premier caract�re de la string
void Usart1_TX_String(char *String);

#endif