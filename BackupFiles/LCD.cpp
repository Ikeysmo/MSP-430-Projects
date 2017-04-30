#include  "msp430.h"
#include  "functions.h"
#include  "macros.h"
#include  "LCD.hpp"
//VARIABLES=====================================================================



//FUNCTION_PROTOTYPES===========================================================
//void lcd_init(void);


void LCD::spi_chipselect_idle(void){
    __delay_cycles(600);
    P1OUT |= SPI_CS_LCD;
}

void LCD::spi_chipselect_active(void){
    P1OUT &= ~SPI_CS_LCD;
    __delay_cycles(10);
}

void LCD::spi_reset_idle(void){
    PJOUT |= RESET;
}

void LCD::spi_reset_active(void){
    PJOUT &= ~RESET;
}

void LCD::Init_LCD(void){
    //------------------------------------------------------------------------------
    //  P1OUT |= SPI_CS_LCD;         // P1 SPI_CS_LCD Port Pin set high
    //  P1OUT |= RESET_LCD;          // P1 RESET_LCD Port Pin set low
    //  P3OUT |= LCD_BACKLITE;
    //------------------------------------------------------------------------------
    Init_SPI_B0();  // Initialize SPI Port
    // turn on power
    spi_reset_idle();
    spi_chipselect_idle();

    // delay 1ms
    __delay_cycles(45000);

    // delay 400 ms
    spi_reset_active();
    __delay_cycles(300000);
    spi_reset_idle();
    __delay_cycles(300000);

    // init Display
    WriteIns(0x3A);   //8-Bit data length extension Bit RE=1; REV=0
    WriteIns(0x09);   //4 line display
    WriteIns(0x06);   //Bottom view
    WriteIns(0x1E);   //Bias setting BS1=1
    WriteIns(0x39);   //8-Bit data length extension Bit RE=0; IS=1
    WriteIns(0x1B);   //BS0=1 -> Bias=1/6
    WriteIns(0x6E);       //Devider on and set value
    WriteIns(0x57);       //Booster on and set contrast (BB1=C5, DB0=C4)
    WriteIns(0x7F);       //Set contrast (DB3-DB0=C3-C0)
    WriteIns(0x38);       //8-Bit data length extension Bit RE=0; IS=0
    ClrDisplay();
    DisplayOnOff(DISPLAY_ON);
    __delay_cycles(8000);
    P3OUT |= LCD_BACKLITE;

    display_1 = NULL;
    display_2 = NULL;
    display_3 = NULL;
    display_4 = NULL;
}

void LCD::lcd_4line(void){
    //  0x3A ->Function set: RE = 1
    WriteIns(0x38);   //4 Lines middle
}

void LCD::lcd_BIG_mid(void){
    //  0x3A ->Function set: RE = 1
    WriteIns(0x3A);   //3 Lines middle
    //  0x17 -> 3 Lines middle
    WriteIns(0x17);   //3 Lines middle
    //  0x3C ->Function set: RE = 0, DH = 1
    WriteIns(0x3C);   //3 Lines middle
}

void LCD::setLine(char *s, char line){
    switch(line){
    case 1:
        display_1 = s;
        break;
    case 2:
        display_2 = s;
        break;
    case 3:
        display_3 = s;
        break;
    case 4:
        display_4 = s;
        break;
    default:
        break;
    }
}
void LCD::print(char *s, char line, char position){ // Write a string to the display, using lcd_putc.
    if(s == NULL)
        return;
    WriteIns(line+position);
    while (*s) {
        WriteData(*s++);
    }
}

void LCD::refresh(){
    ClrDisplay();
    print(display_1, LCD_HOME_L1, 0);
    print(display_2, LCD_HOME_L2, 0);
    print(display_3, LCD_HOME_L3, 0);
    print(display_4, LCD_HOME_L4, 0);
}

void LCD::WriteIns(char instruction){
    //-----------------------------------------------------
    // Func: WriteIns(instruction)
    // Desc: sends instruction to display
    //-----------------------------------------------------
    spi_chipselect_active();
    // 0x1F
    CheckBusy();
    SPI_B0_write(START_WR_INSTRUCTION);    // Send 5 synchronization bits, RS = 0, R/W = 0
    SPI_B0_write(instruction & 0x0F);      // Send lower data bits
    SPI_B0_write((instruction>>4) & 0x0F); // Send higher data bits
    spi_chipselect_idle();
}

void LCD::WriteData(char data){
    //-----------------------------------------------------
    //Func: WriteData(data)
    //Desc: sends data to display
    //-----------------------------------------------------
    //0xF5
    spi_chipselect_active();
    SPI_B0_write(START_WR_DATA);       // Send 5 synchronization bits, RS = 1, R/W = 0
    SPI_B0_write(data & 0x0F);             // Send lower data bits
    SPI_B0_write((data>>4) & 0x0F);    // Send higher data bits
    spi_chipselect_idle();
}

unsigned char LCD::CheckBusy(void){
    //-----------------------------------------------------
    //Func: CheckBusy()
    //Desc: checks if display is idle
    //-----------------------------------------------------
    unsigned char readData = 1;
    //do{
    //SPI_put(0x3F);                     //Send 5 synchronization bits, RS = 0, R/W = 1
    //SPI_put(0x00);                     //dummy write to receive data
    //while(ri_u0c1 == 0);               //wait while data is received
    //    readData= ~u0rbl;                  //store data
    //  }while(readData&0x80);               //check for busy flag
    //
    return readData;
}

void LCD::ClrDisplay(void){
    //-----------------------------------------------------
    // Func: ClrDisplay
    // Desc: Clears entire Display content and set home pos
    //-----------------------------------------------------
    WriteIns(0x01);
    SetPostion(0);
    //SetPostion(LINE1);
}

void LCD::SetPostion(char pos){
    //-----------------------------------------------------
    // Func: SetPostion(postion)
    // Desc: set postion
    //-----------------------------------------------------
    WriteIns(LCD_HOME_L1+pos);
}

void LCD::DisplayOnOff(char data){
    //-----------------------------------------------------
    // Func: DisplayOnOff(control)
    // Desc: use definitions of header file to set display
    //-----------------------------------------------------
    WriteIns(0x08+data);
}

//------------------------------------------------------------------------------
//SPI
//------------------------------------------------------------------------------

void LCD::Init_SPI_B0(void){
    //------------------------------------------------------------------------------
    // Reset peripheral
    UCB0CTLW0 = UCSWRST;
    UCB0CTLW0 |= UCSSEL__SMCLK; // SMCLK is clock source
    UCB0CTLW0 |= UCCKPL;        //
    UCB0CTLW0 |= UCMST;         // master mode
    UCB0CTLW0 |= UCSYNC;
    UCB0CTLW0 |= UCMODE_0;
    UCB0CTLW0 &= ~UCMSB;        // master mode, LSB transmitted first

    UCB0BRW = SPI_CLK_PRESCALER;
    // Enable peripheral
    UCB0CTLW0 &= ~UCSWRST;
    // Wait to ensure the peripheral is up
    __delay_cycles(100);
    //------------------------------------------------------------------------------
}

void LCD::SPI_B0_write(char byte){
    //------------------------------------------------------------------------------
    // Writes a byte out of SPIB, assumes CSB already low
    // Wait for TX empty
    while (!(UCB0IFG & UCTXIFG));
    UCB0TXBUF = byte;
    // Wait for TX empty
    while (!(UCB0IFG & UCTXIFG));
    //------------------------------------------------------------------------------
}


