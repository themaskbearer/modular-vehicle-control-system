/*
 * i2cHandler.cpp
 *
 *  Created on: Feb 24, 2012
 *      Author: jpollard
 */

#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <iostream>
#include <cstdlib>
#include <errno.h>

#include <algorithm>

#include "i2cHandler.h"
#include "I2Caddresses.h"
#include "Exceptions.h"
#include "ErrorHandler.h"

i2cHandler::i2cHandler()
{
	Initialize();
}

i2cHandler::~i2cHandler()
{
	close(device);
}

void i2cHandler::Initialize()
{
	device = open("/dev/i2c-3", O_RDWR);
	
	try
	{
		unsigned char accelreg[4];
		accelreg[0] = ACCEL_POWER_CTL;
		accelreg[1] = ACCEL_PWR_CTL_VAL;
		accelreg[2] = ACCEL_DATA_FORMAT;
		accelreg[3] = ACCEL_DATA_FORMAT_VAL;
		writeAccel(accelreg, 2);
		writeAccel(&accelreg[2], 2);

		unsigned char gyroreg[6];
		gyroreg[0] = GYRO_DLPF_FS;
		gyroreg[1] = GYRO_DLPF_FS_VAL;
		gyroreg[2] = GYRO_SMPLRT_DV;
		gyroreg[3] = GYRO_SMPLRT_DV_VAL;
		gyroreg[4] = GYRO_PWR_MGM;
		gyroreg[5] = GYRO_PWR_MGM_VAL;
		writeGyro(gyroreg, 2);
		writeGyro(&gyroreg[2], 2);
		writeGyro(&gyroreg[4], 2);
	}
	catch(Exception& e)
	{
		ErrorHandler::recorderror(Exception("Failed to initialize device: "+ e.Message, e.errorvalue));
		throw e;
	}
}

void i2cHandler::writeI2C(unsigned char* buffer, int bytestowrite)
{
	int byteswriten = write(device, buffer, bytestowrite);

	if(byteswriten != bytestowrite)
		throw Exception("Failed to write to I2C bus", errno);

	return;
}

void i2cHandler::writeAccel(unsigned char* buffer, int bytestowrite)
{
	int error = ioctl(device, I2C_SLAVE_FORCE, ACCEL_ADDR);

	if(error < 0)
		throw Exception("Failed set ioctl for writing Accelerometer", errno);
	else
		writeI2C(buffer, bytestowrite);
	
}

void i2cHandler::writeComp(unsigned char* buffer, int bytestowrite)
{
	int error = ioctl(device, I2C_SLAVE_FORCE, COMP_ADDR);

	if(error < 0)
		throw Exception("Failed set ioctl for writing Compass", errno);
	else
		writeI2C(buffer, bytestowrite);
}

void i2cHandler::writeGyro(unsigned char* buffer, int bytestowrite)
{
	int error = ioctl(device, I2C_SLAVE_FORCE, GYRO_ADDR);

	if(error < 0)
		throw Exception("Failed to set ioctl for writing Gyro", errno);
	else
		writeI2C(buffer, bytestowrite);
}

void i2cHandler::readI2C(unsigned char* buffer, int bytestoread)
{
	writeI2C(buffer, 1);

	int bytesread = read(device, &buffer[1], bytestoread);

	if(bytesread != bytestoread)
		throw Exception("Failed to read bytes from I2C", errno);

	return;
}

void i2cHandler::readAccel(unsigned char* buffer, int bytestoread)
{
	int error = ioctl(device, I2C_SLAVE_FORCE, ACCEL_ADDR);

	if(error < 0)
		throw Exception("Failed to set ioctl for reading Accelerometer", errno);
	else
		readI2C(buffer, bytestoread);

}

void i2cHandler::readComp(unsigned char* buffer, int bytestoread)
{
	int error = ioctl(device, I2C_SLAVE_FORCE, COMP_ADDR);

	if(error < 0)
		throw Exception("Failed to set ioctl for reading Compass", errno);
	else
		readI2C(buffer, bytestoread);
}

void i2cHandler::readGyro(unsigned char* buffer, int bytestoread)
{
	int error = ioctl(device, I2C_SLAVE_FORCE, GYRO_ADDR);

	if(error < 0)
		throw Exception("Failed to set ioctl for reading Gyro", errno);
	else
		readI2C(buffer, bytestoread);
}

sensordata i2cHandler::getSensorData()
{
	sensordata Currentdata;

	unsigned char data[7];

	data[0] = ACCEL_DATAX0;

	try
	{
		readAccel(data, 6);
	}
	catch(Exception& e)
	{
		ErrorHandler::recorderror(e);

		for(int i = 0; i < 7; i++)
			data[i] = 0;
	}
	Currentdata.Accelerometer.X = *reinterpret_cast<short *>(&data[1]);
	Currentdata.Accelerometer.Y = *reinterpret_cast<short *>(&data[3]);
	Currentdata.Accelerometer.Z = *reinterpret_cast<short *>(&data[5]);

	data[0] = GYRO_XOUT_H;
	try
	{
		readGyro(data, 6);
	}
	catch(Exception& e)
	{
		ErrorHandler::recorderror(e);

		for(int i = 0; i < 7; i++)
			data[i] = 0;
	}
	std::swap(data[1], data[2]);
	std::swap(data[3], data[4]);
	std::swap(data[5], data[6]);
	Currentdata.Gyro.X = *reinterpret_cast<short *>(&data[1]);
	Currentdata.Gyro.Y = *reinterpret_cast<short *>(&data[3]);
	Currentdata.Gyro.Z = *reinterpret_cast<short *>(&data[5]);

	return Currentdata;
}
