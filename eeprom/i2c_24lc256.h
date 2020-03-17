#include "twi/twi.h"

struct DEV_EEPROM {
	uint8_t addr;
	uint8_t data; // contains byte of data from last read or write operation
};

struct I2C_EEPROM {
	uint8_t (*write_byte)(struct DEV_EEPROM *dev_eeprom, uint16_t addr, uint8_t data);
	uint8_t (*read_byte)(struct DEV_EEPROM *dev_eeprom, uint16_t addr);
} eeprom;

void i2c_eeprom_init(void); // set function calls

uint8_t i2c_24lc256_write_byte(struct DEV_EEPROM *dev_eeprom, uint16_t addr, uint8_t data); // write specified byte
uint8_t i2c_24lc256_read_byte(struct DEV_EEPROM *dev_eeprom, uint16_t addr); // read byte from specified location in memory
