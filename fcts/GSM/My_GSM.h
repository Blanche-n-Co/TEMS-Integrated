#ifndef __My_GSM_H
#define __My_GSM_H

/******************************************************************
**                    FUNCTION PROTOTYPES 			 **
******************************************************************/

//Configurer les registres nécessaires à l'USART2
void GsmConfigurationRegistre(void);

//Exécuter les commandes AT nécessaires afin d'envoyer un message
void GsmTextExecution(void);

//Exécuter les commandes AT nécessaires afin de réaliser un appel
void GsmCallExecution(void);

#endif