# VFD on PIC

PIC Microcontroller project to turn a VFD (Vacuum Fluorescent Display) into an I2C-controlled display.

This is a practice exercise for controlling a VFD using commodity components
like an 8-bit PIC16F18345, 74183 decoder, and ULN2003 Darlington arrays.
This is not an useful example of a serious project. Anyone who wishes to
develop a real VFD controller are better off using dedicated components
such as a [Microchip HV5812.](https://www.microchip.com/wwwproducts/en/HV5812)

Created to drive a [salvaged NEC VS-10010-A VFD.](https://newscrewdriver.com/2019/04/02/sleuthing-nec-vsl0010-a-vfd-control-pinout/)
Whose display bit pattern can be created with help of a
[Google Sheets document.](https://docs.google.com/spreadsheets/d/1ENuk7oM4pA1yNM83J_-cP9LZN-myc9q3OBTB5-pvEr4/edit?usp=sharing)
