/*
 * i2cHandler.h
 *
 *  Created on: Feb 24, 2012
 *      Author: jpollard
 */

#ifndef I2CHANDLER_H_
#define I2CHANDLER_H_

struct sensordata
{
	struct acceldata
	{
		short X;
		short Y;
		short Z;
	}Accelerometer;

	struct gyrodata
	{
		short X;
		short Y;
		short Z;
	}Gyro;

};

class i2cHandler
{
private:
	int device;

	void Initialize();

	void writeI2C(unsigned char* buffer, int bytestowrite);
	void writeAccel(unsigned char* buffer, int bytestowrite);
	void writeGyro(unsigned char* buffer, int bytestowrite);
	void writeComp(unsigned char* buffer, int bytestowrite);

	void readI2C(unsigned char* buffer, int bytestoread);
	void readAccel(unsigned char* buffer, int bytestoread);
	void readGyro(unsigned char* buffer, int bytestoread);
	void readComp(unsigned char* buffer, int bytestoread);

public:
	i2cHandler();
	virtual ~i2cHandler();

	sensordata getSensorData();
};

#endif /* I2CHANDLER_H_ */
