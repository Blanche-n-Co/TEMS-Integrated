#include "delaysXLCD.h"
#include "xlcd.h"
#include <delays.h>


/*********************************************************************
 * Category:        Prérequis fonctionnement LCD
 ********************************************************************/
void DelayFor18TCY(void){
    Nop(); Nop(); Nop(); Nop(); Nop(); Nop();
    Nop(); Nop(); Nop(); Nop(); Nop(); Nop();
    Nop(); Nop(); Nop(); Nop(); Nop(); Nop();
}

void DelayPORXLCD(void){
    Delay10KTCYx(6);}           // 15ms

void DelayXLCD(void){
    Delay10KTCYx(2);}           //  5ms
