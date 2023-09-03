/**************************************************
*STM32F103C8 -BluePill GPIO driver header file v1.0
*Autor: GrunF
*Date:17.11.2019
*Machine:Thinkpad T430
*Revision notes:29.01.2020
*Minor bugs fix
*Comment fix
****************************************************/

#ifndef stm32f103C8_h
#define stm32f103C8_h

/***************************************************
*
*GENERIC MACROS
*
****************************************************/
//-------------------MODE----------------------------
#define INPUT 0x00
#define OUTPUT (uint16_t) 0x01
#define ALTERNATIVE (uint16_t) 0x02
//----------------------------------------------------

//----------------------VALUE-------------------------
#define HIGH true
#define LOW false
//----------------------------------------------------
//----------------------SPEED-------------------------
#define SLOW (uint32_t) 2
#define MEDIUM (uint32_t) 1 //2MHz
#define FAST (uint32_t) 3
//----------------------------------------------------

//-------------INTERUPT EDGES-------------------------
typedef enum
{	
	RISING,
	FALLING,
	BOTH
}Edge_Select;
//----------------------------------------------------

//-----------------Port A CRL Pinout------------------
#define A0 (uint16_t) 0x00
#define A1 0x01
#define A2 0x02
#define A3 0x03
#define A4 0x04
#define A5 0x05
#define A6 0x06
#define A7 0x07

//-------------------Port A CRH Pinout----------------

#define A8 0x08
#define A9 0x09
#define A10 0x0a
#define A11 0x0b
#define A12 0x0c
#define A13 0x0d
#define A14 0x0e
#define A15 0x0f
#define A_ALL 0x23
//----------------------Port B CRL Pinout--------------
#define B0 0x10
#define B1 0x11
#define B2 0x12
#define B3 0x13
#define B4 0x14
#define B5 0x15
#define B6 0x16
#define B7 0x17

//------------------------Port B CRH Pinout--------------

#define B8 0x18
#define B9 0x19
#define B10 0x1a
#define B11 0x1b
#define B12 0x1c
#define BA13 0x1d
#define B14 0x1e
#define B15 0x1f
#define B_ALL 0x24
//-------------------------Port C CRH Pinout---------------

#define C13 0x20
#define C14 0x21
#define C15 0x22
#define C_ALL 0x25



#include "stm32f10x.h"                  // Device header

/***************************************************
*
*API's for GPIO 
*
****************************************************/

//-------------------------------------------
//Periherial clock control
//-------------------------------------------

	void GPIO_ClockCtrl(GPIO_TypeDef *pGPIOx, uint8_t EnOrDi); 																												//Periherial clock control
	
//-------------------------------------------
//Input Output Declaration
//-------------------------------------------

	void pinMode( uint16_t pinNumber, uint16_t PinMode); 						//GPIO init 
	
	void GPIO_ResetPort(GPIO_TypeDef *pGPIOx); 																																					//GPIO DE init 
	
//-------------------------------------------
//Port - Pin Read Write
//-------------------------------------------

	bool DigitalRead(uint16_t pinNumber); 																								//Read state of GPIO pin
	
	uint16_t GPIO_DigitalReadPort(GPIO_TypeDef *pGPIOx);																															//Read state of GPIO port
	
	void DigitalWrite(uint16_t PinNumber, bool Value);																		//Write to GPIO pin
	
	void GPIO_DigitalWritePort(GPIO_TypeDef *pGPIOx,uint16_t Value);																									//Write to GPIO port
	
	void GPIO_ToggleOutputPin(GPIO_TypeDef *pGPIOx,uint16_t PinNumber);  																							//Toggle output
	
	
//------------TO DO------------------------

// 1. Analog pin
// 2. Alternative function
//-------------------------------------------
//IRQ config and ISR handling - INTERRUPTS
//-------------------------------------------
void GPIO_AttachInterrupt(GPIO_TypeDef *pGPIOx, uint16_t PinNumber,Edge_Select Edge);
void GPIO_Interrupt_Enable(uint16_t PinNumber, IRQn_Type IrqNumber);
void GPIO_Interrupt_Clear(uint16_t PinNumber);


#endif