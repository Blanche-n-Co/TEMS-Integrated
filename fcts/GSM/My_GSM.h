#ifndef __My_GSM_H
#define __My_GSM_H

/******************************************************************
**                    FUNCTION PROTOTYPES 			 **
******************************************************************/

void GsmFunctionInit(void);     //Configurer les registres n�cessaires au GSM + USART2
void GsmTextExecution(void);    //Ex�cuter les commandes AT n�cessaires afin d'envoyer un message
void GsmCallExecution(void);    //Ex�cuter les commandes AT n�cessaires afin de r�aliser un appel

#endif