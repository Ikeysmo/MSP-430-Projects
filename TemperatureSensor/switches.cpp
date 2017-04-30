/*
 * switches.cpp
 *
 *  Created on: Apr 30, 2017
 *      Author: Isaiah
 */
#include  "msp430.h"
#include "macros.h"

extern volatile bool sleep;


#pragma vector = PORT4_VECTOR
__interrupt void switch_interrupt(void){
  // Switch 1
  // flag, turn on in ports
  if(P4IFG & SW1){
    // Clear sw1 flags
    P4IFG &= ~SW1;
    // Clear any current timer interrupt.
    P3OUT |= LCD_BACKLITE;

//    LPM3_EXIT;
    sleep = false;
    //LPM3_EXIT
  }

  // Switch 2
  if(P4IFG & SW2){
    // Disable the Switch Interrupt.
    // Clear sw2 flags
    P4IFG &= ~SW2;
    // Clear any current timer intterupt.
    P3OUT &= ~LCD_BACKLITE;
//    _bis_SR_register(LPM3_bits + GIE);
    //LPM3;
    //LPM3_EXIT
  }

  // Enable the Timer Interrupt for the debounce.
  TA0CCTL2 |= CCIE;

}


