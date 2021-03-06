/**
 * @file Global.h
 *
 *  Global.h controls 
 *
 * @version $Revision$
 * @author JLJuang <jl_juang@vsigntek.com>
 * @note Copyright (c) 2021, VitalSigns Technology Co., Ltd., all rights reserved.
 * @note
*/

#ifndef __GLOBAL_H__
#define __GLOBAL_H__

///-------------------------------------------------------------///
/// vendor function control
///-------------------------------------------------------------///
#include "Feature.h"

///-------------------------------------------------------------///
/// Std lib
///-------------------------------------------------------------///
#include <stdio.h>
#include <stdlib.h>

#include <dirent.h> 
#include <stdio.h> 

#include <unistd.h>

#include <string.h>
#include <math.h>
#include <time.h>
///-------------------------------------------------------------///
/// Linux thread
///-------------------------------------------------------------///
#include <pthread.h>

#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>

///-------------------------------------------------------------///
/// serial port
///-------------------------------------------------------------///
#include <errno.h>
#include <fcntl.h> 

#ifndef ARCH_WIN32
#include <termios.h>
#else  /// < ifndef ARCH_WIN32
#include <windows.h>
#endif /// < ifndef ARCH_WIN32

///-------------------------------------------------------------///
/// basic
///-------------------------------------------------------------///
#include "Define.h"
#include "TypeDef.h"
#include "Err.h"

///-------------------------------------------------------------///
/// JConfig
///-------------------------------------------------------------///
#include "JConfig.h"

///-------------------------------------------------------------///
/// Packet Command
///-------------------------------------------------------------///
#include "Packet.h"

///-------------------------------------------------------------///
/// Ble
///-------------------------------------------------------------///
#include "Ble.h"
#include "BleCmd.h"

///-------------------------------------------------------------///
/// driver
///-------------------------------------------------------------///
#include "SerialPort.h"
#include "ComPort.h"

///-------------------------------------------------------------///
/// Command
///-------------------------------------------------------------///
#include "Cmd.h"

///-------------------------------------------------------------///
/// Function
///-------------------------------------------------------------///
#include "Util.h"

///-------------------------------------------------------------///
/// Global Variable
///-------------------------------------------------------------///
#include "GlobalVar.h"
#include "VarDef.h"

#include "Func.h"

#endif  ///< for #ifndef __GLOBAL_H__

