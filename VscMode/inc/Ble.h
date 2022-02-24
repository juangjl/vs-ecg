/**
 * @file ble.h
 *
 *  Ble.h 
 *
 * @version $Revision$
 * @author JL Juang <jl_juang@vsigntek.com>
 * @note Copyright (c) 2021,  VitalSigns Technology Co., LTD., all rights reserved.
 * @note
*/
#ifndef __BLE_H__
#define __BLE_H__
#include "Global.h"

#pragma pack(push)
#pragma pack(1)

#define WHITE_LIST_MAX_CNT  (128)
#define SCAN_NAME_SIZE      (24)

#define BLE_DEVICE_LIST_MAX_CNT  (128)

typedef struct BleDeviceItemST
{
  JBYTE bAddr[6];
  JCHAR bRSSI;
  JBYTE name[SCAN_NAME_SIZE];
} BleDeviceItemType;

typedef struct BleDeviceListST
{
	JINT iCnt;
	BleDeviceItemType BleDeviceItems[BLE_DEVICE_LIST_MAX_CNT];
} BleDeviceListType;


#pragma pack(pop)


#endif ///< __BLE_H__

