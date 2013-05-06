/*
* Template dsPIC33F
* Compiler : Microchip xC16
* µC : 33FJ64MC802
* Juillet 2012
*    ____________      _           _
*   |___  /| ___ \    | |         | |
*      / / | |_/ /___ | |__   ___ | |_
*     / /  |    // _ \| '_ \ / _ \| __|
*    / /   | |\ \ (_) | |_) | (_) | |_
*   /_/    |_| \_\___/|____/ \___/'\__|
*			      7robot.fr
*/

#include <p33Fxxxx.h>      /* Includes device header file                     */
#include <stdint.h>        /* Includes uint16_t definition                    */
#include <stdbool.h>       /* Includes true/false definition                  */
#include "header.h"        /* Function / Parameters                           */
#include <libpic30.h>
#include <uart.h>

#include "atp.h"

/******************************************************************************/
/* Configuartion                                                              */
/******************************************************************************/

// Select Oscillator and switching.
_FOSCSEL(FNOSC_FRCPLL & IESO_OFF);
// Select clock.
_FOSC(POSCMD_NONE & OSCIOFNC_ON /*& IOL1WAY_OFF*/ & FCKSM_CSDCMD);
// Watchdog Timer.
_FWDT(FWDTEN_OFF);
// Select debug channel.
_FICD(ICS_PGD1 & JTAGEN_OFF);


/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

volatile unsigned char callback = 0;
volatile unsigned int delay = 1000;
volatile char blink = 1;

void OnSetCallback(unsigned char nbloop) {
    callback = nbloop;
}

void OnSetDelay(unsigned int _delay) {
    delay = _delay;
}

void OnLedOn() {
    blink = 0;
    led = 1;
}

void OnLedOff() {
    blink = 0;
    led = 0;
}

void OnBlinkOn() {
    blink = 1;
}

void OnBlinkOff() {
    blink = 0;
}

int16_t main(void)
{
    ConfigureOscillator();
    InitApp();
    
    AtpInit();

    

    while(1) {
        SendError();
        __delay_ms(delay);
        if (blink) {
            led = led ^ 1;
        }
        if (callback > 0) {
            callback--;
            if (callback == 0) {
                SendCallback();
            }
        }
    }
}
