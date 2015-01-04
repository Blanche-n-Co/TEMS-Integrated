// =======================================================================
//   Dérives de compilations
// =======================================================================
#include <p18cxxx.h>
#include <p18lf46k22.h>
#include <delays.h>

#include "My_CLOCK.h"
#include "../../main.h"
#include "../i2c/i2c.h"
#include "../LCD/xlcd.h"
#include "../LCD/writeOnLCD.h"



// =======================================================================
//   Variables globales
// =======================================================================
unsigned char ClockReadBuffer[]={0,0,0,0,0,0,0,0};                      //Tableau de lecture (BCD)
unsigned char ClockConvBuffer[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};    //Tableau de conversion
unsigned char ClockInitBuffer[]={
    0x05,       //   05 - Seconds (doit être de min 1 sec car ne peut commencer par 0)
    0x45,       //   45 - Minutes
    0x10,       //   10 - Hours format 24h
    0x02,       //Mardi - Days
    0x13,       //   13 - Date
    0x01,       //  Jan - Month
    0x15,       // 2015 - Year
    0x01,       // DOIT être définit à min 1 pour ne pas terminer avec un 0 (puts)
    0x00        // Arrête la transmission avec puts
};



// =======================================================================
//   Fonction de lecture de l'heure
// =======================================================================
void ClockInit(void){
    //I2C State (Initialization)
    TRISDbits.TRISD0 = 1;
    TRISDbits.TRISD1 = 1;

    OpenI2C2( MASTER, SLEW_OFF);
    SSP2ADD = 0x27;             //Baud rate

    //Ecriture de l'heure
    IdleI2C2();
    StartI2C2();                //Condition de START équivalent à SSP2CON2bits.SEN = 1;
    while(SSP2CON2bits.SEN);    //Attends qu'il soit prêt
    WriteI2C2(0b11010000);      //Adresse du périphérique et mode d'écriture (0)
    WriteI2C2(0b00000000);      //Envoie l'adresse de start dans laquelle on commence à écrire

    //On commence à écrire les données en se rapportant au format BCD (DS1307)
    //On définit un tableau pour éviter de faire des write pour chaque valeurs
    putsI2C2(&ClockInitBuffer[0]);   //Le tableau s'incrémente seul
    StopI2C2();
}



// =======================================================================
//   Fonction de lecture de l'heure
// =======================================================================
void ClockRead(void){
    int i = 0;
    int nbBytes = 7;                            //Conversion de la date et l'heure
    unsigned char *ptr = &ClockConvBuffer[0];

    Delay10KTCYx(200);
    Delay10KTCYx(200);

    IdleI2C2();
    StartI2C2();                                //Condition de start
    while(SSP2CON2bits.SEN);                    //On attends qu'il soit prêt
    WriteI2C2(0b11010000);                      //On doit utiliser le rewrite
    WriteI2C2(0b00000000);                      //Lire à partir de... (adresse)

    RestartI2C2();                              //Condition de restart
    while(SSP2CON2bits.RSEN);                   //On attends qu'il soit prêt
    WriteI2C2(0b11010001);

    getsI2C2(&ClockReadBuffer[0],nbBytes);
    StopI2C2();

    for(i=0 ; i < nbBytes ; i++, ptr+=2){
        BCD2ASC(ClockReadBuffer[i], ptr);}
    *ptr = 0;

    ptr = &ClockConvBuffer[0];
}



// =======================================================================
//   Fonction d'affichage de l'heure
// =======================================================================
void ClockShow(void){
    int j = 0;
    
    //Lecture de l'heure
    ClockRead();

    //Affichage de la date
    // -  8 et  9 Affichage du jour de la date
    // - 10 et 11 Affichage du mois de la date
    // - 12 et 13 Affichage de l'année de la date
    writeOnLCDS(FLUSH, 0x00,"Date: ");
    for(j=8 ; j<14 ; j+=2){
        while(BusyXLCD());
        WriteDataXLCD(ClockConvBuffer[j]);
        while(BusyXLCD());
        WriteDataXLCD(ClockConvBuffer[j+1]);

        if(j != 12){
            while(BusyXLCD());
            WriteDataXLCD('-');
        }
    }

    //Affichage de l'heure
    // - 4 et 5 Affichage de l'heure
    // - 2 et 3 Affichage des minutes
    // - 0 et 1 Affichage des secondes
    writeOnLCDS(NOFLUSH, 0x40,"Time: ");
    for(j=5 ; j>=0 ; j-=2){
        while(BusyXLCD());
        WriteDataXLCD(ClockConvBuffer[j-1]);
        while(BusyXLCD());
        WriteDataXLCD(ClockConvBuffer[j]);

        if(j != 1){
            while(BusyXLCD());
            WriteDataXLCD(':');
        }
    }
}



// =======================================================================
//   Fonction de conversion BCD to ASCII
// =======================================================================
void BCD2ASC(unsigned char src, char *dest){
    static const char outputs[] = "0123456789ABCDEF";
    *dest++ = outputs[src>>4];
    *dest++ = outputs[src&0x0f];
}