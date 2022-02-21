/**
 * @file main.cpp
 *
 *   Main Code
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
void Mainloop(void);

GlobalVarType GlobalVar;

void VarInit(void)
{
	
}

void MainInit(void)
{
	/// Init Variable
	VarInit();	
}

JINT main(int argc, char *argv[])
{ 

	MainInit(); 	
	Mainloop();	
  return 0;
}

///------------------------------------------///
///  Function Area
///------------------------------------------///
void Mainloop()
{
	DBG_PRINTF("Hello World\r\n");
}

