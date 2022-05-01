/*
 * @Name: Sricharan Kidambi
 * @Compiler: CCSTUDIO — Code Composer Studio™ integrated development environment (IDE) version: 11.2.0.00007
 * @Date: 04/20/2022
 * @FileName: sd_card.c
 * @Description: SD card driver code
 * @Brief: This file has functions that can
 *          1) Intialise sd card adapter functionality - sd_card_init
 *
 * @References:
 *           http://elm-chan.org/fsw/ff/00index_e.html
 *           GitHub - howlanjo/test: Working SD card software for MSP432
 *           GitHub - amartinezacosta/MSP432-SD_Card: MSP432 interface to a SD Card
 */

#ifndef SRC_SD_CARD_H_
#define SRC_SD_CARD_H_



/*
 * Header files
 */
#include "fatfs/ff.h"
#include <Hardware/TIMERA_Driver.h>
#include <fatfs/diskio.h>



/*
 * initialize timer A for sd card functionality
 * mount sd card
 * open file "start.txt" for read and write operations
 * declare file pointer
 * write data with f_puts()
 * close file
 * @params:
 *      None
 * @returns:
 *      None
 */
void sd_card_init(char* startup_buff);

#endif /* SRC_SD_CARD_H_ */
