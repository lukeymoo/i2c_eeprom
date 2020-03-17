#include "lcd_pcf8574t.h"

int main(void)
{
	twi_init();
	lcd_init(0x27, 16, 2);

	while(1) {
	}
	return 0;
}
