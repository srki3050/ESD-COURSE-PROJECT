/*
 * sd_card.h
 *
 *  Created on: Apr 29, 2022
 *      Author: unnia
 */

#ifndef SRC_SD_CARD_H_
#define SRC_SD_CARD_H_

#include "fatfs/ff.h"
#include <Hardware/TIMERA_Driver.h>
#include <fatfs/diskio.h>

void sd_card_init(char* startup_buff);

#endif /* SRC_SD_CARD_H_ */
