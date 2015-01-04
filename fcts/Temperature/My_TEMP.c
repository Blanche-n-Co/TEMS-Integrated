// =======================================================================
//   D�rives de compilations
// =======================================================================
#include <p18cxxx.h>
#include <p18lf46k22.h>
#include <delays.h>

#include "My_TEMP.h"
#include "../../main.h"
#include "../GSM/My_GSM.h"
#include "../Temperature/ftoa.h"
#include "../Temperature/1wire.h"
#include "../Temperature/My_TEMP.h"



// =======================================================================
//   Variables globales
// =======================================================================
float TempProbeValues[] = {0,-50,100};      // Temp�rature CURRENT(0), MAXIMUM(1), MINIMUM(2)



// =======================================================================
//   Fonction de lancement de conversion
// =======================================================================
void TemperatureConvert(void){
    INTCONbits.GIE  = 0;                    // D�sactive temporairement les interruptons
    Convert_Temperature();                  // Lance une premi�re conversion
    INTCONbits.GIE  = 1;                    // R�active les interruptons apr�s conversion
}



// =======================================================================
//   Fonction de gestion de temp�rature
// =======================================================================
void TemperatureProbe(void){
    INTCONbits.GIE = 0;
    TempProbeValues[0] = Read_Temperature();
    INTCONbits.GIE = 1;

    if (TempProbeValues[0] < TempProbeValues[2])
        TempProbeValues[2] = TempProbeValues[0];

    if (TempProbeValues[0] > TempProbeValues[1])
        TempProbeValues[1] = TempProbeValues[0];

    if (TempProbeValues[0] > TEMPERATURE_MAX){
        GsmCallExecution();
    }
    if (TempProbeValues[0] < TEMPERATURE_MIN){
        GsmCallExecution();
    }

    INTCONbits.GIE = 0;
    Convert_Temperature();
    INTCONbits.GIE = 1;
}