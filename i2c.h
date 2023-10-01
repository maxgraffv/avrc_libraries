#ifndef INCFILE1_H_
#define INCFILE1_H_


#endif /* INCFILE1_H_ */


#include <avr/io.h>
#include <util/twi.h>
#include <avr/interrupt.h>



//			MASTER TRANSMITTER
#define MT_START		0x08
#define	MT_R_START		0x10
#define MT_SLA_W_ACK	0x18
#define MT_SLA_W_NACK	0x20
#define MT_DATA_T_ACK	0x28
#define MT_DATA_T_NACK	0x30
#define MT_ARB_LOST		0x38


//			SLAVE RECEIVER
#define SR_SLA_W_ACK	0x60
#define SR_SLA_W_NACK	0x68
#define SR_GENCALL_ADDR_ACK	0x70
#define SR_ARB_LOST		0x78
#define SR_DATA_ACK		0x80
#define SR_DATA_NACK	0x88
#define	SR_GENCALL_DATA_ACK	0x90
#define SR_GENCALL_DATA_NACK 0x98
#define SR_STOP_RSTART	0xA0


//			MASTER RECEIVER
#define MR_START		0x08
#define MR_R_START		0x10
#define MR_ARB_LOST		0x38
#define MR_SLA_R_ACK	0x40
#define MR_SLA_R_NACK	0x48
#define MR_DATA_R_ACK	0x50
#define MR_DATA_R_NACK	0x58


//		SLAVE TRANSMITTER
#define ST_SLA_R_ACK	0xA8
#define ST_ARB_LOST		0xB0
#define ST_DATA_ACK		0xB8
#define ST_DATA_NACK	0xC0
#define ST_L_DATA_ACK	0xC8


void i2cMasterInit();

void i2cSlaveInit(uint8_t slave_address);

void i2cInit(uint8_t device_slave_address);

void i2cERROR(uint8_t error_code );

void i2cStart();

void i2cByteWrite(uint8_t data);

void i2cStop();

uint8_t i2cSlaveDataRecieved();

uint8_t i2cRead();
