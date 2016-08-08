#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include <inttypes.h>

#include "console.h"

int main(void)
{


	// Demo write to registers.
	DDRB |= _BV(5);

	Console* console = new Console();
	console->println("ARDIX starting...");

	bool state = false;
	while(1) {
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

