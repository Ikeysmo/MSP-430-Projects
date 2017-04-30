/*
 * functions.h
 *
 *  Created on: Jan 5, 2017
 *      Author: Isaiah
 */

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

// Function prototypes main

void main(void);
void Init_Conditions(void);
void Switches_Process(void);
void Init_Timers(void);
void Init_LEDs(void);
extern "C"{
void intToNum(char buff[], unsigned int num); }
void Init_ADC(void);
void menuState();
void tempState();
// Function prototypes clocks
void Init_Clocks(void);
void five_msec_sleep(unsigned int fivemsec);
void Five_msec_Delay(int times);

// Function prototypes systems
void enable_interrupts(void);

// Function prototypes
__interrupt void Timer2_B0_ISR(void);
 __interrupt void TIMER2_B1_ISR(void);
void Init_Timer_B2(void);
void Init_Timer_A0(void);
void measure_delay(void);
void usleep10(unsigned int usec);

// Function prototypes ports
void Init_Ports(void);
void Init_Port1(void);
void Init_Port2(void);
void Init_Port3(void);
void Init_Port4(void);
void Init_PortJ(void);


// SPI
void Init_SPI_B0(void);
void SPI_B0_write(char byte);

// Switches
void Init_Switches(void);
void switch_control(void);
void enable_switch_SW1(void);
void enable_switch_SW2(void);
void disable_switch_SW1(void);
void disable_switch_SW2(void);
void Switches_Process(void);


// Project 5

//ADC
void Init_ADC(void);
void ADC_Process(void);

// UART - Universal Asynchronous Receiver/Transmitter
void Init_Serial_UCA1(int baud_rate);
void Init_Serial_UCA0(int baud_rate);


// IoT Serial Communication
void send_array(char str[]);
void clear_buffer(void);
void send_char(char send);
char receive_char(void);
void receive_array(int num);
void get_IP_address(void);
void get_the_SSID(void);
void parse_command(void);

// USB Serial Communication
void send_arrayUSB(char str[]);
void clear_bufferUSB(void);
void send_charUSB(char send);
char receive_charUSB(void);
void receive_arrayUSB(int num);
void call_commands(char command);




#endif /* FUNCTIONS_H_ */
