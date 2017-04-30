


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


using namespace std;


volatile unsigned int temperature = 0;
extern volatile unsigned int counter;
volatile bool sleep = false;

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
        //temp sensor
                   temperature = ADC10MEM0;
                   ADC10CTL0 &= ~ADC10ENC;
                   ADC10MCTL0 |= ADC10INCH_10;
                   //ADC_READY = 1;

        ADC10CTL0 |= ADC10ENC + ADC10SC;
    }
}


extern "C" {
void intToNum(char buff[], unsigned int num){
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
}


void main(void) {

    Init_Clocks(); //set the clocks... smclock = 8mhz
//    Init_Timers();  //what does timer have to do with LCD????
    Init_Ports();    //make sure ports are correct? But they should be
    PJOUT &= ~0x04; //cannot turn off reset
    PJOUT &= ~0x02;

    __delay_cycles(1000);
    lcd.Init_LCD();
    __delay_cycles(1000);

    Init_ADC();

    __bis_SR_register(GIE); //enable interrupts
    lcd.lcd_4line();
    lcd.ClrDisplay();
    lcd.setLine("ADC", 1);
    lcd.setLine("Measurements", 2);
    lcd.refresh();

    //LPM3
    static char buff_line_1[11];
    static char buff_line_2[11];
    static char buff_line_3[11];
    while (ADC10CTL1 & BUSY);
      ADC10CTL0 |= ADC10ENC | ADC10SC ;       // Start conversion

    char buff[11];
    while(1){

        __delay_cycles(8000000);
        intToNum(buff_line_3, temperature);
        lcd.setLine(buff_line_3, 3);
        lcd.refresh();
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
    ADC10MCTL0 |= ADC10SREF_1 + ADC10INCH_10 ; // V(R+) = AVCC and V(R-) = AVSS
    //
    ADC10IE |= ADC10IE0;
    ADC10CTL0 |= ADC10ENC;
    ADC10CTL0 |= ADC10SC;
}


