#ifndef __My_GSM_H
#define __My_GSM_H

/******************************************************************
**                    FUNCTION PROTOTYPES 			 **
******************************************************************/

//Configurer les registres n�cessaires � l'USART2
void GsmConfigurationRegistre(void);

//Ex�cuter les commandes AT n�cessaires afin d'envoyer un message
void GsmTextExecution(void);

//Ex�cuter les commandes AT n�cessaires afin de r�aliser un appel
void GsmCallExecution(void);

#endif