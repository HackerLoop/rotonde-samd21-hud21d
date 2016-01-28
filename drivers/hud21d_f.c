/*
 * hud21d_f.c
 *
 * Created: 21/01/2016 20:33:17
 *  Author: GroundLayer
 */ 

#include "modules/drivers/hud21d_f.h"

bool HU21D_F_init(void){
	unsigned char data;
	data = HTU21DF_RESET;
	HAL_I2C_write(HTU21DF_I2CADDR , 1 , &data );
	vTaskDelay(100);
	
	data = HTU21DF_READREG;
	HAL_I2C_write(HTU21DF_I2CADDR , 1 , &data );
	HAL_I2C_read(HTU21DF_I2CADDR , 1 , &data );
	
	if(data == 0x20){
		return false;
	}
	
	return true;
}

bool HU21D_F_read_temp_humi(float* temp , float* humi){
	
	unsigned char data[3];
	uint16_t buffer;
	data[0] = HTU21DF_READTEMP;
	HAL_I2C_write(HTU21DF_I2CADDR , 1 , data );
	vTaskDelay(50);
	if(HAL_I2C_read(HTU21DF_I2CADDR , 3 , data) != STATUS_OK){
		return false;
	}
	buffer = data[0] << 8 | data[1];
	*temp = (float) buffer;
	*temp *= 175.72;
	*temp /= 65536;
	*temp -= 46.85;
	
	data[0] = HTU21DF_READHUM;
	HAL_I2C_write(HTU21DF_I2CADDR , 1 , data );
	vTaskDelay(50);
	if(HAL_I2C_read(HTU21DF_I2CADDR , 3 , data) != STATUS_OK){
		return false;
	}
	buffer = data[0] << 8 | data[1];
	*humi = (float) buffer;
	*humi *= 125;
	*humi /= 65536;
	*humi -= 6;
	
	return true;
}