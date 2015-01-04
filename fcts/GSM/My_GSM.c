#include <delays.h>
#include "../USART/My_USART.h"	//N�cessaire pour USART2

void GsmCallExecution(void)
{	
    //#############################################################################################//
    //Cette fonction a pour but d'exécuter les commandes AT nécessaires afin de réaliser un appel  //
    //#############################################################################################//
	
    //VARIABLES LOCALES
    char BaudRate[]="AT";
    char EchoOn[]="ATE1";
    char textMode[]="AT+CMGF=1";
    char full[]="AT+CFUN=1";
    char modeGSM[]="AT+CSCS=\"GSM\"";
    char tel[]="ATD0483061579";
	 
    //BaudRate
    USART2_TX(BaudRate[0]);
    USART2_TX(BaudRate[1]);
    USART2_TX(0x0D);			//Envoi de <CR> pour l'exécution de la commande AT
    Delay10KTCYx(250); 		//500ms	
	
    //EchoOn
    USART2_TX(EchoOn[0]);
    USART2_TX(EchoOn[1]);
    USART2_TX(EchoOn[2]);
    USART2_TX(EchoOn[3]);
    USART2_TX(0x0D);			//Envoi de <CR> pour l'exécution de la commande AT
    Delay10KTCYx(250); 		//500ms

    //TextMode
    USART2_TX(textMode[0]);
    USART2_TX(textMode[1]);
    USART2_TX(textMode[2]);
    USART2_TX(textMode[3]);
    USART2_TX(textMode[4]);
    USART2_TX(textMode[5]);
    USART2_TX(textMode[6]);
    USART2_TX(textMode[7]);
    USART2_TX(textMode[8]);
    USART2_TX(0x0D);			//Envoi de <CR> pour l'exécution de la commande AT
    Delay10KTCYx(250); 		//500ms

    //Full Functionality
    USART2_TX(full[0]);
    USART2_TX(full[1]);
    USART2_TX(full[2]);
    USART2_TX(full[3]);
    USART2_TX(full[4]);
    USART2_TX(full[5]);
    USART2_TX(full[6]);
    USART2_TX(full[7]);
    USART2_TX(full[8]);
    USART2_TX(0x0D);			//Envoi de <CR> pour l'exécution de la commande AT
    Delay10KTCYx(250); 		//500ms

    //Mode GSM
    USART2_TX(modeGSM[0]);
    USART2_TX(modeGSM[1]);
    USART2_TX(modeGSM[2]);
    USART2_TX(modeGSM[3]);
    USART2_TX(modeGSM[4]);
    USART2_TX(modeGSM[5]);
    USART2_TX(modeGSM[6]);
    USART2_TX(modeGSM[7]);
    USART2_TX(modeGSM[8]);
    USART2_TX(modeGSM[9]);
    USART2_TX(modeGSM[10]);
    USART2_TX(modeGSM[11]);
    USART2_TX(modeGSM[12]);
    USART2_TX(modeGSM[13]);
    USART2_TX(modeGSM[14]);
    USART2_TX(0x0D);			//Envoi de <CR> pour l'exécution de la commande AT
    Delay10KTCYx(250); 		//500ms

    //Appel
    USART2_TX(tel[0]);
    USART2_TX(tel[1]);
    USART2_TX(tel[2]);
    USART2_TX(tel[3]);
    USART2_TX(tel[4]);
    USART2_TX(tel[5]);
    USART2_TX(tel[6]);
    USART2_TX(tel[7]);
    USART2_TX(tel[8]);
    USART2_TX(tel[9]);
    USART2_TX(tel[10]);
    USART2_TX(tel[11]);
    USART2_TX(tel[12]);
    USART2_TX(0x0D);			//Envoi de <CR> pour l'exécution de la commande AT
    Delay10KTCYx(250); 		//500ms
}