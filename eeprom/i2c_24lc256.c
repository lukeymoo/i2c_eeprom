#include "i2c_24lc256.h"

// setup function pointers
void i2c_eeprom_init(void)
{
	eeprom.read_byte = i2c_24lc256_read_byte;
	eeprom.write_byte = i2c_24lc256_write_byte;
	return;
}

uint8_t i2c_24lc256_write_byte(struct DEV_EEPROM *dev_eeprom, uint16_t addr, uint8_t data)
{
	_delay_ms(5);
	twi.start();
	if(!(twi.slaw(dev_eeprom->addr))) {
		return 0;
	}
	twi.send_byte(addr >> 8); // write to location, max address space is 0x7FFF(32K byte size cells)
	twi.send_byte(addr & 0xff);
	twi.send_byte(data);
	twi.stop();
	dev_eeprom->data = 0;
	return 1;
}

uint8_t i2c_24lc256_read_byte(struct DEV_EEPROM *dev_eeprom, uint16_t addr)
{
	_delay_ms(5);
	twi.start();
	twi.slaw(dev_eeprom->addr);
	twi.send_byte(addr >> 8);
	twi.send_byte(addr & 0xff);
	_delay_us(6);
	twi.start(); // REPEATED START
	twi.slar(dev_eeprom->addr);
	TWCR = (1 << TWINT) | (1 << TWEN); // READ
	while(!(TWCR & (1 << TWINT)));
	dev_eeprom->data = TWDR;
	twi.stop();
	return 1;
}
