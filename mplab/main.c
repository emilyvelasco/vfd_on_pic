/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.76
        Device            :  PIC16F18345
        Driver Version    :  2.00
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

#include "mcc_generated_files/mcc.h"

#define CONTROL_MAX 0x7F

// Control data block
// Purpose
// Number of grids/digits/etc. to cycle through
#define CDB_GRIDS 0x00

// How many cycles to stay within this data block
#define CDB_CYCLES 0x01

// Starting address of next control data block
#define CDB_NEXT 0x02

// 03    Reserved for future feature

#define CDB_GRID_DATA 0x04
// 04    Grid 0 LSB
// 05    Grid 0 MSB
// 06    Grid 1 LSB
// 07    Grid 1 MSB
// 08    Grid 2 LSB
// 09    Grid 2 MSB
// [... repeat for as many grids as necessary... ]

static uint8_t controlData[CONTROL_MAX];

// Variables for the current pattern
unsigned char controlBlockStart;
unsigned char gridIndex;
unsigned char cycleCount;

void everyTimerTick(void)
{
    I2C1_CopyBuffer(controlData);
    
    // Output grid selection to demultiplexor
    PORTB = gridIndex << 4;
    
    // Copy LSB bit pattern to outputs
    PORTC = controlData[controlBlockStart+CDB_GRID_DATA+(2*gridIndex)];
    
    // If this interferes with I2C on RA4/RA5 we have to do bit twiddling
    PORTA = controlData[controlBlockStart+CDB_GRID_DATA+(2*gridIndex)+1];

    // Next timer tick, next grid
    gridIndex++;
    
    // If this is all the grids we need to cover, go back to the start.
    // Increment number of times we've covered all the grids (cycles))
    if (gridIndex >= controlData[controlBlockStart+CDB_GRIDS])
    {
        gridIndex = 0;
        cycleCount++;
    }
    
    // If we've gone through the number of specified cycles, move on to the
    // next pattern.
    if (cycleCount >= controlData[controlBlockStart+CDB_CYCLES])
    {
        cycleCount = 0;
        controlBlockStart = controlData[controlBlockStart+CDB_NEXT];
    }
}

/*
                         Main application
 */
void main(void)
{
    // initialize the device
    SYSTEM_Initialize();

    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();

    // Set up our 1ms timer interrupt handler
    TMR0_SetInterruptHandler(everyTimerTick);
    
    // Start with control block zero
    controlBlockStart = 0;
    gridIndex = 0;
    cycleCount = 0;
    
    while (1)
    {
        // Add your application code
    }
}
/**
 End of File
*/