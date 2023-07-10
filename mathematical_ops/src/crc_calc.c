/**
 ******************************************************************************
 * @file           : crc_calc.c
 * @project        : Agnikul Generic Software Library
 * @brief          : Cyclic Redundancy Check functions
 * @author         : Sreedhar Mahadevan
 * @version        : v1.0
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) Agnikul Cosmos Private Limited
 * All rights reserved.</center></h2>
 *
 ******************************************************************************
 */

/*******************************************************************************
 * Header inclusions
 ******************************************************************************/
#include <stdio.h>
#include <stdint.h>
#include "crc_calc.h"

/*******************************************************************************
 * Function definitions
 ******************************************************************************/
/**
 * @brief Calculating CRC-32 for the passed input byte stream
 * @param uint16_t len - Length of input byte stream
 * @param unsigned char *data - Pointer to input byte stream
 * @return uint32_t - Calculated CRC32 value
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
uint32_t crc32_calc(uint16_t len, unsigned char *data)
{
	/**<Check for null pointer*/
	if(data == NULL){
		PRINT_ERR("NULL pointer detected!\n");
		return FAILURE;
	}

	/**<Check for 0 value of len*/
	if(len <= 0){
		PRINT_ERR("Invalid parameter!\n");
		return FAILURE;
	}

	unsigned char *buffer = (unsigned char*) data;
	int32_t crc = -1;

	while( len-- )
	{
		crc = crc ^ (*buffer++ << 24);
		for( int bit = 0; bit < 8; bit++ )
		{
			if( crc & (1L << 31)) crc = (crc << 1) ^ CRC_POLY;
			else                  crc = (crc << 1);
		}
	}
	return (uint32_t)crc;
}
