#include <avr/io.h>
#include <util/twi.h>
#include <avr/interrupt.h>
#include "i2c.h"

void i2cMasterInit()
{
	TWSR = 0x00; //Prescaler to 1
	TWBR = 60; //Set Bitrate
	TWCR = (1<<TWEN) | (1<<TWIE); //TWI Enable
}

void i2cSlaveInit(uint8_t slave_address)
{
	TWAR = (slave_address<<1); //set slave Address
	TWCR = (1<<TWEA) | (1<<TWEN) | (1<<TWIE);
}

void i2cERROR(uint8_t error_code)
{
	
}

void i2cStart()
{
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	while(!(TWCR & (1<<TWINT)))
	;

}

void i2cByteWrite(uint8_t data)
{
	TWDR = data;
	TWCR = (1<<TWINT) | (1<<TWEN);
	
	while(!(TWCR & (1<<TWINT)))
	;
}

void i2cStop()
{
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
	while (TWCR & (1 << TWSTO));
}

uint8_t i2cSlaveDataRecieved() //Put into ISR(TWI_vect)
{
	if ((TWSR & 0xF8) == MT_START)
	{
		TWCR |= (1<<TWINT) | (1<<TWEA);
	}
	else if ((TWSR & 0xF8) == 0x80)
	{
		TWCR |= (1<<TWINT) | (1<<TWEA);
		return TWDR;
	}
	else
	{
		TWCR |= (1<<TWINT) | (1<<TWEA);
	}
}

uint8_t i2cRead()
{
	TWCR |= (1<<TWEN) | (1<<TWINT);
	while (!(TWCR & (1 << TWINT)));
	
	return TWDR;
}
