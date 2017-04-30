/*
 * acc_xyz.cpp
 *
 *  Created on: Apr 30, 2017
 *      Author: Isaiah
 */

#include <msp430.h>
#include "acc_xyz.h"

void SetupAccel(void)
{
  //Setup  accelerometer
  // ~20KHz sampling
  //Configure GPIO
  ACC_PORT_SEL0 |= ACC_X_PIN + ACC_Y_PIN + ACC_Z_PIN;    //Enable A/D channel inputs
  ACC_PORT_SEL1 |= ACC_X_PIN + ACC_Y_PIN + ACC_Z_PIN;
  ACC_PORT_DIR &= ~(ACC_X_PIN + ACC_Y_PIN + ACC_Z_PIN);
  ACC_PWR_PORT_DIR |= ACC_PWR_PIN;              //Enable ACC_POWER
  ACC_PWR_PORT_OUT |= ACC_PWR_PIN;

  // Allow the accelerometer to settle before sampling any data
 // __delay_cycles(200000);

  //Single channel, once,
  ADC10CTL0 &= ~ADC10ENC;                        // Ensure ENC is clear
  ADC10CTL0 = ADC10ON + ADC10SHT_5;
  ADC10CTL1 = ADC10SHS_0 + ADC10SHP + ADC10CONSEQ_0 + ADC10SSEL_0;
  ADC10CTL2 = ADC10RES;
  ADC10MCTL0 = ADC10SREF_0 + ADC10INCH_12;
  ADC10IV = 0x00;                          // Clear all ADC12 channel int flags
  ADC10IE |= ADC10IE0;


}


//volatile int ACCEL_X, ACCEL_Y, ACCEL_Z;
