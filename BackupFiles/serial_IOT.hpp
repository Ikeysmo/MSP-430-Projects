/*
 * serial_IOT.hpp
 *
 *  Created on: Jan 14, 2017
 *      Author: Isaiah
 */

#ifndef SERIAL_IOT_HPP_
#define SERIAL_IOT_HPP_

#define SMALL_RING_SIZE 128
#define b9600 96
#define b115200 115

class Serial_IOT{
public:
    void Init_Serial(int baud_rate);
    void send_array(char* str);
    void clear_buffer(void);
    void send_char(char send);
    char receive_char(void);
    void receive_array(char buff[], int num);
    char isAvailable(void);
private:
    static volatile bool txready;
    static volatile bool RXFULL;
    char incrementBuffer(char num, char size);
    static const char rxbufsize = 128;
    static const char txbufsize = 16;
    static volatile char usb_rx_ring_wr;
    static volatile char usb_rx_ring_rd;
    static volatile char usb_tx_ring_wr;
    static volatile char usb_tx_ring_rd;
    static volatile char USB_Char_Rx[SMALL_RING_SIZE] ;
    static volatile char USB_Char_Tx[SMALL_RING_SIZE] ;
    static __interrupt void USB_ISR(void);

};
Serial_IOT serial_IOT;


#endif /* SERIAL_IOT_HPP_ */
