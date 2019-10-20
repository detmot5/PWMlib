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
 * 	Required libraires : <avr/io.h> <avr/interrupt.h>
 *
 *  The library takes about 600 bytes of FLASH memory with sample program
 *  for all 4 software channels and hardware channel active.
 *
 *  MCU used in project is ATmega32
 *
 *  Created on: 3 oct 2019
 *      Author: Norbert Bielak
 *	main.c
 */

//---------------------------------------------------------------------------------
// 								SAMPLE PROGRAM
//---------------------------------------------------------------------------------

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "PWMlib/pwm.h"

#define RED_CH 1
#define GREEN_CH 2
#define BLUE_CH 3

#define COLOR_HEX 1

void color_set(u8 red, u8 green, u8 blue);
void color_hex(u32 hex_color);



void color_set(u8 red, u8 green, u8 blue){
	soft_PWM_write(RED_CH, red);
	soft_PWM_write(GREEN_CH, green);
	soft_PWM_write(BLUE_CH, blue);
}
void color_hex(u32 hex_color){
	color_set((hex_color & 0xFF0000) >> 16, (hex_color & 0x00FF00) >> 8, (hex_color & 0x0000FF));
}



int main(void) {
sei();

 soft_PWM_init();
 hard_PWM_init();


 while(1){
// diode lights in all RGB colors

	  for (u16 i = 0; i <= 255; i++) {
		 color_set(255 - i, i, 0);
		 hard_PWM_write(i); // another LED control
	    _delay_ms(1);
	  }

	  for (u16 i = 0; i <= 255; i++) {
		 color_set(0, 255 - i, i);
		_delay_ms(1);
	  }

	  for (u16 i = 0; i <= 255; i++) {
		 color_set(i, 0, 255 - i);
		 hard_PWM_write(255-i);
		_delay_ms(1);
	  }

	 // Color can also be enteret by hex value
	 /* color_hex(0xffab02);*/
//cos
   }
}

