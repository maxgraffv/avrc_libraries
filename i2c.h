#ifndef INCFILE1_H_
#define INCFILE1_H_


#endif /* INCFILE1_H_ */



#include <avr/io.h>
#include <util/twi.h>
#include <avr/interrupt.h>


void i2cMasterInit();

void i2cSlaveInit(uint8_t slave_address);

void i2cInit(uint8_t device_slave_address);

void i2cERROR(uint8_t error_code );

void i2cStart();

void i2cByteWrite(uint8_t data);

void i2cStop();

uint8_t i2cSlaveDataReceived();

uint8_t i2cRead(uint8_t addr, uint8_t register);

void i2cWrite(uint8_t addr, uint8_t register, uint8_t data2write);

uint8_t i2cReadAck();




