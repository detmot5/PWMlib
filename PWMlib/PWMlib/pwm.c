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
 *  Required libraries : <avr/io.h> <avr/interrupt.h>
 *
 *  The library takes about 600 bytes of FLASH memory with sample program
 *  for all 4 software channels and hardware channel active.
 *
 *  MCU used in project is ATmega32
 *
 *  Created on: 3 oct 2019
 *      Author: Norbert Bielak
 *	pwm.c
 */



#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "pwm.h"
typedef uint8_t u8;
typedef uint16_t u16;
 // variables used in interrupt
volatile u8 pwm1, pwm2, pwm3, pwm4;



static inline void soft_pwm_dir_out(void){
#if USE_PWM_CHANNEL1 == 1
	DDR(PWM_PORT_1) |= (1<<PWM_PIN_1);
#endif
#if USE_PWM_CHANNEL2 == 1
	DDR(PWM_PORT_2) |= (1<<PWM_PIN_2);
#endif
#if USE_PWM_CHANNEL3 == 1
	DDR(PWM_PORT_3) |= (1<<PWM_PIN_3);
#endif
#if USE_PWM_CHANNEL4 == 1
	DDR(PWM_PORT_4) |= (1<<PWM_PIN_4);
#endif
}

//--------------------------------------------------------------------
//					    USER'S FUNCTION
//--------------------------------------------------------------------

#if USE_SOFT_PWM == 1
void soft_PWM_init(void){
	// PWM channels - output
	soft_pwm_dir_out();


	// Timer mode - normal
	TCCR0 |= (1<<CS00); // prescaler /1
	TIMSK |= (1<<TOIE0); // OVF interrupts permission
	TCNT0 = 100;

}
#endif

 	 	 // hardware PWM
#if USE_HARD_PWM == 1
void hard_PWM_init(void){
	DDR(HARD_PWM_PORT) |= (1<<HARD_PWM_PIN);
	TCCR2 |= (1<<WGM20) | (1<<WGM21); //  fastPWM mode
	TCCR2 |= (1<<CS20); // prescaler /1
	TCCR2 |= (1<<COM21); // non-inverting mode
	OCR2 = 0;
}
#endif

// Width setting on each channels

#if USE_SOFT_PWM == 1

void soft_PWM_write(u8 channel, u16 width){

#if GND_VCC_ON_SWITCH == 0 // inverting mode (common anode)
	  width = 255-width;
#endif

	switch(channel){
		case 1:	pwm1 = width; break;
		case 2: pwm2 = width; break;
		case 3: pwm3 = width; break;
		case 4: pwm4 = width; break;
	}
}
#endif
	// Width setting on hardware channel
#if USE_HARD_PWM == 1

void hard_PWM_write(u8 width){

#if GND_VCC_ON_SWITCH == 0
	width = 255-width;
#endif

	OCR2 = width;
}
#endif

//---------------------------------------------------------------------
//							ISR
//---------------------------------------------------------------------

ISR( TIMER0_OVF_vect ) {
	TCNT0 = 100;
	static uint8_t counter;

#if USE_PWM_CHANNEL1 == 1
	if(counter <= pwm1) SET_PWM1_HIGH; else SET_PWM1_LOW;
	if(pwm1 == 0) SET_PWM1_LOW;
#endif
#if USE_PWM_CHANNEL2 == 1
	if(counter <= pwm2) SET_PWM2_HIGH; else SET_PWM2_LOW;
	if(pwm2 == 0) SET_PWM2_LOW;
#endif
#if USE_PWM_CHANNEL3 == 1
	if(counter <= pwm3) SET_PWM3_HIGH; else SET_PWM3_LOW;
	if(pwm3 == 0) SET_PWM3_LOW;
#endif
#if USE_PWM_CHANNEL4 == 1
	if(counter <= pwm4) SET_PWM4_HIGH; else SET_PWM4_LOW;
	if(pwm4 == 0) SET_PWM4_LOW;
#endif


	counter++;
	if(counter>255) counter = 0;
}






