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
	/// set social security number
	sprintf((char *)&GlobalVar.strSSN[0], "%s", "000-00-0000");
}

void MainInit(void)
{
	char strFolderName[256];

	/// Init Variable
	VarInit();	

	/// init print	
	printf("\r\n");
	printf("\r\n");	
	printf("--------------------------------------------------------------\r\n");
	printf(" VSC Mode (V1.0) programmed by JL JUANG 										\r\n");
	printf("--------------------------------------------------------------\r\n");
	printf("\r\n");

	///-----------------------------------------------------------------------------///
	/// DATA ROOT Set
	///-----------------------------------------------------------------------------///
	UtilCurDirGet((char *)&GlobalVar.strCurDir[0]);
	/// Create folder
	sprintf(strFolderName, "%s/data", (char *)&GlobalVar.strCurDir[0]);
	ConfigStrSet((char *)CONFIG_ITEM_DATA_ROOT, strFolderName);			
	UtilFolderCreate(strFolderName);
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
	
	ConfigLoad();

	TaskRoundInit();

	TaskVsDongleOpen();

	TaskVSH101Open();

	TaskVSH101Read();

	TaskVSH101Close();

	TaskVsDongleClose();

	TaskRoundEnd();

	ConfigSave();
	printf("\r\nbyebye\r\n");
	return;
}

