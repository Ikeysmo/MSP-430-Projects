/*
 * macros.h
 *
 *  Created on: Jan 5, 2017
 *      Author: Isaiah
 */

#ifndef MACROS_H_
#define MACROS_H_



//******************************************************************************
//
//  Description: This file contains the Main Routine - "While" Operating System
//
//
//  Isaiah Smoak
//  Sep 2015
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//******************************************************************************

// Required defines
// In the event the universe no longer exists, this bit will reset
#define ALWAYS                  (1)
#define CNTL_STATE_INDEX        (3) // Control States
#define SW1                  (0x01) // Switch 1
#define SW2                  (0x02) // Switch 2
#define CNTL_STATE_INDEX        (3)
#define display_line_size       (16)
#define INITIAL_TIME            (0)
#define DELAY                  (50)
#define fourth_digit           (1000)
#define third_digit            (100)
#define second_digit           (10)
#define thrd_digit              (99)
#define secs_digit              (9)
#define I0                      (0)
#define I1                      (1)
#define I2                      (2)
#define I3                      (3)
#define I4                      (4)
#define I5                      (5)
#define I6                      (6)
#define max_hex_length          (6)
#define black_default           (700)
#define START                   (1)
#define msec_50                 (10)
#define msec_250             (50)
#define msec_500             (100)
#define msec_750             (150)
#define msec_1000            (200)
#define msec_1250           (250)
#define msec_2000               (400)
#define msec_2500               (500)
#define TRUE                   (1)
#define FALSE                  (0)
#define L1position              (3)
#define L2position              (1)
#define L3position               (2)
#define L4position               (1)
#define SIZE_COUNT_INIT          (0)
#define SIZE_COUNT_MAX            (5)
#define LCDMAX_CHAR               (11)
#define clear_display           (0)
#define RESET_STATE             (0x0000)
#define    GIO  (0x00)
#define    OUTP (0x00)
#define L1new                   (1)
#define L2new                   (2)
#define L3new                   (3)
#define L4new                   (1)
//Configure Port 1
#define V_DETECT_R (0x01) //
#define V_DETECT_L (0x02) //
#define IR_LED (0x04) //
#define V_THUMB (0x08) //
#define SPI_CS_LCD (0x10) // LCD Chip Select
#define SA0_LCD (0x20) // LCD SA0 H/L Slave Address
#define SPI_SIMO (0x40)
#define SPI_SOMI (0x80)
/*#define SIMO_B (0x40) // SPI mode
//- slave in/master out of USCI_B0
#define SOMI_B (0x80) // SPI mode
//- slave out/master in of USCI_B0*/

#define SMALL_RING_SIZE        (16)
#define LARGE_RING_SIZE         (64)
#define ON                      (1)
#define OFF                     (0)
#define LF                      (10)
#define BEGINNING               (0)
#define CLEAR                   (0)

//Configure Port 2
#define USB_TXD (0x01)
#define USB_RXD (0x02)
#define SPI_SCK (0x04)
#define UNKNOWN (0x08)
#define UNKNOWN1 (0x10) //
#define CPU_TXD (0x20) //
#define CPU_RXD (0x40) //
#define UNKNOWN2 (0x80) //
#define CLEAR_REG (0x00)

//Configure Port 3
#define X (0x01)
#define Y (0x02)
#define ZED (0x04)
#define LCD_BACKLITE (0x08)
#define R_FORWARD (0x10)
#define R_REVERSE (0x20)
#define L_FORWARD (0x40)
#define L_REVERSE (0x80)

//Configure Port 4
// Port 4 has only two pins
// Port 4 Pins
#define SW1 (0x01) // Switch 1
#define SW2 (0x02) // Switch 2


//Configure Port J
//Port J has 6 pins
#define IOT_FACTORY (0x01)
#define IOT_WAKEUP (0x02)
#define IOT_STA_MINIAP (0x04)
#define RESET (0x08)
#define XINR (0x10)
#define XOUTR (0x20)
#define LED1 (0x01) // LED 5
#define LED2 (0x02) // LED 6
#define LED3 (0x04) // LED 7
#define LED4 (0x08) // LED 8
#define NULL (0x00)

#define I7              7
#define I8              8
#define I10             10
#define I11             11
#define I12             12
#define I14             14
#define I16             16
#define I17             17
#define I100            100
#define PAUSE           500
#define SW1 (0x01) // Switch 1
#define SW2 (0x02) // Switch 2

#define DEBOUNCETIME 2500 //gamble on this

#define L0      0
#define L1      0
#define L2      0
#define L3      0




// LCD
#define LCD_HOME_L1           0x80
#define LCD_HOME_L2             0xA0
#define LCD_HOME_L3             0xC0
#define LCD_HOME_L4             0xE0
#define CSLOCK               (0x01) // Any incorrect password locks registers


#define TA0CCR0_INTERVAL    (12500)      // 10 ms timer
#define TA0CCR1_INTERVAL    (25000)      // 5 ms timer
#define TA0CCR2_INTERVAL    (50000)      // 10 ms timer








/*this is stuff from the old macros!
// Required defines
// In the event the universe no longer exists, this bit will reset
#define ALWAYS                  (1)
#define LED1                 (0x01) // LED 1
#define BLINK_LED            (0x01) // Allow LED to Blink
#define CNTL_STATE_INDEX        (3) // Control States
#define LCD_LINE_1           (0x80) // Position Cursor at Character 01 of Line 1
#define LCD_LINE_2           (0xC0) // Position Cursor at Character 01 of Line 2
#define GPS_ONOFF            (0x08) //
#define USE_LED5             (0x40)  //
#define USE_SMCLK            (0x00)  //
#define USE_NFETS            (0xA0)  //
#define CLEAR_DISPLAY        (0x01)


// Display Modes
#define ORIGINAL             (0x00) //



end
*/


#endif /* MACROS_H_ */
