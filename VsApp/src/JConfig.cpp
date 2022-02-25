/**
 * @file JConfig.cpp
 *
 * Config api
 *
 * @version $Revision$
 * @author JLJuang <jl_juang@vsigntek.com>
 * @note Copyright (c) 2021, VitalSigns Technology Co., Ltd.,, all rights reserved.
 * @note
*/
///------------------------------------------///
///  Include Area
///------------------------------------------///
#include "Global.h"

ConfigItemType ConfigItem[] = 
{
		///------------------------------------------------------------------------------------///
		///  NAME       VALUE											TYPE
		///------------------------------------------------------------------------------------///
		{CONFIG_ITEM_TIME_ZONE_SEC,  		"28800", 									JCONFIG_TYPE_INT},				
		{CONFIG_ITEM_COM_PORT, 					"COM7", 									JCONFIG_TYPE_STR},		
		{CONFIG_ITEM_SERIAL_PORT, 			"/dev/ttyUSB0", 					JCONFIG_TYPE_STR},				
		{CONFIG_ITEM_SSN,  							"11-222-3333", 						JCONFIG_TYPE_STR},									
		{CONFIG_ITEM_DATA_ROOT,   			"./data", 								JCONFIG_TYPE_STR},					
		{CONFIG_ITEM_BLE_DEVICE_NAME, 	"", 											JCONFIG_TYPE_STR},							
		{CONFIG_ITEM_BLE_DEVICE_MAC,  	"", 											JCONFIG_TYPE_STR},			
		///------------------------------------------------------------------------------------///
		{"", "", JCONFIG_TYPE_STR},			
};

void ConfigPrint()
{
	JINT i = 0;
  ConfigItemType *pItem = NULL;
  char msg[256];
 	while(1)
 	{
 		pItem = (ConfigItemType *)&ConfigItem[i];
 		i = i + 1;
 		if(strlen(pItem->strName) == 0)
		{
			break;
		}
 		sprintf(msg, "\t%20s = %-40s (type = %02d) \n", pItem->strName, pItem->strValue, pItem->iType);
 		DBG_PRINTF(msg);
 	}
}

void ConfigSet(char *strName, char *strValue)
{
  JINT i = 0;
  ConfigItemType *pItem = NULL;
 	while(1)
 	{
 		pItem = (ConfigItemType *)&ConfigItem[i];
 		i = i + 1;
 		if(strlen(pItem->strName) == 0)
		{
			break;
		}
 		if(strstr(pItem->strName, strName) == pItem->strName)
		{
			strcpy(pItem->strValue, strValue);
			break;
		}
 	}
}

void ConfigStrSet(char *strName, char *strValue)
{
  JINT i = 0;
  ConfigItemType *pItem = NULL;
 	while(1)
 	{
 		pItem = (ConfigItemType *)&ConfigItem[i];
 		i = i + 1;
 		if(strlen(pItem->strName) == 0)
		{
			break;
		}
 		if(strstr(pItem->strName, strName) == pItem->strName)
		{
			strcpy(pItem->strValue, strValue);
			break;
		}
 	}
}


void ConfigStrGet(char *strName, char *strValue)
{
  JINT i = 0;
  ConfigItemType *pItem = NULL;
 	while(1)
 	{
 		pItem = (ConfigItemType *)&ConfigItem[i];
 		i = i + 1;
 		if(strlen(pItem->strName) == 0)
		{
			break;
		}
 		if(strstr(pItem->strName, strName) == pItem->strName)
		{
			strcpy(strValue, pItem->strValue);
			break;
		}
 	}
}

void ConfigIntGet(char *strName, JINT *piVal)
{
  JINT i = 0;
  ConfigItemType *pItem = NULL;
 	while(1)
 	{
 		pItem = (ConfigItemType *)&ConfigItem[i];
 		i = i + 1;
 		if(strlen(pItem->strName) == 0)
		{
			break;
		}
		if(strstr(pItem->strName, strName) == pItem->strName)
		{
			sscanf(pItem->strValue, "%d", piVal);
			break;
		}
 	}
}


void ConfigIntGet(char *strName, JINT iVal)
{
  JINT i = 0;
  ConfigItemType *pItem = NULL;
 	while(1)
 	{
 		pItem = (ConfigItemType *)&ConfigItem[i];
 		i = i + 1;
 		if(strlen(pItem->strName) == 0)
		{
			break;
		}
		if(strstr(pItem->strName, strName) == pItem->strName)
		{
			sprintf(pItem->strValue, "%d", iVal);
			break;
		}
 	}
}


void ConfigFloatGet(char *strName, JFLOAT *pfVal)
{
  JINT i = 0;
  ConfigItemType *pItem = NULL;
 	while(1)
 	{
 		pItem = (ConfigItemType *)&ConfigItem[i];
 		i = i + 1;
 		if(strlen(pItem->strName) == 0)
		{
			break;
		}
 		if(strstr(pItem->strName, strName) == pItem->strName)
		{
			sscanf(pItem->strValue, "%f", pfVal);
			break;
		}
 	}
}

void ConfigFloatSet(char *strName, JFLOAT fVal)
{
  JINT i = 0;
  ConfigItemType *pItem = NULL;
 	while(1)
 	{
 		pItem = (ConfigItemType *)&ConfigItem[i];
 		i = i + 1;
 		if(strlen(pItem->strName) == 0)
		{
			break;
		}
 		if(strstr(pItem->strName, strName) == pItem->strName)
		{
			sprintf(pItem->strValue, "%f", fVal);
			break;
		}
 	}
}

void ConfigParse(char *strLine)
{
	char strName[128];
	char strValue[128];	
	JINT iCnt = strlen(strLine);
	JINT i = 0;
	JINT idx = 0;	
	char *ptr = NULL;
	
	ptr = &strName[0];	
	for(i = 0 ; i < iCnt; i = i + 1)
	{
		if(strLine[i] == '=')
		{
			ptr = &strValue[0];
			*ptr = 0;
			continue;
		}
		if(strLine[i] == '\r')
		{
			continue;
		}
		if(strLine[i] == '\n')
		{
			continue;
		}		
		if(strLine[i] == 0)
		{
			break;
		}
		*ptr = strLine[i];
		 ptr  =  ptr + 1;
		*ptr = 0;
	}
	ConfigStrSet(strName, strValue);
}

void ConfigLoad(void)
{
	FILE *fp = NULL;
	char fileName[256];
	char line[256];
	JINT iRet = 0;

	#if OS_TYPE == OS_TYPE_UBUNTU
	sprintf(fileName, "./data/config.txt");
	#elif OS_TYPE == OS_TYPE_MAC_OS
	sprintf(fileName, "./data/config.mac.txt");
	#elif OS_TYPE == OS_TYPE_WINDOWS
	sprintf(fileName, "./data/config.win.txt");
	#endif ///< for #if

	UtilWinPathNameSet(fileName);
	fp = fopen(fileName, "r");
	if(fp == NULL)
	{
		ConfigSave();
		return;
	}
	
	while(1)
	{
		iRet = fscanf(fp, "%[^\n]\n", line);
		if(iRet <= 0)
		{
			break;
		}		
		ConfigParse(line);
	}
	
	fclose(fp);

	//ConfigPrint();
}

void ConfigSave(void)
{
	JINT i = 0;
  ConfigItemType *pItem = NULL;
  FILE * fp = NULL;
  char fileName[256];  
	
	/// Log save
	#if OS_TYPE == OS_TYPE_UBUNTU
	sprintf(fileName, "./data/config.txt");
	#elif OS_TYPE == OS_TYPE_MAC_OS
	sprintf(fileName, "./data/config.mac.txt");
	#elif OS_TYPE == OS_TYPE_WINDOWS
	sprintf(fileName, "./data/config.win.txt");	
	#endif
	UtilWinPathNameSet(fileName);
  fp = fopen(fileName, "w+");
  if(fp == NULL)
	{
		DBG_PRINTF("Failed to open the config file\r\n");
		return;
	}
  
	while(1)
 	{
 		pItem = (ConfigItemType *)&ConfigItem[i];
 		i = i + 1;
 		if(strlen(pItem->strName) == 0)
		{
			break;
		}
		fprintf(fp, "%s=%s\n", pItem->strName, pItem->strValue);
 	}
	fclose(fp);
	
	//ConfigPrint();	
}
