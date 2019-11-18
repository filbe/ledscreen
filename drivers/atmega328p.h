#ifndef __LCD_DRIVER_ATMEGA328P_H
#define __LCD_DRIVER_ATMEGA328P_H

#ifdef ATMEGA328P

#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

#define LCD_OUTPUT_PORT_REG	DDRD
#define LCD_OUTPUT_PORT 	PORTD

#define AVR_PGMMEM

inline void __LCD_DRIVER_INIT() {
	LCD_OUTPUT_PORT_REG |= 255;
}
inline void __LCD_DRIVER_WRITE_ZERO_SIG_UP() {
	LCD_OUTPUT_PORT |= 1;
}

inline void __LCD_DRIVER_WRITE_ZERO_SIG_UP_AFTER() {
	__asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");
}

inline void __LCD_DRIVER_WRITE_ZERO_SIG_DOWN() {
	LCD_OUTPUT_PORT &= ~(1);
}

inline void __LCD_DRIVER_WRITE_ZERO_SIG_DOWN_AFTER() {
	// we dont need this since other processing will spend some time, so this is a great place to squeeze all the juices out of the MCU ;)
	//__asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");
}

inline void __LCD_DRIVER_WRITE_ONE_SIG_UP() {
	LCD_OUTPUT_PORT |= 1;
}

inline void __LCD_DRIVER_WRITE_ONE_SIG_UP_AFTER() {
	__asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");
}

inline void __LCD_DRIVER_WRITE_ONE_SIG_DOWN() {
	LCD_OUTPUT_PORT &= ~(1);
}

inline void __LCD_DRIVER_WRITE_ONE_SIG_DOWN_AFTER() {
	__asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");__asm("nop");
}

inline void __LCD_DRIVER_WRITE_RESET() {
	LCD_OUTPUT_PORT &= ~(1);
}
inline void __LCD_DRIVER_WRITE_RESET_AFTER() {
	// we dont need this since other processing will spend some time, so this is a great place to squeeze all the juices out of the MCU ;)
	//__asm("nop");__asm("nop");__asm("nop");__asm("nop");

}

#endif /* ATMEGA328P */
#endif /* __LCD_DRIVER_ATMEGA328P_H */