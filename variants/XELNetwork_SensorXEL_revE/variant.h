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

#define PA6  0  // D0/A0//PWM
#define PA7  1  // D1/A1//PWM
#define PB1  2  // D2/A2//PWM
#define PB6  3  // D3/A3//PWM
#define PB7  4  // D4//PWM
#define PB12 5  // D5/A5//PWM
#define PB13 6  // D6/A6//PWM
#define PB14 7  // D7/A7//PWM
#define PB15 8  // D8/A8//PWM
#define PA11 9  // D9//

#define PA10 10 // UART_RX
#define PA9  11 // UART_TX

#define PB11 12 // EX_UART_RX
#define PB10 13 // EX_UART_TX

#define PA3  14 // DXL_RX 
#define PA2  15 // DXL_TX
#define PA0  16 // DIR_PIN

#define PA1  17 // BUTTON
#define PA4  18 // LED

#define PB5  19 // MOSI
#define PB4  20 // MISO
#define PB3  21 // SCK
#define PIN_SPI_MOSI PB5
#define PIN_SPI_MISO PB4
#define PIN_SPI_SCK PB3

#define PB9  22 // SDA
#define PB8  23 // SCL

// This must be a literal
#define NUM_DIGITAL_PINS        24+8
// This must be a literal with a value less than or equal to to MAX_ANALOG_INPUTS
#define NUM_ANALOG_INPUTS       8
#define NUM_ANALOG_FIRST        24

// On-board LED pin number
#define LED_BUILTIN             PA4

// On-board user button
#define USER_BTN                PA1

// Timer Definitions
// Use TIM6/TIM7 when possible as servo and tone don't need GPIO output pin
#define TIMER_TONE              TIM6
#define TIMER_SERVO             TIM3  //TODO: advanced-control timers don't work

// UART Definitions
// Mandatory for Firmata
#define HAVE_HWSERIAL1
#define PIN_SERIAL_RX           PA10
#define PIN_SERIAL_TX           PA9
#define PIN_SERIAL1_RX          PA10
#define PIN_SERIAL1_TX          PA9

#define HAVE_HWSERIAL2
#define PIN_SERIAL2_RX          PA3
#define PIN_SERIAL2_TX          PA2

#define HAVE_HWSERIAL3
#define PIN_SERIAL3_RX          PB11
#define PIN_SERIAL3_TX          PB10

#define SERIAL_UART_INSTANCE    1

/* Extra HAL modules */
//#define HAL_ADC_MODULE_DISABLED
//#define HAL_I2C_MODULE_DISABLED
//#define HAL_RTC_MODULE_DISABLED
//#define HAL_SPI_MODULE_DISABLED
//#define HAL_TIM_MODULE_DISABLED


// DXL MODEL
#define DEFAULT_XEL_MODEL_NUM   44200
#define DEFAULT_DXL_SERIAL      Serial2
#define DEFAULT_DXL_PIN         PA0

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
#endif


#endif /* _VARIANT_ARDUINO_STM32_ */
