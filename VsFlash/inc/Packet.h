/**
 * @file packet.h
 *
 *  packet.h define command packet format
 *
 * @version $Revision$
 * @author JLJuang <jl_juang@vsigntek.com>
 * @note Copyright (c) 2021, VitalSigns Technology Co., Ltd., all rights reserved.
 * @note
*/
#ifndef __PACKET_H__
#define __PACKET_H__

#include "Global.h"

#define CMD_ACK															'A'
#define CMD_NACK														'N'

///=====================================================================///  
///  Command Group
///=====================================================================///
#define CMD_GROUP_ID_I2C										(0x20)
#define CMD_GROUP_ID_SMB										(0x30)
#define CMD_GROUP_ID_SPI										(0x40)
#define CMD_GROUP_ID_UART										(0x50)
#define CMD_GROUP_ID_GPIO										(0x60)
#define CMD_GROUP_ID_MOTOR								  (0x70)
#define CMD_GROUP_ID_ADC										(0x80)
#define CMD_GROUP_ID_I2C2										(0x99)
#define CMD_GROUP_ID_DAC										(0xA0)
#define CMD_GROUP_ID_PWM										(0xA1)
#define CMD_GROUP_ID_IOE										(0xA2)
#define CMD_GROUP_ID_TMP										(0xA3)
#define CMD_GROUP_ID_HMD										(0xA4)
#define CMD_GROUP_ID_SREG										(0xA5)
#define CMD_GROUP_ID_DF	  									(0xAA)
#define CMD_GROUP_ID_JDS	  								(0xAB)
#define CMD_GROUP_ID_JFILE	  							(0xAC)
#define CMD_GROUP_ID_REPORT	  							(0xAD)
#define CMD_GROUP_ID_SYS                		(0xC0)
#define CMD_GROUP_ID_BLE                    (0xC2)


///-------------------------------------------------------------------------------///
/// CMD:   GROUP  CMD    MOSI0 MOSI1 MISO0 MISO1   GIO#  		VALUE
/// RTN:   GROUP  A/N
///-------------------------------------------------------------------------------///
///    EX:  60    01 	 02    00    00    00      00    		00  --> GIO0 input mode
///    EX:  60    01   02    00    00    00      01    		01  --> GIO1 output mode
///-------------------------------------------------------------------------------///
#define CMD_GIO_MODE														(0x00)
	#define GIO_MODE_INPUT													(0x00)
	#define GIO_MODE_OUTPUT													(0x01)	
	#define GIO_MODE_OPENDRAIN											(0x02)		

///-------------------------------------------------------------------------------///
/// CMD:   GROUP  CMD    MOSI0 MOSI1 MISO0 MISO1   GIO#  		VALUE
/// RTN:   GROUP  A/N
///-------------------------------------------------------------------------------///
///    EX:  60    01 		 02    00    00    00      00    		00  --> GIO0 = 0
///    EX:  60    01  	 02    00    00    00      01    		01  --> GIO1 = 1
///-------------------------------------------------------------------------------///
#define CMD_GIO_SET 														(0x01)	

///-------------------------------------------------------------------------------///
/// CMD:   GROUP  CMD    MOSI0 MOSI1 MISO0 MISO1   GIO# 
/// RTN:   GROUP  A/N
///-------------------------------------------------------------------------------///
///    EX:  60    02 		 01    00    01    00      00    		--> Get GIO0 return 1 byte
///    EX:  60    02  	 01    00    01    00      01    		--> Get GIO1 return 1 byte
///-------------------------------------------------------------------------------///
#define CMD_GIO_GET 														(0x02)

#define CMD_GIO_GIO0_IDX                           (0)
#define CMD_GIO_GIO1_IDX                           (1)
#define CMD_GIO_GIO2_IDX                           (2)
#define CMD_GIO_UART_BLE_IDX                       (3)
#define CMD_GIO_UART_USB_IDX                       (4)
#define CMD_GIO_RESET_IDX 		                     (5)
#define CMD_GIO_TOGGLE  												(0x04)

///-------------------------------------------------------------------------------///
/// I2C
///-------------------------------------------------------------------------------///
#define CMD_I2C_MASTER_WRITE_DATA							(0x00)
#define CMD_I2C_MASTER_READ_DATA							(0x08)	

#define CMD_I2C_SLAVE_WRITE_DATA							(0x10)
#define CMD_I2C_SLAVE_READ_DATA								(0x18)

#define CMD_I2C_READ													(0x60)
#define CMD_I2C_WRITE													(0x61)

///-------------------------------------------------------------------------------///
/// Report
///-------------------------------------------------------------------------------///
#define CMD_REPORT00_READ   											(0)			///< GG3 data
#define CMD_REPORT01_READ   											(1)			///< GG4 data
#define CMD_REPORT02_READ   											(2) 		///< GG4 data
#define CMD_REPORT03_READ   											(3) 		///< GG_NCTU data
#define CMD_REPORT04_READ   											(4)
#define CMD_REPORT05_READ   											(5)
#define CMD_REPORT06_READ   											(6)
#define CMD_REPORT07_READ   											(7)			
#define CMD_REPORT08_READ   											(8)			///< ECG
#define CMD_REPORT09_READ   											(9)
#define CMD_REPORT10_READ  												(10)

///-------------------------------------------------------------------------------///
/// JFile
///-------------------------------------------------------------------------------///
#define CMD_JFILE_LIST_CLEAR										(0x70) ///< File list clear
#define CMD_JFILE_LIST_READ  										(0x71) ///< File list read
#define CMD_JFILE_READ  												(0x72) ///< File read

///-------------------------------------------------------------------------------///
/// SYS
///-------------------------------------------------------------------------------///
#define CMD_SYS_VER_GET	  											(0x00)
#define CMD_SYS_BOOTLOADER_ENTER                (0x01)

#define CMD_SYS_TIME_SET                        (0x40)
#define CMD_SYS_TIME_GET                        (0x41)

#define CMD_SYS_SSN_GET                        	(0xA0)
#define CMD_SYS_SSN_SET                        	(0xA1)

/// boot code used - START
#define CMD_UPGRADE_START                       (0x23)	///< DFU Start
#define CMD_UPGRADE_FILE_DATA                   (0x24)	///< DFU DATA
#define CMD_UPGRADE_INTERUPT				          	(0x25)	///< DFU Interrupt
#define CMD_UPGRADE_END							            (0x26)	///< DFU End
/// boot code used - END


///-------------------------------------------------------------------------------///
/// BLE
///-------------------------------------------------------------------------------///
#define CMD_BLE_STATUS                          (0x00)
#define CMD_BLE_SCAN_TABLE                      (0x10)
#define CMD_BLE_SERVICE                         (0x11)
#define CMD_BLE_UUID_RX                         (0x12)
#define CMD_BLE_UUID_TX                         (0x13)
#define CMD_MODE_WRITE                          (0x14)
#define CMD_BLE_OPEN                            (0x20)
#define CMD_BLE_WRITE                           (0x21)
#define CMD_BLE_READ                            (0x22)
#define CMD_OTA_CTL_READ                        (0x23)
#define CMD_OTA_CTL_WRITE                       (0x24)
#define CMD_OTA_DATA_READ                       (0x25)
#define CMD_OTA_DATA_WRITE                      (0x26)
#define CMD_BLE_WRITE_RESULT                    (0x27)
#define CMD_BLE_READ_DATA                       (0x28)
#define CMD_BLE_CLOSE                           (0x2F)

///---------------------------------------------------------------///
///  ADDED BY JL- START
///---------------------------------------------------------------///
#define CMD_BLE_BIT_MODE_START                  (0x40)
#define CMD_BLE_BIT_MODE_STOP	                  (0x41)

#define CMD_BLE_BIT_MODE_QUEUE_PASS             (0x42)
#define CMD_BLE_BIT_MODE_QUEUE_FAIL	            (0x43)

#define CMD_BLE_MONITOR_START		                (0x44)
#define CMD_BLE_MONITOR_STOP		                (0x45)

#define CMD_BLE_STATE 	 			                  (0x60)

#define CMD_BLE_PACKET_WRITE                    (0x61)
#define CMD_BLE_PACKET_READ                     (0x62)

#define CMD_BLE_PACKET_WRITE                    (0x61)
#define CMD_BLE_PACKET_READ                     (0x62)

#define CMD_BLE_VSC_MODE_START					      	(0x64)
#define CMD_BLE_VSC_MODE_STOP					      		(0x65)

#define CMD_BLE_CONNECT_STATUS									(0x66)  
#define CMD_BLE_MEAS_MODE												(0x67)  
#define CMD_BLE_MONITOR_MODE										(0x68) 

#define CMD_BLE_VSC_MODE_CLEAR									(0x69)  
#define CMD_BLE_VSC_MODE_READ										(0x6A)  

#define CMD_BLE_TEST														(0xF0) 

///---------------------------------------------------------------///
///  ADDED BY JL- END
///---------------------------------------------------------------///
#define CMD_BLE_RESET                           (0xFE)

///=============================================================///
/// Packet definition
///=============================================================///

#pragma pack(push)  /* push current alignment to stack */
#pragma pack(1)     /* set alignment to 1 byte boundary */
#define PACKET_CMD_DATA_SIZE										(2000)
typedef struct PacketStruct
{
	///----------------------------------------------------///
	/// In data packet 65 bytes
	///----------------------------------------------------///
	JBYTE bPCode;				  								///< Command Group
 	JBYTE bGroupId;												///< Command Group
	JBYTE bCmd;												  	///< Command Command Byte						
	JBYTE bCheckSum; 											///< Checksum		
	JWORD wMOSILen;												///< Slave: Data in length /  Master Data out length
	JWORD wMISOLen;												///< Slave: Data out length /  Master Data in length
	JBYTE bData[16]; 											///< Data Buffer						
	JBYTE bCmdData[PACKET_CMD_DATA_SIZE]; ///< Dummy bytes
} PacketType;

#define PACKET_ACK_DATA_SIZE										(10000)
typedef struct PacketAckStruct
{
	///----------------------------------------------------///
	/// In data packet 64 bytes
	///----------------------------------------------------///
	JBYTE bPCode;				  								///< Command Group	
	JBYTE bGroupId;												///< Command Group
	JBYTE bAck;														///< Command Command Byte
	JBYTE bChkSum;							 					///< Checksum				
	JWORD wDataIdx;												///< Data in length
	JWORD wDataLen;												///< Data out length
	JBYTE bData[PACKET_ACK_DATA_SIZE]; 	  ///< In  Data Buffer					
} PacketAckType;

#pragma pack(pop)     ///< pop previous alignment out

///=====================================================================///  
///  Packet header size
///=====================================================================///
#define PACKET_CMD_HEADER_SIZE              			(8)
#define PACKET_CMD_BDATA_SIZE  	            			(16)
#define PACKET_ACK_HEADER_SIZE   	                (8)    

extern JVOID PacketInit(PacketType *pPacketOut);
extern JVOID PacketAckInit(PacketAckType *pPacketAck);
extern JBYTE PacketCheckSumGet(PacketType *pPacketOut);
extern JVOID PacketCheckSumSet(PacketType *pPacketOut);
extern JINT  PacketSend(PacketType * pPacketOut, PacketAckType * pPacketIn, int iTimeout);

extern void  PacketPrint(PacketAckType *pPacket);
extern void  PacketAckPrint(PacketAckType *pPacket);

extern JINT PacketSendBootCode(PacketType * pPacketOut, PacketAckType * pPacketIn, int iTimeout);

#endif ///< __PACKET_H__

