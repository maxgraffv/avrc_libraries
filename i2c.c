#include <avr/io.h>
#include <util/twi.h>
#include <avr/interrupt.h>


void i2cMasterInit()
{
	TWSR = 0x00;//Prescaler to 1
	TWBR = 60; //Set Bitrate
	TWCR = (1<<TWEN); //TWI Enable
}

void i2cSlaveInit(uint8_t slave_address)
{
	TWAR = (slave_address<<1); //set slave Address
	TWCR = (1<<TWEA) | (1<<TWEN);
}

void i2cERROR(uint8_t error_code)
{
	
}

void i2cStart()
{
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	while(!(TWCR & (1<<TWINT)))
		;
		
	if(TWSR != (0x08)) //0x08 - Master Status Register i2c Start
		i2cERROR(0x08);
}

void i2cWrite(uint8_t data)
{
	TWDR = data;
	TWCR = (1<<TWINT) | (1<<TWEN);	
	
	while(!(TWCR & (1<<TWINT)))
		;
	
	if(TWSR != 0x28) //0x28 - Master Status Register Data sent Acknowledge
		i2cERROR(0x28);
}

void i2cStop()
{
		TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
		while (TWCR & (1 << TWSTO));
}


uint8_t data_recieved()
{
	if ((TWSR & 0xF8) == TW_SR_SLA_ACK)
	{
		// Slave address received with acknowledge
		TWCR |= (1 << TWINT) | (1 << TWEA); // Clear interrupt flag and send acknowledge
	}
	else if ((TWSR & 0xF8) == TW_SR_DATA_ACK)
	{
		// Data received with acknowledge
		TWCR |= (1 << TWINT) | (1 << TWEA); // Clear interrupt flag and send acknowledge
		return TWDR;
	}
	else
	{
		// Other cases
		TWCR |= (1 << TWINT) | (1 << TWEA); // Clear interrupt flag and send acknowledge
	}
}
