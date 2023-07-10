/**
 ******************************************************************************
 * @file           : spi.h
 * @project        : Agnikul Generic Software Library
 * @brief          : SPI configuration and transfer functions
 * @author         : Shawn N, Sreedhar Mahadevan
 * @version        : v2.0
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) Agnikul Cosmos Private Limited
 * All rights reserved.</center></h2>
 *
 ******************************************************************************
 *
 * Adapted from SPI C Transfer Example, Written by Derek Molloy (www.derekmolloy.ie)
 * for the book Exploring BeagleBone. Based on the spidev_test.c code
 * example at www.kernel.org
 *
 * -----------------------------
 * How to use the SPI functions:
 * -----------------------------
 *
 * 1. Call ConfigureSPI() with the right parameters and obtain File descriptor for SPI
 * 2. Call TransferDataOverSPI() - Initiate SPI transfer with the buffer parameters
 * 3. On successful SPI transfer, consume the received data in SpiMessage structure
 * 4. Call CloseSPI() - Close the SPI file descriptor
 *
 * 	//1. Example code on passing parameters to configure SPI
 * 	unsigned int file = ConfigureSPI(SPI_MODE_0, SPI_8_BITS_PER_WORD, SPI_FREQ_10MHZ);

 * 	// Sample data structure used as a buffer
 * 	datapacket_t SpiMessage;

 * 	while(1)
 * 	{
 * 	    // Clearing the sample data structure before every SPI transfer
 * 		(void) memset (&SpiMessage, 0, sizeof(SpiMessage));
 *
 * 		//2. Example code on How to initiate transfer
 * 		if (TransferDataOverSPI(file, &null, (unsigned char*) &SpiMessage, sizeof(SpiMessage)) == -1)
 * 		{
 * 			perror("\n\rSPI transfer failed");
 * 			return -1;
 * 		}
 *
 * 		//3. Consume the received data in SpiMessage structure
 * 	}
 *
 * 	//4. Close the File-descriptor for SPI
 * 	CloseSPI(file);
 *
 ******************************************************************************
*/

#ifndef SRC_SPI_H_
#define SRC_SPI_H_

/*******************************************************************************
 * Header inclusions
 ******************************************************************************/
#include "fault_handling.h"
#include <stdint.h>

/*******************************************************************************
 * Structures and Enumerations
 ******************************************************************************/


/*******************************************************************************
 * Pre-processor Definitions
 ******************************************************************************/
//!@name DEFINES SPIDEV
//!@{
#define SPI0_1CS_PATH "/dev/spidev0.0"    /**< SPIDEV 0.0 - Raspberry Pi 4B */
#define SPI2_1CS_PATH "/dev/spidev2.0"    /**< SPIDEV 2.0 - NXP LS1028A Board*/

#define SPI_FREQ_1MHZ     1000000            /**< SPI frequency 1 MHz */
#define SPI_FREQ_2_5MHZ   2500000            /**< SPI frequency 2.5 MHz */
#define SPI_FREQ_5MHZ     5000000            /**< SPI frequency 5 MHz */
#define SPI_FREQ_5_5MHZ   5500000            /**< SPI frequency 5.5 MHz */
#define SPI_FREQ_6MHZ     6000000            /**< SPI frequency 6 MHz */
#define SPI_FREQ_10MHZ    10000000           /**< SPI frequency 10 MHz */
#define SPI_FREQ_15MHZ    15000000           /**< SPI frequency 15 MHz */
#define SPI_FREQ_20MHZ    20000000           /**< SPI frequency 20 MHz */

#define SPI_8_BITS_PER_WORD 8             /**< SPI - 8 bits per word */

/* User space versions of kernel symbols for SPI clocking modes,
 * matching <linux/spi/spi.h>
 */
#define SPI_CPHA		0x01
#define SPI_CPOL		0x02

#define SPI_MODE_0		(0|0)
#define SPI_MODE_1		(0|SPI_CPHA)
#define SPI_MODE_2		(SPI_CPOL|0)
#define SPI_MODE_3		(SPI_CPOL|SPI_CPHA)

#define SPI_CS_HIGH		0x04
#define SPI_LSB_FIRST	0x08
#define SPI_3WIRE		0x10
#define SPI_LOOP		0x20
#define SPI_NO_CS		0x40
#define SPI_READY		0x80
//!@}


/*******************************************************************************
 * Function prototypes
 ******************************************************************************/
/**
 * @brief   Function implementation to initiate transfer of data over SPI
 * @details Configuring transfer of data over SPI including both Transmit and
 *          receive buffers for simultaneous action.
 * @param   fd_spi  - File descriptor for SPI device
 * @param   send    - Parameter for transmit buffer
 * @param   receive - Parameter for receive buffer
 * @param   length  - Number of bytes for each transfer
 * @return  FUNC_STATUS - Success / Failure
 *
 * */
FUNC_STATUS TransferDataOverSPI(int fd_spi, unsigned char send[], unsigned char receive[], uint32_t length);

/**
 * @brief   Function implementation to configure parameters for SPI
 * @details Function opens the SPI device, assigns it to a file descriptor and
 *          then takes in SPI parameters and configures it before usage.
 * @param   mode_ip  - SPI mode (SPI_MODE_0 or SPI_MODE_1 or SPI_MODE_2 or SPI_MODE_3)
 * @param   bits_ip  - Parameter for bits per word setting
 * @param   speed_hz - Clock frequency - SPI
 * @return  fd       - File descriptor for SPI dev / Failure
 *
 * */
int ConfigureSPI(uint8_t mode_ip, uint8_t bits_ip, uint32_t speed_hz);


/**
 * @brief   Function implementation to close the SPI file handle
 * @param   fd - File descriptor for SPI to be closed
 * @return  FUNC_STATUS - Success / Failure
 *
 * */
FUNC_STATUS CloseSPI(int fd);


#endif /* SRC_SPI_H_ */
