/**
 * @file SReg.cpp
 *
 *  SReg
 *
 *
 * @version $Revision$
 * @author JLJuang <jl_juang@vsigntek.com>
 * @note Copyright (c) 2021, VitalSigns Technology Co., Ltd., all rights reserved.
 */
#include "Global.h"
SRegAppType SRegApp;

///---------------------------------------------------------------------------------------------------------------///
///
/// Action Function Area
///
///---------------------------------------------------------------------------------------------------------------///
JBOOL SRegActDefault(SRegType *pSReg, JBYTE bAction)
{
  char msg[256];

  if(bAction == SREG_ACT_WRITE)
  {
    ///----------------------------------------------------------------------------------------------///
    /// SREG_WRITE 
    ///----------------------------------------------------------------------------------------------///
    sprintf(msg, "[SREG][WRITE] %s\r\n", pSReg->strName);
    DBG_PRINTF(msg);
  }
  else if(bAction == SREG_ACT_READ)
  {    
    ///----------------------------------------------------------------------------------------------///
    /// SREG_READ
    ///----------------------------------------------------------------------------------------------///
    sprintf(msg, "\t [SREG][READ] %s \r\n", pSReg->strName);
    DBG_PRINTF(msg);
  }  
  return TRUE;
}

JBOOL SRegActDeviceName(SRegType *pSReg, JBYTE bAction)
{
  char msg[256];
  if(bAction == SREG_ACT_WRITE)
  {
    ///----------------------------------------------------------------------------------------------///
    /// SREG_WRITE 
    ///----------------------------------------------------------------------------------------------///
    sprintf(msg, "[SREG][WRITE] %s\r\n", pSReg->strName);
    DBG_PRINTF(msg);
  }
  else if(bAction == SREG_ACT_READ)
  {  
    UtilMemcpy((JBYTE *)&SRegApp.DEVICE_NAME[0],  (JBYTE *) &pSReg->bData[0], SREG_DATA_DEVICE_NAME_SIZE);       
    ///----------------------------------------------------------------------------------------------///
    /// SREG_READ
    ///----------------------------------------------------------------------------------------------///
    sprintf(msg, "\t [SREG][READ] %s \r\n", pSReg->strName);
    DBG_PRINTF(msg);
  }      
  return TRUE;
}

JBOOL SRegActDeviceSsn(SRegType *pSReg, JBYTE bAction)
{
  char msg[256];
  if(bAction == SREG_ACT_WRITE)
  {
    ///----------------------------------------------------------------------------------------------///
    /// SREG_WRITE 
    ///----------------------------------------------------------------------------------------------///
    sprintf(msg, "[SREG][WRITE] %s\r\n", pSReg->strName);
    DBG_PRINTF(msg);
  }
  else if(bAction == SREG_ACT_READ)
  {  
    UtilMemcpy((JBYTE *)&SRegApp.DEVICE_SSN[0],  (JBYTE *) &pSReg->bData[0], SREG_DATA_DEVICE_SSN_SIZE);       
    ///----------------------------------------------------------------------------------------------///
    /// SREG_READ
    ///----------------------------------------------------------------------------------------------///
    sprintf(msg, "\t [SREG][READ] %s \r\n", pSReg->strName);
    DBG_PRINTF(msg);
  }      
  return TRUE;
}

JBOOL SRegActMeasZeroBase(SRegType *pSReg, JBYTE bAction)
{
  char msg[256];
  if(bAction == SREG_ACT_WRITE)
  {    
    ///----------------------------------------------------------------------------------------------///
    /// SREG_WRITE 
    ///----------------------------------------------------------------------------------------------///
    sprintf(msg, "[SREG][WRITE] %s\r\n", pSReg->strName);
    DBG_PRINTF(msg);
  }
  else if(bAction == SREG_ACT_READ)
  {  
    UtilMemcpy((JBYTE *)&SRegApp.MEAS_ZERO_BASE[0],  (JBYTE *) &pSReg->bData[0], SREG_DATA_MEAS_ZERO_BASE_SIZE);       
    ///----------------------------------------------------------------------------------------------///
    /// SREG_READ
    ///----------------------------------------------------------------------------------------------///
    sprintf(msg, "\t [SREG][READ] %s \r\n", pSReg->strName);
    DBG_PRINTF(msg);
  }      
  return TRUE;
}

JBOOL SRegActMeasLeadOff(SRegType *pSReg, JBYTE bAction)
{
  char msg[256];
  if(bAction == SREG_ACT_WRITE)
  {    
    ///----------------------------------------------------------------------------------------------///
    /// SREG_WRITE 
    ///----------------------------------------------------------------------------------------------///
    sprintf(msg, "[SREG][WRITE] %s\r\n", pSReg->strName);
    DBG_PRINTF(msg);
  }
  else if(bAction == SREG_ACT_READ)
  {  
    UtilMemcpy((JBYTE *)&SRegApp.MEAS_LEAD_OFF[0],  (JBYTE *) &pSReg->bData[0], SREG_DATA_MEAS_LEAD_OFF_SIZE);       
    ///----------------------------------------------------------------------------------------------///
    /// SREG_READ
    ///----------------------------------------------------------------------------------------------///
    sprintf(msg, "\t [SREG][READ] %s :%d\r\n", pSReg->strName, SRegApp.MEAS_LEAD_OFF[0]);
    DBG_PRINTF(msg);
  }      
  return TRUE;
}

JBOOL SRegActMeasLeadOffCompThreshold(SRegType *pSReg, JBYTE bAction)
{
  char msg[256];
  JFLOAT fData;
  if(bAction == SREG_ACT_WRITE)
  {    
    ///----------------------------------------------------------------------------------------------///
    /// SREG_WRITE 
    ///----------------------------------------------------------------------------------------------///
    sprintf(msg, "[SREG][WRITE] %s\r\n", pSReg->strName);
    DBG_PRINTF(msg);
  }
  else if(bAction == SREG_ACT_READ)
  {  
    UtilMemcpy((JBYTE *)&SRegApp.MEAS_LEAD_OFF_COMP_TH[0],  (JBYTE *) &pSReg->bData[0], SREG_DATA_MEAS_LEAD_COMP_TH_SIZE);     
    UtilMemcpy((JBYTE *)&fData,  (JBYTE *) &pSReg->bData[0], SREG_DATA_MEAS_LEAD_COMP_TH_SIZE);      
    ///----------------------------------------------------------------------------------------------///
    /// SREG_READ
    ///----------------------------------------------------------------------------------------------///
    sprintf(msg, "\t [SREG][READ] %s : %.1f\r\n", pSReg->strName, fData);
    DBG_PRINTF(msg);
  }      
  return TRUE;
}


JBOOL SRegActMeasLeadOffCurrLevel(SRegType *pSReg, JBYTE bAction)
{
  char msg[256];
  if(bAction == SREG_ACT_WRITE)
  {    
    ///----------------------------------------------------------------------------------------------///
    /// SREG_WRITE 
    ///----------------------------------------------------------------------------------------------///
    sprintf(msg, "[SREG][WRITE] %s\r\n", pSReg->strName);
    DBG_PRINTF(msg);
  }
  else if(bAction == SREG_ACT_READ)
  {  
    UtilMemcpy((JBYTE *)&SRegApp.MEAS_LEAD_OFF_CURR[0],  (JBYTE *) &pSReg->bData[0], SREG_DATA_MEAS_LEAD_OFF_CURR_SIZE);       
    ///----------------------------------------------------------------------------------------------///
    /// SREG_READ
    ///----------------------------------------------------------------------------------------------///
    sprintf(msg, "\t [SREG][READ] %s \r\n", pSReg->strName);
    DBG_PRINTF(msg);
  }      
  return TRUE;
}

///---------------------------------------------------------------------------------------------------------------///
///
/// Basic Function Area
///
///---------------------------------------------------------------------------------------------------------------///
void SRegActProcess(SRegType *pSReg, JBYTE bAction)
{
  SRegActType *pSRegAct = NULL;
  JINT i = 0;
  char strName[SREG_NAME_SIZE];
  while(1)
  {
    pSRegAct = &SRegActArr[i];
    if(strlen(pSRegAct->strName) == 0)
    {
      break;
    }
    UtilMemset((JBYTE *)&strName[0], 0x00, SREG_NAME_SIZE);
    sprintf(strName, "%s", pSRegAct->strName);
    if(UtilMemcmp((JBYTE *)&pSReg->strName[0], (JBYTE *) &strName[0], SREG_NAME_SIZE) == MEMCMP_SAME)
    {      
      pSRegAct->act(pSReg, bAction);      
      break;
    }   
    i = i + 1;
  }   
}

void SRegRead(SRegType *pSReg)
{  
  if(CmdSBleSRegRead(pSReg) != NO_ERR)
  {    
    GlobalVar.dwSysCtl6 |= SYS_CTL6_BLE_MASTER_CLOSE;
  }
  SRegActProcess(pSReg, SREG_ACT_READ);
}

void SRegWrite(SRegType *pSReg)
{
  if(CmdSBleSRegWrite(pSReg) != NO_ERR)
  {
    GlobalVar.dwSysCtl6 |= SYS_CTL6_BLE_MASTER_CLOSE;
  }
}

void SRegInit(void)
{
  SRegApp.MEAS_ZERO_BASE[0]     = 0xFF;
  SRegApp.MEAS_LEAD_OFF[0]      = 0xFF;
  SRegApp.MEAS_LEAD_OFF_CURR[0] = 0xFF; 
}

///---------------------------------------------------------------------------------------------------------------///
///
/// Action Function Pointer Area
///
///---------------------------------------------------------------------------------------------------------------///
SRegActType SRegActArr[] =
{
  SREG_DEVICE_NAME,            SRegActDeviceName,
  SREG_DEVICE_RESET,           SRegActDefault,
  SREG_DEVICE_SSN,             SRegActDeviceSsn,
  SREG_MEAS_ZERO_BASE,         SRegActMeasZeroBase,  
  SREG_MEAS_LEAD_OFF_COMP_TH,  SRegActMeasLeadOffCompThreshold,  
  SREG_MEAS_LEAD_OFF_CURR,     SRegActMeasLeadOffCurrLevel,  
  SREG_MEAS_LEAD_OFF,          SRegActMeasLeadOff,  
  "",                          SRegActDefault
};

