/**
 ******************************************************************************
 * @file		   : uart.h
 * @project        : Agnikul Generic Software Library
 * @brief		   : UART configuration and functionalities for send and receive.
 * @author		   : Sreedhar Mahadevan, Shawn Nagar
 * @version		   : v2.0
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) Agnikul Cosmos Private Limited
 * All rights reserved.</center></h2>
 *
 ******************************************************************************
*/

#ifndef UART_H_
#define UART_H_

/* Standard includes */
#include "stdint.h"
#include <termios.h> // Contains POSIX terminal control definitions
#include "common.h"
#include "fault_handling.h"

//!@name DEFINES UART
//!@{
/** Preprocessor defines for the right UART port based on the
 * target used (Raspberry Pi or NXP LS1028). Selected based on
 * choice of hardware, specified at the Makefile */
#define UART_PORT_RPI 	"/dev/ttyAMA1"
#define UART_PORT1_NXP 	"/dev/ttyS0"
#define UART_PORT2_NXP	"/dev/ttyS1"
//!@}

/**
 * Routine to open serial port, set the necessary configurations
 * and return the file id
 * @param    speed_t - uart_baud - Baud rate. Refer termios.h for valid values
 * @param	 path_name - Path to serial port to open
 * @return    file-id of the Serial port opened
 * \todo Add additional check and assign default baud rate if wrong parameter is sent
 * */
int OpenSerialPort(const char* path_name, speed_t uart_baud);

/**
 * Routine to close the specified serial port
 * @param	serial_port - Serial port ID
 * @return	FUNC_STATUS - Success / Failure
 * */
FUNC_STATUS CloseSerialPort(int serial_port);

/**
 * @brief	Transmit data through UART
 * @param	int - serial port to use
 * @param   uint8_t* - pointer to transmit-data buffer
 * @param   uint16_t - number of bytes to be transmitted
 * @return  ssize_t - Num of bytes written or -1
 * */
ssize_t SendDataOverUART(int serial_port, uint8_t* transmit_data, uint16_t tx_msg_size);

/**
 * @brief 	Receive single byte through UART.
 * @details
 * @param	int - serial port to use
 * @param   uint8_t* - pointer to byte to store data
 * @return	ssize_t - 1 on success, -1 on failure
 * */
ssize_t ReceiveValOverUART(int, uint8_t*);

/**
 * @brief 	Receive data through UART. Non-blocking by default
 * @details
 * @param	int - serial port to use
 * @param   uint8_t* - pointer to buffer to store data in
 * @param   uint16_t - Max number of bytes expected
 * @return	ssize_t - Number of bytes read or FAILURE
 * */
ssize_t ReceiveDataOverUART(int serial_port, uint8_t* data_uart_rx, uint16_t Max_rx_msg_size);


#endif /* UART_H_ */
