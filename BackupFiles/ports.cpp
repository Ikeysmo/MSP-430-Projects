/*
 * ports.cpp
 *
 *  Created on: Jan 5, 2017
 *      Author: Isaiah
 */
//******************************************************************************
//
//  Description: This file contains the ports function and its child functions
//  for each individual port.  The function links the pins of each port to the
//  correct area of the MSP430.
//
//
//  Isaiah Smoak
//  Sep 2015
//  Built with IAR Embedded Workbench for MSP430: V6.30.3
//******************************************************************************
#include  "msp430.h"
#include  "functions.h"
#include  "macros.h"


void Init_Port_1(void);         // prototype port 1
void Init_Port_2(void);         // prototype port 2
void Init_Port_3(void);         // prototype port 3
void Init_Port_4(void);         // prototype port 4
void Init_Port_J(void);         // prototype port J
void Init_PortJ(void);

void Init_Ports(void){
  Init_Port_1();
  Init_Port_2();
  Init_Port_3();
  Init_Port_4();
  Init_PortJ();
}
void Init_Port_1(void){ // iniitialize all pins for port 1
//------------------------------------------------------------------------------
//Configure Port 1
// V_DETECT_R           (0x01) //
// V_DETECT_L           (0x02) //
// IR_LED               (0x04) //
// V_THUMB              (0x08) //
// SPI_CS_LCD           (0x10) // LCD Chip Select
// SA0_LCD              (0x20) // LCD SA0 H/L Slave Address
// SPI_SIMO             (0x40) // SPI mode - slave in/master out of USCI_B0
// SPI_SOMI             (0x80) // SPI mode- slave out/master in of USCI_B0
//------------------------------------------------------------------------------
 P1SEL0 = GIO;                // P1 set as I/0
 P1SEL1 = GIO;                // P1 set as I/0
 P1DIR = OUTP;                 // Set P1 direction to input
 // V_DETECT_R
 P1SEL0 |= V_DETECT_R;         // V_DETECT_R selected
 P1SEL1 |= V_DETECT_R;         // V_DETECT_R selected
 // V_DETECT_L
 P1SEL0 |= V_DETECT_L;         // V_DETECT_L selected
 P1SEL1 |= V_DETECT_L;         // V_DETECT_L selected
 // IR_LED
 P1SEL0 &= ~IR_LED;            // IR_LED GPI/O selected
 P1SEL1 &= ~IR_LED;            // IR_LED GPI/O selected
 P1OUT |= IR_LED;              // P1 IR_LED Port Pin set low
 P1DIR |= IR_LED;              // Set P1 IR_LED direction to output
 // V_THUMB
 P1SEL0 |= V_THUMB;            // V_THUMB selected
 P1SEL1 |= V_THUMB;            // V_THUMB selected
 // SPI_CS_LCD
 P1SEL0 &= ~SPI_CS_LCD;        // SPI_CS_LCD GPI/O selected
 P1SEL1 &= ~SPI_CS_LCD;        // SPI_CS_LCD GPI/O selected
 P1OUT |= SPI_CS_LCD;          // P1 SPI_CS_LCD Port Pin set high
 P1DIR |= SPI_CS_LCD;          // Set SPI_CS_LCD output direction
 // SAO_LCD
 P1SEL0 &= ~SA0_LCD;           // SA0_LCD GPI/O selected
 P1SEL1 &= ~SA0_LCD;           // SA0_LCD GPI/O selected
 P1OUT &= ~SA0_LCD;            // P1 SA0_LCD Port Pin set low
 P1DIR |= SA0_LCD;             // Set SA0_LCD output direction
 // SPI_SIMO
 P1SEL0 &= ~SPI_SIMO;            // SPI_SIMO selected
 P1SEL1 |= SPI_SIMO;             // SPI_SIMO selected
 P1DIR |= SPI_SIMO;              // SPI_SIMO set to Output
 // SPI_SOMI
 P1SEL0 &= ~SPI_SOMI;            // SPI_SOMI is used on the LCD
 P1SEL1 |= SPI_SOMI;             // SPI_SOMI is used on the LCD
 P1DIR &= ~SPI_SOMI;             // SPI_SOMI set to Input
 P1REN |= SPI_SOMI;              // Enable pullup resistor
//-----------------------------------------------------------------------------
  }
void Init_Port_2(void){ // iniitialize all pins for port 2
//----------------------------------------------------------------------------
// Configure PORT 2
// USB_TXD              (0x01) //
// USB_RXD              (0x02) //
// SPI_SCK              (0x04) // Serial Clock
// UNKNOWN_1            (0x08) //
// UNKNOWN_2            (0x10) //
// CPU_TXD              (0x20) //
// CPU_RXD              (0x40) //
// UNKNOWN_3            (0x80) //
//------------------------------------------------------------------------------
P2SEL0 = GIO;          // P2 set as I/0
P2SEL1 = GIO;          // P2 set as I/0
P2DIR = OUTP;          // Set P2 direction to input
P2OUT = OUTP;
//USB_TXD
P2SEL0 &= ~USB_TXD;            // USB_TXD selected
P2SEL1 |= USB_TXD;             // USB_TXD selected
P1DIR |= USB_TXD;              // USB_TXD set to Output
//USB_RXD
P2SEL0 &= ~USB_RXD;            // USB_RXD selected
P2SEL1 |= USB_RXD;             // USB_RXD selected
P1DIR &= ~USB_RXD;             // USB_RXD set to Input
//SPI_SCK
P2SEL0 &= ~SPI_SCK;            // SPI_SCK selected
P2SEL1 |= SPI_SCK;             // SPI_SCK selected
P2OUT |= SPI_SCK;              // SPI_SCK Port Pin set high
P2DIR |= SPI_SCK;              // SPI_SCK set to Output
//UNKNOWN_1
P2SEL0 &= ~UNKNOWN;          //UNKNOWN_1 selected
P2SEL1 &= ~UNKNOWN;          //UNKNOWN_1 selected
P2OUT &= ~UNKNOWN;           //UNKNOWN_1 set low
P2DIR |= UNKNOWN;            // Direction = input
//UNKNOWN_2
P2SEL0 &= ~UNKNOWN1;          //UNKNOWN_2 selected
P2SEL1 &= ~UNKNOWN1;          //UNKNOWN_2 selected
P2OUT &= ~UNKNOWN1;           //UNKNOWN_2 set low
P2DIR |= UNKNOWN1;            // Direction = input
//CPU_TXD
P2SEL0 &= ~CPU_TXD;            // CPU_TXD selected
P2SEL1 |= CPU_TXD;             // CPU_TXD selected
P2OUT &= ~CPU_TXD;             // CPU_TXD Port Pin set low
P1DIR |= CPU_TXD;              // CPU_TXD set to Output
//CPU_RXD
P2SEL0 &= ~CPU_RXD;            // CPU_RXD selected
P2SEL1 |= CPU_RXD;             // CPU_RXD selected
P1DIR &= ~CPU_RXD;             // CPU_RXD set to Input
//UNKNOWN_3
P2SEL0 &= ~UNKNOWN2;          //UNKNOWN_3 selected
P2SEL1 &= ~UNKNOWN2;          //UNKNOWN_3 selected
P2OUT &= ~UNKNOWN2;           //UNKNOWN_3 set low
P2DIR |= UNKNOWN2;            // Direction = input
//------------------------------------------------------------------------------
   }
void Init_Port_3(void){ // iniitialize all pins for port 3
//------------------------------------------------------------------------------
// Configure PORT 3
// X                    (0x01) //
// Y                    (0x02) //
// Z                    (0x04) //
// LCD_BACKLITE         (0x08) //
// R_FORWARD            (0x10) //
// R_REVERSE            (0x20) //
// L_FORWARD            (0x40) //
// L_REVERSE            (0x80) //
//------------------------------------------------------------------------------
 P3SEL0 = GIO;         // P3 set as I/0
 P3SEL1 = GIO;         // P3 set as I/0
 P3DIR = OUTP;          // Set P3 direction to input
 P3OUT = OUTP;
// IES?
// X
 P3SEL0 &= ~X;          // X set as I/0
 P3SEL1 &= ~X;          // X set as I/0
 P3OUT &= ~X;           // Configure pullup resistor
 P3DIR &= ~X;           // Direction = input
 P3REN |= X;            // Enable pullup resistor
// Y
 P3SEL0 &= ~Y;          // Y set as I/0
 P3SEL1 &= ~Y;          // Y set as I/0
 P3OUT &= ~Y;           // Configure pullup resistor
 P3DIR &= ~Y;           // Direction = input
 P3REN |= Y;            // Enable pullup resistor
// Z
 P3SEL0 &= ~ZED;         // ZED set as I/0
 P3SEL1 &= ~ZED;         // ZED set as I/0
 P3OUT &= ~ZED;          // Configure pullup resistor
 P3DIR &= ~ZED;          // Direction = input
 P3REN |= ZED;           // Enable pullup resistor
// LCD_BACKLITE
 P3SEL0 &= ~LCD_BACKLITE;       // LCD_BACKLITE GPI/O selected
 P3SEL1 &= ~LCD_BACKLITE;       // LCD_BACKLITE GPI/O selected
 P3OUT &= ~LCD_BACKLITE;        // LCD_BACKLITE Port Pin set low
 P3DIR |= LCD_BACKLITE;         // LCD_BACKLITE direction to output
// R_FORWARD
 P3SEL0 &= ~R_FORWARD;          // R_FORWARD GPI/O selected
 P3SEL1 &= ~R_FORWARD;          // R_FORWARD GPI/O selected
 P3OUT &= ~R_FORWARD;           // R_FORWARD Port Pin set low
 P3DIR |= R_FORWARD;            // R_FORWARD direction to output
// R_REVERSE
 P3SEL0 &= ~R_REVERSE;          // R_REVERSE GPI/O selected
 P3SEL1 &= ~R_REVERSE;          // R_REVERSE GPI/O selected
 P3OUT &= ~R_REVERSE;           // R_REVERSE Port Pin set low
 P3DIR |= R_REVERSE;            // R_REVERSE direction to output
// L_FORWARD
 P3SEL0 &= ~L_FORWARD;          // L_FORWARD GPI/O selected
 P3SEL1 &= ~L_FORWARD;          // L_FORWARD GPI/O selected
 P3OUT &= ~L_FORWARD;           // L_FORWARD Port Pin set low
 P3DIR |= L_FORWARD;            // L_FORWARD direction to output
// L_REVERSE
 P3SEL0 &= ~L_REVERSE;          // L_REVERSE GPI/O selected
 P3SEL1 &= ~L_REVERSE;          // L_REVERSE GPI/O selected
 P3OUT &= ~L_REVERSE;           // L_REVERSE Port Pin set low
 P3DIR |= L_REVERSE;            // L_REVERSE direction to output
//------------------------------------------------------------------------------
  }
void Init_Port_4(void){ // iniitialize all pins for port 4
//------------------------------------------------------------------------------
// Configure PORT 4
// Port 4 has only two pins
// Port 4 Pins
// SW1 (0x01) // Switch 1
// SW2 (0x02) // Switch 2
//------------------------------------------------------------------------------
 P4SEL0 = GIO;          // P4 set as I/0
 P4SEL1 = GIO;          // P4 set as I/0
 P4DIR = OUTP;          // Set P4 direction to input
 P4OUT = OUTP;
// SW1
 P4SEL0 &= ~SW1;        // SW1 set as I/0
 P4SEL1 &= ~SW1;        // SW1 set as I/0
 P4OUT |= SW1;          // Configure pullup resistor
 P4DIR &= ~SW1;         // Direction = input
 P4REN |= SW1;          // Enable pullup resistor
 P4IES |= SW1;          // SW1 Hi/Lo edge interrupt
// SW2
 P4SEL0 &= ~SW2;        // SW2 set as I/0
 P4SEL1 &= ~SW2;        // SW2 set as I/0
 P4OUT |= SW2;          // Configure pullup resistor
 P4DIR &= ~SW2;         // Direction = input
 P4REN |= SW2;          // Enable pullup resistor
 P4IES |= SW2;          // SW2 Hi/Lo edge interrupt
 P4IE  |= SW1;
 P4IE  |= SW2;
//-----------------------------------------------------------------------------
  }
void Init_Port_J(void){ // iniitialize all pins for port J
//------------------------------------------------------------------------------
// Port J Pins
// LED1 (0x01) // LED 5
// LED2 (0x02) // LED 6
// LED3 (0x04) // LED 7
// LED4 (0x08) // LED 8
// XINR (0x10) // XINR
// XOUTR (0x20) // XOUTR
//------------------------------------------------------------------------------
 PJSEL0 = CLEAR_REG; // PJ set as I/0
 PJSEL1 = CLEAR_REG; // PJ set as I/0
 PJDIR = CLEAR_REG; // Set PJ direction to output
 PJSEL0 &= ~LED1;
PJSEL1 &= ~LED1;
PJOUT &= ~LED1;
 PJDIR |= LED1; // Set PJ Pin 1 direction to output
 PJSEL0 &= ~LED2;
 PJSEL1 &= ~LED2;
 PJOUT &= ~LED2;
PJDIR |= LED2; // Set PJ Pin 2 direction to output
 PJSEL0 &= ~LED3;
 PJSEL1 &= ~LED3;
 PJOUT &= ~LED3;
PJDIR |= LED3; // Set PJ Pin 3 direction to output
 PJSEL0 &= ~RESET;
 PJSEL1 &= ~RESET;
 PJDIR |= RESET; // Set P3 Pin 4 direction to output
 PJOUT &= ~RESET;
// XT1 Setup
 PJSEL0 |= XINR;
 PJSEL0 |= XOUTR;
//------------------------------------------------------------------------------
}

void Init_PortJ(void){

  //------------------------------------------------------------------------------
//Port J has 6 pins
//IOT_FACTORY (0x01)
// IOT_WAKEUP (0x02)
// IOT_STA_MINIAP (0x04)
// RESET (0x08)
// XIN (0x10)
// XOUT (0x20)
//------------------------------------------------------------------------------
 PJSEL0 = CLEAR_REG; // P1 set as I/0
 PJSEL1 = CLEAR_REG; // P1 set as I/0
 PJDIR = CLEAR_REG; // Set P1 direction to input
 PJOUT = CLEAR_REG;

 PJDIR |= IOT_FACTORY;
 PJDIR |= IOT_WAKEUP; //used as reset for wifi chip!
 PJDIR |= IOT_STA_MINIAP;
 PJDIR |= RESET;

 //PJOUT |= IOT_FACTORY;
 PJOUT |= IOT_WAKEUP; //reset is active low!!
 //PJOUT |= IOT_STA_MINIAP;
// PJSEL0 |= XINR;
 //PJSEL0 |= XOUTR;



//------------------------------------------------------------------------------


}
































































































/*//ports.c   //THIS ONE IS the older version
#include  "msp430.h"
#include "macros.h"

void Init_Port1(void);
void Init_Port2(void);
void Init_Port3(void);
void Init_Port4(void);
void Init_PortJ(void);

void Init_Ports(void){
  Init_Port1();
  Init_Port2();
  Init_Port3();
  Init_Port4();
  Init_PortJ();
}

void Init_Port1(void){
//------------------------------------------------------------------------------
//Configure Port 1
// V_DETECT_R (0x01) //
// V_DETECT_L (0x02) //
// IR_LED (0x04) //
// V_THUMB (0x08) //
// SPI_CS_LCD (0x10) // LCD Chip Select
// SA0_LCD (0x20) // LCD SA0 H/L Slave Address
// SIMO_B (0x40) // SPI mode
// SOMI_B (0x80) // SPI mode
//------------------------------------------------------------------------------
 P1SEL0 = CLEAR_REG; // P1 set as I/0
 P1SEL1 = CLEAR_REG; // P1 set as I/0
 P1DIR = CLEAR_REG; // Set P1 direction to input
 P1SEL0 |= V_DETECT_R; // V_DETECT_R selected
 P1SEL1 |= V_DETECT_R; // V_DETECT_R selected
 P1SEL0 |= V_DETECT_L; // V_DETECT_L selected
 P1SEL1 |= V_DETECT_L; // V_DETECT_L selected
 P1SEL0 &= ~IR_LED; // IR_LED GPI/O selected
 P1SEL1 &= ~IR_LED; // IR_LED GPI/O selected
 P1OUT |= IR_LED; // P1 IR_LED Port Pin set low
 P1DIR |= IR_LED; // Set P1 IR_LED direction to output
 P1SEL0 |= V_THUMB; // V_THUMB selected
 P1SEL1 |= V_THUMB; // V_THUMB selected
 P1SEL0 &= ~SPI_CS_LCD; // SPI_CS_LCD GPI/O selected
 P1SEL1 &= ~SPI_CS_LCD; // SPI_CS_LCD GPI/O selected
 P1OUT |= SPI_CS_LCD; // P1 SPI_CS_LCD Port Pin set high
 P1DIR |= SPI_CS_LCD; // Set SPI_CS_LCD output direction
 P1SEL0 &= ~SA0_LCD; // SA0_LCD GPI/O selected
 P1SEL1 &= ~SA0_LCD; // SA0_LCD GPI/O selected
 P1OUT &= ~SA0_LCD; // P1 SA0_LCD Port Pin set low
 P1DIR |= SA0_LCD; // Set SA0_LCD output direction
 P1SEL0 &= ~SIMO_B; // SIMO_B selected
 P1SEL1 |= SIMO_B; // SIMO_B selected
 P1DIR |= SIMO_B; // SIMO_B set to Output
 P1SEL0 &= ~SOMI_B; // SOMI_B is used on the LCD
 P1SEL1 |= SOMI_B; // SOMI_B is used on the LCD
 P1DIR &= ~SOMI_B; // SOMI_B set to Input
 P1REN |= SOMI_B; // Enable pullup resistor
//------------------------------------------------------------------------------
}

void Init_Port2(void){
  //------------------------------------------------------------------------------
//Configure Port 2
// USB_TXD (0x01) //
// USB_RXD (0x02) //
// SPI_SCK (0x04) //
// UNKNOWN (0x08) //
// UNKNOWN (0x10) // LCD Chip Select
// CPU_TXD (0x20) // LCD SA0 H/L Slave Address
// CPU_RXD (0x40) // SPI mode
// UNKNOWN (0x80) // SPI mode
//------------------------------------------------------------------------------
 P2SEL0 = CLEAR_REG; // P1 set as I/0
 P2SEL1 = CLEAR_REG; // P1 set as I/0
 P2DIR = CLEAR_REG; // Set P1 direction to input
 P2OUT = CLEAR_REG;

 P2SEL0 &= ~USB_TXD; // USB_TXD selected
 P2SEL1 |= USB_TXD; // USB_TXD = 1 for SEL1
 P2DIR  |= USB_TXD;
 //HOW TO SET INITIAL VALUE FOR IT???
 P2SEL0 &= ~USB_RXD; // EQUAL TO ZERO
 P2SEL1 |= USB_RXD; // EQUAL TO ONE
 P2DIR  &= ~USB_RXD;

 P2SEL1 |= SPI_SCK; // EQUAL TO ONE
 P2DIR  |=  SPI_SCK;
 P2OUT  |= SPI_SCK;



 //P2SEL1 &= ~UNKNOWN; // IGNORE BOTH UNKNOWNS
 P2SEL1 |= CPU_TXD;
 P2DIR  |= CPU_TXD;
 P2OUT  &= ~CPU_TXD;
 P2SEL1 |= CPU_RXD;
 P2DIR  &= ~CPU_RXD;


 //P2REN |= SOMI_B; // Enable pullup resistor EXAMPLE
//-----------------------------------------------
}

void Init_Port3(void){
  //------------------------------------------------------------------------------
//Configure Port 3
// X (0x01) //
// Y (0x02) //
// Z (0x04) //
// LCD_BACKLITE (0x08) //
// R_FORWARD (0x10) // LCD Chip Select
// R_REVERSE (0x20) // LCD SA0 H/L Slave Address
// L_FORWARD (0x40) // SPI mode
// L_REVERSE (0x80) // SPI mode

//------------------------------------------------------------------------------
 P3SEL0 = CLEAR_REG; // P1 set as I/0
 P3SEL1 = CLEAR_REG; // P1 set as I/0
 P3DIR = CLEAR_REG; // Set P1 direction to input
 P3OUT = CLEAR_REG;
 P3SEL0 |= X;
 P3SEL1 |= X; //WHAT DIRCTION ARE FUNCTIONS? OUTPUT OR INPUT?
 P3SEL0 |= Y;
 P3SEL1 |= Y; //WHAT DIRCTION ARE FUNCTIONS? OUTPUT OR INPUT?
 P3SEL0 |= ZED;
 P3SEL1 |= ZED; //WHAT DIRCTION ARE FUNCTIONS? OUTPUT OR INPUT?

 P3DIR |= LCD_BACKLITE;
 P3DIR |= R_FORWARD;
 P3DIR |= R_REVERSE;
 P3DIR |= L_FORWARD;
 P3DIR |= L_REVERSE;



}

void Init_Port4(void){
//------------------------------------------------------------------------------
// Configure PORT 4
// Port 4 has only two pins
// Port 4 Pins
// SW1 (0x01) // Switch 1
// SW2 (0x02) // Switch 2
//------------------------------------------------------------------------------
 P4SEL0 = CLEAR_REG; // P4 set as I/0
 P4SEL1 = CLEAR_REG; // P4 set as I/0
 P4DIR = CLEAR_REG; // Set P4 direction to input
 P4OUT = CLEAR_REG;
// SW1
 P4SEL0 &= ~SW1; // SW1 set as I/0 (REDUNDANT)
 P4SEL1 &= ~SW1; // SW1 set as I/0 (REDUNDANT)
 P4OUT |= SW1; // Configure pullup resistor
 P4DIR &= ~SW1; // Direction = input (REDUNDANT)
 P4REN |= SW1; // Enable pullup resistor
 P4IES |= SW1; // SW1 Hi/Lo edge interrupt
// SW2
 P4SEL0 &= ~SW2; // SW2 set as I/0
 P4SEL1 &= ~SW2; // SW2 set as I/0 (REDUNDANT)
 P4OUT |= SW2; // Configure pullup resistor
 P4DIR &= ~SW2; // Direction = input (REDUNDANT)
 P4REN |= SW2; // Enable pullup resistor
 P4IES |= SW2; // SW2 Hi/Lo edge interrupt
//------------------------------------------------------------------------------
}

void Init_PortJ(void){
//------------------------------------------------------------------------------
// Port J Pins
// LED1 (0x01) // LED 5
// LED2 (0x02) // LED 6
// LED3 (0x04) // LED 7
// LED4 (0x08) // LED 8
// XINR (0x10) // XINR
// XOUTR (0x20) // XOUTR
//------------------------------------------------------------------------------
 PJSEL0 = CLEAR_REG; // PJ set as I/0
 PJSEL1 = CLEAR_REG; // PJ set as I/0
 PJDIR = CLEAR_REG; // Set PJ direction to output
 PJSEL0 &= ~LED1;
PJSEL1 &= ~LED1;
PJOUT &= ~LED1;
 PJDIR |= LED1; // Set PJ Pin 1 direction to output
 PJSEL0 &= ~LED2;
 PJSEL1 &= ~LED2;
 PJOUT &= ~LED2;
PJDIR |= LED2; // Set PJ Pin 2 direction to output
 PJSEL0 &= ~LED3;
 PJSEL1 &= ~LED3;
 PJOUT &= ~LED3;
PJDIR |= LED3; // Set PJ Pin 3 direction to output
 PJSEL0 &= ~RESET;
 PJSEL1 &= ~RESET;
 PJDIR |= RESET; // Set P3 Pin 4 direction to output
 PJOUT &= ~RESET;
// XT1 Setup
 PJSEL0 |= XINR;
 PJSEL0 |= XOUTR;
//------------------------------------------------------------------------------
}

void Init_PortJ(void){

  //------------------------------------------------------------------------------
//Port J has 6 pins
//IOT_FACTORY (0x01)
// IOT_WAKEUP (0x02)
// IOT_STA_MINIAP (0x04)
// RESET (0x08)
// XIN (0x10)
// XOUT (0x20)
//------------------------------------------------------------------------------
 PJSEL0 = CLEAR_REG; // P1 set as I/0
 PJSEL1 = CLEAR_REG; // P1 set as I/0
 PJDIR = CLEAR_REG; // Set P1 direction to input

 PJDIR |= IOT_FACTORY;
 PJDIR |= IOT_WAKEUP;
 PJDIR |= IOT_STA_MINIAP;
 PJDIR |= RESET;
//------------------------------------------------------------------------------


} */



