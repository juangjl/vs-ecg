/**
 * @file Func.cpp
 *
 *  Function 
 *
 * @version $Revision$
 * @author JLJuang <jl_juang@vsigntek.com>
 * @note Copyright (c) 2021, VitalSigns Technology Co., Ltd., all rights reserved.
 */
#include "Global.h"

JBOOL FuncVSDongleOpen(char *strPortName)
{
	JBOOL bSerialOpen = FALSE;

	SERIAL_PORT_NAME_SET(strPortName);
	bSerialOpen = SERIAL_PORT_OPEN();
	if(bSerialOpen == TRUE)
	{
		GlobalVar.bSerialPortOpen = TRUE;		
	}
	else
	{
		GlobalVar.bSerialPortOpen = FALSE;
		return FALSE;
	}
	return TRUE;
}

JBOOL FuncVSDongleClose(void)
{
	JINT iErrNo = NO_ERR;
	JBOOL bRet = TRUE;

	JBOOL bConnect = FALSE;
	GlobalVar.bSerialPortOpen = FALSE;
	SERIAL_PORT_CLOSE();
	
	return bRet;
}

JBOOL FuncVSDongleVersionGet(void)
{
	JINT iErrNo = NO_ERR;
	
	iErrNo = CmdSysVersion();
	
	if(iErrNo != NO_ERR)
	{
		return FALSE;
	}
	return TRUE;
}

JBOOL FuncVSDongleTimeSet(void)
{
	JINT iErrNo = NO_ERR;
	time_t t = time(NULL);
	JTM jtm;
		
	UtilLocalTime(&jtm, t);
	iErrNo = CmdSysTimeSet(&jtm);	
	if(iErrNo != NO_ERR)
	{
		return FALSE;
	}
	return TRUE;
}

JBOOL FuncMBleScan(void)
{
	JINT iErrNo = NO_ERR;
	JINT i = 0;
	BleDeviceItemType *pItem = NULL;
	char msg[256];
	iErrNo = CmdMBleScan();
	JINT iRSSI = 0;

	if(iErrNo == NO_ERR)
	{		
		sprintf(msg, "[MBLE] device count = %d \r\n", GlobalVar.BleDeviceList.iCnt);
		DBG_PRINTF(msg);
		for(i = 0 ; i < GlobalVar.BleDeviceList.iCnt; i = i + 1)
		{
			pItem =  &GlobalVar.BleDeviceList.BleDeviceItems[i];
			iRSSI = pItem->bRSSI;
			printf("\t#%-2d: %-24s, %02X-%02X-%02X-%02X-%02X-%02X, %02d db\r\n",  
							i,
							pItem->name,
							pItem->bAddr[0], pItem->bAddr[1], pItem->bAddr[2],
							pItem->bAddr[3], pItem->bAddr[4], pItem->bAddr[5],
							iRSSI);
		}
	}
	else
	{
		printf("\t [ERROR] Failed to scan device\r\n");
	}

	return TRUE;
}

JBOOL FuncMBleSelect(void)
{
	JINT iNum = 0;
	JINT iRet = 0;
	char strBleDeviceName[256];
	char strBleDeviceMac[256];
	BleDeviceItemType *pBleDeviceItem = NULL;
	char msg[256];

	if(GlobalVar.BleDeviceList.iCnt < 0)
	{
		sprintf(msg, "\t\t [ERROR] There is no device scanned\r\n");
		return FALSE;
	}

	///------------------------------------------------------------///
	/// Select a device
	///------------------------------------------------------------///
	printf("Select a device (0 ~ %d): ", (GlobalVar.BleDeviceList.iCnt - 1));
	iRet = scanf("%d", &iNum);		
	if(iRet > 0)
	{
		if((iNum >= 0) && (iNum < GlobalVar.BleDeviceList.iCnt))
		{
			pBleDeviceItem = &GlobalVar.BleDeviceList.BleDeviceItems[iNum];

			sprintf(strBleDeviceName, "%s", pBleDeviceItem->name);
			sprintf(strBleDeviceMac, 	"%02X:%02X:%02X:%02X:%02X:%02X", 
							pBleDeviceItem->bAddr[0], pBleDeviceItem->bAddr[1], pBleDeviceItem->bAddr[2], 
							pBleDeviceItem->bAddr[3], pBleDeviceItem->bAddr[4], pBleDeviceItem->bAddr[5]);
			ConfigStrSet((char *)CONFIG_ITEM_BLE_DEVICE_NAME, strBleDeviceName);			
			ConfigStrSet((char *)CONFIG_ITEM_BLE_DEVICE_MAC, 	strBleDeviceMac); 	

			/// selected device information print
			sprintf(msg, "NAME : %s \r\n", strBleDeviceName);
			DBG_PRINTF(msg);
			sprintf(msg, "MAC  : %s \r\n", strBleDeviceMac);
			DBG_PRINTF(msg);

			return TRUE;		
		}
	}		
	
	sprintf(msg, "\t\t device selected\r\n");
	return FALSE;
	
}

JBOOL FuncMBleOpen(void)
{
	JINT iErrNo = NO_ERR;
	
	JDWORD dwMacAddr[6];

	char strMacAddr[256];

	/// Get the name
	ConfigStrGet((char *)CONFIG_ITEM_BLE_DEVICE_NAME, &GlobalVar.strBleDeviceName[0]);

	/// Get the mac
	ConfigStrGet((char *)CONFIG_ITEM_BLE_DEVICE_MAC, 	&strMacAddr[0]);
		
	sscanf(strMacAddr, "%02X:%02X:%02X:%02X:%02X:%02X",
				(unsigned int *)&dwMacAddr[0], (unsigned int *)&dwMacAddr[1], (unsigned int *)&dwMacAddr[2],
				(unsigned int *)&dwMacAddr[3], (unsigned int *)&dwMacAddr[4], (unsigned int *)&dwMacAddr[5]);

	GlobalVar.bBleMacAddr[0] = (JBYTE)dwMacAddr[0];
	GlobalVar.bBleMacAddr[1] = (JBYTE)dwMacAddr[1];
	GlobalVar.bBleMacAddr[2] = (JBYTE)dwMacAddr[2];
	GlobalVar.bBleMacAddr[3] = (JBYTE)dwMacAddr[3];
	GlobalVar.bBleMacAddr[4] = (JBYTE)dwMacAddr[4];
	GlobalVar.bBleMacAddr[5] = (JBYTE)dwMacAddr[5];

	
	CmdMBleOpen(&GlobalVar.bBleMacAddr[0]);

	///------------------------------------------------------------///
	/// Connect Device
	///------------------------------------------------------------///

	return TRUE;
}

JBOOL FuncMBleOpenCheck(JINT iSec)
{
	JINT iErrNo = NO_ERR;	
	JINT iMS = 0;
	char msg[256];

	GlobalVar.bBleConnected = FALSE;
	
	sprintf(msg, "Device connect start\r\n");
	DBG_PRINTF(msg);

	while(1)
	{
		///----------------------------------------------------------------///
		/// Connection
		///----------------------------------------------------------------///
		iErrNo = CmdMBleConnectStatus(&GlobalVar.bBleConnected);
		if(iErrNo != NO_ERR)
		{			
			return FALSE;
		}

		if(GlobalVar.bBleConnected == TRUE)
		{
			sprintf(msg, "Device connected\r\n");
			DBG_PRINTF(msg);			
			return TRUE;
		}

		/// timeout check
		UtilMsSleep(100);
		iMS = iMS + 100;
		if(iMS >= iSec * 1000)
		{
			break;
		}

	}
	
	sprintf(msg, "Failed to connect device %s \r\n", GlobalVar.strBleDeviceName);
	DBG_PRINTF(msg);

	return TRUE;
}

JBOOL FuncMBleClose(void)
{
	JINT iErrNo = NO_ERR;

	/// BLE Close
	CmdMBleClose();

	return TRUE;
}

JBOOL FuncSBleVersionGet(void)
{
	JINT iErrNo = NO_ERR;
	JINT i = 0;

	if(GlobalVar.bBleConnected == FALSE)
	{
		return FALSE;
	}
	
	UtilMsSleep(200);

	for(i = 0 ; i < 5; i = i + 1)
	{
		iErrNo = CmdSBleSysVersionGet();
		sleep(1);
	}

	return TRUE;
}