/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.76
        Device            :  PIC16F18345
        Driver Version    :  2.11
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

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set ELEM_I aliases
#define ELEM_I_TRIS                 TRISAbits.TRISA0
#define ELEM_I_LAT                  LATAbits.LATA0
#define ELEM_I_PORT                 PORTAbits.RA0
#define ELEM_I_WPU                  WPUAbits.WPUA0
#define ELEM_I_OD                   ODCONAbits.ODCA0
#define ELEM_I_ANS                  ANSELAbits.ANSA0
#define ELEM_I_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define ELEM_I_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define ELEM_I_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define ELEM_I_GetValue()           PORTAbits.RA0
#define ELEM_I_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define ELEM_I_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define ELEM_I_SetPullup()          do { WPUAbits.WPUA0 = 1; } while(0)
#define ELEM_I_ResetPullup()        do { WPUAbits.WPUA0 = 0; } while(0)
#define ELEM_I_SetPushPull()        do { ODCONAbits.ODCA0 = 0; } while(0)
#define ELEM_I_SetOpenDrain()       do { ODCONAbits.ODCA0 = 1; } while(0)
#define ELEM_I_SetAnalogMode()      do { ANSELAbits.ANSA0 = 1; } while(0)
#define ELEM_I_SetDigitalMode()     do { ANSELAbits.ANSA0 = 0; } while(0)

// get/set ELEM_J aliases
#define ELEM_J_TRIS                 TRISAbits.TRISA1
#define ELEM_J_LAT                  LATAbits.LATA1
#define ELEM_J_PORT                 PORTAbits.RA1
#define ELEM_J_WPU                  WPUAbits.WPUA1
#define ELEM_J_OD                   ODCONAbits.ODCA1
#define ELEM_J_ANS                  ANSELAbits.ANSA1
#define ELEM_J_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define ELEM_J_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define ELEM_J_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define ELEM_J_GetValue()           PORTAbits.RA1
#define ELEM_J_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define ELEM_J_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define ELEM_J_SetPullup()          do { WPUAbits.WPUA1 = 1; } while(0)
#define ELEM_J_ResetPullup()        do { WPUAbits.WPUA1 = 0; } while(0)
#define ELEM_J_SetPushPull()        do { ODCONAbits.ODCA1 = 0; } while(0)
#define ELEM_J_SetOpenDrain()       do { ODCONAbits.ODCA1 = 1; } while(0)
#define ELEM_J_SetAnalogMode()      do { ANSELAbits.ANSA1 = 1; } while(0)
#define ELEM_J_SetDigitalMode()     do { ANSELAbits.ANSA1 = 0; } while(0)

// get/set ELEM_K aliases
#define ELEM_K_TRIS                 TRISAbits.TRISA2
#define ELEM_K_LAT                  LATAbits.LATA2
#define ELEM_K_PORT                 PORTAbits.RA2
#define ELEM_K_WPU                  WPUAbits.WPUA2
#define ELEM_K_OD                   ODCONAbits.ODCA2
#define ELEM_K_ANS                  ANSELAbits.ANSA2
#define ELEM_K_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define ELEM_K_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define ELEM_K_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define ELEM_K_GetValue()           PORTAbits.RA2
#define ELEM_K_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define ELEM_K_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define ELEM_K_SetPullup()          do { WPUAbits.WPUA2 = 1; } while(0)
#define ELEM_K_ResetPullup()        do { WPUAbits.WPUA2 = 0; } while(0)
#define ELEM_K_SetPushPull()        do { ODCONAbits.ODCA2 = 0; } while(0)
#define ELEM_K_SetOpenDrain()       do { ODCONAbits.ODCA2 = 1; } while(0)
#define ELEM_K_SetAnalogMode()      do { ANSELAbits.ANSA2 = 1; } while(0)
#define ELEM_K_SetDigitalMode()     do { ANSELAbits.ANSA2 = 0; } while(0)

// get/set SCL1 aliases
#define SCL1_TRIS                 TRISAbits.TRISA4
#define SCL1_LAT                  LATAbits.LATA4
#define SCL1_PORT                 PORTAbits.RA4
#define SCL1_WPU                  WPUAbits.WPUA4
#define SCL1_OD                   ODCONAbits.ODCA4
#define SCL1_ANS                  ANSELAbits.ANSA4
#define SCL1_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define SCL1_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define SCL1_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define SCL1_GetValue()           PORTAbits.RA4
#define SCL1_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define SCL1_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define SCL1_SetPullup()          do { WPUAbits.WPUA4 = 1; } while(0)
#define SCL1_ResetPullup()        do { WPUAbits.WPUA4 = 0; } while(0)
#define SCL1_SetPushPull()        do { ODCONAbits.ODCA4 = 0; } while(0)
#define SCL1_SetOpenDrain()       do { ODCONAbits.ODCA4 = 1; } while(0)
#define SCL1_SetAnalogMode()      do { ANSELAbits.ANSA4 = 1; } while(0)
#define SCL1_SetDigitalMode()     do { ANSELAbits.ANSA4 = 0; } while(0)

// get/set SDA1 aliases
#define SDA1_TRIS                 TRISAbits.TRISA5
#define SDA1_LAT                  LATAbits.LATA5
#define SDA1_PORT                 PORTAbits.RA5
#define SDA1_WPU                  WPUAbits.WPUA5
#define SDA1_OD                   ODCONAbits.ODCA5
#define SDA1_ANS                  ANSELAbits.ANSA5
#define SDA1_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define SDA1_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define SDA1_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define SDA1_GetValue()           PORTAbits.RA5
#define SDA1_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define SDA1_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define SDA1_SetPullup()          do { WPUAbits.WPUA5 = 1; } while(0)
#define SDA1_ResetPullup()        do { WPUAbits.WPUA5 = 0; } while(0)
#define SDA1_SetPushPull()        do { ODCONAbits.ODCA5 = 0; } while(0)
#define SDA1_SetOpenDrain()       do { ODCONAbits.ODCA5 = 1; } while(0)
#define SDA1_SetAnalogMode()      do { ANSELAbits.ANSA5 = 1; } while(0)
#define SDA1_SetDigitalMode()     do { ANSELAbits.ANSA5 = 0; } while(0)

// get/set GRID0 aliases
#define GRID0_TRIS                 TRISBbits.TRISB4
#define GRID0_LAT                  LATBbits.LATB4
#define GRID0_PORT                 PORTBbits.RB4
#define GRID0_WPU                  WPUBbits.WPUB4
#define GRID0_OD                   ODCONBbits.ODCB4
#define GRID0_ANS                  ANSELBbits.ANSB4
#define GRID0_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define GRID0_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define GRID0_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define GRID0_GetValue()           PORTBbits.RB4
#define GRID0_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define GRID0_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define GRID0_SetPullup()          do { WPUBbits.WPUB4 = 1; } while(0)
#define GRID0_ResetPullup()        do { WPUBbits.WPUB4 = 0; } while(0)
#define GRID0_SetPushPull()        do { ODCONBbits.ODCB4 = 0; } while(0)
#define GRID0_SetOpenDrain()       do { ODCONBbits.ODCB4 = 1; } while(0)
#define GRID0_SetAnalogMode()      do { ANSELBbits.ANSB4 = 1; } while(0)
#define GRID0_SetDigitalMode()     do { ANSELBbits.ANSB4 = 0; } while(0)

// get/set GRID1 aliases
#define GRID1_TRIS                 TRISBbits.TRISB5
#define GRID1_LAT                  LATBbits.LATB5
#define GRID1_PORT                 PORTBbits.RB5
#define GRID1_WPU                  WPUBbits.WPUB5
#define GRID1_OD                   ODCONBbits.ODCB5
#define GRID1_ANS                  ANSELBbits.ANSB5
#define GRID1_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define GRID1_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define GRID1_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define GRID1_GetValue()           PORTBbits.RB5
#define GRID1_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define GRID1_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define GRID1_SetPullup()          do { WPUBbits.WPUB5 = 1; } while(0)
#define GRID1_ResetPullup()        do { WPUBbits.WPUB5 = 0; } while(0)
#define GRID1_SetPushPull()        do { ODCONBbits.ODCB5 = 0; } while(0)
#define GRID1_SetOpenDrain()       do { ODCONBbits.ODCB5 = 1; } while(0)
#define GRID1_SetAnalogMode()      do { ANSELBbits.ANSB5 = 1; } while(0)
#define GRID1_SetDigitalMode()     do { ANSELBbits.ANSB5 = 0; } while(0)

// get/set GRID2 aliases
#define GRID2_TRIS                 TRISBbits.TRISB6
#define GRID2_LAT                  LATBbits.LATB6
#define GRID2_PORT                 PORTBbits.RB6
#define GRID2_WPU                  WPUBbits.WPUB6
#define GRID2_OD                   ODCONBbits.ODCB6
#define GRID2_ANS                  ANSELBbits.ANSB6
#define GRID2_SetHigh()            do { LATBbits.LATB6 = 1; } while(0)
#define GRID2_SetLow()             do { LATBbits.LATB6 = 0; } while(0)
#define GRID2_Toggle()             do { LATBbits.LATB6 = ~LATBbits.LATB6; } while(0)
#define GRID2_GetValue()           PORTBbits.RB6
#define GRID2_SetDigitalInput()    do { TRISBbits.TRISB6 = 1; } while(0)
#define GRID2_SetDigitalOutput()   do { TRISBbits.TRISB6 = 0; } while(0)
#define GRID2_SetPullup()          do { WPUBbits.WPUB6 = 1; } while(0)
#define GRID2_ResetPullup()        do { WPUBbits.WPUB6 = 0; } while(0)
#define GRID2_SetPushPull()        do { ODCONBbits.ODCB6 = 0; } while(0)
#define GRID2_SetOpenDrain()       do { ODCONBbits.ODCB6 = 1; } while(0)
#define GRID2_SetAnalogMode()      do { ANSELBbits.ANSB6 = 1; } while(0)
#define GRID2_SetDigitalMode()     do { ANSELBbits.ANSB6 = 0; } while(0)

// get/set GRID4 aliases
#define GRID4_TRIS                 TRISBbits.TRISB7
#define GRID4_LAT                  LATBbits.LATB7
#define GRID4_PORT                 PORTBbits.RB7
#define GRID4_WPU                  WPUBbits.WPUB7
#define GRID4_OD                   ODCONBbits.ODCB7
#define GRID4_ANS                  ANSELBbits.ANSB7
#define GRID4_SetHigh()            do { LATBbits.LATB7 = 1; } while(0)
#define GRID4_SetLow()             do { LATBbits.LATB7 = 0; } while(0)
#define GRID4_Toggle()             do { LATBbits.LATB7 = ~LATBbits.LATB7; } while(0)
#define GRID4_GetValue()           PORTBbits.RB7
#define GRID4_SetDigitalInput()    do { TRISBbits.TRISB7 = 1; } while(0)
#define GRID4_SetDigitalOutput()   do { TRISBbits.TRISB7 = 0; } while(0)
#define GRID4_SetPullup()          do { WPUBbits.WPUB7 = 1; } while(0)
#define GRID4_ResetPullup()        do { WPUBbits.WPUB7 = 0; } while(0)
#define GRID4_SetPushPull()        do { ODCONBbits.ODCB7 = 0; } while(0)
#define GRID4_SetOpenDrain()       do { ODCONBbits.ODCB7 = 1; } while(0)
#define GRID4_SetAnalogMode()      do { ANSELBbits.ANSB7 = 1; } while(0)
#define GRID4_SetDigitalMode()     do { ANSELBbits.ANSB7 = 0; } while(0)

// get/set ELEM_A aliases
#define ELEM_A_TRIS                 TRISCbits.TRISC0
#define ELEM_A_LAT                  LATCbits.LATC0
#define ELEM_A_PORT                 PORTCbits.RC0
#define ELEM_A_WPU                  WPUCbits.WPUC0
#define ELEM_A_OD                   ODCONCbits.ODCC0
#define ELEM_A_ANS                  ANSELCbits.ANSC0
#define ELEM_A_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define ELEM_A_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define ELEM_A_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define ELEM_A_GetValue()           PORTCbits.RC0
#define ELEM_A_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define ELEM_A_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define ELEM_A_SetPullup()          do { WPUCbits.WPUC0 = 1; } while(0)
#define ELEM_A_ResetPullup()        do { WPUCbits.WPUC0 = 0; } while(0)
#define ELEM_A_SetPushPull()        do { ODCONCbits.ODCC0 = 0; } while(0)
#define ELEM_A_SetOpenDrain()       do { ODCONCbits.ODCC0 = 1; } while(0)
#define ELEM_A_SetAnalogMode()      do { ANSELCbits.ANSC0 = 1; } while(0)
#define ELEM_A_SetDigitalMode()     do { ANSELCbits.ANSC0 = 0; } while(0)

// get/set ELEM_B aliases
#define ELEM_B_TRIS                 TRISCbits.TRISC1
#define ELEM_B_LAT                  LATCbits.LATC1
#define ELEM_B_PORT                 PORTCbits.RC1
#define ELEM_B_WPU                  WPUCbits.WPUC1
#define ELEM_B_OD                   ODCONCbits.ODCC1
#define ELEM_B_ANS                  ANSELCbits.ANSC1
#define ELEM_B_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define ELEM_B_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define ELEM_B_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define ELEM_B_GetValue()           PORTCbits.RC1
#define ELEM_B_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define ELEM_B_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define ELEM_B_SetPullup()          do { WPUCbits.WPUC1 = 1; } while(0)
#define ELEM_B_ResetPullup()        do { WPUCbits.WPUC1 = 0; } while(0)
#define ELEM_B_SetPushPull()        do { ODCONCbits.ODCC1 = 0; } while(0)
#define ELEM_B_SetOpenDrain()       do { ODCONCbits.ODCC1 = 1; } while(0)
#define ELEM_B_SetAnalogMode()      do { ANSELCbits.ANSC1 = 1; } while(0)
#define ELEM_B_SetDigitalMode()     do { ANSELCbits.ANSC1 = 0; } while(0)

// get/set ELEM_C aliases
#define ELEM_C_TRIS                 TRISCbits.TRISC2
#define ELEM_C_LAT                  LATCbits.LATC2
#define ELEM_C_PORT                 PORTCbits.RC2
#define ELEM_C_WPU                  WPUCbits.WPUC2
#define ELEM_C_OD                   ODCONCbits.ODCC2
#define ELEM_C_ANS                  ANSELCbits.ANSC2
#define ELEM_C_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define ELEM_C_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define ELEM_C_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define ELEM_C_GetValue()           PORTCbits.RC2
#define ELEM_C_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define ELEM_C_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define ELEM_C_SetPullup()          do { WPUCbits.WPUC2 = 1; } while(0)
#define ELEM_C_ResetPullup()        do { WPUCbits.WPUC2 = 0; } while(0)
#define ELEM_C_SetPushPull()        do { ODCONCbits.ODCC2 = 0; } while(0)
#define ELEM_C_SetOpenDrain()       do { ODCONCbits.ODCC2 = 1; } while(0)
#define ELEM_C_SetAnalogMode()      do { ANSELCbits.ANSC2 = 1; } while(0)
#define ELEM_C_SetDigitalMode()     do { ANSELCbits.ANSC2 = 0; } while(0)

// get/set ELEM_D aliases
#define ELEM_D_TRIS                 TRISCbits.TRISC3
#define ELEM_D_LAT                  LATCbits.LATC3
#define ELEM_D_PORT                 PORTCbits.RC3
#define ELEM_D_WPU                  WPUCbits.WPUC3
#define ELEM_D_OD                   ODCONCbits.ODCC3
#define ELEM_D_ANS                  ANSELCbits.ANSC3
#define ELEM_D_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define ELEM_D_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define ELEM_D_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define ELEM_D_GetValue()           PORTCbits.RC3
#define ELEM_D_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define ELEM_D_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define ELEM_D_SetPullup()          do { WPUCbits.WPUC3 = 1; } while(0)
#define ELEM_D_ResetPullup()        do { WPUCbits.WPUC3 = 0; } while(0)
#define ELEM_D_SetPushPull()        do { ODCONCbits.ODCC3 = 0; } while(0)
#define ELEM_D_SetOpenDrain()       do { ODCONCbits.ODCC3 = 1; } while(0)
#define ELEM_D_SetAnalogMode()      do { ANSELCbits.ANSC3 = 1; } while(0)
#define ELEM_D_SetDigitalMode()     do { ANSELCbits.ANSC3 = 0; } while(0)

// get/set ELEM_E aliases
#define ELEM_E_TRIS                 TRISCbits.TRISC4
#define ELEM_E_LAT                  LATCbits.LATC4
#define ELEM_E_PORT                 PORTCbits.RC4
#define ELEM_E_WPU                  WPUCbits.WPUC4
#define ELEM_E_OD                   ODCONCbits.ODCC4
#define ELEM_E_ANS                  ANSELCbits.ANSC4
#define ELEM_E_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define ELEM_E_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define ELEM_E_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define ELEM_E_GetValue()           PORTCbits.RC4
#define ELEM_E_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define ELEM_E_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define ELEM_E_SetPullup()          do { WPUCbits.WPUC4 = 1; } while(0)
#define ELEM_E_ResetPullup()        do { WPUCbits.WPUC4 = 0; } while(0)
#define ELEM_E_SetPushPull()        do { ODCONCbits.ODCC4 = 0; } while(0)
#define ELEM_E_SetOpenDrain()       do { ODCONCbits.ODCC4 = 1; } while(0)
#define ELEM_E_SetAnalogMode()      do { ANSELCbits.ANSC4 = 1; } while(0)
#define ELEM_E_SetDigitalMode()     do { ANSELCbits.ANSC4 = 0; } while(0)

// get/set ELEM_F aliases
#define ELEM_F_TRIS                 TRISCbits.TRISC5
#define ELEM_F_LAT                  LATCbits.LATC5
#define ELEM_F_PORT                 PORTCbits.RC5
#define ELEM_F_WPU                  WPUCbits.WPUC5
#define ELEM_F_OD                   ODCONCbits.ODCC5
#define ELEM_F_ANS                  ANSELCbits.ANSC5
#define ELEM_F_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define ELEM_F_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define ELEM_F_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define ELEM_F_GetValue()           PORTCbits.RC5
#define ELEM_F_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define ELEM_F_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define ELEM_F_SetPullup()          do { WPUCbits.WPUC5 = 1; } while(0)
#define ELEM_F_ResetPullup()        do { WPUCbits.WPUC5 = 0; } while(0)
#define ELEM_F_SetPushPull()        do { ODCONCbits.ODCC5 = 0; } while(0)
#define ELEM_F_SetOpenDrain()       do { ODCONCbits.ODCC5 = 1; } while(0)
#define ELEM_F_SetAnalogMode()      do { ANSELCbits.ANSC5 = 1; } while(0)
#define ELEM_F_SetDigitalMode()     do { ANSELCbits.ANSC5 = 0; } while(0)

// get/set ELEM_G aliases
#define ELEM_G_TRIS                 TRISCbits.TRISC6
#define ELEM_G_LAT                  LATCbits.LATC6
#define ELEM_G_PORT                 PORTCbits.RC6
#define ELEM_G_WPU                  WPUCbits.WPUC6
#define ELEM_G_OD                   ODCONCbits.ODCC6
#define ELEM_G_ANS                  ANSELCbits.ANSC6
#define ELEM_G_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define ELEM_G_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define ELEM_G_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define ELEM_G_GetValue()           PORTCbits.RC6
#define ELEM_G_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define ELEM_G_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define ELEM_G_SetPullup()          do { WPUCbits.WPUC6 = 1; } while(0)
#define ELEM_G_ResetPullup()        do { WPUCbits.WPUC6 = 0; } while(0)
#define ELEM_G_SetPushPull()        do { ODCONCbits.ODCC6 = 0; } while(0)
#define ELEM_G_SetOpenDrain()       do { ODCONCbits.ODCC6 = 1; } while(0)
#define ELEM_G_SetAnalogMode()      do { ANSELCbits.ANSC6 = 1; } while(0)
#define ELEM_G_SetDigitalMode()     do { ANSELCbits.ANSC6 = 0; } while(0)

// get/set ELEM_H aliases
#define ELEM_H_TRIS                 TRISCbits.TRISC7
#define ELEM_H_LAT                  LATCbits.LATC7
#define ELEM_H_PORT                 PORTCbits.RC7
#define ELEM_H_WPU                  WPUCbits.WPUC7
#define ELEM_H_OD                   ODCONCbits.ODCC7
#define ELEM_H_ANS                  ANSELCbits.ANSC7
#define ELEM_H_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define ELEM_H_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define ELEM_H_Toggle()             do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define ELEM_H_GetValue()           PORTCbits.RC7
#define ELEM_H_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define ELEM_H_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)
#define ELEM_H_SetPullup()          do { WPUCbits.WPUC7 = 1; } while(0)
#define ELEM_H_ResetPullup()        do { WPUCbits.WPUC7 = 0; } while(0)
#define ELEM_H_SetPushPull()        do { ODCONCbits.ODCC7 = 0; } while(0)
#define ELEM_H_SetOpenDrain()       do { ODCONCbits.ODCC7 = 1; } while(0)
#define ELEM_H_SetAnalogMode()      do { ANSELCbits.ANSC7 = 1; } while(0)
#define ELEM_H_SetDigitalMode()     do { ANSELCbits.ANSC7 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/