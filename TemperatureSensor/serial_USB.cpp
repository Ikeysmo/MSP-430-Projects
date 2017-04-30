/*
 * serial_USB.cpp
 *
 *  Created on: Jan 14, 2017
 *      Author: Isaiah
 */

#include "msp430.h"
#include "serial_USB.hpp"
#include "macros.h"

volatile bool Serial_USB::txready = true;
volatile bool Serial_USB::RXFULL;
volatile char Serial_USB::usb_rx_ring_wr = BEGINNING;
volatile char Serial_USB::usb_rx_ring_rd;
volatile char Serial_USB::usb_tx_ring_wr;
volatile char Serial_USB::usb_tx_ring_rd;
volatile char Serial_USB::USB_Char_Rx[SMALL_RING_SIZE] ;
volatile char Serial_USB::USB_Char_Tx[SMALL_RING_SIZE] ;

using namespace std;
// USB
//----------------------------------------------------------------------------
void Serial_USB::Init_Serial(int baud_rate){
    int i;
    for(i=0; i<SMALL_RING_SIZE; i++){
        //volatile char Serial_USB::USB_Char_Rx[i] = CLEAR; // USB Rx Buffer
    }
    usb_rx_ring_wr = BEGINNING;
    usb_rx_ring_rd = BEGINNING;

    for(i=I0; i<txbufsize; i++){ // May not use this
        USB_Char_Tx[i] = CLEAR; // USB Tx Buffer
    }

    usb_tx_ring_wr = BEGINNING;
    usb_tx_ring_rd = BEGINNING;

    UCA0CTLW0 = CLEAR; // Use word register
    UCA0CTLW0 |= UCSWRST; // Set Software reset enable
    UCA0CTLW0 |= UCSSEL__SMCLK; // Set SMCLK as fBRCLK


    switch(baud_rate){
    case b9600:
        UCA0BRW = 52;
        UCA0MCTLW = 0x4911;
        break;
    case b115200:
        UCA0BRW = 4;
        UCA0MCTLW = 0xEE18; //0x5518?
        break;
    }

    UCA0CTL1 &= ~UCSWRST; // Release from reset
    UCA0IE |= UCRXIE; // Enable RX interrupt
    UCA0IE |= UCTXIE;
    //USB_flag = OFF; // global flag, gets turned on when first char is received from putty
}

char Serial_USB::incrementBuffer(char num, char size){
    if(++num >= size ){
        return 0;
    }
    else
        return num;
}
char Serial_USB::receive_char(void){ //should only be called after seeing if available!!!
    char rd = usb_rx_ring_rd;
    usb_rx_ring_rd = incrementBuffer(usb_rx_ring_rd, rxbufsize); //go ahead and increment
    //if(usb_rx_ring_rd == usb_rx_ring_wr) //if equal after incrementing, then empty!
        //RXFULL = false; //it is empty!
    RXFULL = false;
    return USB_Char_Rx[rd];
}

char Serial_USB::isAvailable(){ //check to see if full
    if((usb_rx_ring_rd == usb_rx_ring_wr) && !RXFULL) //only condition where not available
        return false;
    else
        return true;
}

void Serial_USB::send_char(char send){ //should send characters from streamming buffer ideally
    UCA0TXBUF = send;
}


void Serial_USB::send_array(char* str){
    if(!str)
        return;
    while(*str){
        UCA0TXBUF = *str;
        txready = false;
        while(!txready){;}
        str++;
    }
}







// USB
//------------------------------------------------------------------------------
#pragma vector = USCI_A0_VECTOR
__interrupt void Serial_USB::USB_ISR(void){
    char temp, temp1;
    switch(__even_in_range(UCA0IV,0x08)){
    case 0: // Vector 0 - no interrupt
        break;
    case 2: // Vector 2 - RXIFG
        UCA1TXBUF = UCA0RXBUF;
//        if(RXFULL) //my buffer do not override
//            return;
//        temp = usb_rx_ring_wr;
//        USB_Char_Rx[temp] = UCA0RXBUF; // RX -> USB_Char_Rx character
//        if(++usb_rx_ring_wr >= rxbufsize)
//            usb_rx_ring_wr = 0;
//        if(usb_rx_ring_wr == usb_rx_ring_rd) //if this is true, then full
//            RXFULL = true;

        //   if (UCA0RXBUF == LF){
        //     the_end0 = ON;
        //     USB_Char_Rx[temp] = CLEAR;
        //   }
        //SerialRx_available = ON;
        break;
    case 4:
        txready = true;
        // Vector 4 – TXIFG
        //temp1 = usb_tx_ring_wr;
        //UCA0TXBUF = USB_Char_Tx[temp1]; // USB0_Char_Tx
        //if (++usb_tx_ring_wr >= (SMALL_RING_SIZE)){
        //usb_tx_ring_wr = BEGINNING;
        //}
        //UCA0TXBUF = 'P';
        break;
    default: break;
    }
}
//------------------------------------------------------------------------------

