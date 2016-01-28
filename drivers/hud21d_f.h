/*
 * hud21d_f.h
 *
 * Created: 21/01/2016 20:33:28
 *  Author: GroundLayer
 */ 


#ifndef HUD21D_F_H_
#define HUD21D_F_H_

#include "asf.h"
#include "HAL/i2c.h"

#define HTU21DF_I2CADDR       0x40
#define HTU21DF_READTEMP      0xE3
#define HTU21DF_READHUM       0xE5
#define HTU21DF_WRITEREG       0xE6
#define HTU21DF_READREG       0xE7
#define HTU21DF_RESET		0xFE

bool HU21D_F_init(void);
bool HU21D_F_read_temp_humi(float* temp , float* humi);



#endif /* HUD21D_F_H_ */