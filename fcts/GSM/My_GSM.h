#ifndef __My_GSM_H
#define __My_GSM_H

/******************************************************************
**                    FUNCTION PROTOTYPES 			 **
******************************************************************/

void GsmFunctionInit(void);     //Configurer les registres nécessaires au GSM + USART2
void GsmTextExecution(void);    //Exécuter les commandes AT nécessaires afin d'envoyer un message
void GsmCallExecution(void);    //Exécuter les commandes AT nécessaires afin de réaliser un appel

#endif