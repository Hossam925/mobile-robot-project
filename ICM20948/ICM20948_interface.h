/*
A new complete driver for ICM-20948
Auther: Hossam
published: 5/3/2020

*/
#include <stdbool.h>
#include "ICM_20948_REGISTERS.h"
#include "ICM_20948_ENUMERATIONS.h"
#include "AK09916_REGISTERS.h"
#include "AK09916_ENUMERATIONS.h"
#include "GPIO_interface.h"
#include "SPI_Private.h"
#include "UART_interface.h"
#include "delay.h"

/////////////////Public definitions//////////////

#define MAG_AK09916_WHO_AM_I 0x4809
#define MAG_AK09916_I2C_ADDR 0x0C

typedef enum{
	OK,
	ERROR
}state;

typedef union {
		int16_t i16bit[3];
		uint8_t u8bit[6];
	} axis3_bit16_t;

	typedef union {
		int16_t i16bit;
		uint8_t u8bit[2];
	} axis1_bit16_t;

	typedef struct
	{
		uint8_t a : 2;
		uint8_t g : 2;
		uint8_t reserved_0 : 4;
	} fss_t;
	
	typedef union {
		axis3_bit16_t raw;
		struct
		{
			int16_t x;
			int16_t y;
			int16_t z;
		} axes;
	} named_3axis_t;

	typedef struct
	{
		named_3axis_t acc;
		named_3axis_t gyr;
		named_3axis_t mag;
		union {
			axis1_bit16_t raw;
			int16_t val;
		} tmp;
		fss_t fss; // Full-scale range settings for this measurement
		uint8_t magStat1;
		uint8_t magStat2;
	} ICM_sensor_data_t;



/////////////////Public functions///////////////

state ICM_Read(ICM_20948_Reg_Addr_e reg, uint8_t* data, uint8_t len);
state ICM_Write(ICM_20948_Reg_Addr_e reg, uint8_t* data, uint8_t len);
state ICM_SetBank(uint8_t Bank);


//interface functions
state ICM_init(void);
uint8_t ICM_GetWhoAmI(void);
state ICM_Reset(void);
state ICM_SetSampleRate(ICM_20948_LP_CONFIG_CYCLE_e mode);
state ICM_SetGyroScale(ICM_20948_GYRO_CONFIG_1_FS_SEL_e scale);
state ICM_SetAccScale(ICM_20948_ACCEL_CONFIG_FS_SEL_e scale);
state ICM_GyroDlpfCfg(ICM_20948_GYRO_CONFIG_1_DLPCFG_e filter);
state ICM_AccDlpfCfg(ICM_20948_ACCEL_CONFIG_DLPCFG_e filter);
state ICM_Dlpf(bool choice);
state ICM_Sleep(bool choice);
state ICM_LowPower(bool choice);
//magnetometer functions
state MAG_init(void);
state MAG_CheckWhoIAm(void);
//i2c slaves functions
state ICM_I2CMasterEnable(void);
state ICM_I2CSlv4SingleRead(uint8_t adress,uint8_t reg,uint8_t* data);
state ICM_I2CSlv4SingleWrite(uint8_t adress,uint8_t reg,uint8_t* data);
state ICM_I2CMasterReset(void);
state ICM_I2CMasterCofigSlv0(void);
//helper functions
state ICM_GetRawData(ICM_sensor_data_t* data_union);
state ICM_PrintRawData(ICM_sensor_data_t* data_union);
state ICM_PrintFormatedInt(int16_t data);
state ICM_GetScaledData(ICM_sensor_data_t* data_union);
state ICM_PrintScaledData(ICM_sensor_data_t* data_union);
uint8_t ICM_DataReady(void);
float getAccMG( int16_t raw, uint8_t fss );
float getGyrDPS( int16_t raw, uint8_t fss );
float getMagUT( int16_t raw );
float getTmpC( int16_t raw );
void printFormattedFloat(float val, uint8_t leading, uint8_t decimals);
