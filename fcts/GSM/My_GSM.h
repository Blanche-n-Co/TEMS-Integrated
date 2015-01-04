#ifndef __My_GSM_H
#define __My_GSM_H

//###############################################//
//           Prototypes de fonctions             //
//###############################################//

//Cette fonction a pour but de configurer les registres nécessaires à l'USART2
void GsmConfigurationRegistre(void);

//Cette fonction a pour but d'exécuter les commandes AT nécessaires afin de réaliser un appel
void GsmCallExecution(void);

#endif