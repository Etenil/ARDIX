#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include <inttypes.h>

#include "console.hh"
#include "platform/arduino_nano.h"
#include "memory.hh"
#include "kernelmem.hh"

int main(void)
{
	uint8_t run_kernel = 1;

	// Demo write to registers.
	DDRB |= _BV(5);

	Console* console = new Console();
	console->println("ARDIX starting...");

	Memory* mem = new Memory(console);
	KernelMem* kmem = new KernelMem(
		(uint8_t)KERNEL_START,
		(uint8_t)KERNEL_END - KERNEL_START
	);


	bool state = false;
	while(run_kernel) {
		if (!state) {
			console->println("LED on...");
			PORTB |= _BV(5);
			state = true;
		} else {
			console->println("LED off...");
			PORTB &= ~_BV(5);
			state = false;
		}
		_delay_ms(5000);
	}

	return 0;
}

