#include "lcd_pcf8574t.h"
#include "eeprom/i2c_24lc256.h"

struct CELL {
	char buffer[3];
};

int main(void)
{
	twi_init();
	lcd_init(0x27, 16, 2);
	i2c_eeprom_init();

	struct CELL cells[7]; // we'll read/write within' first 7 bytes of memory

	// initialize memory
	for(int i = 0; i < 7; i++) {
		for(int j = 0; j < 3; j++) {
			cells[i].buffer[j] = 'X';
		}
	}

	struct DEV_EEPROM mem;

	// eeprom addr is 1010111|0 <- R/W bit
	// twi functions take unprepared address

	mem.addr = 0x57;
	mem.data = 0;

	// grab first 7 bytes of memory
	for(int i = 0; i < 7; i++) {
		eeprom.read_byte(&mem, i);
		itoa(mem.data, cells[i].buffer, 16);
	}

	// Write the grabbed bytes to screen
	for(int i = 0; i < 7; i++) {
		lcd_nibble.data(cells[i].buffer[0]);
		lcd_nibble.data(cells[i].buffer[1]);
	}


	while(1) {
	}
	return 0;
}
