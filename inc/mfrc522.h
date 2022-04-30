/*
 * @Name: Abijith
 * @Compiler: CCSTUDIO — Code Composer Studio™ integrated development environment (IDE) version: 11.2.0.00007
 * @Date: 04/20/2022
 * @FileName: mfrc522.c
 * @Description: MFRC522 driver code
 * @Brief: This file has functions that can
 *          1) Send one byte data via SPI - SPI_SendByte(uint8_t data)
 *          2) Write data to register by specifying address of register - SPI_WriteRegister(uint8_t address, uint8_t value)
 *          3) Read from register at specified address - SPI_ReadRegister(uint8_t address)
 *          4) Write RFID data to the specified address - MFRC522_WriteRegister(uint8_t addr, uint8_t val)
 *          5) Read RFID data from specified register address - MFRC522_ReadRegister(uint8_t addr)
 *          6) Initialize mrfc522 module - MFRC522_Init(void)
 *          7) Checks if card has been read or not - MFRC522_Check(uint8_t* id)
 *          8) return MI_OK if user's scanned RFID is same as predefined RFID - MFRC522_Compare(uint8_t* CardID, uint8_t* CompareID)
 *          9) to mask the register - MFRC522_SetBitMask(uint8_t reg, uint8_t mask)
 *          10) to clear the bit mask - MFRC522_ClearBitMask(uint8_t reg, uint8_t mask)
 *          11) to switch on the reader - MFRC522_AntennaOn(void)
 *          12) to switch off the reader - MFRC522_AntennaOff(void)
 *          13) to reset the reader - MFRC522_Reset(void)
 *          14) request for rfid from scanned card - MFRC522_Request(uint8_t reqMode, uint8_t* TagType)
 *          15) read RFID value from card - MFRC522_ToCard
 *          16) To avoid repeated scanning of same card - MFRC522_Anticoll(uint8_t* serNum)
 *          17) Error checking for received data - MFRC522_CalculateCRC(uint8_t*  pIndata, uint8_t len, uint8_t* pOutData)
 *          18) Stop read operation after getting RFID value from card - MFRC522_Halt(void)
 *
 * Mifare MFRC522 RFID Card reader
 * It works on 13.56 MHz.
 *
 * This library uses SPI for driving MFRC255 chip.
 * MF RC522 Default pin out
 *
 *      MFRC522     STM32F1XX   DESCRIPTION
 *      CS(SDA)     P5.0        Chip select for SPI
 *      SCK         P1.5        Serial Clock for SPI
 *      MISO        P1.7        Master In Slave Out for SPI
 *      MOSI        P1.6        Master Out Slave In for SPI
 *      GND         GND         Ground
 *      VCC         3.3V        3.3V power
 *      RST         3.3V        Reset pin
 * @References:
 *          1) https://www.youtube.com/watch?v=e4ph5T1C7dg
 *          2) https://github.com/viduraembedded/MSP432_SimpleLink_SDK/tree/master/MFRC522_RFID
 */



#ifndef MFRC522_H
#define MFRC522_H 100



/*
 * Header files
 */
#include <stdint.h>
#include <stddef.h>



/*
 * Driver Header files
 */
#include <Hardware/GPIO_Driver.h>
#include <ti/devices/msp432p4xx/driverlib/rom_map.h>
#include <ti/posix/ccs/unistd.h>   //usleep()
#include <ti/drivers/GPIO.h>
#include <ti/devices/msp432p4xx/driverlib/spi.h>



/*
 * Driver configuration
 */
#include "inc/ti_drivers_config.h"



/*
 * Status enumeration
 *
 * Used with most functions
 */
typedef enum {
    MI_OK = 0,
    MI_NOTAGERR,
    MI_ERR
} MFRC522_Status_t;



// Chip Enable(CE) high and low declaration
#define CS_LOW()        MAP_GPIO_setOutputLowOnPin(5, 0)
#define CS_HIGH()       MAP_GPIO_setOutputHighOnPin(5, 0)




/*
 * MFRC522 Commands
 */
#define PCD_IDLE                        0x00   //NO action; Cancel the current command
#define PCD_AUTHENT                     0x0E   //Authentication Key
#define PCD_RECEIVE                     0x08   //Receive Data
#define PCD_TRANSMIT                    0x04   //Transmit data
#define PCD_TRANSCEIVE                  0x0C   //Transmit and receive data,
#define PCD_RESETPHASE                  0x0F   //Reset
#define PCD_CALCCRC                     0x03   //CRC Calculate



/*
 * Mifare_One card command word
 */
#define PICC_REQIDL                     0x26   // find the antenna area does not enter hibernation
#define PICC_REQALL                     0x52   // find all the cards antenna area
#define PICC_ANTICOLL                   0x93   // anti-collision
#define PICC_SElECTTAG                  0x93   // election card
#define PICC_AUTHENT1A                  0x60   // authentication key A
#define PICC_AUTHENT1B                  0x61   // authentication key B
#define PICC_READ                       0x30   // Read Block
#define PICC_WRITE                      0xA0   // write block
#define PICC_DECREMENT                  0xC0   // debit
#define PICC_INCREMENT                  0xC1   // recharge
#define PICC_RESTORE                    0xC2   // transfer block data to the buffer
#define PICC_TRANSFER                   0xB0   // save the data in the buffer
#define PICC_HALT                       0x50   // Sleep



/*
 * MFRC522 Registers
 */
//Page 0: Command and Status
#define MFRC522_REG_RESERVED00          0x00
#define MFRC522_REG_COMMAND             0x01
#define MFRC522_REG_COMM_IE_N           0x02
#define MFRC522_REG_DIV1_EN             0x03
#define MFRC522_REG_COMM_IRQ            0x04
#define MFRC522_REG_DIV_IRQ             0x05
#define MFRC522_REG_ERROR               0x06
#define MFRC522_REG_STATUS1             0x07
#define MFRC522_REG_STATUS2             0x08
#define MFRC522_REG_FIFO_DATA           0x09
#define MFRC522_REG_FIFO_LEVEL          0x0A
#define MFRC522_REG_WATER_LEVEL         0x0B
#define MFRC522_REG_CONTROL             0x0C
#define MFRC522_REG_BIT_FRAMING         0x0D
#define MFRC522_REG_COLL                0x0E
#define MFRC522_REG_RESERVED01          0x0F
//Page 1: Command
#define MFRC522_REG_RESERVED10          0x10
#define MFRC522_REG_MODE                0x11
#define MFRC522_REG_TX_MODE             0x12
#define MFRC522_REG_RX_MODE             0x13
#define MFRC522_REG_TX_CONTROL          0x14
#define MFRC522_REG_TX_AUTO             0x15
#define MFRC522_REG_TX_SELL             0x16
#define MFRC522_REG_RX_SELL             0x17
#define MFRC522_REG_RX_THRESHOLD        0x18
#define MFRC522_REG_DEMOD               0x19
#define MFRC522_REG_RESERVED11          0x1A
#define MFRC522_REG_RESERVED12          0x1B
#define MFRC522_REG_MIFARE              0x1C
#define MFRC522_REG_RESERVED13          0x1D
#define MFRC522_REG_RESERVED14          0x1E
#define MFRC522_REG_SERIALSPEED         0x1F
//Page 2: CFG
#define MFRC522_REG_RESERVED20          0x20
#define MFRC522_REG_CRC_RESULT_M        0x21
#define MFRC522_REG_CRC_RESULT_L        0x22
#define MFRC522_REG_RESERVED21          0x23
#define MFRC522_REG_MOD_WIDTH           0x24
#define MFRC522_REG_RESERVED22          0x25
#define MFRC522_REG_RF_CFG              0x26
#define MFRC522_REG_GS_N                0x27
#define MFRC522_REG_CWGS_PREG           0x28
#define MFRC522_REG__MODGS_PREG         0x29
#define MFRC522_REG_T_MODE              0x2A
#define MFRC522_REG_T_PRESCALER         0x2B
#define MFRC522_REG_T_RELOAD_H          0x2C
#define MFRC522_REG_T_RELOAD_L          0x2D
#define MFRC522_REG_T_COUNTER_VALUE_H   0x2E
#define MFRC522_REG_T_COUNTER_VALUE_L   0x2F
//Page 3:TestRegister
#define MFRC522_REG_RESERVED30          0x30
#define MFRC522_REG_TEST_SEL1           0x31
#define MFRC522_REG_TEST_SEL2           0x32
#define MFRC522_REG_TEST_PIN_EN         0x33
#define MFRC522_REG_TEST_PIN_VALUE      0x34
#define MFRC522_REG_TEST_BUS            0x35
#define MFRC522_REG_AUTO_TEST           0x36
#define MFRC522_REG_VERSION             0x37
#define MFRC522_REG_ANALOG_TEST         0x38
#define MFRC522_REG_TEST_ADC1           0x39
#define MFRC522_REG_TEST_ADC2           0x3A
#define MFRC522_REG_TEST_ADC0           0x3B
#define MFRC522_REG_RESERVED31          0x3C
#define MFRC522_REG_RESERVED32          0x3D
#define MFRC522_REG_RESERVED33          0x3E
#define MFRC522_REG_RESERVED34          0x3F
//Dummy byte
#define MFRC522_DUMMY                   0x00

#define MFRC522_MAX_LEN                 16

/*
 * Initialize MFRC522 RFID reader
 *
 * Prepare MFRC522 to work with RFIDs
 *
 * @params:
 *      None
 * @returns:
 *      None
 *
 */
extern void MFRC522_Init(void);



/*
 * Check for RFID card existance
 *
 * @prarams:
 *  - uint8_t* id:
 *      Pointer to 5bytes long memory to store valid card id in.
 *      ID is valid only if card is detected, so when function returns MI_OK
 *
 * @returns:
 *      MI_OK if card is detected
 */
extern MFRC522_Status_t MFRC522_Check(uint8_t* id);



/*
 * Compare 2 RFID ID's
 * Useful if you have known ID (database with allowed IDs), to compare detected card with with your ID
 *
 * @params:
 *  - uint8_t* CardID:
 *      Pointer to 5bytes detected card ID
 *  - uint8_t* CompareID:
 *      Pointer to 5bytes your ID
 *
 * @returns:
 *      MI_OK if IDs are the same, or MI_ERR if not
 */
extern MFRC522_Status_t MFRC522_Compare(uint8_t* CardID, uint8_t* CompareID);



/*
 * Write value to corresponding register
 *
 * @params:
 *  - uint8_t addr
 *      register address
 *  - uint8_t
 *      one byte value
 * @returns:
 *      None
 */
extern void MFRC522_WriteRegister(uint8_t addr, uint8_t val);



/*
 * read value from corresponding register
 *
 * @params:
 *  - uint8_t addr
 *      register address
 * @returns:
 *      None
 */
extern uint8_t MFRC522_ReadRegister(uint8_t addr);



/*
 * apply bit mask to value at register address
 *
 * @params:
 *  - uint8_t reg
 *      register address
 *  - mask
 *      8-bit mask
 * @returns:
 *      None
 */
extern void MFRC522_SetBitMask(uint8_t reg, uint8_t mask);



/*
 * apply bit mask to value at register address
 *
 * @params:
 *  - uint8_t reg
 *      register address
 *  - mask
 *      8-bit mask
 * @returns:
 *      None
 */
extern void MFRC522_ClearBitMask(uint8_t reg, uint8_t mask);



/*
 * switch on RFID reader
 *
 * @params:
 *      None
 * @returns:
 *      None
 */
extern void MFRC522_AntennaOn(void);



/*
 * switch off RFID reader
 *
 * @params:
 *      None
 * @returns:
 *      None
 */
extern void MFRC522_AntennaOff(void);



/*
 * reset RFID reader by writing 0x0F value at address 0x01
 *
 * @params:
 *      None
 * @returns:
 *      None
 */
extern void MFRC522_Reset(void);



/*
 * During MFRC522_Check, request function returns the status of the RFID scan
 * This time we are using mode to find the antenna area does not enter hibernation
 *
 *
 * @params:
 *  - uint8_t reqMode
 *          request mode
 *  - uint8_t TagType
 *          pointer to save id
 * @returns:
 *      MI_OK if card detected
 */
extern MFRC522_Status_t MFRC522_Request(uint8_t reqMode, uint8_t* TagType);



/*
 * During MFRC522_Request, function returns MI_OK once transfer is successful
 *
 *
 * @params:
 *  - uint8_t command
 *          command to read MFRC522 tag
 *  - uint8_t sendData
 *          pointer to send data
 *  - uint8_t sendLen
 *          length of data to be sent
 *  - uint8_t backData
 *          pointer to receive data
 *  - uint8_t backLen
 *          length of data to be received
 * @returns:
 *      MI_OK if transfer of data successful
 */
extern MFRC522_Status_t MFRC522_ToCard(uint8_t command, uint8_t* sendData, uint8_t sendLen, uint8_t* backData, uint16_t* backLen);



/*
 * Anti-collision, return card serial number 4 bytes
 *
 *
 * @params:
 *  - uint8_t serNum
 *          returns card serial number
 * @returns
 *      MI_OK if no collision detected
 *
 */
extern MFRC522_Status_t MFRC522_Anticoll(uint8_t* serNum);



/*
 * Does Cyclic Redundancy Check for errors
 *
 *
 * @params:
 *  - uint8_t pIndata
 *          pass RFID card data
 *  - len
 *          length of data passed
 *  - pOutData
 *          post CRC check, pOutData saves it
 * @returns
 *      None
 *
 */
extern void MFRC522_CalculateCRC(uint8_t* pIndata, uint8_t len, uint8_t* pOutData);



/*
 * Stop the RFID reader operation
 * Go into hibernation mode
 *
 *
 * @params:
 *      None
 * @returns
 *      None
 *
 */
extern void MFRC522_Halt(void);

#endif
