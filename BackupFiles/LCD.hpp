/*
 * LCD.hpp
 *
 *  Created on: Jan 8, 2017
 *      Author: Isaiah
 */

#ifndef LCD_HPP_
#define LCD_HPP_

/*
 * LCD.cpp
 *
 *  Created on: Jan 5, 2017
 *      Author: Isaiah
 */

//------------------------------------------------------------------------------
//
//  Description: This file contains the LCD Routine -
//
//
//  Jim Carlson
//  Aug 2013
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//0x3F for read     00111111
//0x5F  equal 01011111
#define DISPLAY_ON (4) //used to be 0x04
#define START_WR_INSTRUCTION (0x1F) //RS = 0, R/W = 0
#define START_WR_DATA       (0x5F) //RS =1   , R/W = 0
// With 8MHz SMCLK, this makes the SPI clock 100kHz.
#define SPI_CLK_PRESCALER      (80)

class LCD{
public:
    char *display_1;
    char *display_2;
    char *display_3;
    char *display_4;
    bool bigMode;
    void Init_LCD(void);
    void lcd_4line(void);
    void lcd_BIG_mid(void);
    void setLine(char *s, char line);
    void print(char *s, char line, char position);
    void ClrDisplay(void);
    void DisplayOnOff(char data);
    void refresh();
private:
    unsigned char display_mode;
    //volatile unsigned char SPI_Char;
    //extern volatile unsigned char current_character;
    //unsigned char lcd_control;
    char display_line_1[11];
    char display_line_2[11];
    char display_line_3[11];
    char display_line_4[11];
    char current_line;
    volatile unsigned int update_display_count;
    volatile unsigned int display_update_time;

    void spi_chipselect_idle(void);
    void spi_chipselect_active(void);
    void spi_reset_idle(void);
    void spi_reset_active(void);
    void Init_SPI_B0(void);
    void SPI_B0_write(char byte);
    void WriteIns(char instruction);
    void WriteData(char data);
    void SetPostion(char pos);
    unsigned char CheckBusy(void);
};

LCD lcd;

#endif /* LCD_HPP_ */
