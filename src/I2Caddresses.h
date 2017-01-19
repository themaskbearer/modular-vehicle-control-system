

#ifndef IMU_REGISTERS
#define	IMU_REGISTERS

#define ACCEL_ADDR				0x53
#define ACCEL_DEVID				0x00
#define ACCEL_BW_RATE			0x2C
#define ACCEL_POWER_CTL			0x2D
#define ACCEL_DATA_FORMAT		0x31
#define ACCEL_DATAX0			0x32
#define ACCEL_DATAX1			0x33
#define ACCEL_DATAY0			0x34
#define ACCEL_DATAY1			0x35
#define ACCEL_DATAZ0			0x36
#define ACCEL_DATAZ1			0x37

#define ACCEL_DEVID_VAL			0xE5
#define ACCEL_PWR_CTL_VAL		0x08
#define ACCEL_DATA_FORMAT_VAL	0x0B

#define GYRO_ADDR				0x68
#define GYRO_WHO_AM_I			0x00
#define GYRO_SMPLRT_DV			0x15
#define GYRO_DLPF_FS			0x16
#define GYRO_TEMP_OUT_H			0x1B
#define GYRO_TEMP_OUT_L			0x1C
#define GYRO_XOUT_H				0x1D
#define GYRO_XOUT_L				0x1E
#define GYRO_YOUT_H				0x1F
#define GYRO_YOUT_L				0x20
#define GYRO_ZOUT_H				0x21
#define GYRO_ZOUT_L				0x22
#define GYRO_PWR_MGM			0x3E

#define GYRO_WHO_AM_I_VAL		0x68
#define GYRO_SMPLRT_DV_VAL		0x09
#define GYRO_DLPF_FS_VAL		0x19
#define GYRO_PWR_MGM_VAL		0x01

#define COMP_ADDR				0x1E
#define COMP_CONFIG_A			0x00
#define COMP_CONFIG_B			0x01
#define COMP_MODE				0x02
#define COMP_X_MSB				0x03
#define COMP_X_LSB				0x04
#define COMP_Y_MSB				0x05
#define COMP_Y_LSB				0x06
#define COMP_Z_MSB				0x07
#define COMP_Z_LSB				0x08
#define COMP_ID_A				0x0A

#define COMP_ID_A_VAL			0x48
#define COMP_CONFIG_A_VAL		0x18
#define COMP_CONFIG_B_VAL		0x20
#define COMP_MODE_VAL			0x00

#endif
