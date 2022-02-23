#ifndef __BLECMD_H__
#define __BLECMD_H__

#include "Global.h"

#define CMD_TIMEOUT_50MS						(50)
#define CMD_TIMEOUT_100MS						(100)
#define CMD_TIMEOUT_200MS						(200)
#define CMD_TIMEOUT_300MS						(300)
#define CMD_TIMEOUT_500MS						(500)

///-------------------------------------------------------------------------------------///
/// Functions
///-------------------------------------------------------------------------------------///

///--------------------------------------------------------------------------------///
/// BLE: 
///			MBLE --> packet send to master
///     SBLE --> packet send to slave, shall be connected first
///--------------------------------------------------------------------------------///

///--------------------------------------------------------------------------------///
///		SBLE --> packet send to slave, shall be connected first
///--------------------------------------------------------------------------------///
extern JINT CmdSBleSysVersionGet(void);

///--------------------------------------------------------------------------------///
///			MBLE --> packet send for master 
///--------------------------------------------------------------------------------///
extern JINT CmdMBleScan(void);
extern JINT CmdMBleOpen(JBYTE *pbMacAddr);
extern JINT CmdMBleClose(void);
extern JINT CmdMBleConnectStatus(JBOOL *pbStatus);



#endif ///< for __BLECMD_H__

