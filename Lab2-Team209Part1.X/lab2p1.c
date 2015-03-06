// ******************************************************************************************* //
// File:         lab2p1.c
// Date:         March 13 2015
// Authors:      Angel Lopez, Arminda Estrada, Rubi Ballesteros, Miguel Garcia, Phillip Showers.
//
// Description: This is part one of Lab 2. 
// ******************************************************************************************* //

#include "p24fj64ga002.h"
#include "lcd.h"
#include "timer.h"
#include "keypad.h"
#include <stdio.h>

_CONFIG1( JTAGEN_OFF & GCP_OFF & GWRP_OFF & BKBUG_ON & COE_OFF & ICS_PGx1 &
          FWDTEN_OFF & WINDIS_OFF & FWPSA_PR128 & WDTPS_PS32768 )

_CONFIG2( IESO_OFF & SOSCSEL_SOSC & WUTSEL_LEG & FNOSC_PRIPLL & FCKSM_CSDCMD & OSCIOFNC_OFF &
          IOL1WAY_OFF & I2C1SEL_PRI & POSCMOD_XT )

typedef enum stateTypeEnum
{
    wait,
    keyFind,
    writeLCDs
}stateType;

volatile stateType curState;
volatile char keys[17] = {'\0','\0','\0','\0','\0','\0','\0','\0',
                '\0','\0','\0','\0','\0','\0','\0','\0','\0'};
volatile int keysIndex = 0;

int main(void)
{
    initKeypad();
    initLCD();
    clearLCD();
    curState = wait;
    

    while(1){
        switch (curState)
        {
            case wait:
                break;

            case keyFind:
                keys[keysIndex] = scanKeypad();
                keysIndex++;
                curState = writeLCDs;
                break;

            case writeLCDs:
                if (keys[keysIndex-1] != -1){
                    clearPrintStringLCD(keys);
                    if (keysIndex == 16) keysIndex = 0;
//                    printCharLCD(keyToWrite);
                }
                else{
                    if (keysIndex != 0)
                    keysIndex--;
                }
                curState = wait;
                break;

        } // switch
    } // while
    
    return 0;
}

void _ISR _CNInterrupt(){
    _CNIF = 0;
    delayMs(10); //press/release delay

 
    if (curState == wait){
        if (COL1 == 0 || COL2 == 0 || COL3 == 0){
//        curState = keyFind;
            /*
             NOTE: I can use the statement right above this, but the program breaks more often by pressing keys fast and simultaneously.
             * By scanning the keys here in the interrupt it no longer breaks.
             */
            keys[keysIndex] = scanKeypad();
                keysIndex++;
                curState = writeLCDs;
        }
    }

} // _CNInterrupt
