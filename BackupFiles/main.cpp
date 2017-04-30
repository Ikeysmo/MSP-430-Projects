/*
 * main.cpp
 *
 *  Created on: Jan 5, 2017
 *      Author: Isaiah
 */

//***************************************************************************************
//  MSP430 Blink the LED Demo - Software Toggle P1.0
//
//  Description; Toggle P1.0 by xor'ing P1.0 inside of a software loop.
//  ACLK = n/a, MCLK = SMCLK = default DCO
//
//                MSP430x5xx
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//            |             P1.0|-->LED
//
//  J. Stevenson
//  Texas Instruments, Inc
//  July 2011
//  Built with Code Composer Studio v5
//***************************************************************************************


#define CALADC12_15V_30C  *((unsigned int *)0x1A1A)   // Temperature Sensor Calibration-30 C
//See device datasheet for TLV table memory mapping
#define CALADC12_15V_85C  *((unsigned int *)0x1A1C)   // Temperature Sensor Calibration-85 C
enum state{ MENU, TEMP};
#include <msp430.h>
#include "hamburger.h"
#include "functions.h"
#include "macros.h"
#include "LCD.hpp"
#include "serial_USB.hpp"
#include "serial_IOT.hpp"
//#include <string>

// Pin Definitions
#define ACC_PWR_PIN       BIT7
#define ACC_PWR_PORT_DIR  P2DIR
#define ACC_PWR_PORT_OUT  P2OUT
#define ACC_PORT_DIR      P3DIR
#define ACC_PORT_OUT      P3OUT
#define ACC_PORT_SEL0     P3SEL0
#define ACC_PORT_SEL1     P3SEL1
#define ACC_X_PIN         BIT0
#define ACC_Y_PIN         BIT1
#define ACC_Z_PIN         BIT2

// Accelerometer Input Channel Definitions
#define ACC_X_CHANNEL     ADC10INCH_12
#define ACC_Y_CHANNEL     ADC10INCH_13
#define ACC_Z_CHANNEL     ADC10INCH_14

using namespace std;

volatile int ACCEL_X, ACCEL_Y, ACCEL_Z;
volatile unsigned int Temperature =0;
volatile unsigned int counter = 0;
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
volatile bool sleep = false;

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer0_A0_ISR(void){
  TA0CCR0 += TA0CCR0_INTERVAL;          // Add offset to TACCR0
//  PJOUT ^= LED1; used to blink every time counter increased
  // check if debouncing

}

#pragma vector = TIMER0_A1_VECTOR

__interrupt void TIMER0_A1_ISR(void){
  switch(__even_in_range(TA0IV,14)){
  case I0: break;                        // No interrupt
  case I2:                               // CCR1 not used
    TA0CCR1 += TA0CCR1_INTERVAL;        // Add offset to TACCR1
    //PJOUT ^= 0x02;
    if(!sleep)
        counter++;
    if(counter > 40 && !sleep){
        sleep = true;
        counter = 0;
    }
    break;
  case I4:                               // CCR2 not used
//    TA0CCR2 += TA0CCR2_INTERVAL;        // Add offset to TACCR2
    break;
  case I6: break;                        // reserved
  case I8: break;                        // reserved
  case I10: break;                       // reserved
  case I12: break;                       // reserved
  case I14:                              // overflow
    // Put code here for overflow
    break;
  default: break;
  }
}



#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void){
    switch(__even_in_range(ADC10IV,12)) {
    case 0: break; // No interrupt
    case 2: break; // conversion result overflow
    case 4: break; // conversion time overflow
    case 6: break; // ADC10HI
    case 8: break; // ADC10LO
    case 10: break; // ADC10IN
    case 12:
        switch(ADC10MCTL0_L & 0x0F){
                case 12: //XOUT
                    ACCEL_X = ADC10MEM0;
                    ADC10CTL0 &= ~ADC10ENC;
                    ADC10MCTL0_L = 13;
                    break;
                case 13: //YOUT
                    ACCEL_Y = ADC10MEM0;
                    ADC10CTL0 &= ~ADC10ENC;
                    ADC10MCTL0_L = 14;
                    break;
                case 14: //ZOUT
                    ACCEL_Z = ADC10MEM0;
                    ADC10CTL0 &= ~ADC10ENC;
                    ADC10MCTL0_L = 12;
                    //ADC_READY = 1;
                    break;
        }
        ADC10CTL0 |= ADC10ENC + ADC10SC;
        break;
    default: break;
    }
}

char selection;
unsigned int ADC_THUMB;
state MSTATE;
//string name;
//String nam2e;
#pragma LOCATION(0x1980)
#pragma PERSISTENT
int xyx  = 3;

volatile char d;

int convertToGrav(int num){
    int answer = (num - 520)/10.204;
    answer = -1*answer;
    return answer;
}
void intToNum(char buff[], int num){
    int number = num;
    char temp[11];
    int i = 0;
    if(number == 0){
        buff[0] = '0';
        return;
    }
    while(number){
        if(number > 0){
        temp[i] = (number%10) + '0';
        }
        else if(number < 0){
            temp[i] = (-number%10) + '0';
        }
        number = number/10;
        i++;
        if(i >= 11)
            break;
        if(num < 0 && number == 0){
            temp[i++] = '-';
        }
    } //gonna be backwards
    temp[i] = 0;
    for(int j = 0; j < i; j++){
        buff[j] = temp[i-1-j];
    }
    buff[i] = 0;
}
void turnOnRelay(){
    P3OUT &= ~R_FORWARD;
    P3OUT &= ~R_REVERSE;
}

void turnOffRelay(){
    P3OUT |= R_FORWARD;
    P3OUT &= ~R_REVERSE;
}

#pragma vector = PORT4_VECTOR
__interrupt void switch_interrupt(void){
  // Switch 1
  // flag, turn on in ports
  if(P4IFG & SW1){
    // Clear sw1 flags
    P4IFG &= ~SW1;
    // Clear any current timer interrupt.
    P3OUT |= LCD_BACKLITE;
    turnOnRelay();
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
    turnOffRelay();
//    _bis_SR_register(LPM3_bits + GIE);
    //LPM3;
    //LPM3_EXIT
  }

  // Enable the Timer Interrupt for the debounce.
  TA0CCTL2 |= CCIE;

}
void powerRelay(){
    P3OUT |= L_FORWARD;
    P3OUT &= ~L_REVERSE;
}



void main(void) {

    MSTATE = TEMP;
    Init_Clocks(); //set the clocks... smclock = 8mhz
//    Init_Timers();  //what does timer have to do with LCD????
    Init_Ports();    //make sure ports are correct? But they should be
    PJOUT &= ~0x04; //cannot turn off reset
    PJOUT &= ~0x02;
    powerRelay();

    __delay_cycles(10000);
//    lcd.Init_LCD();
    __delay_cycles(1000);

    Init_ADC();
    SetupAccel();
    //serial_USB.Init_Serial(b9600);
    //serial_IOT.Init_Serial(b9600);
    //serial_USB.Init_Serial(b9600);
    //serial_IOT.Init_Serial(b115200);
    __bis_SR_register(GIE); //enable interrupts
//    lcd.lcd_4line();
//    lcd.ClrDisplay();
//    lcd.setLine("ADC", 1);
//    lcd.setLine("Measurements", 2);
//    lcd.refresh();

    //LPM3
    static char buff_line_1[11];
    static char buff_line_2[11];
    static char buff_line_3[11];
    while (ADC10CTL1 & BUSY);
      ADC10CTL0 |= ADC10ENC | ADC10SC ;       // Start conversion

    while(1){
        //serial_IOT.send_array("AT+GMR\r\n");
        //serial_IOT.send_array("AT+UART_DEF=9600,8,1,0,0\r\n");
//        turnOnRelay();
//        __delay_cycles(8000000);
//        __delay_cycles(8000000);
//        __delay_cycles(8000000);
//        __delay_cycles(8000000);
//        __delay_cycles(8000000);
//        __delay_cycles(8000000);
//        __delay_cycles(8000000);
//        __delay_cycles(8000000);
//
//        turnOffRelay();
//        __delay_cycles(8000000);
//                __delay_cycles(8000000);
//                __delay_cycles(8000000);
//                __delay_cycles(8000000);
//                __delay_cycles(8000000);
//                __delay_cycles(8000000);
//                __delay_cycles(8000000);
//                __delay_cycles(8000000);
        //serial_USB.send_char('a');
//        int new_accel_x = convertToGrav(ACCEL_X);
//        int new_accel_y = convertToGrav(ACCEL_Y);
//        int new_accel_z = convertToGrav(ACCEL_Z);
//        intToNum(buff_line_1, new_accel_x);
//        intToNum(buff_line_2, new_accel_y);
//        intToNum(buff_line_3, new_accel_z);
//        lcd.setLine(buff_line_1, 2);
//        lcd.setLine(buff_line_2, 3);
//        lcd.setLine(buff_line_3, 4);
//        lcd.refresh();
//        if(sleep){
//            P3OUT &= ~LCD_BACKLITE;
////            _bis_SR_register(LPM3_bits + GIE);
//        }
//        if(serial_IOT.isAvailable())
//            serial_USB.send_char(serial_IOT.receive_char());

        //        //UCA0
    }

}




void Init_ADC(void){
    REFCTL0     |=   REFON | REFVSEL_1;                                       // V_REF enabled ( 2 V )
    ADC10CTL0 = CLEAR_REG;
    ADC10CTL0 |=  ADC10SHT_2; //16 cycles to sample
    ADC10CTL0 &= ~ADC10MSC; // Single Sequence
    ADC10CTL0 |= ADC10ON; // ADC ON - Core Enabled
    ADC10CTL1 |= ADC10SHS_0; // ADC10SC bit
    ADC10CTL1 |= ADC10SHP; // SAMPCON signal sourced from sampling timer
    ADC10CTL1 &= ~ADC10ISSH; // The sample-input signal is not inverted.
    ADC10CTL1 |= ADC10DIV_4; // ADC10_B clock divider – Divide by 4.
    ADC10CTL1 |= ADC10SSEL_3; // SMCLK
    ADC10CTL1 |= ADC10CONSEQ_0; // Single-channel, single-conversion
    //ADC10CTL2 |= ADC10PDIV__64;
    ADC10CTL2 |= ADC10PDIV__64; // Pre-divide by 1
    ADC10CTL2 |= ADC10RES;
    ADC10CTL2 &= ~ADC10DF;
    ADC10CTL2 &= ~ADC10SR; // supports up to approximately 200 ksps
    //
    ADC10MCTL0 |= ADC10SREF_1; // V(R+) = AVCC and V(R-) = AVSS
    ADC10MCTL0 |= ADC10INCH_10;
    //
    ADC10IE |= ADC10IE0;
    ADC10CTL0 |= ADC10ENC;
    ADC10CTL0 |= ADC10SC;
}


