#include "serial_IOT.hpp"
#include "msp430.h"
#include "macros.h"
#define SMALL_RING_SIZE 128
// IOT
//----------------------------------------------------------------------------

volatile bool Serial_IOT::txready = true;
volatile bool Serial_IOT::RXFULL;
volatile char Serial_IOT::usb_rx_ring_wr = BEGINNING;
volatile char Serial_IOT::usb_rx_ring_rd;
volatile char Serial_IOT::usb_tx_ring_wr;
volatile char Serial_IOT::usb_tx_ring_rd;
volatile char Serial_IOT::USB_Char_Rx[SMALL_RING_SIZE] ;
volatile char Serial_IOT::USB_Char_Tx[SMALL_RING_SIZE] ;

using namespace std;
// USB
//----------------------------------------------------------------------------
void Serial_IOT::Init_Serial(int baud_rate){
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

        UCA1CTLW0 = CLEAR; // Use word register
        UCA1CTLW0 |= UCSWRST; // Set Software reset enable
        UCA1CTLW0 |= UCSSEL__SMCLK; // Set SMCLK as fBRCLK


        switch(baud_rate){
        case b9600:
            UCA1BRW = 52;
            UCA1MCTLW = 0x4911;
            break;
        case b115200:
            UCA1BRW = 4;
            UCA1MCTLW = 0x5551; //0x5518?
            break;
        }
    UCA1CTL1 &= ~UCSWRST; // Release from reset
    UCA1IE |= UCRXIE; // Enable RX interrupt
    UCA1IE |= UCTXIE;
    //USB_flag = OFF; // global flag, gets turned on when first char is received from putty
}

char Serial_IOT::incrementBuffer(char num, char size){
    if(++num >= size ){
        return 0;
    }
    else
        return num;
}

char Serial_IOT::receive_char(void){ //should only be called after seeing if available!!!
    char rd = usb_rx_ring_rd;
    usb_rx_ring_rd = incrementBuffer(usb_rx_ring_rd, rxbufsize); //go ahead and increment
    //if(usb_rx_ring_rd == usb_rx_ring_wr) //if equal after incrementing, then empty!
        //RXFULL = false; //it is empty!
    RXFULL = false;
    return USB_Char_Rx[rd];
}

char Serial_IOT::isAvailable(){ //check to see if full
    if((usb_rx_ring_rd == usb_rx_ring_wr) && !RXFULL) //only condition where not available
        return false;
    else
        return true;
}

void Serial_IOT::send_char(char send){ //should send characters from streamming buffer ideally
    UCA1TXBUF = send;
}


void Serial_IOT::send_array(char* str){
    if(!str)
        return;
    while(*str){
        UCA1TXBUF = *str;
        txready = false;
        while(!txready){;}
        str++;
    }
}

// IoT
//------------------------------------------------------------------------------
extern volatile char d;
 #pragma vector = USCI_A1_VECTOR
__interrupt void Serial_IOT::USB_ISR(void){
 unsigned int temp, temp1;
 switch(__even_in_range(UCA1IV,0x08)){
 case 0: // Vector 0 - no interrupt
 break;
 case 2: // Vector 2 - RXIFG
   temp = usb_rx_ring_wr;
   USB_Char_Rx[temp] = UCA1RXBUF; // RX -> USB_Char_Rx character
   //UCA0TXBUF = UCA1RXBUF;
//   if (UCA0RXBUF == LF){
//     the_end = ON;
//     USB_Char_Rx[temp] = CLEAR;
//   }
   //SerialRx_available = ON;
   if (++usb_rx_ring_wr >= (SMALL_RING_SIZE)){
   usb_rx_ring_wr = BEGINNING; // Circular buffer back to beginning
   }
   break;
 case 4: // Vector 4 – TXIFG
     txready = true;
//   temp1 = usb_tx_ring_wr;
//   UCA1TXBUF = USB_Char_Tx[temp1];
//   if (++usb_tx_ring_wr >= (SMALL_RING_SIZE)){
//     usb_tx_ring_wr = BEGINNING;
//   }
 break;
 default: break;
 }
}
//------------------------------------------------------------------------------




