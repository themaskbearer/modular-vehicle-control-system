/*
 * i2cHandler.cpp
 *
 *  Created on: Feb 24, 2012
 *      Author: jpollard
 */

#include "i2cHandler.h"

#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <iostream>
#include <cstdlib>
#include <errno.h>
#include <algorithm>

#include "I2Caddresses.h"
#include "utils/Exceptions.h"
#include "utils/ErrorLogger.h"
#include "utils/OperatorFunctions.h"

I2cHandler::I2cHandler()
{
    _device = open(_deviceFilePath.c_str(), O_RDWR);
    if(_device < 0) {
        ERROR_LOGGER.logError("Failed to open " + _deviceFilePath + " with errno " + errno);
        throw FileOpenFailure(_deviceFilePath);
    }

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

I2cHandler::~I2cHandler()
{
    close(_device);
}

void I2cHandler::writeI2C(unsigned char* buffer, int bytestowrite)
{
    int byteswriten = write(_device, buffer, bytestowrite);
    if(byteswriten != bytestowrite) {
        ERROR_LOGGER.logError("Failed I2C write with errno " + errno);
        throw I2CFailure("I2C write", errno);
    }
}

void I2cHandler::writeAccel(unsigned char* buffer, int bytestowrite)
{
    int error = ioctl(_device, I2C_SLAVE_FORCE, ACCEL_ADDR);
    if(error < 0) {
        ERROR_LOGGER.logError("Failed I2C write to the accelerometer with errno " + errno);
        throw I2CFailure("Set ioctl for writing Accelerometer", errno);
    }

    writeI2C(buffer, bytestowrite);
}

void I2cHandler::writeCompass(unsigned char* buffer, int bytestowrite)
{
    int error = ioctl(_device, I2C_SLAVE_FORCE, COMP_ADDR);
    if(error < 0) {
        ERROR_LOGGER.logError("Failed I2C write to the compass with errno " + errno);
        throw I2CFailure("Set ioctl for writing Compass", errno);
    }

    writeI2C(buffer, bytestowrite);
}

void I2cHandler::writeGyro(unsigned char* buffer, int bytestowrite)
{
    int error = ioctl(_device, I2C_SLAVE_FORCE, GYRO_ADDR);
    if(error < 0) {
        ERROR_LOGGER.logError("Failed I2C write to the gyro with errno " + errno);
        throw I2CFailure("Set ioctl for writing Gyro", errno);
    }

    writeI2C(buffer, bytestowrite);
}

void I2cHandler::readI2C(unsigned char* buffer, int bytestoread)
{
    writeI2C(buffer, 1);

    int bytesread = read(_device, &buffer[1], bytestoread);
    if(bytesread != bytestoread) {
        ERROR_LOGGER.logError("Failed I2C read with errno " + errno);
        throw I2CFailure("I2C read", errno);
    }
}

void I2cHandler::readAccel(unsigned char* buffer, int bytestoread)
{
    int error = ioctl(_device, I2C_SLAVE_FORCE, ACCEL_ADDR);
    if(error < 0) {
        ERROR_LOGGER.logError("Failed I2C read the accelerometer with errno " + errno);
        throw I2CFailure("Set ioctl for reading Accelerometer", errno);
    }

    readI2C(buffer, bytestoread);
}

void I2cHandler::readCompass(unsigned char* buffer, int bytestoread)
{
    int error = ioctl(_device, I2C_SLAVE_FORCE, COMP_ADDR);
    if(error < 0) {
        ERROR_LOGGER.logError("Failed I2C read the compass with errno " + errno);
        throw I2CFailure("Set ioctl for reading Compass", errno);
    }

    readI2C(buffer, bytestoread);
}

void I2cHandler::readGyro(unsigned char* buffer, int bytestoread)
{
    int error = ioctl(_device, I2C_SLAVE_FORCE, GYRO_ADDR);
    if(error < 0) {
        ERROR_LOGGER.logError("Failed I2C read the gyro with errno " + errno);
        throw I2CFailure("Set ioctl for reading Gyro", errno);
    }

    readI2C(buffer, bytestoread);
}

SensorData I2cHandler::getSensorData()
{
    SensorData Currentdata;

    unsigned char data[7];

    data[0] = ACCEL_DATAX0;

    try
    {
        readAccel(data, 6);
    }
    catch(Exception& e)
    {
        ERROR_LOGGER.logError(e.what());

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
        ERROR_LOGGER.logError(e.what());

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
