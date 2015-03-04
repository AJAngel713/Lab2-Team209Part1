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
char keyToWrite = -1;

int main(void)
{
    initKeypad();
    initLCD();
    moveCursorLCD(0,0);
    curState = wait;
    

    while(1){
        switch (curState)
        {
            case wait:
                break;

            case keyFind:

                keyToWrite = scanKeypad();
                curState = writeLCDs;
                break;

            case writeLCDs:
                if (keyToWrite != -1){
                    printCharLCD(keyToWrite);
                }
                curState = wait;
                break;

        } // switch
    } // while
    
    return 0;
}

void _ISR _CNInterrupt(){
    _CNIF = 0;
    delayMs(5); //press/release delay

 
    if (curState == wait){
        curState = keyFind;
    }

} // _CNInterrupt
