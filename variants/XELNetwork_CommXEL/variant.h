/*
  Copyright (c) 2011 Arduino.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef _VARIANT_ARDUINO_STM32_
#define _VARIANT_ARDUINO_STM32_

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/*----------------------------------------------------------------------------
 *        Pins
 *----------------------------------------------------------------------------*/

#define PA11   0 //OTG_FS_N
#define PA12   1 //OTG_FS_P

#define PD6    2 //UART_RX
#define PD5    3 //UART_TX

#define PB7    4 //DXL_RX 
#define PB6    5 //DXL_TX
#define PB8    6 //DIR_PIN

#define PC12   7 //BUTTON
#define PC11   8 //LED

#define PA1    9 //ETH_REF_CLK
#define PA2    10 //ETH_MDIO
#define PA7    11 //ETH_CRS_DV
#define PC1    12 //ETH_MDC
#define PC0    13 //ETH_RXER
#define PC4    14 //ETH_RXD0
#define PC5    15 //ETH_RXD1
#define PB11   16 //ETH_RX_EN
#define PB12   17 //ETH_TXD0
#define PB13   18 //ETH_TXD1


// This must be a literal
#define NUM_DIGITAL_PINS        19
// This must be a literal with a value less than or equal to to MAX_ANALOG_INPUTS
#define NUM_ANALOG_INPUTS       0
#define NUM_ANALOG_FIRST        19

// On-board LED pin number
#define LED_BUILTIN             PC11

// On-board user button
#define USER_BTN                PC12

// Timer Definitions
// Use TIM6/TIM7 when possible as servo and tone don't need GPIO output pin
#define TIMER_TONE              TIM6
#define TIMER_SERVO             TIM7

// UART Definitions
#define HAVE_HWSERIAL1
#define PIN_SERIAL1_RX          PD6
#define PIN_SERIAL1_TX          PD5

#define HAVE_HWSERIAL2
#define PIN_SERIAL2_RX          PB7
#define PIN_SERIAL2_TX          PB6

//#define SERIAL_UART_INSTANCE    1
#define ENABLE_SERIALUSB

/* Extra HAL modules */
#define HAL_ETH_MODULE_ENABLED
#define HAL_IWDG_MODULE_ENABLED
// #define HAL_PCD_MODULE_ENABLED

#ifdef __cplusplus
} // extern "C"
#endif
/*----------------------------------------------------------------------------
 *        Arduino objects - C++ only
 *----------------------------------------------------------------------------*/

#ifdef __cplusplus
// These serial port names are intended to allow libraries and architecture-neutral
// sketches to automatically default to the correct port name for a particular type
// of use.  For example, a GPS module would normally connect to SERIAL_PORT_HARDWARE_OPEN,
// the first hardware serial port whose RX/TX pins are not dedicated to another use.
//
// SERIAL_PORT_MONITOR        Port which normally prints to the Arduino Serial Monitor
//
// SERIAL_PORT_USBVIRTUAL     Port which is USB virtual serial
//
// SERIAL_PORT_LINUXBRIDGE    Port which connects to a Linux system via Bridge library
//
// SERIAL_PORT_HARDWARE       Hardware serial port, physical RX & TX pins.
//
// SERIAL_PORT_HARDWARE_OPEN  Hardware serial ports which are open for use.  Their RX & TX
//                            pins are NOT connected to anything by default.
#define SERIAL_PORT_MONITOR     Serial
#define SERIAL_PORT_HARDWARE    Serial
#define SERIAL_PORT_USBVIRTUAL  Serial
#endif

#endif /* _VARIANT_ARDUINO_STM32_ */
