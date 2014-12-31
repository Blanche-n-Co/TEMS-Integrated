#include <stdlib.h>

#include "xlcd.h"
#include "writeOnLCD.h"
#include "delaysXLCD.h"
#include "../../main.h"
#include "../Temperature/ftoa.h"


//enum {NOFLUSH, FLUSH, AFTER};

void prepareLCD (int flushStatut, int position){
    if (flushStatut == FLUSH) {
        while(BusyXLCD());
        WriteCmdXLCD(0x01);
    }

    if (position != AFTER) {
        while(BusyXLCD());
        SetDDRamAddr(position);
    }
}

//void writeOnLCDS (int flushStatut, int position, const rom char *string)
void writeOnLCDS (int flushStatut, int position, const char *string)
{
    prepareLCD(flushStatut, position);

    while(BusyXLCD());
    putrsXLCD(string);
}


void writeOnLCDC (int flushStatut, int position, char charactere) {
    prepareLCD(flushStatut, position);

    while(BusyXLCD());
    putcXLCD(charactere);
}

void writeOnLCDV (int flushStatut, int position, char *variable) {
    prepareLCD(flushStatut, position);

    while(BusyXLCD());
    putsXLCD(variable);
}

/*void writeOnLCDI (int flushStatut, int position, int entier) {
    char string[6];

    itoa(string, entier, 10);

    prepareLCD(flushStatut, position);

    while(BusyXLCD());
    putsXLCD(string);
*/

void writeOnLCDF(int flushStatut, int position, float reel,char Dec) {
    char string[6];

    ftoa(reel, string, Dec, 'F');

    prepareLCD(flushStatut, position);

    while(BusyXLCD());
    putsXLCD(string);
}