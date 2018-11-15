/*
 * i2cHandler.h
 *
 *  Created on: Feb 24, 2012
 *      Author: jpollard
 */

#ifndef I2CHANDLER_H_
#define I2CHANDLER_H_

#include <string>

struct SensorData
{
    struct AccelData
    {
        short X;
        short Y;
        short Z;
    }Accelerometer;

    struct GyroData
    {
        short X;
        short Y;
        short Z;
    }Gyro;

};

class I2cHandler
{
public:
    I2cHandler();
    ~I2cHandler();

    SensorData getSensorData();

private:
    int _device;
    std::string _deviceFilePath = "/dev/i2c-3";

    void writeI2C(unsigned char* buffer, int bytestowrite);
    void writeAccel(unsigned char* buffer, int bytestowrite);
    void writeGyro(unsigned char* buffer, int bytestowrite);
    void writeCompass(unsigned char* buffer, int bytestowrite);

    void readI2C(unsigned char* buffer, int bytestoread);
    void readAccel(unsigned char* buffer, int bytestoread);
    void readGyro(unsigned char* buffer, int bytestoread);
    void readCompass(unsigned char* buffer, int bytestoread);
};

#endif /* I2CHANDLER_H_ */
