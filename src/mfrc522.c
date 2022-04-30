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
 * @References:
 *          1) https://www.youtube.com/watch?v=e4ph5T1C7dg
 *          2) https://github.com/viduraembedded/MSP432_SimpleLink_SDK/tree/master/MFRC522_RFID
 */


/*
 * Header files
 */
#include <stdint.h>
#include <stddef.h>



/*
 * Driver Header files
 */
#include <ti/posix/ccs/unistd.h>   //usleep()
#include <ti/devices/msp432p4xx/inc/msp432p401r.h>
#include <ti/drivers/GPIO.h>
#include <ti/drivers/SPI.h>



/*
 * Driver configuration
 */
#include "inc/ti_drivers_config.h"
#include "inc/mfrc522.h"

eUSCI_SPI_MasterConfig SPI0MasterConfig =
{
     EUSCI_B_SPI_CLOCKSOURCE_SMCLK,
     3000000,
     500000,
     EUSCI_B_SPI_MSB_FIRST,
     EUSCI_B_SPI_PHASE_DATA_CHANGED_ONFIRST_CAPTURED_ON_NEXT,
     EUSCI_B_SPI_CLOCKPOLARITY_INACTIVITY_HIGH,
     EUSCI_B_SPI_3PIN
};

/*
 * Check header file for documentation
 */

uint8_t SPI_SendByte(uint8_t data){
    bool spiTransferOk;
    SPI_Transaction spiTransaction;

    uint8_t readValue;

    spiTransaction.count = 1;
    spiTransaction.txBuf = &data;
    spiTransaction.count = 1;
    spiTransaction.rxBuf = &readValue;
    spiTransferOk = true;

    if(spiTransferOk == false){
        // Error in SPI or transfer already in progress.
      while(1){}
    }

    return readValue;
}



/*
 * Check header file for documentation
 */
void SPI_WriteRegister(uint8_t address, uint8_t value){
    // CS pin is set to low
    CS_LOW();
    // send eight bit address
    SPI_SendByte(address);
    // send eight bit data
    SPI_SendByte(value);
    // make CS pin high
    CS_HIGH();
}



/*
 * Check header file for documentation
 */
uint8_t SPI_ReadRegister(uint8_t address) {
    uint8_t val;

    CS_LOW();
    SPI_SendByte(address);
    // send 0x00 to retrieve data
    val = SPI_SendByte(0x00);
    CS_HIGH();
    return val;
}



/*
 * Check header file for documentation
 */
void MFRC522_WriteRegister(uint8_t addr, uint8_t val) {
    addr = (addr << 1) & 0x7E;  // Address format: 0XXXXXX0
    SPI_WriteRegister(addr, val);
}



/*
 * Check header file for documentation
 */
uint8_t MFRC522_ReadRegister(uint8_t addr) {
    uint8_t val;

    addr = ((addr << 1) & 0x7E) | 0x80;// Address format: 1XXXXXX0
    // read value from address
    val = SPI_ReadRegister(addr);
    return val;
}



/*
 * Check header file for documentation
 */
void MFRC522_Init(void) {
    //MX_GPIO_Init();
    SPI_Init(EUSCI_B0_BASE, SPI0MasterConfig);
    GPIO_Init(GPIO_PORT_P5, GPIO_PIN0);
    CS_Init();
    // reset prior to start
    MFRC522_Reset();

    // send following commands to get it started
    MFRC522_WriteRegister(MFRC522_REG_T_MODE, 0x8D);
    MFRC522_WriteRegister(MFRC522_REG_T_PRESCALER, 0x3E);
    MFRC522_WriteRegister(MFRC522_REG_T_RELOAD_L, 30);
    MFRC522_WriteRegister(MFRC522_REG_T_RELOAD_H, 0);

    /* 48dB gain */
    MFRC522_WriteRegister(MFRC522_REG_RF_CFG, 0x70);

    MFRC522_WriteRegister(MFRC522_REG_TX_AUTO, 0x40);
    MFRC522_WriteRegister(MFRC522_REG_MODE, 0x3D);

    //Open the antenna
    MFRC522_AntennaOn();
}



/*
 * Check header file for documentation
 */
MFRC522_Status_t MFRC522_Check(uint8_t* id) {
    MFRC522_Status_t status;
    //Find cards, MFRC522_Check(uint8_t* id)return card type
    status = MFRC522_Request(PICC_REQIDL, id);
    if (status == MI_OK) {
        //Card detected
        //Anti-collision, return card serial number 4 bytes
        status = MFRC522_Anticoll(id);
    }
    //Command card into hibernation
    MFRC522_Halt();

    return status;
}



/*
 * Check header file for documentation
 */
MFRC522_Status_t MFRC522_Compare(uint8_t* CardID, uint8_t* CompareID) {
    uint8_t i;
    for (i = 0; i < 5; i++) {
        // compare every digit of RFID number
        if (CardID[i] != CompareID[i]) {
            return MI_ERR;
        }
    }
    return MI_OK;
}



/*
 * Check header file for documentation
 */
void MFRC522_SetBitMask(uint8_t reg, uint8_t mask) {
    MFRC522_WriteRegister(reg, MFRC522_ReadRegister(reg) | mask);
}



/*
 * Check header file for documentation
 */
void MFRC522_ClearBitMask(uint8_t reg, uint8_t mask){
    MFRC522_WriteRegister(reg, MFRC522_ReadRegister(reg) & (~mask));
}



/*
 * Check header file for documentation
 */
void MFRC522_AntennaOn(void) {
    uint8_t temp;

    temp = MFRC522_ReadRegister(MFRC522_REG_TX_CONTROL);
    if (!(temp & 0x03)) {
        MFRC522_SetBitMask(MFRC522_REG_TX_CONTROL, 0x03);
    }
}



/*
 * Check header file for documentation
 */
void MFRC522_AntennaOff(void) {
    MFRC522_ClearBitMask(MFRC522_REG_TX_CONTROL, 0x03);
}



/*
 * Check header file for documentation
 */
void MFRC522_Reset(void) {
    MFRC522_WriteRegister(MFRC522_REG_COMMAND, PCD_RESETPHASE);
}



/*
 * Check header file for documentation
 */
MFRC522_Status_t MFRC522_Request(uint8_t reqMode, uint8_t* TagType) {
    MFRC522_Status_t status;
    uint16_t backBits;          //The received data bits

    MFRC522_WriteRegister(MFRC522_REG_BIT_FRAMING, 0x07);       //TxLastBists = BitFramingReg[2..0] ???

    TagType[0] = reqMode;
    status = MFRC522_ToCard(PCD_TRANSCEIVE, TagType, 1, TagType, &backBits);

    if ((status != MI_OK) || (backBits != 0x10)) {
        status = MI_ERR;
    }

    return status;
}



/*
 * Check header file for documentation
 */
MFRC522_Status_t MFRC522_ToCard(uint8_t command, uint8_t* sendData, uint8_t sendLen, uint8_t* backData, uint16_t* backLen) {
    MFRC522_Status_t status = MI_ERR;
    uint8_t irqEn = 0x00;
    uint8_t waitIRq = 0x00;
    uint8_t lastBits;
    uint8_t n;
    uint16_t i;

    switch (command) {
        case PCD_AUTHENT: {
            irqEn = 0x12;
            waitIRq = 0x10;
            break;
        }
        case PCD_TRANSCEIVE: {
            irqEn = 0x77;
            waitIRq = 0x30;
            break;
        }
        default:
            break;
    }

    MFRC522_WriteRegister(MFRC522_REG_COMM_IE_N, irqEn | 0x80);
    MFRC522_ClearBitMask(MFRC522_REG_COMM_IRQ, 0x80);
    MFRC522_SetBitMask(MFRC522_REG_FIFO_LEVEL, 0x80);

    MFRC522_WriteRegister(MFRC522_REG_COMMAND, PCD_IDLE);

    //Writing data to the FIFO
    for (i = 0; i < sendLen; i++) {
        MFRC522_WriteRegister(MFRC522_REG_FIFO_DATA, sendData[i]);
    }

    //Execute the command
    MFRC522_WriteRegister(MFRC522_REG_COMMAND, command);
    if (command == PCD_TRANSCEIVE) {
        MFRC522_SetBitMask(MFRC522_REG_BIT_FRAMING, 0x80);      //StartSend=1,transmission of data starts
    }

    //Waiting to receive data to complete
    i = 2000;   //i according to the clock frequency adjustment, the operator M1 card maximum waiting time 25ms???
    do {
        //CommIrqReg[7..0]
        //Set1 TxIRq RxIRq IdleIRq HiAlerIRq LoAlertIRq ErrIRq TimerIRq
        n = MFRC522_ReadRegister(MFRC522_REG_COMM_IRQ);
        i--;
    } while ((i!=0) && !(n&0x01) && !(n&waitIRq));

    MFRC522_ClearBitMask(MFRC522_REG_BIT_FRAMING, 0x80);            //StartSend=0

    if (i != 0)  {
        if (!(MFRC522_ReadRegister(MFRC522_REG_ERROR) & 0x1B)) {
            status = MI_OK;
            if (n & irqEn & 0x01) {
                status = MI_NOTAGERR;
            }

            if (command == PCD_TRANSCEIVE) {
                n = MFRC522_ReadRegister(MFRC522_REG_FIFO_LEVEL);
                lastBits = MFRC522_ReadRegister(MFRC522_REG_CONTROL) & 0x07;
                if (lastBits) {
                    *backLen = (n - 1) * 8 + lastBits;
                } else {
                    *backLen = n * 8;
                }

                if (n == 0) {
                    n = 1;
                }
                if (n > MFRC522_MAX_LEN) {
                    n = MFRC522_MAX_LEN;
                }

                //Reading the received data in FIFO
                for (i = 0; i < n; i++) {
                    backData[i] = MFRC522_ReadRegister(MFRC522_REG_FIFO_DATA);
                }
            }
        } else {
            status = MI_ERR;
        }
    }

    return status;
}



/*
 * Check header file for documentation
 */
MFRC522_Status_t MFRC522_Anticoll(uint8_t* serNum) {
    MFRC522_Status_t status;
    uint8_t i;
    uint8_t serNumCheck = 0;
    uint16_t unLen;

    MFRC522_WriteRegister(MFRC522_REG_BIT_FRAMING, 0x00);       //TxLastBists = BitFramingReg[2..0]

    serNum[0] = PICC_ANTICOLL;
    serNum[1] = 0x20;
    status = MFRC522_ToCard(PCD_TRANSCEIVE, serNum, 2, serNum, &unLen);

    if (status == MI_OK) {
        //Check card serial number
        for (i = 0; i < 4; i++) {
            serNumCheck ^= serNum[i];
        }
        if (serNumCheck != serNum[i]) {
            status = MI_ERR;
        }
    }
    return status;
}



/*
 * Check header file for documentation
 */
void MFRC522_CalculateCRC(uint8_t*  pIndata, uint8_t len, uint8_t* pOutData) {
    uint8_t i, n;

    MFRC522_ClearBitMask(MFRC522_REG_DIV_IRQ, 0x04);            //CRCIrq = 0
    MFRC522_SetBitMask(MFRC522_REG_FIFO_LEVEL, 0x80);           //Clear the FIFO pointer
    //Write_MFRC522(CommandReg, PCD_IDLE);

    //Writing data to the FIFO
    for (i = 0; i < len; i++) {
        MFRC522_WriteRegister(MFRC522_REG_FIFO_DATA, *(pIndata+i));
    }
    MFRC522_WriteRegister(MFRC522_REG_COMMAND, PCD_CALCCRC);

    //Wait CRC calculation is complete
    i = 0xFF;
    do {
        n = MFRC522_ReadRegister(MFRC522_REG_DIV_IRQ);
        i--;
    } while ((i!=0) && !(n&0x04));          //CRCIrq = 1

    //Read CRC calculation result
    pOutData[0] = MFRC522_ReadRegister(MFRC522_REG_CRC_RESULT_L);
    pOutData[1] = MFRC522_ReadRegister(MFRC522_REG_CRC_RESULT_M);
}



/*
 * Check header file for documentation
 */
void MFRC522_Halt(void) {
    uint16_t unLen;
    uint8_t buff[4];

    buff[0] = PICC_HALT;
    buff[1] = 0;
    MFRC522_CalculateCRC(buff, 2, &buff[2]);

    MFRC522_ToCard(PCD_TRANSCEIVE, buff, 4, buff, &unLen);
}
