/*
 * hud21d_f.c
 *
 * Created: 21/01/2016 20:49:35
 *  Author: GroundLayer
 */ 

#include "modules/drivers/hud21d_f.h"
#include "modules/modules/hud21d_f.h"

#include "registrar/registrar.h"
#include "tasks/modules.h"

#define MODULE_NAME "HUD21D_F_TEMP_HUMI"
#define MODULE_DATA_SIZE 2
#define MODULE_TEMP "temperature"
#define MODULE_HUMIDITY "humidity"

data_name HUD21D_F_names[MODULE_DATA_SIZE] = { MODULE_TEMP , MODULE_HUMIDITY };
data_type HUD21D_F_types[] = { FLOAT , FLOAT };

void HUD21D_F_tick(void);
definition *HUD21D_F_def;

void HUD21D_F_module_init(void) {
	HU21D_F_init();
	HUD21D_F_def = register_definition(EVENT , MODULE_NAME , HUD21D_F_names , HUD21D_F_types , MODULE_DATA_SIZE , NULL, HUD21D_F_tick , 1000);
}

void HUD21D_F_tick(void) {
	float temp , humi;
	
	if(HU21D_F_read_temp_humi(&temp , &humi)) {
		instance inst = create_instance(MODULE_NAME);
		if(inst.def != NULL && inst.values != NULL){
			(*(float*) inst.values[0]) = temp;
			(*(float*) inst.values[1]) = humi;
			portBASE_TYPE xStatus = xQueueSendToBack(module_out, &inst , 10 / portTICK_RATE_MS );
			if(xStatus != pdPASS){
				release_instance(inst);
			}
		}
	}
}
