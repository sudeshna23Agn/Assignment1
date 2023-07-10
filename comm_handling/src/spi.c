/**
 ******************************************************************************
 * @file           : spi.c
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

/*******************************************************************************
 * Header inclusions
 ******************************************************************************/
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdint.h>
#include <linux/spi/spidev.h>
#include <string.h>
#include "spi.h"
#include "common.h"

/*******************************************************************************
 * Global Variables
 ******************************************************************************/

/**<Default values*/
static uint8_t bits = 8, mode = SPI_MODE_0;      /**< 8-bits per word, SPI mode 0 */
static uint32_t speed = SPI_FREQ_1MHZ;           /**< Default Speed is 1 MHz */

/*******************************************************************************
 * Function definitions
 ******************************************************************************/
/**
 * @brief   Function implementation to initiate transfer of data over SPI
 * @details Configuring transfer of data over SPI including both Transmit and
 *          receive buffers for simultaneous action.
 * @param   fd_spi  - File descriptor for SPI device
 * @param   send    - Parameter for transmit buffer
 * @param   receive - Parameter for receive buffer
 * @param   length  - Number of bytes for each transfer
 * @return  FUNC_STATUS - Failure case of IOCTL call
 *
 * */
FUNC_STATUS TransferDataOverSPI(int fd_spi, unsigned char send[],
			unsigned char receive[], uint32_t length)
{
	struct spi_ioc_transfer transfer;              /**<the transfer structure*/

	(void) memset (&transfer, 0, sizeof(transfer));

	transfer.tx_buf        = (unsigned long) send;    /**<the buffer for sending data*/
	transfer.rx_buf        = (unsigned long) receive; /**<the buffer for receiving data*/
	transfer.len           = length;                  /**<the length of buffer*/
	transfer.speed_hz      = speed;                   /**<the speed in Hz*/
	transfer.bits_per_word = bits;                    /**<bits per word*/
	transfer.delay_usecs   = 0;                       /**<delay in us*/
	transfer.cs_change     = 0;						  /**<Keep CS low after sending*/

	/**<send the SPI message (all of the above fields, inc. buffers)*/
	int status = ioctl(fd_spi, SPI_IOC_MESSAGE(1), &transfer);
	if (status < 0) {
		//perror("SPI: SPI_IOC_MESSAGE Failed");
		PRINT_ERR();
		return FAILURE;
	}

	return SUCCESS;
}

/**
 * @brief   Function implementation to configure parameters for SPI
 * @details Function opens the SPI device, assigns it to a file descriptor and
 *          then takes in SPI parameters and configures it before usage.
 * @param   mode_ip  - SPI mode (SPI_MODE_0 or SPI_MODE_1 or SPI_MODE_2 or SPI_MODE_3)
 * @param   bits_ip  - Parameter for bits per word setting
 * @param   speed_hz - Clock frequency - SPI
 * @return  fd       - File descriptor for SPI dev
 *
 * */
int ConfigureSPI(uint8_t mode_ip, uint8_t bits_ip, uint32_t speed_hz)
{
	int fd;

	/**<Modifying SPI configuration parameters based on inputs*/
	mode   = mode_ip;
	bits   = bits_ip;
	speed  = speed_hz;

	// The following calls set up the SPI bus properties
    /**<Open the serial port*/
#ifdef NXP_LS1028
	if ((fd = open(SPI2_1CS_PATH, O_RDWR))<0)
#elif RASPBERRYPI_4B
	if ((fd = open(SPI0_1CS_PATH, O_RDWR))<0)
#endif
	{
		//perror("SPI Error: Can't open device.");
		PRINT_ERR();
		return FAILURE;
	}

	printf("SPI Mode before IOCTL setups is: %d\n\r", mode);
	/**<SPI placed in WR Mode*/
	if (ioctl(fd, SPI_IOC_WR_MODE, &mode)==-1){
		//perror("SPI: Can't get SPI mode.");
		PRINT_ERR();
		return FAILURE;
	}

	/**<SPI also placed in RD Mode*/
	if (ioctl(fd, SPI_IOC_RD_MODE, &mode)==-1){
		//perror("SPI: Can't set SPI mode.");
		PRINT_ERR();
		return FAILURE;
	}

	/**<SPI write bits per word set*/
	if (ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits)==-1){
		//perror("SPI: Can't set bits per word.");
		PRINT_ERR();
		return FAILURE;
	}

	/**<SPI read bits per word set*/
	if (ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &bits)==-1){
		//perror("SPI: Can't get bits per word.");
		PRINT_ERR();
		return FAILURE;
	}

	/**<SPI write max speed set*/
	if (ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed)==-1){
		//perror("SPI: Can't set max speed HZ");
		PRINT_ERR();
		return FAILURE;
	}

	/**<SPI read max speed set*/
	if (ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed)==-1){
		//perror("SPI: Can't get max speed HZ.");
		PRINT_ERR();
		return FAILURE;
	}

	/**<Check that the properties have been set*/
	printf("SPI Mode is: %d\n", mode);
	printf("SPI Bits is: %d\n", bits);
	printf("SPI Speed is: %0.2f MHz\n", speed/(double)1000000.0f);

	return fd;
}

/**
 * @brief   Function implementation to close the SPI file handle
 * @param   fd - File descriptor for SPI to be closed
 * @return  FUNC_STATUS - SUCCESS/FAILURE
 *
 * */
FUNC_STATUS CloseSPI(int fd)
{
	/**<close the file*/
	if(close(fd) < 0){
		PRINT_ERR();
		return FAILURE;
	}
	return SUCCESS;
}
