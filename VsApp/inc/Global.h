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
/// APP
///-------------------------------------------------------------///
#include <gtk/gtk.h>

#include "UI.h"

#include "Cairo.h"
#include "JDraw.h"
#include "JView.h"
#include "App.h"

///-------------------------------------------------------------///
/// CHART
///-------------------------------------------------------------///
#include "JDataSet.h"
#include "JChart.h"

///-------------------------------------------------------------///
/// JConfig
///-------------------------------------------------------------///
#include "JConfig.h"

///-------------------------------------------------------------///
/// ATR
///-------------------------------------------------------------///
#include "AtrCtl.h"	  ///< ATR control
#include "JAtr.h"	    ///< ATR

///-------------------------------------------------------------///
/// Packet Command
///-------------------------------------------------------------///
#include "Packet.h"

///-------------------------------------------------------------///
/// SReg
///-------------------------------------------------------------///
#include "SReg.h"

///-------------------------------------------------------------///
/// Ble
///-------------------------------------------------------------///
#include "Ble.h"
#include "BleCmd.h"

#include "BleControl.h"
#include "BleState.h"

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
/// Timer
///-------------------------------------------------------------///
#include "Timer.h"

///-------------------------------------------------------------///
/// Gatt lib
///-------------------------------------------------------------///
#include "JGatt.h"
#include "JGattCmd.h"
#include "JGattState.h"

///-------------------------------------------------------------///
/// VSC Mode
///-------------------------------------------------------------///
#include "VscMode.h"

///-------------------------------------------------------------///
/// Thread
///-------------------------------------------------------------///
#include "Thread.h"

///-------------------------------------------------------------///
/// Global Variable
///-------------------------------------------------------------///
#include "GlobalVar.h"
#include "VarDef.h"

///-------------------------------------------------------------///
/// Function & Task
///-------------------------------------------------------------///
#include "Func.h"
#include "Task.h"

#endif  ///< for #ifndef __GLOBAL_H__

