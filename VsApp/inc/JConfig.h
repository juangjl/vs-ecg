/**
 * @file config.h
 *
 *  Config function
 *
 * @version $Revision$
 * @author JLJuang <jl_juang@vsigntek.com>
 * @note Copyright (c) 2021, VitalSigns Technology Co., Ltd., all rights reserved.
 * @note
*/
#ifndef __CONFIG_H__
#define __CONFIG_H__ 

#define JCONFIG_TYPE_STR 		(0)
#define JCONFIG_TYPE_INT 		(1)
#define JCONFIG_TYPE_FLOAT 	(1)


#define CONFIG_FILE_PATH					"./data/config.txt"

///-----------------------------------------------------------------------------------///
/// CONFIG ITEMS
///-----------------------------------------------------------------------------------///
#define CONFIG_ITEM_COM_PORT						"COM_PORT"
#define CONFIG_ITEM_SERIAL_PORT					"SERIAL_PORT"
#define CONFIG_ITEM_DATA_ROOT						"DATA_ROOT"

#define CONFIG_ITEM_BLE_DEVICE_NAME			"BLE_DEVICE_NAME"
#define CONFIG_ITEM_BLE_DEVICE_MAC			"BLE_DEVICE_MAC"

#define CONFIG_ITEM_SSN									"SSN"
#define CONFIG_ITEM_TIME_ZONE_SEC				"TIME_ZONE_SEC"
#define CONFIG_ITEM_VSC_MODE_SAVE				"VSC_MODE_SAVE"

typedef struct ConfigSt
{
	char strName[128];
	char strValue[128];	
	JINT iType;
} ConfigItemType;

extern ConfigItemType ConfigItem[];

extern void ConfigLoad();
extern void ConfigSave();

extern void ConfigStrGet(char *strName, char *strValue);
extern void ConfigStrSet(char *strName, char *strValue);

extern void ConfigIntGet(char *strName, JINT *piVal);
extern void ConfigIntSet(char *strName, JINT iVal);



extern void ConfigFloatGet(char *strName, JFLOAT *pfVal);
extern void ConfigFloatSet(char *strName, JFLOAT fVal);

#endif ///<  __CONFIG_H__

