#include "ICM20948_interface.h"

//Read a single or mulible bytes from an icm register
state ICM_Read(ICM_20948_Reg_Addr_e reg, uint8_t* data, uint8_t len){
		GPIO_set_pin_data( PORTD, 3 ,0);
    delayUs(5);
    SPI_uint8_tTrancieve(SPI0, ((reg & 0x7F) | 0x80) );
    for(uint32_t indi = 0; indi < len; indi++){
      *(data + indi) = SPI_uint8_tTrancieve(0,0x00);
    }
    delayUs(5);
    GPIO_set_pin_data( PORTD, 3 ,1);

    return OK;
  }

	
/////////////////////////////////////////////////////////////////////

//Write a single or mulible bytes to an icm register
state ICM_Write(ICM_20948_Reg_Addr_e reg, uint8_t* data, uint8_t len){
		GPIO_set_pin_data( PORTD, 3 ,0);
    delayUs(5);
    SPI_uint8_tTrancieve(SPI0, ((reg & 0x7F) | 0x00) );
    for(uint32_t indi = 0; indi < len; indi++){
    	SPI_uint8_tTrancieve(SPI0,*(data + indi));
    }
    delayUs(5);
    GPIO_set_pin_data( PORTD, 3 ,1);

    return OK;

}


/////////////////////////////////////////////////////////////////////


state ICM_SetBank(uint8_t Bank){
			uint8_t data = (Bank<<4) & 0x30;
			return ICM_Write(AGB0_REG_REG_BANK_SEL, &data, 1);
}


/////////////////////////////////////////////////////////////////////
state ICM_init(void){
	
			uint8_t whoami=0x00;
	
			//Stablize the SPI
			SPI_uint8_tTrancieve(SPI0,0x00);
			delayMs(10);
			//check who Am I
			while(whoami != 0xEA){
						UART_sendString("WhoAmI dose not match,Waiting...\n\r");
						whoami = ICM_GetWhoAmI();
						delayMs(500);
			}
			UART_sendString("sensor connected succesfully\n\r");
			//Reset
			ICM_Reset();
			delayMs(250);
			//wake up the sensor
			ICM_Sleep(false);
			ICM_LowPower(false);
			//define sample rate
			ICM_SetSampleRate(ICM_20948_Sample_Mode_Continuous);
			//define scales
			ICM_SetAccScale(gpm2);
			ICM_SetGyroScale(dps250);
			//configure filters
			ICM_AccDlpfCfg(acc_d473bw_n499bw);
			ICM_GyroDlpfCfg(gyr_d361bw4_n376bw5);
			//choose to enable or disable the filters
			ICM_Dlpf(true);
			//setup the magnetometer
			MAG_init();
			
			
			return OK;
}


/////////////////////////////////////////////////////////////////////


uint8_t ICM_GetWhoAmI(void){
			ICM_SetBank(0);
			uint8_t value = 0;
			ICM_Read(AGB0_REG_WHO_AM_I,&value,1);
			return value;

}


/////////////////////////////////////////////////////////////////////



state ICM_Reset(void){
			ICM_SetBank(0);
			ICM_20948_PWR_MGMT_1_t reg; 
			ICM_Read(AGB0_REG_PWR_MGMT_1, (uint8_t*)&reg, 1);
			//sensor reset
			reg.DEVICE_RESET = 1;
			reg.CLKSEL = ICM_20948_Clock_Auto;
			ICM_Write(AGB0_REG_PWR_MGMT_1, (uint8_t*)&reg, 1);
//			//sensor clock select
//			reg.DEVICE_RESET = 1;
//			reg.CLKSEL = ICM_20948_Clock_Auto;
//			ICM_Write(AGB0_REG_PWR_MGMT_1, (uint8_t*)&reg, 1);
	
			return OK;

}




/////////////////////////////////////////////////////////////////////
state ICM_SetSampleRate(ICM_20948_LP_CONFIG_CYCLE_e mode){
			//set the correct bank
			ICM_SetBank(0);
			//read the current value
			ICM_20948_LP_CONFIG_t reg;
			ICM_Read(AGB0_REG_LP_CONFIG,(uint8_t*) &reg,1);
			//update the value
			reg.ACCEL_CYCLE = mode;
			reg.GYRO_CYCLE = mode;
			//reg.I2C_MST_CYCLE = mode;
			ICM_Write(AGB0_REG_LP_CONFIG,(uint8_t*) &reg,1);
	
			return OK;
}




/////////////////////////////////////////////////////////////////////
state ICM_SetGyroScale(ICM_20948_GYRO_CONFIG_1_FS_SEL_e scale){
			//set the correct bank
			ICM_SetBank(2);
			//read the current value
			ICM_20948_GYRO_CONFIG_1_t reg;
			ICM_Read(AGB2_REG_GYRO_CONFIG_1,(uint8_t*) &reg,1);
			//update the value
			reg.GYRO_FS_SEL = scale;
			ICM_Write(AGB2_REG_GYRO_CONFIG_1,(uint8_t*) &reg,1);
			return OK;
}


/////////////////////////////////////////////////////////////////////


state ICM_SetAccScale(ICM_20948_ACCEL_CONFIG_FS_SEL_e scale){
			//set the correct bank
			ICM_SetBank(2);
			//read the current value
			ICM_20948_ACCEL_CONFIG_t reg;
			ICM_Read(AGB2_REG_ACCEL_CONFIG,(uint8_t*) &reg,1);
			//update the value
			reg.ACCEL_FS_SEL = scale;
			ICM_Write(AGB2_REG_ACCEL_CONFIG,(uint8_t*) &reg,1);
			return OK;
			
			
}


/////////////////////////////////////////////////////////////////////


state ICM_GyroDlpfCfg(ICM_20948_GYRO_CONFIG_1_DLPCFG_e filter){
			//set the correct bank
			ICM_SetBank(2);
			//read the current value
			ICM_20948_GYRO_CONFIG_1_t reg;
			ICM_Read(AGB2_REG_GYRO_CONFIG_1,(uint8_t*) &reg,1);
			//update the value
			reg.GYRO_DLPFCFG = filter;
			ICM_Write(AGB2_REG_GYRO_CONFIG_1,(uint8_t*) &reg,1);
			return OK;
}


/////////////////////////////////////////////////////////////////////
state ICM_AccDlpfCfg(ICM_20948_ACCEL_CONFIG_DLPCFG_e filter){
			//set the correct bank
			ICM_SetBank(2);
			//read the current value
			ICM_20948_ACCEL_CONFIG_t reg;
			ICM_Read(AGB2_REG_ACCEL_CONFIG,(uint8_t*) &reg,1);
			//update the value
			reg.ACCEL_DLPFCFG = filter;
			ICM_Write(AGB2_REG_ACCEL_CONFIG,(uint8_t*) &reg,1);
			return OK;
}


/////////////////////////////////////////////////////////////////////
state ICM_Dlpf(bool choice){
			//set the correct bank
			ICM_SetBank(2);
	
			//set Accelerometer value first
			//read the current value
			ICM_20948_ACCEL_CONFIG_t Areg;
			ICM_Read(AGB2_REG_ACCEL_CONFIG,(uint8_t*) &Areg,1);
			//update the value
			Areg.ACCEL_FCHOICE = choice;
			ICM_Write(AGB2_REG_ACCEL_CONFIG,(uint8_t*) &Areg,1);
			
			ICM_SetBank(2);
			//set Gyroscope value
			//read the current value
			ICM_20948_GYRO_CONFIG_1_t Greg;
			ICM_Read(AGB2_REG_GYRO_CONFIG_1,(uint8_t*) &Greg,1);
			//update the value
			Greg.GYRO_FCHOICE = choice;
			ICM_Write(AGB2_REG_GYRO_CONFIG_1,(uint8_t*) &Greg,1);
	
			return OK;
}


/////////////////////////////////////////////////////////////////////
state ICM_Sleep(bool choice){
			//set the correct bank
			ICM_SetBank(0);
			//Read the current value
			ICM_20948_PWR_MGMT_1_t reg; 
			ICM_Read(AGB0_REG_PWR_MGMT_1, (uint8_t*)&reg, 1);
			//sensor wakeup
			reg.SLEEP = choice;
			ICM_Write(AGB0_REG_PWR_MGMT_1, (uint8_t*)&reg, 1);
		
			return OK;

}



/////////////////////////////////////////////////////////////////////
state ICM_LowPower(bool choice){
			//set the correct bank
			ICM_SetBank(0);
			//Read the current value
			ICM_20948_PWR_MGMT_1_t reg; 
			ICM_Read(AGB0_REG_PWR_MGMT_1, (uint8_t*)&reg, 1);
			//sensor wakeup
			reg.LP_EN = choice;
			ICM_Write(AGB0_REG_PWR_MGMT_1, (uint8_t*)&reg, 1);
		
			return OK;
}




/////////////////////////////////////////////////////////////////////
state MAG_init(void){
			//enable the i2c master
			ICM_I2CMasterEnable();
			UART_sendString("Trying to connect to the the magnetometer...\n\r");
			//check magnetometer id
			for(uint8_t i =0;i<=5;i++){
					if(MAG_CheckWhoIAm() == OK){
							UART_sendString("Magnetometer connected succesfully\n\r");
							break;
					}
					else if(i == 5){
							UART_sendString("ERROR. Magnetometer didn't respond\n\r");
					}
					ICM_I2CMasterReset();
					delayMs(5);
			}
			//setting up the magnetometer settings
			AK09916_CNTL2_Reg_t reg;
			reg.MODE = AK09916_mode_cont_100hz;
			ICM_I2CSlv4SingleWrite(MAG_AK09916_I2C_ADDR,AK09916_REG_CNTL2,(uint8_t*)&reg);
			//conigure the magnetometer as slv0 for continouse reading
			ICM_I2CMasterCofigSlv0();
			
			return OK;
			
}



/////////////////////////////////////////////////////////////////////
state MAG_CheckWhoIAm(void){
			uint8_t whoiam1, whoiam2;
			ICM_I2CSlv4SingleRead(MAG_AK09916_I2C_ADDR,AK09916_REG_WIA1,&whoiam1);
			ICM_I2CSlv4SingleRead(MAG_AK09916_I2C_ADDR,AK09916_REG_WIA2,&whoiam2);
			if((whoiam1 == (MAG_AK09916_WHO_AM_I&0xff))&&(whoiam2 == (MAG_AK09916_WHO_AM_I>>8))){
					return OK;
			}
			return ERROR;
			
}



/////////////////////////////////////////////////////////////////////
state ICM_I2CMasterEnable(void){
		//disable passthrough
			//set the correct bank
			ICM_SetBank(0);
			//Read the current value
			ICM_20948_INT_PIN_CFG_t reg;
			ICM_Read(AGB0_REG_INT_PIN_CONFIG, (uint8_t*)&reg, 1);
			//update the values
			reg.BYPASS_EN = false;
			ICM_Write(AGB0_REG_INT_PIN_CONFIG, (uint8_t*)&reg, 1);
		//congiure clock and stop bits
			//set the correct bank
			ICM_SetBank(3);
			//Read the current value
			ICM_20948_I2C_MST_CTRL_t ctrl;
			ICM_Read(AGB3_REG_I2C_MST_CTRL, (uint8_t*)&ctrl, 1);
			//update the values
			ctrl.I2C_MST_CLK = 0x07;
			ctrl.I2C_MST_P_NSR = 1;
			ICM_Write(AGB3_REG_I2C_MST_CTRL, (uint8_t*)&ctrl, 1);
		//enable i2c master
			//set the correct bank
			ICM_SetBank(0);
			//Read the current value
			ICM_20948_USER_CTRL_t  uctrl;
			ICM_Read(AGB0_REG_USER_CTRL, (uint8_t*)&uctrl, 1);
			//update the values
			uctrl.I2C_MST_EN = 1;
			ICM_Write(AGB0_REG_USER_CTRL, (uint8_t*)&uctrl, 1);
			
			return OK;
			
}


/////////////////////////////////////////////////////////////////////
state ICM_I2CMasterReset(void){
			//set the correct bank
			ICM_SetBank(0);
			//Read the current value
			ICM_20948_USER_CTRL_t  ctrl;
			ICM_Read(AGB0_REG_USER_CTRL, (uint8_t*)&ctrl, 1);
			//update the values
			ctrl.I2C_MST_RST = 1;
			ICM_Write(AGB0_REG_USER_CTRL, (uint8_t*)&ctrl, 1);
	
			return OK;
}



/////////////////////////////////////////////////////////////////////
state ICM_I2CSlv4SingleRead(uint8_t adress,uint8_t reg,uint8_t* data){
			bool data_ready = false;
			adress |= 0x80;
		//set up the slave
			//set the correct bank
			ICM_SetBank(3);
			//send the slave adress
			ICM_Write(AGB3_REG_I2C_SLV4_ADDR,&adress,1);
			//send the reg adress
			ICM_Write(AGB3_REG_I2C_SLV4_REG,&reg,1);
			//setup the ctrl reg
			ICM_20948_I2C_SLV4_CTRL_t ctrl;
			ctrl.EN = 1;
			ctrl.DLY = 0;
			ctrl.INT_EN = 0;
			ctrl.REG_DIS = 0;
			ICM_Write(AGB3_REG_I2C_SLV4_CTRL,(uint8_t*)&ctrl,1);
		//wait for the data
			ICM_20948_I2C_MST_STATUS_t i2c_mst_status;
			//set the correct bank
			ICM_SetBank(0);
			uint16_t max = 0;
			while(!data_ready){
						ICM_Read(AGB0_REG_I2C_MST_STATUS,(uint8_t*)&i2c_mst_status,1);
						data_ready = i2c_mst_status.I2C_SLV4_DONE;
						data_ready |= (max<=1000);
						max++;
			}
		//get the data
			//set the correct bank
			ICM_SetBank(3);
			ICM_Read(AGB3_REG_I2C_SLV4_DI,data,1);
			
			if(i2c_mst_status.I2C_SLV4_NACK){
						return ERROR;
			}
			
			return OK;
			
			
}



/////////////////////////////////////////////////////////////////////
state ICM_I2CSlv4SingleWrite(uint8_t adress,uint8_t reg,uint8_t* data){
			bool data_ready = false;
			adress |= 0x00;
		//set up the slave
			//set the correct bank
			ICM_SetBank(3);
			//send the slave adress
			ICM_Write(AGB3_REG_I2C_SLV4_ADDR,&adress,1);
			//send the reg adress
			ICM_Write(AGB3_REG_I2C_SLV4_REG,&reg,1);
			//put the data in the DO registe
			ICM_Write(AGB3_REG_I2C_SLV4_DO,data,1);
			//setup the ctrl reg
			ICM_20948_I2C_SLV4_CTRL_t ctrl;
			ctrl.EN = 1;
			ctrl.DLY = 0;
			ctrl.INT_EN = 0;
			ctrl.REG_DIS = 0;
			ICM_Write(AGB3_REG_I2C_SLV4_CTRL,(uint8_t*)&ctrl,1);
		//wait for the data
			ICM_20948_I2C_MST_STATUS_t i2c_mst_status;
			//set the correct bank
			ICM_SetBank(0);
			uint16_t max = 0;
			while(!data_ready){
						ICM_Read(AGB0_REG_I2C_MST_STATUS,(uint8_t*)&i2c_mst_status,1);
						data_ready = i2c_mst_status.I2C_SLV4_DONE;
						data_ready |= (max<=1000);
						max++;
			}
			if(i2c_mst_status.I2C_SLV4_NACK){
						return ERROR;
			}
			
			return OK;
}



/////////////////////////////////////////////////////////////////////
state ICM_I2CMasterCofigSlv0(void){
			uint8_t adress = MAG_AK09916_I2C_ADDR|0x80;
		//set up the slave
			//set the correct bank
			ICM_SetBank(3);
			//send the slave adress
			ICM_Write(AGB3_REG_I2C_SLV0_ADDR,&adress,1);
			//send the reg adress
			uint8_t reg = AK09916_REG_ST1;
			ICM_Write(AGB3_REG_I2C_SLV0_REG,&reg,1);
			//put the data in the DO registe
			//setup the ctrl reg
			ICM_20948_I2C_SLVX_CTRL_t ctrl;
			ctrl.EN = 1;
			ctrl.BYTE_SW = 0;
			ctrl.GRP = 0;
			ctrl.LENG = 9;
			ctrl.REG_DIS = 0;
			ICM_Write(AGB3_REG_I2C_SLV0_CTRL,(uint8_t*)&ctrl,1);
	
			return OK;
}





/////////////////////////////////////////////////////////////////////
uint8_t ICM_DataReady(void){
			//set the correct bank
			ICM_SetBank(0);
			//Read the current value
			ICM_20948_INT_STATUS_1_t reg; 
			ICM_Read(AGB0_REG_INT_STATUS_1, (uint8_t*)&reg, 1);
	
			return reg.RAW_DATA_0_RDY_INT;
}
/////////////////////////////////////////////////////////////////////
state ICM_GetRawData(ICM_sensor_data_t* data_union){
			uint8_t data[14+9] = {0};
			//set the correct bank
			ICM_SetBank(0);
			//Read the data
			ICM_Read(AGB0_REG_ACCEL_XOUT_H, (uint8_t*)&data, 14+9);
			//update the data union
			//Accelerometer raw data
			data_union->acc.raw.i16bit[0] = (data[0]<<8) | (data[1]);
			data_union->acc.raw.i16bit[1] = (data[2]<<8) | (data[3]);
			data_union->acc.raw.i16bit[2] = (data[4]<<8) | (data[5]);
			//Gyro raw data
			data_union->gyr.raw.i16bit[0] = (data[6]<<8) | (data[7]);
			data_union->gyr.raw.i16bit[1] = (data[8]<<8) | (data[9]);
			data_union->gyr.raw.i16bit[2] = (data[10]<<8)| (data[11]);
			//Tempreture raw data
			data_union->tmp.raw.i16bit    = (data[12]<<8)| (data[13]);
			//Mag Raw data
			data_union->magStat1 = data[14];
			data_union->mag.raw.i16bit[0] = (data[16]<<8)| (data[15]);
			data_union->mag.raw.i16bit[1] = (data[18]<<8)| (data[17]);
			data_union->mag.raw.i16bit[2] = (data[20]<<8)| (data[19]);
			data_union->magStat2 = data[22];
			//Get the current scale values
			//set the correct bank
			ICM_SetBank(2);
			//Gyroscope scale
			ICM_20948_GYRO_CONFIG_1_t Greg;
			ICM_Read(AGB2_REG_GYRO_CONFIG_1, (uint8_t*)&Greg, 1);
			data_union->fss.a = Greg.GYRO_FS_SEL;
			//Accelometer scale
			ICM_20948_ACCEL_CONFIG_t reg;
			ICM_Read(AGB2_REG_ACCEL_CONFIG, (uint8_t*)&reg, 1);
			data_union->fss.a = reg.ACCEL_FS_SEL;
			ICM_20948_ACCEL_CONFIG_2_t acfg2;
			ICM_Read(AGB2_REG_ACCEL_CONFIG_2, (uint8_t*)&acfg2, 1);
			return OK;

}



/////////////////////////////////////////////////////////////////////
state ICM_GetScaledData(ICM_sensor_data_t* data_union){
			ICM_GetRawData(data_union);
			//Scaling accelometer
			data_union->acc.axes.x = getAccMG(data_union->acc.raw.i16bit[0],data_union->fss.a);
			data_union->acc.axes.y = getAccMG(data_union->acc.raw.i16bit[1],data_union->fss.a);
			data_union->acc.axes.z = getAccMG(data_union->acc.raw.i16bit[2],data_union->fss.a);
			//scaling gyroscope
			data_union->gyr.axes.x = getGyrDPS(data_union->gyr.raw.i16bit[0],data_union->fss.g);
			data_union->gyr.axes.y = getGyrDPS(data_union->gyr.raw.i16bit[1],data_union->fss.g);
			data_union->gyr.axes.z = getGyrDPS(data_union->gyr.raw.i16bit[2],data_union->fss.g);
			//scaling temp
			data_union->tmp.val    = getTmpC(data_union->tmp.raw.i16bit);
			//scalling magnetometer
			data_union->mag.axes.x = getMagUT(data_union->mag.raw.i16bit[0]);
			data_union->mag.axes.y = getMagUT(data_union->mag.raw.i16bit[1]);
			data_union->mag.axes.z = getMagUT(data_union->mag.raw.i16bit[2]);
	
			return OK;
}



/////////////////////////////////////////////////////////////////////
state ICM_PrintRawData(ICM_sensor_data_t* data_union){
			UART_sendString("RAW. Acc [ ");
			ICM_PrintFormatedInt( data_union->acc.raw.i16bit[0] );
			UART_sendString(", ");
			ICM_PrintFormatedInt( data_union->acc.raw.i16bit[1]);
			UART_sendString(", ");
			ICM_PrintFormatedInt( data_union->acc.raw.i16bit[2]);
			UART_sendString(" ], Gyr [ ");
			ICM_PrintFormatedInt( data_union->gyr.raw.i16bit[0] );
			UART_sendString(", ");
			ICM_PrintFormatedInt( data_union->gyr.raw.i16bit[1]);
			UART_sendString(", ");
			ICM_PrintFormatedInt( data_union->gyr.raw.i16bit[2] );
			UART_sendString(" ], Mag [ ");
			ICM_PrintFormatedInt( data_union->mag.raw.i16bit[0] );
			UART_sendString(", ");
			ICM_PrintFormatedInt( data_union->mag.raw.i16bit[1] );
			UART_sendString(", ");
			ICM_PrintFormatedInt( data_union->mag.raw.i16bit[2] );
			UART_sendString(" ], Tmp [ ");
			ICM_PrintFormatedInt( data_union->tmp.val );
			UART_sendString(" ] \n\r");
			
			return OK;
			
}


/////////////////////////////////////////////////////////////////////
state ICM_PrintFormatedInt(int16_t val){
			if(val > 0){
				UART_sendByte(UART_0,' ');
				if(val < 10000){ UART_sendByte(UART_0,'0'); }
				if(val < 1000 ){ UART_sendByte(UART_0,'0'); }
				if(val < 100  ){ UART_sendByte(UART_0,'0'); }
				if(val < 10   ){ UART_sendByte(UART_0,'0'); }
			}else{
				UART_sendByte(UART_0,'-');
				if(Myabs(val) < 10000){ UART_sendByte(UART_0,'0'); }
				if(Myabs(val) < 1000 ){ UART_sendByte(UART_0,'0'); }
				if(Myabs(val) < 100  ){ UART_sendByte(UART_0,'0'); }
				if(Myabs(val) < 10   ){ UART_sendByte(UART_0,'0'); }
			}
			UART_Print_Number(Myabs(val));
			
			return OK;

}





/////////////////////////////////////////////////////////////////////
state ICM_PrintScaledData(ICM_sensor_data_t* data_union){
			UART_sendString("RAW. Acc [ ");
			ICM_PrintFormatedInt( data_union->acc.axes.x);
			UART_sendString(", ");
			ICM_PrintFormatedInt( data_union->acc.axes.y);
			UART_sendString(", ");
			ICM_PrintFormatedInt( data_union->acc.axes.z);
			UART_sendString(" ], Gyr [ ");
			ICM_PrintFormatedInt( data_union->gyr.axes.x);
			UART_sendString(", ");
			ICM_PrintFormatedInt( data_union->gyr.axes.y);
			UART_sendString(", ");
			ICM_PrintFormatedInt( data_union->gyr.axes.z);
			UART_sendString(" ], Mag [ ");
			ICM_PrintFormatedInt( data_union->mag.raw.i16bit[0] );
			UART_sendString(", ");
			ICM_PrintFormatedInt( data_union->mag.raw.i16bit[1] );
			UART_sendString(", ");
			ICM_PrintFormatedInt( data_union->mag.raw.i16bit[2] );
			UART_sendString(" ], Tmp [ ");
			ICM_PrintFormatedInt( data_union->tmp.val);
			UART_sendString(" ] \n\r");
			
			return OK;
}





/////////////////////////////////////////////////////////////////////
float getAccMG( int16_t raw, uint8_t fss ){
  switch(fss){
    case 0 : return (((float)raw)/16.384); break;
    case 1 : return (((float)raw)/8.192); break;
    case 2 : return (((float)raw)/4.096); break;
    case 3 : return (((float)raw)/2.048); break;
    default : return 0; break;
  }
}




/////////////////////////////////////////////////////////////////////
float getGyrDPS( int16_t raw, uint8_t fss ){
  switch(fss){
    case 0 : return (((float)raw)/131); break;
    case 1 : return (((float)raw)/65.5); break;
    case 2 : return (((float)raw)/32.8); break;
    case 3 : return (((float)raw)/16.4); break;
    default : return 0; break;
  }
}




/////////////////////////////////////////////////////////////////////
float getMagUT( int16_t raw ){
  return (((float)raw)*0.15);
}



/////////////////////////////////////////////////////////////////////
float getTmpC( int16_t raw ){
  return (((float)raw)/333.87)+21;
}



/////////////////////////////////////////////////////////////////////
void printFormattedFloat(float val, uint8_t leading, uint8_t decimals){
  float aval = Myabs(val);
  if(val < 0){
    UART_sendByte(UART_0,'-');
  }else{
    UART_sendByte(UART_0,' ');
  }
  for( uint8_t indi = 0; indi < leading; indi++ ){
    uint32_t tenpow = 0;
    if( indi < (leading-1) ){
      tenpow = 1;
    }
    for(uint8_t c = 0; c < (leading-1-indi); c++){
      tenpow *= 10;
    }
    if( aval < tenpow){
      UART_sendByte(UART_0,'0');
    }else{
      break;
    }
  }
  if(val < 0){
    UART_Print_Number(Myabs(val));
  }
}




