/**
  MSSP1 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    i2c1.c

  @Summary
    This is the generated header file for the MSSP1 driver using 
    PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for I2C1.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.76
        Device            :  PIC16F18345
        Driver Version    :  2.01
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.00
        MPLAB 	          :  MPLAB X 5.10	
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "i2c1.h"
#include "string.h"

#define I2C1_SLAVE_ADDRESS 0x42 
#define I2C1_SLAVE_MASK    0x7F

typedef enum
{
    SLAVE_NORMAL_DATA,
    SLAVE_DATA_ADDRESS,
} SLAVE_WRITE_DATA_TYPE;

/**
 Section: Global Variables
*/

volatile uint8_t    I2C1_slaveWriteData      = 0x55;

/**
 Section: Local Functions
*/
void I2C1_StatusCallback(I2C1_SLAVE_DRIVER_STATUS i2c_bus_state);


/**
  Prototype:        void I2C1_Initialize(void)
  Input:            none
  Output:           none
  Description:      I2C1_Initialize is an
                    initialization routine that takes inputs from the GUI.
  Comment:          
  Usage:            I2C1_Initialize();

*/
void I2C1_Initialize(void)
{
    // initialize the hardware
    // R_nW write_noTX; P stopbit_notdetected; S startbit_notdetected; BF RCinprocess_TXcomplete; SMP High Speed; UA dontupdate; CKE disabled; D_nA lastbyte_address; 
    SSP1STAT = 0x00;
    // SSPEN enabled; WCOL no_collision; CKP disabled; SSPM 7 Bit Polling; SSPOV no_overflow; 
    SSP1CON1 = 0x26;
    // ACKEN disabled; GCEN disabled; PEN disabled; ACKDT acknowledge; RSEN disabled; RCEN disabled; ACKSTAT received; SEN disabled; 
    SSP1CON2 = 0x00;
    // ACKTIM ackseq; SBCDE disabled; BOEN disabled; SCIE disabled; PCIE disabled; DHEN disabled; SDAHT 100ns; AHEN disabled; 
    SSP1CON3 = 0x00;
    // SSP1MSK 127; 
    SSP1MSK = (I2C1_SLAVE_MASK << 1);  // adjust UI mask for R/nW bit            
    // SSP1ADD 66; 
    SSP1ADD = (I2C1_SLAVE_ADDRESS << 1);  // adjust UI address for R/nW bit
	
    // clear the slave interrupt flag
    PIR1bits.SSP1IF = 0;
    // enable the master interrupt
    PIE1bits.SSP1IE = 1;

}

void I2C1_ISR ( void )
{
    uint8_t     i2c_data                = 0x55;


    // NOTE: The slave driver will always acknowledge
    //       any address match.

    PIR1bits.SSP1IF = 0;        // clear the slave interrupt flag
    i2c_data        = SSP1BUF;  // read SSPBUF to clear BF
    if(1 == SSP1STATbits.R_nW)
    {
        if((1 == SSP1STATbits.D_nA) && (1 == SSP1CON2bits.ACKSTAT))
        {
            // callback routine can perform any post-read processing
            I2C1_StatusCallback(I2C1_SLAVE_READ_COMPLETED);
        }
        else
        {
            // callback routine should write data into SSPBUF
            I2C1_StatusCallback(I2C1_SLAVE_READ_REQUEST);
        }
    }
    else if(0 == SSP1STATbits.D_nA)
    {
        // this is an I2C address

        // callback routine should prepare to receive data from the master
        I2C1_StatusCallback(I2C1_SLAVE_WRITE_REQUEST);
    }
    else
    {
        I2C1_slaveWriteData   = i2c_data;

        // callback routine should process I2C1_slaveWriteData from the master
        I2C1_StatusCallback(I2C1_SLAVE_WRITE_COMPLETED);
    }

    SSP1CON1bits.CKP    = 1;    // release SCL

} // end I2C1_ISR()



/**

    Example implementation of the callback

    This slave driver emulates an EEPROM Device.
    Sequential reads from the EEPROM will return data at the next
    EEPROM address.

    Random access reads can be performed by writing a single byte
    EEPROM address, followed by 1 or more reads.

    Random access writes can be performed by writing a single byte
    EEPROM address, followed by 1 or more writes.

    Every read or write will increment the internal EEPROM address.

    When the end of the EEPROM is reached, the EEPROM address will
    continue from the start of the EEPROM.
*/

static uint8_t EEPROM_Buffer[] =
{
    0x08, // Number of grids
    0x0A, // Time slices to dwell on each grid.
    0x0B, // Number of cycles through all grids
    0x14, // Index for next pattern
    0x81,0x01,0x02,0x01,0x40,0x02,0x10,0x02,0x08,0x04,0x04,0x04,0x40,0x02,0x20,0x02,
    
    0x08, // Number of grids
    0x0A, // Time slices to dwell on each grid.
    0x0B, // Number of cycles through all grids
    0x28, // Index for next pattern
    0x02,0x01,0x40,0x02,0x10,0x02,0x08,0x04,0x04,0x04,0x40,0x02,0x20,0x02,0x81,0x01,
    
    0x08, // Number of grids
    0x0A, // Time slices to dwell on each grid.
    0x0B, // Number of cycles through all grids
    0x3C, // Index for next pattern
    0x40,0x02,0x10,0x02,0x08,0x04,0x04,0x04,0x40,0x02,0x20,0x02,0x81,0x01,0x02,0x01,

    0x08, // Number of grids
    0x0A, // Time slices to dwell on each grid.
    0x0B, // Number of cycles through all grids
    0x50, // Index for next pattern
    0x10,0x02,0x08,0x04,0x04,0x04,0x40,0x02,0x20,0x02,0x81,0x01,0x02,0x01,0x40,0x02,
    
    0x08, // Number of grids
    0x0A, // Time slices to dwell on each grid.
    0x0B, // Number of cycles through all grids
    0x64, // Index for next pattern
    0x08,0x04,0x04,0x04,0x40,0x02,0x20,0x02,0x81,0x01,0x02,0x01,0x40,0x02,0x10,0x02,
    
    0x08, // Number of grids
    0x0A, // Time slices to dwell on each grid.
    0x0B, // Number of cycles through all grids
    0x78, // Index for next pattern
    0x04,0x04,0x40,0x02,0x20,0x02,0x81,0x01,0x02,0x01,0x40,0x02,0x10,0x02,0x08,0x04,

    0x08, // Number of grids
    0x0A, // Time slices to dwell on each grid.
    0x0B, // Number of cycles through all grids
    0x8C, // Index for next pattern
    0x40,0x02,0x20,0x02,0x81,0x01,0x02,0x01,0x40,0x02,0x10,0x02,0x08,0x04,0x04,0x04,
    
    0x08, // Number of grids
    0x0A, // Time slices to dwell on each grid.
    0x0B, // Number of cycles through all grids
    0x00, // Index for next pattern
    0x20,0x02,0x81,0x01,0x02,0x01,0x40,0x02,0x10,0x02,0x08,0x04,0x04,0x04,0x40,0x02,
    
    0xA0,0xA1,0xA2,0xA3,0xA4,0xA5,0xA6,0xA7,0xA8,0xA9,0xAa,0xAb,0xAc,0xAd,0xAe,0xAf,
    0xB0,0xB1,0xB2,0xB3,0xB4,0xB5,0xB6,0xB7,0xB8,0xB9,0xBa,0xBb,0xBc,0xBd,0xBe,0xBf,
    0xC0,0xC1,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCa,0xCb,0xCc,0xCd,0xCe,0xCf,
    0xD0,0xD1,0xD2,0xD3,0xD4,0xD5,0xD6,0xD7,0xD8,0xD9,0xDa,0xDb,0xDc,0xDd,0xDe,0xDf,
    0xE0,0xE1,0xE2,0xE3,0xE4,0xE5,0xE6,0xE7,0xE8,0xE9,0xEa,0xEb,0xEc,0xEd,0xEe,0xEf,
    0xF0,0xF1,0xF2,0xF3,0xF4,0xF5,0xF6,0xF7,0xF8,0xF9,0xFa,0xFb,0xFc,0xFd,0xFe
};

void I2C1_StatusCallback(I2C1_SLAVE_DRIVER_STATUS i2c_bus_state)
{
    static uint8_t eepromAddress    = 0;
    static uint8_t slaveWriteType   = SLAVE_NORMAL_DATA;


    switch (i2c_bus_state)
    {
        case I2C1_SLAVE_WRITE_REQUEST:
            // the master will be sending the eeprom address next
            slaveWriteType  = SLAVE_DATA_ADDRESS;
            break;


        case I2C1_SLAVE_WRITE_COMPLETED:

            switch(slaveWriteType)
            {
                case SLAVE_DATA_ADDRESS:
                    eepromAddress   = I2C1_slaveWriteData;
                    break;


                case SLAVE_NORMAL_DATA:
                default:
                    // the master has written data to store in the eeprom
                    EEPROM_Buffer[eepromAddress]    = I2C1_slaveWriteData;
                    if(eepromAddress < sizeof(EEPROM_Buffer))
                    {
                        eepromAddress++;
                    }
                    break;

            } // end switch(slaveWriteType)

            slaveWriteType  = SLAVE_NORMAL_DATA;
            break;

        case I2C1_SLAVE_READ_REQUEST:
            SSP1BUF = EEPROM_Buffer[eepromAddress];
            if(eepromAddress < sizeof(EEPROM_Buffer))
            {
                eepromAddress++;
            }
            break;

        case I2C1_SLAVE_READ_COMPLETED:
        default:;

    } // end switch(i2c_bus_state)

}

// Copies EEPROM_Buffer in its current state. Note we may be in the middle of
// an I2C write so data may be inconsistent.
void I2C1_CopyBuffer(uint8_t *bufferArray)
{
    memcpy(bufferArray, EEPROM_Buffer, sizeof(EEPROM_Buffer));

    return;
}

