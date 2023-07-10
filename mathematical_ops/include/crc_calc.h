/**
 ******************************************************************************
 * @file           : crc_calc.h
 * @project        : Agnikul Generic Software Library
 * @brief          : Cyclic Redundancy Check header
 * @author         : Shawn N, Sreedhar Mahadevan
 * @version        : v2.0
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) Agnikul Cosmos Private Limited
 * All rights reserved.</center></h2>
 *
 * How to use (Sample code):
 * -----------
 * {
 *      #define CRC_BUFFER_SIZE 20  // Local implementation
 * 	uint32_t calculated_CRC;    // Local implementation
 * 	uint8_t buffer_CRC[CRC_BUFFER_SIZE] = {0x21, 0x00, 0x02, 0x00, 0x03, 0x04, 
 *                                             0x05, 0x06, 0x07, 0x08, 0x11, 0x10, 
 *                                             0x12, 0x10, 0x13, 0x14, 0x15, 0x16, 
 *                                             0x17, 0x18}; // Local implementation

 * 	calculated_CRC = crc32_calc(CRC_BUFFER_SIZE, buffer_CRC); //Function call of interest
 * 	printf("\n\nCalculated CRC: %x \n", calculated_CRC);
 * }
 * 
 * Expected output:
 * ----------------
 * Calculated CRC: 8964776b
 * 
 ******************************************************************************
*/

#ifndef INC_CRC_CALC_H_
#define INC_CRC_CALC_H_

#include "fault_handling.h"

/*******************************************************************************
 * Preprocessor definitions
 ******************************************************************************/
#define CRC_POLY 				0x04C11DB7

/*******************************************************************************
 * Function prototypes
 ******************************************************************************/
/**
 * @brief Calculating CRC-32 for the passed input byte stream
 * @param uint16_t len - Length of input byte stream
 * @param unsigned char *data - Pointer to input byte stream
 * @return uint32_t - Calculated CRC32 value or FAILURE on failure
 * */
/*
 * Polynomial used: <X^32 + X^26 + X^23 + X^22 + X^16 + X^12 + X^11 + X^10 +
 * X^8 + X^7 + X^5 + X^4 + X^2+ X +1> = 0x04C11DB7U
 * Default CRC Init value    - 0xFFFFFFFFU
 * CRC INPUTDATA_INVERSION   - Not done
 * CRC OUTPUTDATA_INVERSION  - Not done
 * Final output XOR          - Not done
 *
 * The following code is a variant of the CRC implementation available
 * in the following link:
 * https://github.com/Michaelangel007/crc32/blob/master/src/crc32.cpp
 *
 * Refer the same link for a detailed explanation on CRC reverse and
 * forward polynomials.
 *
 * The following link is an online CRC calculator and can be used for validation
 * http://www.sunshine2k.de/coding/javascript/crc/crc_js.html
 *
 */
uint32_t crc32_calc(uint16_t len, unsigned char *data);


#endif /* INC_CRC_CALC_H_ */
