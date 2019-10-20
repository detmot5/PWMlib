/*  Library for software and hardware PWM operating for AVR uC.
 * 	It can be used in light brightness adjustment, controlling DC motor's speed or
 * 	as in example RGB LED control
 *
 *	Allows using soft and hard PWM in inverting mode or non-inverting mode
 *
 *  I recommend using 16MHZ crystal.
 *
 *  Required use soft_pwm_init() or hard_pwm_init function before using PWM
 *  Required use sei() function in main.c
 *
 * 	Libraries required : <avr/io.h> <avr/interrupt.h>
 *
 *  The library takes about 600 bytes of FLASH memory with sample program
 *  for all 4 software channels and hardware channel active.
 *
 *  MCU used in project is ATmega32
 *
 *
 *
 *  Created on: 3 oct 2019
 *      Author: Norbert Bielak
 *	pwm.h
 */

#ifndef PWMLIB_PWM_H_
#define PWMLIB_PWM_H_

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;

//-------------------------------------------------------------------------
// 						 PROGRAM SETTINGS
//-------------------------------------------------------------------------
#define USE_SOFT_PWM	1
#define USE_HARD_PWM 	1


#define GND_VCC_ON_SWITCH 1   // 1 non-inverting mode / 0 - inverting mode

#define USE_PWM_CHANNEL1	1 // Activating each PWM software chnnel
#define USE_PWM_CHANNEL2	1 //
#define USE_PWM_CHANNEL3	1 //
#define USE_PWM_CHANNEL4	1 //





//--------------------------------------------------------------------------
// 					 SIMPLYFYING PORT ACCESS MACROS
//--------------------------------------------------------------------------
// PORT - output
#define PORT(x) SPORT(x)
#define SPORT(x) (PORT##x)
// PIN - input
#define PIN(x) SPIN(x)
#define SPIN(x) (PIN##x)
// DDR - direction
#define DDR(x) SDDR(x)
#define SDDR(x) (DDR##x)


//--------------------------------------------------------------------------
//						MACROS FOR uC PINS AND PORTS
//--------------------------------------------------------------------------
#define HARD_PWM_PORT D // OCx PIN
#define HARD_PWM_PIN 7

#if USE_PWM_CHANNEL1 == 1
#define PWM_PORT_1 A
#define PWM_PIN_1 0
#endif

#if USE_PWM_CHANNEL2 == 1
#define PWM_PORT_2 A
#define PWM_PIN_2 1
#endif

#if USE_PWM_CHANNEL3 == 1
#define PWM_PORT_3 A
#define PWM_PIN_3 2
#endif

#if USE_PWM_CHANNEL4 == 1
#define PWM_PORT_4 A
#define PWM_PIN_4 3
#endif

//--------------------------------------------------------------------------
//				MACROS FOR CHANGE LOGIC STATE ON PWM PINS
//--------------------------------------------------------------------------
#if USE_PWM_CHANNEL1 == 1
#define SET_PWM1_HIGH PORT(PWM_PORT_1) |= (1<<PWM_PIN_1)
#define SET_PWM1_LOW PORT(PWM_PORT_1) &= ~(1<<PWM_PIN_1)
#endif

#if USE_PWM_CHANNEL2 == 1
#define SET_PWM2_HIGH PORT(PWM_PORT_2) |= (1<<PWM_PIN_2)
#define SET_PWM2_LOW PORT(PWM_PORT_2) &= ~(1<<PWM_PIN_2)
#endif

#if USE_PWM_CHANNEL3 == 1
#define SET_PWM3_HIGH PORT(PWM_PORT_3) |= (1<<PWM_PIN_3)
#define SET_PWM3_LOW PORT(PWM_PORT_3) &= ~(1<<PWM_PIN_3)
#endif

#if USE_PWM_CHANNEL4 == 1
#define SET_PWM4_HIGH PORT(PWM_PORT_4) |= (1<<PWM_PIN_4)
#define SET_PWM4_LOW PORT(PWM_PORT_4) &= ~(1<<PWM_PIN_4)
#endif
//--------------------------------------------------------------------------
// 					DECLARATIONS OF FUNCIONS AND VARIABLES
//--------------------------------------------------------------------------

extern volatile u8 pwm1, pwm2, pwm3, pwm4;



void soft_PWM_init(void);					// software pwm initialization
void hard_PWM_init(void);					// hardware pwm initialization
void soft_PWM_write(u8 channel, u16 width); // soft pwm width adjustment
void hard_PWM_write(u8 width);				// hard pwm width adjustment

#endif /* PWMLIB_PWM_H_ */
