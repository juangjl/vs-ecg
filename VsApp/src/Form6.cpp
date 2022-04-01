/**
 * @file Form6.cpp
 *
 *   Form6 View function (FORM6 / JVForm6)
 *
 * @version $Revision$
 * @author JLJuang <jl_juang@vsigntek.com>
 * @note Copyright (c) 2021, VitalSigns Technology Co., Ltd., all rights reserved.
 * @note
*/
///------------------------------------------///
///  Include Area
///------------------------------------------///
#include "Global.h"

#include "Form6.h"

///--------------------------------------------------------///
/// chart
///--------------------------------------------------------///
	
static ViewDataForm6Type  	ViewDataForm6;

///------------------------------------------------------------------------------------///
/// Variable area
///------------------------------------------------------------------------------------///
static JView *pThis = &JVForm6;

///------------------------------------------------------------------------------------///
/// Callback area
///------------------------------------------------------------------------------------///
static void CallbackForm6EntryDeviceNameActive(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	ViewDataForm6Type * pViewDataPtr = (ViewDataForm6Type * ) pThis->pViewData;
	printf("entry activate\r\n");	
}

static void CallbackForm6BtnDeviceNameGetClicked(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	ViewDataForm6Type * pViewDataPtr = (ViewDataForm6Type *)pThis->pViewData;	
	
	if(FuncSRegRead((char *)SREG_DEVICE_NAME) == FALSE)
	{
		MESSAGE_BOX("Device is busy");
		return;
	}
	DBG_PRINTF("[FORM6]Device Name Get\r\n");	
}

static void CallbackForm6BtnDeviceNameSetClicked(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	ViewDataForm6Type * pViewDataPtr = (ViewDataForm6Type *)pThis->pViewData;	
	
	JBYTE bData[256];
	char *pStrDeviceName = NULL;	
	char msg[256];
	
	pStrDeviceName = (char *) gtk_entry_get_text(GTK_ENTRY(pViewDataPtr->pEntryDeviceName));    
	if(strlen(pStrDeviceName) == 0)
	{
		MESSAGE_BOX("Device is empty");
		return;
	}

	UtilMemset((JBYTE *)&bData[0], 0x00, SREG_DATA_SIZE);

	sprintf((char *)&bData[0], "%s", pStrDeviceName);
	if(FuncSRegWrite((char *)SREG_DEVICE_NAME, &bData[0]) == FALSE)
	{
		MESSAGE_BOX("Device is busy");
		return;
	}
	sprintf(msg, "[FORM6]Device Name Set = %s\r\n", pStrDeviceName);
	DBG_PRINTF(msg);	
}

static void CallbackForm6BtnDeviceResetSetClicked(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	ViewDataForm6Type * pViewDataPtr = (ViewDataForm6Type *)pThis->pViewData;	
	
	JBYTE bData[256];
	char *pStrDeviceName = NULL;	
	char msg[256];
	
	UtilMemset((JBYTE *)&bData[0], 0x00, SREG_DATA_SIZE);
	
	if(FuncSRegWrite((char *)SREG_DEVICE_RESET, &bData[0]) == FALSE)
	{
		MESSAGE_BOX("Device is busy");
		return;
	}
	sprintf(msg, "%s", "[FORM6]Device Reset\r\n");
	DBG_PRINTF(msg);	
	MESSAGE_BOX("Device Reset OK");
}

static void CallbackForm6BtnDeviceSsnGetClicked(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	ViewDataForm6Type * pViewDataPtr = (ViewDataForm6Type *)pThis->pViewData;	
	
	if(FuncSRegRead((char *)SREG_DEVICE_SSN) == FALSE)
	{
		MESSAGE_BOX("Device is busy");
		return;
	}
	DBG_PRINTF("[FORM6] Device SSN Get\r\n");	
}

static void CallbackForm6BtnDeviceSsnSetClicked(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	ViewDataForm6Type * pViewDataPtr = (ViewDataForm6Type *)pThis->pViewData;	
	JBYTE bData[256];
	char *pStrDeviceName = NULL;	
	char msg[256];
	
	pStrDeviceName = (char *) gtk_entry_get_text(GTK_ENTRY(pViewDataPtr->pEntryDeviceSsn));    
	if(strlen(pStrDeviceName) == 0)
	{
		MESSAGE_BOX("Device SSN is empty");
		return;
	}

	UtilMemset((JBYTE *)&bData[0], 0x00, SREG_DATA_SIZE);

	sprintf((char *)&bData[0], "%s", pStrDeviceName);
	if(FuncSRegWrite((char *)SREG_DEVICE_SSN, &bData[0]) == FALSE)
	{
		MESSAGE_BOX("Device is busy");
		return;
	}
	sprintf(msg, "[FORM6] Device SSN Set = %s\r\n", pStrDeviceName);
	DBG_PRINTF(msg);	
}

static void CallbackForm6BtnMeasZeroBaseGetClicked(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	ViewDataForm6Type * pViewDataPtr = (ViewDataForm6Type *)pThis->pViewData;	
	
	if(FuncSRegRead((char *)SREG_MEAS_ZERO_BASE) == FALSE)
	{
		MESSAGE_BOX("Device is busy");
		return;
	}
	DBG_PRINTF("[FORM6] MEAS ZERO BASE Get\r\n");	
}

static void CallbackForm6BtnMeasZeroBaseOnClicked(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	ViewDataForm6Type * pViewDataPtr = (ViewDataForm6Type *)pThis->pViewData;	
	JBYTE bData[256];
	char *pStrDeviceName = NULL;	
	char msg[256];
	

	UtilMemset((JBYTE *)&bData[0], 0x00, SREG_DATA_SIZE);

	bData[0] = TRUE;

	if(FuncSRegWrite((char *)SREG_MEAS_ZERO_BASE, &bData[0]) == FALSE)
	{
		MESSAGE_BOX("Device is busy");
		return;
	}
	sprintf(msg, "[FORM6] MEAS ZERO BASE Set = %s\r\n", pStrDeviceName);
	DBG_PRINTF(msg);	
}

static void CallbackForm6BtnMeasZeroBaseOffClicked(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	ViewDataForm6Type * pViewDataPtr = (ViewDataForm6Type *)pThis->pViewData;	
	JBYTE bData[256];
	char *pStrDeviceName = NULL;	
	char msg[256];
	
	UtilMemset((JBYTE *)&bData[0], 0x00, SREG_DATA_SIZE);

	bData[0] = FALSE;
	
	if(FuncSRegWrite((char *)SREG_MEAS_ZERO_BASE, &bData[0]) == FALSE)
	{
		MESSAGE_BOX("Device is busy");
		return;
	}
	sprintf(msg, "[FORM6] MEAS ZERO BASE Set = %s\r\n", pStrDeviceName);
	DBG_PRINTF(msg);	
}

static void CallbackForm6BtnMeasLeadoffGetClicked(GtkWidget *widget, GdkEvent *event, gpointer data)
{	
  ViewDataForm6Type * pViewDataPtr = (ViewDataForm6Type *)pThis->pViewData;	
	
	if(FuncSRegRead((char *)SREG_MEAS_LEAD_OFF) == FALSE)
	{
		MESSAGE_BOX("Device is busy");
		return;
	}
	DBG_PRINTF("[FORM6] MEAS ZERO BASE Get\r\n");	
}

static void CallbackForm6BtnMeasLeadOffEnableClicked(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	ViewDataForm6Type * pViewDataPtr = (ViewDataForm6Type *)pThis->pViewData;	
	JBYTE bData[256];
	char *pStrDeviceName = NULL;	
	char msg[256];
	

	UtilMemset((JBYTE *)&bData[0], 0x00, SREG_DATA_SIZE);

	bData[0] = TRUE;

	if(FuncSRegWrite((char *)SREG_MEAS_LEAD_OFF, &bData[0]) == FALSE)
	{
		MESSAGE_BOX("Device is busy");
		return;
	}
	sprintf(msg, "[FORM6] MEAS ZERO BASE Set = %s\r\n", pStrDeviceName);
	DBG_PRINTF(msg);	
}

static void CallbackForm6BtnMeasLeadOffDisableClicked(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	ViewDataForm6Type * pViewDataPtr = (ViewDataForm6Type *)pThis->pViewData;	
	JBYTE bData[256];
	char *pStrDeviceName = NULL;	
	char msg[256];
	
	UtilMemset((JBYTE *)&bData[0], 0x00, SREG_DATA_SIZE);

	bData[0] = FALSE;
	
	if(FuncSRegWrite((char *)SREG_MEAS_LEAD_OFF, &bData[0]) == FALSE)
	{
		MESSAGE_BOX("Device is busy");
		return;
	}
	sprintf(msg, "[FORM6] MEAS ZERO BASE Set = %s\r\n", pStrDeviceName);
	DBG_PRINTF(msg);	
}

static void CallbackForm6BtnMeasLeadoffCurrSetClicked(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	ViewDataForm6Type * pViewDataPtr = (ViewDataForm6Type *)pThis->pViewData;	
	
	JBYTE bData[256];
	char *pStr = NULL;	
	char msg[256];
	float fData;
  JINT iData = 0;
	pStr = (char *) gtk_entry_get_text(GTK_ENTRY(pViewDataPtr->pEntryLeadOffCurrent));    
	if(strlen(pStr) == 0)
	{
		MESSAGE_BOX("Current Level is empty");
		return;
	}

	UtilMemset((JBYTE *)&bData[0], 0x00, SREG_DATA_SIZE);
  iData = atoi(pStr);

  bData[0] = iData;
  
	if(FuncSRegWrite((char *)SREG_MEAS_LEAD_OFF_CURR, &bData[0]) == FALSE)
	{
		MESSAGE_BOX("Device is busy");
		return;
	}
	sprintf(msg, "[FORM6]Leadoff Current Level Set = %s\r\n", pStr);
	DBG_PRINTF(msg);
}

static void CallbackForm6BtnMeasLeadoffCurrGetClicked(GtkWidget *widget, GdkEvent *event, gpointer data)
{	
  ViewDataForm6Type * pViewDataPtr = (ViewDataForm6Type *)pThis->pViewData;	
	
	if(FuncSRegRead((char *)SREG_MEAS_LEAD_OFF_CURR) == FALSE)
	{
		MESSAGE_BOX("Device is busy");
		return;
	}
	DBG_PRINTF("[FORM6]Leadoff Current level Get\r\n");	
}

static void CallbackForm6BtnMeasLeadoffCompThresholdGetClicked(GtkWidget *widget, GdkEvent *event, gpointer data)
{
  ViewDataForm6Type * pViewDataPtr = (ViewDataForm6Type *)pThis->pViewData;	
	
	if(FuncSRegRead((char *)SREG_MEAS_LEAD_OFF_COMP_TH) == FALSE)
	{
		MESSAGE_BOX("Device is busy");
		return;
	}
	DBG_PRINTF("[FORM6]Leadoff Compare Threshold Get\r\n");	
}

static void CallbackForm6BtnMeasLeadoffCompThresholdSetClicked(GtkWidget *widget, GdkEvent *event, gpointer data)
{  
	ViewDataForm6Type * pViewDataPtr = (ViewDataForm6Type *)pThis->pViewData;	
	
	JBYTE bData[256];
	char *pStr = NULL;	
	char msg[256];
	float fData;
	pStr = (char *) gtk_entry_get_text(GTK_ENTRY(pViewDataPtr->pEntryLeadOffCompThreshold));    
	if(strlen(pStr) == 0)
	{
		MESSAGE_BOX("Device is empty");
		return;
	}

	UtilMemset((JBYTE *)&bData[0], 0x00, SREG_DATA_SIZE);
  fData = atof(pStr);
  UtilMemcpy((JBYTE *)&bData[0], (JBYTE *)&fData , SREG_DATA_MEAS_LEAD_COMP_TH_SIZE);
	if(FuncSRegWrite((char *)SREG_MEAS_LEAD_OFF_COMP_TH, &bData[0]) == FALSE)
	{
		MESSAGE_BOX("Device is busy");
		return;
	}
	sprintf(msg, "[FORM6]Leadoff Compare Threshold Set = %s\r\n", pStr);
	DBG_PRINTF(msg);	
}


static void CallbackForm6BtnMeasMotionModeGetClicked(GtkWidget *widget, GdkEvent *event, gpointer data)
{	
  ViewDataForm6Type * pViewDataPtr = (ViewDataForm6Type *)pThis->pViewData;	
	
	if(FuncSRegRead((char *)SREG_MEAS_MOTION_MODE) == FALSE)
	{
		MESSAGE_BOX("Device is busy");
		return;
	}
	DBG_PRINTF("[FORM6] Motion Mode  Get\r\n");	
}

static void CallbackForm6BtnMeasMotionModeEnableClicked(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	ViewDataForm6Type * pViewDataPtr = (ViewDataForm6Type *)pThis->pViewData;	
	JBYTE bData[256];
	char *pStrDeviceName = NULL;	
	char msg[256];
	

	UtilMemset((JBYTE *)&bData[0], 0x00, SREG_DATA_SIZE);

	bData[0] = TRUE;

	if(FuncSRegWrite((char *)SREG_MEAS_MOTION_MODE, &bData[0]) == FALSE)
	{
		MESSAGE_BOX("Device is busy");
		return;
	}
	sprintf(msg, "[FORM6] Motion Mode Set = %s\r\n", pStrDeviceName);
	DBG_PRINTF(msg);	
}

static void CallbackForm6BtnMeasMotionModeDisableClicked(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	ViewDataForm6Type * pViewDataPtr = (ViewDataForm6Type *)pThis->pViewData;	
	JBYTE bData[256];
	char *pStrDeviceName = NULL;	
	char msg[256];
	
	UtilMemset((JBYTE *)&bData[0], 0x00, SREG_DATA_SIZE);

	bData[0] = FALSE;
	
	if(FuncSRegWrite((char *)SREG_MEAS_MOTION_MODE, &bData[0]) == FALSE)
	{
		MESSAGE_BOX("Device is busy");
		return;
	}
	sprintf(msg, "[FORM6]Motion Mode Set = %s\r\n", pStrDeviceName);
	DBG_PRINTF(msg);	
}

gint CallbackForm6Timer1 (gpointer data)
{    		
	char strDeviceName[256];
	char strDeviceNameEntry[256];

	char strLabel[256];
	char strEntry[256];
  JFLOAT fData = 0;
	JBOOL bEnable = TRUE;

	ViewDataForm6Type * pViewDataPtr = (ViewDataForm6Type *)pThis->pViewData;	
	if(pViewDataPtr->bShow == FALSE)
	{
		return TRUE;
	}

	if((GlobalVar.dwSysSta5 & SYS_STA5_SERIAL_PORT_OPEN) == 0)
	{
		bEnable = FALSE;
	}

	if(GlobalVar.iBleState == BLE_STATE_CLOSE)
	{
		bEnable = FALSE;
	}

	if(bEnable == FALSE)
	{
		JViewButtonDisable(pViewDataPtr->pBtnDeviceNameGet);
		JViewButtonDisable(pViewDataPtr->pBtnDeviceNameSet);
		JViewButtonDisable(pViewDataPtr->pBtnDeviceReset);
		JViewButtonDisable(pViewDataPtr->pBtnDeviceSsnSet);
		JViewButtonDisable(pViewDataPtr->pBtnDeviceSsnGet);
		JViewButtonDisable(pViewDataPtr->pBtnMeasZeroBaseGet);
		JViewButtonDisable(pViewDataPtr->pBtnMeasZeroBaseOn);
		JViewButtonDisable(pViewDataPtr->pBtnMeasZeroBaseOff);

		JViewButtonDisable(pViewDataPtr->pBtnMeasLeadOffGet);
		JViewButtonDisable(pViewDataPtr->pBtnMeasLeadOffEnable);
		JViewButtonDisable(pViewDataPtr->pBtnMeasLeadOffDisable);
    
		JViewButtonDisable(pViewDataPtr->pBtnMeasLeadOffCompThresholdSet);
		JViewButtonDisable(pViewDataPtr->pBtnMeasLeadOffCompThresholdGet);

    JViewButtonDisable(pViewDataPtr->pBtnMeasLeadOffCurrSet);
		JViewButtonDisable(pViewDataPtr->pBtnMeasLeadOffCurrGet);
    
		JViewButtonDisable(pViewDataPtr->pBtnMeasMotionModeGet);
		JViewButtonDisable(pViewDataPtr->pBtnMeasMotionModeEnable);
		JViewButtonDisable(pViewDataPtr->pBtnMeasMotionModeDisable);
    
		gtk_widget_set_sensitive(pViewDataPtr->pEntryDeviceName, FALSE);
		gtk_widget_set_sensitive(pViewDataPtr->pEntryDeviceSsn, FALSE);
		gtk_widget_set_sensitive(pViewDataPtr->pEntryLeadOffCompThreshold, FALSE);
		gtk_widget_set_sensitive(pViewDataPtr->pEntryLeadOffCurrent, FALSE);
	}
	else
	{
		JViewButtonEnable(pViewDataPtr->pBtnDeviceNameGet);
		JViewButtonEnable(pViewDataPtr->pBtnDeviceNameSet);
		JViewButtonEnable(pViewDataPtr->pBtnDeviceReset);
		JViewButtonEnable(pViewDataPtr->pBtnDeviceSsnSet);
		JViewButtonEnable(pViewDataPtr->pBtnDeviceSsnGet);
		JViewButtonEnable(pViewDataPtr->pBtnMeasZeroBaseGet);
		JViewButtonEnable(pViewDataPtr->pBtnMeasZeroBaseOn);
		JViewButtonEnable(pViewDataPtr->pBtnMeasZeroBaseOff);

		JViewButtonEnable(pViewDataPtr->pBtnMeasLeadOffGet);
		JViewButtonEnable(pViewDataPtr->pBtnMeasLeadOffEnable);
		JViewButtonEnable(pViewDataPtr->pBtnMeasLeadOffDisable);
    
		JViewButtonEnable(pViewDataPtr->pBtnMeasLeadOffCompThresholdSet);
		JViewButtonEnable(pViewDataPtr->pBtnMeasLeadOffCompThresholdGet);

		JViewButtonEnable(pViewDataPtr->pBtnMeasLeadOffCurrSet);
		JViewButtonEnable(pViewDataPtr->pBtnMeasLeadOffCurrGet);

		JViewButtonEnable(pViewDataPtr->pBtnMeasMotionModeGet);
		JViewButtonEnable(pViewDataPtr->pBtnMeasMotionModeEnable);
		JViewButtonEnable(pViewDataPtr->pBtnMeasMotionModeDisable);

		gtk_widget_set_sensitive(pViewDataPtr->pEntryDeviceName, TRUE);
		gtk_widget_set_sensitive(pViewDataPtr->pEntryDeviceSsn, TRUE);
		gtk_widget_set_sensitive(pViewDataPtr->pEntryLeadOffCompThreshold, TRUE);
		gtk_widget_set_sensitive(pViewDataPtr->pEntryLeadOffCurrent, TRUE);		
	}

	///---------------------------------------------------------------------------------------------///
	/// DEVICE_NAME
	///---------------------------------------------------------------------------------------------///
	strcpy(strDeviceName, (char *) &SRegApp.DEVICE_NAME[0]);
	if(strlen(strDeviceName) > 0)
	{
		gtk_label_set_text(GTK_LABEL(pViewDataPtr->pLabelDeviceName), (char *) &strDeviceName[0]);		
	}
	
	strcpy(strDeviceNameEntry, gtk_entry_get_text(GTK_ENTRY(pViewDataPtr->pEntryDeviceName)));
	if(strlen(strDeviceNameEntry) == 0)
	{
		gtk_entry_set_text(GTK_ENTRY(pViewDataPtr->pEntryDeviceName), (char *) &strDeviceName[0]);			
	}

	///---------------------------------------------------------------------------------------------////
	/// DEVICE_SSN
	///---------------------------------------------------------------------------------------------///
	strcpy(strLabel, (char *) &SRegApp.DEVICE_SSN[0]);
	if(strlen(strLabel) > 0)
	{
		gtk_label_set_text(GTK_LABEL(pViewDataPtr->pLabelDeviceSsn), (char *) &strLabel[0]);		
	}

	strcpy(strEntry, gtk_entry_get_text(GTK_ENTRY(pViewDataPtr->pEntryDeviceSsn)));
	if(strlen(strEntry) == 0)
	{
		gtk_entry_set_text(GTK_ENTRY(pViewDataPtr->pEntryDeviceSsn), (char *) &strLabel[0]);			
	}

	///---------------------------------------------------------------------------------------------///
	/// MEAS_ZERO_BASE
	///---------------------------------------------------------------------------------------------///	
	if(SRegApp.MEAS_ZERO_BASE[0] == 1)
	{
		sprintf(strLabel, "%s", "ON");
	}
	else if(SRegApp.MEAS_ZERO_BASE[0] == 0)
	{
		sprintf(strLabel, "%s", "OFF");
	}
	else
	{
		sprintf(strLabel, "%s", "--");
	}
	

	if(strlen(strLabel) > 0)
	{
		gtk_label_set_text(GTK_LABEL(pViewDataPtr->pLabelMeasZeroBase), (char *) &strLabel[0]);		
	}

	///---------------------------------------------------------------------------------------------///
	/// MEAS_LEAD_OFF
	///---------------------------------------------------------------------------------------------///	
	if(SRegApp.MEAS_LEAD_OFF[0] == 1)
	{
		sprintf(strLabel, "%s", "ON");
	}
	else if(SRegApp.MEAS_LEAD_OFF[0] == 0)
	{
		sprintf(strLabel, "%s", "OFF");
	}
	else
	{
		sprintf(strLabel, "%s", "--");
	}
	if(strlen(strLabel) > 0)
	{
		gtk_label_set_text(GTK_LABEL(pViewDataPtr->pLabelMeasLeadOff), (char *) &strLabel[0]);		
	}
	///---------------------------------------------------------------------------------------------///
	/// MEAS_LEAD_OFF CompThreshold
	///---------------------------------------------------------------------------------------------///	
	UtilMemcpy((JBYTE*)&fData, &SRegApp.MEAS_LEAD_OFF_COMP_TH[0], SREG_DATA_MEAS_LEAD_COMP_TH_SIZE);
	if(fData < 70)
  {
  	sprintf(strLabel, "%s", "--");
	} 
  else
  {
    sprintf(strLabel, "%.1f", fData);
  }
	if(strlen(strLabel) > 0)
	{
		gtk_label_set_text(GTK_LABEL(pViewDataPtr->pLabelLeadOffCompThreshold), (char *) &strLabel[0]);		
	}

	///---------------------------------------------------------------------------------------------///
	/// MEAS_LEAD_OFF Current
	///---------------------------------------------------------------------------------------------///	
	if(SRegApp.MEAS_LEAD_OFF_CURR[0] > 10)
  {
  	sprintf(strLabel, "%s", "--");
	} 
	else
  {
    sprintf(strLabel, "%d", SRegApp.MEAS_LEAD_OFF_CURR[0]);
  }
  
	if(strlen(strLabel) > 0)
	{
		gtk_label_set_text(GTK_LABEL(pViewDataPtr->pLabelLeadOffCurrent), (char *) &strLabel[0]);		
	}

	///---------------------------------------------------------------------------------------------///
	/// MEAS_MOTION_MODE
	///---------------------------------------------------------------------------------------------///	
	if(SRegApp.MEAS_MOTION_MODE[0] == 1)
	{
		sprintf(strLabel, "%s", "ON");
	}
	else if(SRegApp.MEAS_MOTION_MODE[0] == 0)
	{
		sprintf(strLabel, "%s", "OFF");
	}
	else
	{
		sprintf(strLabel, "%s", "--");
	}
	if(strlen(strLabel) > 0)
	{
		gtk_label_set_text(GTK_LABEL(pViewDataPtr->pLabelMeasMotionMode), (char *) &strLabel[0]);		
	}


	return TRUE;
}

///------------------------------------------------------------------------------------///
/// Form6 Function
///------------------------------------------------------------------------------------///
static JINT LabelInit(void)
{
	ViewDataForm6Type * pViewDataPtr = &ViewDataForm6;
	JINT iRet = TRUE;
	GtkWidget *pLabel 	= NULL;

	JINT x0 = 0;
	JINT y0 = 0;	
	JINT w  = 0;
	JINT h  = 0;

	GtkStyleContext *pContext = NULL;

	///-----------------------------------------------------------------------///
	/// Label Device Name
	///-----------------------------------------------------------------------///
	x0 = FORM6_FRAME0_LEFT + FORM6_FRAME0_XGAP;
	y0 = FORM6_FRAME0_TOP  + FORM6_FRAME0_YGAP;
	w  = 300;
	h  = 30;	
		
	pLabel = gtk_label_new_with_mnemonic("");
	pContext = gtk_widget_get_style_context(pLabel);	
	gtk_style_context_add_class(pContext, "label_type2");  	
  gtk_widget_set_name(pLabel, "");  	
	gtk_label_set_xalign(GTK_LABEL(pLabel), 0.01);
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pLabel, x0, y0);
	gtk_widget_set_size_request(pLabel, w, h);  
  gtk_widget_show(pLabel);
	pViewDataPtr->pLabelDeviceName = pLabel;

	///-----------------------------------------------------------------------///
	/// Label Device Ssn
	///-----------------------------------------------------------------------///
	x0 = FORM6_FRAME2_LEFT + FORM6_FRAME2_XGAP;
	y0 = FORM6_FRAME2_TOP  + FORM6_FRAME2_YGAP;
	w  = 300;
	h  = 30;	
		
	pLabel = gtk_label_new_with_mnemonic("--");
	pContext = gtk_widget_get_style_context(pLabel);	
	gtk_style_context_add_class(pContext, "label_type2");  	
  gtk_widget_set_name(pLabel, "");  	
	gtk_label_set_xalign(GTK_LABEL(pLabel), 0.01);
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pLabel, x0, y0);
	gtk_widget_set_size_request(pLabel, w, h);  
  gtk_widget_show(pLabel);
	pViewDataPtr->pLabelDeviceSsn = pLabel;	

	///-----------------------------------------------------------------------///
	/// Label ZeroBase
	///-----------------------------------------------------------------------///
	x0 = FORM6_FRAME3_LEFT + FORM6_FRAME3_XGAP;
	y0 = FORM6_FRAME3_TOP  + FORM6_FRAME3_YGAP;
	w  = 300;
	h  = 30;	
		
	pLabel = gtk_label_new_with_mnemonic("--");
	pContext = gtk_widget_get_style_context(pLabel);	
	gtk_style_context_add_class(pContext, "label_type2");  	
  gtk_widget_set_name(pLabel, "");  	
	//gtk_label_set_xalign(GTK_LABEL(pLabel), 0.01);
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pLabel, x0, y0);
	gtk_widget_set_size_request(pLabel, w, h);  
  gtk_widget_show(pLabel);
	pViewDataPtr->pLabelMeasZeroBase = pLabel;		

	///-----------------------------------------------------------------------///
	/// Label LeadOff
	///-----------------------------------------------------------------------///
	x0 = FORM6_FRAME4_LEFT + FORM6_FRAME4_XGAP;
	y0 = FORM6_FRAME4_TOP  + FORM6_FRAME4_YGAP;
	w  = 300;
	h  = 30;	
		
	pLabel = gtk_label_new_with_mnemonic("--");
	pContext = gtk_widget_get_style_context(pLabel);	
	gtk_style_context_add_class(pContext, "label_type2");  	
  gtk_widget_set_name(pLabel, "");  	
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pLabel, x0, y0);
	gtk_widget_set_size_request(pLabel, w, h);  
  gtk_widget_show(pLabel);
	pViewDataPtr->pLabelMeasLeadOff = pLabel;		

	///-----------------------------------------------------------------------///
	/// Label LeadOff
	///-----------------------------------------------------------------------///
	x0 = FORM6_FRAME5_LEFT + FORM6_FRAME5_XGAP;
	y0 = FORM6_FRAME5_TOP  + FORM6_FRAME5_YGAP ;
	w  = 300;
	h  = 30;	
		
	pLabel = gtk_label_new_with_mnemonic("--");
	pContext = gtk_widget_get_style_context(pLabel);	
	gtk_style_context_add_class(pContext, "label_type2");  	
  gtk_widget_set_name(pLabel, "");  	
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pLabel, x0, y0);
	gtk_widget_set_size_request(pLabel, w, h);  
  gtk_widget_show(pLabel);
	pViewDataPtr->pLabelLeadOffCompThreshold = pLabel;		

	///-----------------------------------------------------------------------///
	/// Label LeadOff
	///-----------------------------------------------------------------------///
	x0 = FORM6_FRAME6_LEFT + FORM6_FRAME6_XGAP;
	y0 = FORM6_FRAME6_TOP  + FORM6_FRAME6_YGAP ;
	w  = 300;
	h  = 30;	
		
	pLabel = gtk_label_new_with_mnemonic("--");
	pContext = gtk_widget_get_style_context(pLabel);	
	gtk_style_context_add_class(pContext, "label_type2");  	
  gtk_widget_set_name(pLabel, "");  	
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pLabel, x0, y0);
	gtk_widget_set_size_request(pLabel, w, h);  
  gtk_widget_show(pLabel);
	pViewDataPtr->pLabelLeadOffCurrent = pLabel;		
  
	///-----------------------------------------------------------------------///
	/// Label LeadOff
	///-----------------------------------------------------------------------///
	x0 = FORM6_FRAME7_LEFT + FORM6_FRAME7_XGAP;
	y0 = FORM6_FRAME7_TOP  + FORM6_FRAME7_YGAP ;
	w  = 300;
	h  = 30;	
		
	pLabel = gtk_label_new_with_mnemonic("--");
	pContext = gtk_widget_get_style_context(pLabel);	
	gtk_style_context_add_class(pContext, "label_type2");  	
  gtk_widget_set_name(pLabel, "");  	
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pLabel, x0, y0);
	gtk_widget_set_size_request(pLabel, w, h);  
  gtk_widget_show(pLabel);
	pViewDataPtr->pLabelMeasMotionMode = pLabel;		
  

	return TRUE;
}

static JINT EntryInit(void) 
{
	ViewDataForm6Type * pViewDataPtr = &ViewDataForm6;
	GtkWidget *pEntry = NULL;

	JINT iRet = TRUE;	
	JINT x0 = 0;
	JINT y0 = 0;
	JINT w = 0;
	JINT h = 0;

	///-----------------------------------------------------------------------///
	/// Entry DeviceName
	///-----------------------------------------------------------------------///
	x0 = FORM6_FRAME0_LEFT + FORM6_FRAME0_XGAP ;
	y0 = FORM6_FRAME0_TOP  + FORM6_FRAME0_YGAP + FORM6_FRAME0_ROW;
	w  = 300;
	h  = 20;

	pEntry =  gtk_entry_new(); 
  gtk_entry_set_placeholder_text(GTK_ENTRY(pEntry), "set BLE name to your device");
  gtk_widget_set_name(pEntry, "label_type1");  
  gtk_widget_set_size_request(pEntry, w, h); 
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pEntry, x0, y0);
	gtk_entry_set_text(GTK_ENTRY(pEntry), "");    
  g_signal_connect(G_OBJECT(pEntry),   "activate",   G_CALLBACK(CallbackForm6EntryDeviceNameActive), NULL);
  gtk_widget_show(pEntry);
	pViewDataPtr->pEntryDeviceName = pEntry;

	///-----------------------------------------------------------------------///
	/// Entry DeviceSsn
	///-----------------------------------------------------------------------///
	x0 = FORM6_FRAME2_LEFT + FORM6_FRAME2_XGAP ;
	y0 = FORM6_FRAME2_TOP  + FORM6_FRAME2_YGAP + FORM6_FRAME2_ROW;
	w  = 300;
	h  = 20;

	pEntry =  gtk_entry_new(); 
  gtk_entry_set_placeholder_text(GTK_ENTRY(pEntry), "set SSN to your device");
  gtk_widget_set_name(pEntry, "label_type1");  
  gtk_widget_set_size_request(pEntry, w, h); 
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pEntry, x0, y0);
	gtk_entry_set_text(GTK_ENTRY(pEntry), "");    
  //g_signal_connect(G_OBJECT(pEntry),   "activate",   G_CALLBACK(CallbackForm6EntryDeviceNameActive), NULL);
  gtk_widget_show(pEntry);
	pViewDataPtr->pEntryDeviceSsn = pEntry;

	///-----------------------------------------------------------------------///
	/// Entry LeadOffCompThreshold
	///-----------------------------------------------------------------------///
	x0 = FORM6_FRAME5_LEFT + FORM6_FRAME5_XGAP ;
	y0 = FORM6_FRAME5_TOP  + FORM6_FRAME5_YGAP + FORM6_FRAME4_ROW;
	w  = 300;
	h  = 20;

	pEntry =  gtk_entry_new(); 
  gtk_entry_set_placeholder_text(GTK_ENTRY(pEntry), "set Lead Off Compare Threshold");
  gtk_widget_set_name(pEntry, "label_type1");  
  gtk_widget_set_size_request(pEntry, w, h); 
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pEntry, x0, y0);
	gtk_entry_set_text(GTK_ENTRY(pEntry), "");    
  //g_signal_connect(G_OBJECT(pEntry),   "activate",   G_CALLBACK(CallbackForm6EntryDeviceNameActive), NULL);
  gtk_widget_show(pEntry);
	pViewDataPtr->pEntryLeadOffCompThreshold = pEntry;

	///-----------------------------------------------------------------------///
	/// Entry LeadOffCurrent
	///-----------------------------------------------------------------------///
	x0 = FORM6_FRAME6_LEFT + FORM6_FRAME6_XGAP ;
	y0 = FORM6_FRAME6_TOP  + FORM6_FRAME6_YGAP + FORM6_FRAME4_ROW;
	w  = 300;
	h  = 20;
  

	pEntry =  gtk_entry_new(); 
  gtk_entry_set_placeholder_text(GTK_ENTRY(pEntry), "set Lead Off Current Level");
  gtk_widget_set_name(pEntry, "label_type1");  
  gtk_widget_set_size_request(pEntry, w, h); 
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pEntry, x0, y0);
	gtk_entry_set_text(GTK_ENTRY(pEntry), "");    
  //g_signal_connect(G_OBJECT(pEntry),   "activate",   G_CALLBACK(CallbackForm6EntryDeviceNameActive), NULL);
  gtk_widget_show(pEntry);
	pViewDataPtr->pEntryLeadOffCurrent = pEntry;


	return iRet;	
}

static JINT ButtonInit(void)
{
	ViewDataForm6Type * pViewDataPtr = &ViewDataForm6;
	JINT iRet = TRUE;
	GtkWidget *pButton 	= NULL;
	JINT x0 = 0;
	JINT y0 = 0;
	JINT w = 0;
	JINT h = 0;	

 	///-----------------------------------------------------------------------///
	/// Button -> BleDeviceNameGet
	///-----------------------------------------------------------------------///
	x0 = FORM6_FRAME0_LEFT + FORM6_FRAME0_XGAP + 320;
	y0 = FORM6_FRAME0_TOP  + FORM6_FRAME0_YGAP ;
	w = 120;
	h = 30;
	pButton = gtk_button_new_with_label("Get");
  gtk_widget_set_size_request(pButton, w, h); 
  g_signal_connect(G_OBJECT(pButton), "clicked",   G_CALLBACK(CallbackForm6BtnDeviceNameGetClicked), NULL);
  gtk_widget_set_name(pButton, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pButton, x0, y0);
  gtk_widget_show(pButton);  
 	pViewDataPtr->pBtnDeviceNameGet = pButton;

 	///-----------------------------------------------------------------------///
	/// Button -> BleDeviceNameSet
	///-----------------------------------------------------------------------///
	x0 = FORM6_FRAME0_LEFT + FORM6_FRAME0_XGAP + 320;
	y0 = FORM6_FRAME0_TOP  + FORM6_FRAME0_YGAP + FORM6_FRAME0_ROW;
	w = 120;
	h = 30;
	pButton = gtk_button_new_with_label("Set");
  gtk_widget_set_size_request(pButton, w, h); 
  g_signal_connect(G_OBJECT(pButton), "clicked",   G_CALLBACK(CallbackForm6BtnDeviceNameSetClicked), NULL);
  gtk_widget_set_name(pButton, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pButton, x0, y0);
  gtk_widget_show(pButton);  
 	pViewDataPtr->pBtnDeviceNameSet = pButton;

	///-----------------------------------------------------------------------///
	/// Button -> BleDeviceReset
	///-----------------------------------------------------------------------///
	x0 = FORM6_FRAME1_LEFT + FORM6_FRAME1_XGAP;
	y0 = FORM6_FRAME1_TOP  + FORM6_FRAME1_YGAP;
	w = 120;
	h = 30;
	pButton = gtk_button_new_with_label("Reset");
  gtk_widget_set_size_request(pButton, w, h); 
  g_signal_connect(G_OBJECT(pButton), "clicked",   G_CALLBACK(CallbackForm6BtnDeviceResetSetClicked), NULL);
  gtk_widget_set_name(pButton, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pButton, x0, y0);
  gtk_widget_show(pButton);  
 	pViewDataPtr->pBtnDeviceReset = pButton;

	///-----------------------------------------------------------------------///
	/// Button -> BleDeviceSsnGet
	///-----------------------------------------------------------------------///
	x0 = FORM6_FRAME2_LEFT + FORM6_FRAME2_XGAP + 320;
	y0 = FORM6_FRAME2_TOP  + FORM6_FRAME2_YGAP ;
	w = 120;
	h = 30;
	pButton = gtk_button_new_with_label("Get");
  gtk_widget_set_size_request(pButton, w, h); 
  g_signal_connect(G_OBJECT(pButton), "clicked",   G_CALLBACK(CallbackForm6BtnDeviceSsnGetClicked), NULL);
  gtk_widget_set_name(pButton, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pButton, x0, y0);
  gtk_widget_show(pButton);  
 	pViewDataPtr->pBtnDeviceSsnGet = pButton;

	///-----------------------------------------------------------------------///
	/// Button -> BleDeviceSsnSet
	///-----------------------------------------------------------------------///
	x0 = FORM6_FRAME2_LEFT + FORM6_FRAME2_XGAP + 320;
	y0 = FORM6_FRAME2_TOP  + FORM6_FRAME2_YGAP + FORM6_FRAME0_ROW;
	w = 120;
	h = 30;
	pButton = gtk_button_new_with_label("Set");
  gtk_widget_set_size_request(pButton, w, h); 
  g_signal_connect(G_OBJECT(pButton), "clicked",   G_CALLBACK(CallbackForm6BtnDeviceSsnSetClicked), NULL);
  gtk_widget_set_name(pButton, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pButton, x0, y0);
  gtk_widget_show(pButton);  
 	pViewDataPtr->pBtnDeviceSsnSet = pButton;	 

 	///-----------------------------------------------------------------------///
	/// Button -> BleMeasZeroBaseGet
	///-----------------------------------------------------------------------///
	x0 = FORM6_FRAME3_LEFT + FORM6_FRAME3_XGAP + 320;
	y0 = FORM6_FRAME3_TOP  + FORM6_FRAME3_YGAP ;
	w = 120;
	h = 30;
	pButton = gtk_button_new_with_label("Get");
  gtk_widget_set_size_request(pButton, w, h); 
  g_signal_connect(G_OBJECT(pButton), "clicked",   G_CALLBACK(CallbackForm6BtnMeasZeroBaseGetClicked), NULL);
  gtk_widget_set_name(pButton, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pButton, x0, y0);
  gtk_widget_show(pButton);  
 	pViewDataPtr->pBtnMeasZeroBaseGet = pButton;	 

	///-----------------------------------------------------------------------///
	/// Button -> BleMeasZeroBaseOn
	///-----------------------------------------------------------------------///
	x0 = FORM6_FRAME3_LEFT + FORM6_FRAME3_XGAP;
	y0 = FORM6_FRAME3_TOP  + FORM6_FRAME3_YGAP + FORM6_FRAME0_ROW;
	w = 120;
	h = 30;
	pButton = gtk_button_new_with_label("On");
  gtk_widget_set_size_request(pButton, w, h); 
  g_signal_connect(G_OBJECT(pButton), "clicked",   G_CALLBACK(CallbackForm6BtnMeasZeroBaseOnClicked), NULL);
  gtk_widget_set_name(pButton, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pButton, x0, y0);
  gtk_widget_show(pButton);  
 	pViewDataPtr->pBtnMeasZeroBaseOn = pButton;	 

	///-----------------------------------------------------------------------///
	/// Button -> BleMeasZeroBaseOff
	///-----------------------------------------------------------------------///
	x0 = FORM6_FRAME3_LEFT + FORM6_FRAME3_XGAP + 180;
	y0 = FORM6_FRAME3_TOP  + FORM6_FRAME3_YGAP + FORM6_FRAME0_ROW;
	w = 120;
	h = 30;
	pButton = gtk_button_new_with_label("Off");
  gtk_widget_set_size_request(pButton, w, h); 
  g_signal_connect(G_OBJECT(pButton), "clicked",   G_CALLBACK(CallbackForm6BtnMeasZeroBaseOffClicked), NULL);
  gtk_widget_set_name(pButton, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pButton, x0, y0);
  gtk_widget_show(pButton);  
 	pViewDataPtr->pBtnMeasZeroBaseOff = pButton;	 	 
	
 	///-----------------------------------------------------------------------///
	/// Button -> BleMeasLeadoffGet
	///-----------------------------------------------------------------------///
	x0 = FORM6_FRAME4_LEFT + FORM6_FRAME4_XGAP + 320;
	y0 = FORM6_FRAME4_TOP  + FORM6_FRAME4_YGAP;
	w = 120;
	h = 30;
	pButton = gtk_button_new_with_label("Get");
  gtk_widget_set_size_request(pButton, w, h); 
  g_signal_connect(G_OBJECT(pButton), "clicked",   G_CALLBACK(CallbackForm6BtnMeasLeadoffGetClicked), NULL);
  gtk_widget_set_name(pButton, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pButton, x0, y0);
  gtk_widget_show(pButton);  
 	pViewDataPtr->pBtnMeasLeadOffGet = pButton;	 

	///-----------------------------------------------------------------------///
	/// Button -> BleMeasLeadoffEnable
	///-----------------------------------------------------------------------///
	x0 = FORM6_FRAME4_LEFT + FORM6_FRAME4_XGAP;
	y0 = FORM6_FRAME4_TOP  + FORM6_FRAME4_YGAP + FORM6_FRAME0_ROW;
	w = 120;
	h = 30;
	pButton = gtk_button_new_with_label("On");
  gtk_widget_set_size_request(pButton, w, h); 
  g_signal_connect(G_OBJECT(pButton), "clicked",   G_CALLBACK(CallbackForm6BtnMeasLeadOffEnableClicked), NULL);
  gtk_widget_set_name(pButton, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pButton, x0, y0);
  gtk_widget_show(pButton);  
 	pViewDataPtr->pBtnMeasLeadOffEnable = pButton;	 

	///-----------------------------------------------------------------------///
	/// Button -> BleMeasLeadOffDisable
	///-----------------------------------------------------------------------///
	x0 = FORM6_FRAME4_LEFT + FORM6_FRAME4_XGAP + 180;
	y0 = FORM6_FRAME4_TOP  + FORM6_FRAME4_YGAP + FORM6_FRAME4_ROW;
	w = 120;
	h = 30;
	pButton = gtk_button_new_with_label("Off");
  gtk_widget_set_size_request(pButton, w, h); 
  g_signal_connect(G_OBJECT(pButton), "clicked",   G_CALLBACK(CallbackForm6BtnMeasLeadOffDisableClicked), NULL);
  gtk_widget_set_name(pButton, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pButton, x0, y0);
  gtk_widget_show(pButton);  
 	pViewDataPtr->pBtnMeasLeadOffDisable = pButton;


	///-----------------------------------------------------------------------///
	/// Button -> LeadOffCompThresholdSet
	///-----------------------------------------------------------------------///
	x0 = FORM6_FRAME5_LEFT + FORM6_FRAME5_XGAP + 320;
	y0 = FORM6_FRAME5_TOP  + FORM6_FRAME5_YGAP ;
	w = 120;
	h = 30;
	pButton = gtk_button_new_with_label("Get");
  gtk_widget_set_size_request(pButton, w, h); 
  g_signal_connect(G_OBJECT(pButton), "clicked",   G_CALLBACK(CallbackForm6BtnMeasLeadoffCompThresholdGetClicked), NULL);
  gtk_widget_set_name(pButton, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pButton, x0, y0);
  gtk_widget_show(pButton);  
 	pViewDataPtr->pBtnMeasLeadOffCompThresholdSet = pButton;

	///-----------------------------------------------------------------------///
	/// Button -> LeadOffCompThresholdGet
	///-----------------------------------------------------------------------///
	x0 = FORM6_FRAME5_LEFT + FORM6_FRAME5_XGAP + 320;
	y0 = FORM6_FRAME5_TOP  + FORM6_FRAME5_YGAP + FORM6_FRAME5_ROW;
	w = 120;
	h = 30;
	pButton = gtk_button_new_with_label("Set");
  gtk_widget_set_size_request(pButton, w, h); 
  g_signal_connect(G_OBJECT(pButton), "clicked",   G_CALLBACK(CallbackForm6BtnMeasLeadoffCompThresholdSetClicked), NULL);
  gtk_widget_set_name(pButton, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pButton, x0, y0);
  gtk_widget_show(pButton);  
 	pViewDataPtr->pBtnMeasLeadOffCompThresholdGet = pButton;

	///-----------------------------------------------------------------------///
	/// Button -> LeadOffCurrGet
	///-----------------------------------------------------------------------///
	x0 = FORM6_FRAME6_LEFT + FORM6_FRAME6_XGAP + 320;
	y0 = FORM6_FRAME6_TOP  + FORM6_FRAME6_YGAP ;
	w = 120;
	h = 30;
	pButton = gtk_button_new_with_label("Get");
  gtk_widget_set_size_request(pButton, w, h); 
  g_signal_connect(G_OBJECT(pButton), "clicked",   G_CALLBACK(CallbackForm6BtnMeasLeadoffCurrGetClicked), NULL);
  gtk_widget_set_name(pButton, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pButton, x0, y0);
  gtk_widget_show(pButton);  
 	pViewDataPtr->pBtnMeasLeadOffCurrGet = pButton;

	///-----------------------------------------------------------------------///
	/// Button ->LeadOffCurrSet
	///-----------------------------------------------------------------------///
	x0 = FORM6_FRAME6_LEFT + FORM6_FRAME6_XGAP + 320;
	y0 = FORM6_FRAME6_TOP  + FORM6_FRAME6_YGAP + FORM6_FRAME6_ROW;
	w = 120;
	h = 30;
	pButton = gtk_button_new_with_label("Set");
  gtk_widget_set_size_request(pButton, w, h); 
  g_signal_connect(G_OBJECT(pButton), "clicked",   G_CALLBACK(CallbackForm6BtnMeasLeadoffCurrSetClicked), NULL);
  gtk_widget_set_name(pButton, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pButton, x0, y0);
  gtk_widget_show(pButton);  
 	pViewDataPtr->pBtnMeasLeadOffCurrSet = pButton;

 	///-----------------------------------------------------------------------///
	/// Button -> BleMeasMotionModeGet
	///-----------------------------------------------------------------------///
	x0 = FORM6_FRAME7_LEFT + FORM6_FRAME7_XGAP + 320;
	y0 = FORM6_FRAME7_TOP  + FORM6_FRAME7_YGAP;
	w = 120;
	h = 30;
	pButton = gtk_button_new_with_label("Get");
  gtk_widget_set_size_request(pButton, w, h); 
  g_signal_connect(G_OBJECT(pButton), "clicked",   G_CALLBACK(CallbackForm6BtnMeasMotionModeGetClicked), NULL);
  gtk_widget_set_name(pButton, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pButton, x0, y0);
  gtk_widget_show(pButton);  
 	pViewDataPtr->pBtnMeasMotionModeGet = pButton;	 

	///-----------------------------------------------------------------------///
	/// Button -> BleMeasMotionModeEnable
	///-----------------------------------------------------------------------///
	x0 = FORM6_FRAME7_LEFT + FORM6_FRAME7_XGAP;
	y0 = FORM6_FRAME7_TOP  + FORM6_FRAME7_YGAP + FORM6_FRAME0_ROW;
	w = 120;
	h = 30;
	pButton = gtk_button_new_with_label("On");
  gtk_widget_set_size_request(pButton, w, h); 
  g_signal_connect(G_OBJECT(pButton), "clicked",   G_CALLBACK(CallbackForm6BtnMeasMotionModeEnableClicked), NULL);
  gtk_widget_set_name(pButton, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pButton, x0, y0);
  gtk_widget_show(pButton);  
 	pViewDataPtr->pBtnMeasMotionModeEnable = pButton;	 

	///-----------------------------------------------------------------------///
	/// Button -> BleMeasMotionModeDisable
	///-----------------------------------------------------------------------///
	x0 = FORM6_FRAME7_LEFT + FORM6_FRAME7_XGAP + 180;
	y0 = FORM6_FRAME7_TOP  + FORM6_FRAME7_YGAP + FORM6_FRAME7_ROW;
	w = 120;
	h = 30;
	pButton = gtk_button_new_with_label("Off");
  gtk_widget_set_size_request(pButton, w, h); 
  g_signal_connect(G_OBJECT(pButton), "clicked",   G_CALLBACK(CallbackForm6BtnMeasMotionModeDisableClicked), NULL);
  gtk_widget_set_name(pButton, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pButton, x0, y0);
  gtk_widget_show(pButton);  
 	pViewDataPtr->pBtnMeasMotionModeDisable = pButton;

  
	return iRet;
}

static JINT FrameInit(void)
{
	JINT iRet = TRUE;
	ViewDataForm6Type * pViewDataPtr = &ViewDataForm6;	
  GtkWidget * pFrame = gtk_frame_new ("");
	char strFrameName[256];
	JFLOAT fXAlign = 0.03;

  JINT x0 = 0;
  JINT y0 = 0;
  JINT w  = 0;
  JINT h  = 0;
  
	///-----------------------------------------------------------------------///
	/// FRAME#0
	///-----------------------------------------------------------------------///
	x0 = FORM6_FRAME0_LEFT;
	y0 = FORM6_FRAME0_TOP;
  w  = FORM6_FRAME0_WIDTH;
  h  = FORM6_FRAME0_HEIGHT;
	sprintf(strFrameName, "%s", "Device Name");

  pFrame = gtk_frame_new (strFrameName);
  gtk_frame_set_shadow_type (GTK_FRAME (pFrame), GTK_SHADOW_ETCHED_IN);
  gtk_frame_set_label_align (GTK_FRAME (pFrame), fXAlign, 0.5);
  gtk_widget_set_size_request(pFrame, w, h); 
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pFrame, x0, y0);
  gtk_widget_show(pFrame);

	///-----------------------------------------------------------------------///
	/// FRAME#1
	///-----------------------------------------------------------------------///
	x0 = FORM6_FRAME1_LEFT;
	y0 = FORM6_FRAME1_TOP;
  w  = FORM6_FRAME1_WIDTH;
  h  = FORM6_FRAME1_HEIGHT;
	sprintf(strFrameName, "%s", "Device Reset");

  pFrame = gtk_frame_new (strFrameName);
  gtk_frame_set_shadow_type (GTK_FRAME (pFrame), GTK_SHADOW_ETCHED_IN);
  gtk_frame_set_label_align (GTK_FRAME (pFrame), fXAlign, 0.5);
  gtk_widget_set_size_request(pFrame, w, h); 
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pFrame, x0, y0);
  gtk_widget_show(pFrame);

	///-----------------------------------------------------------------------///
	/// FRAME#2
	///-----------------------------------------------------------------------///
	x0 = FORM6_FRAME2_LEFT;
	y0 = FORM6_FRAME2_TOP;
  w  = FORM6_FRAME2_WIDTH;
  h  = FORM6_FRAME2_HEIGHT;
	sprintf(strFrameName, "%s", "Social Security Number (SSN)");

  pFrame = gtk_frame_new (strFrameName);
  gtk_frame_set_shadow_type (GTK_FRAME (pFrame), GTK_SHADOW_ETCHED_IN);
  gtk_frame_set_label_align (GTK_FRAME (pFrame), fXAlign, 0.5);
  gtk_widget_set_size_request(pFrame, w, h); 
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pFrame, x0, y0);
  gtk_widget_show(pFrame);	

	///-----------------------------------------------------------------------///
	/// FRAME#3
	///-----------------------------------------------------------------------///
	x0 = FORM6_FRAME3_LEFT;
	y0 = FORM6_FRAME3_TOP;
  w  = FORM6_FRAME3_WIDTH;
  h  = FORM6_FRAME3_HEIGHT;
	sprintf(strFrameName, "%s", "Zero Base Function");

  pFrame = gtk_frame_new (strFrameName);
  gtk_frame_set_shadow_type (GTK_FRAME (pFrame), GTK_SHADOW_ETCHED_IN);
  gtk_frame_set_label_align (GTK_FRAME (pFrame), fXAlign, 0.5);
  gtk_widget_set_size_request(pFrame, w, h); 
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pFrame, x0, y0);
  gtk_widget_show(pFrame);		

	///-----------------------------------------------------------------------///
	/// FRAME#4
	///-----------------------------------------------------------------------///
	x0 = FORM6_FRAME4_LEFT;
	y0 = FORM6_FRAME4_TOP;
  w  = FORM6_FRAME4_WIDTH;
  h  = FORM6_FRAME4_HEIGHT;
	sprintf(strFrameName, "%s", "Lead Off Function");

  pFrame = gtk_frame_new (strFrameName);
  gtk_frame_set_shadow_type (GTK_FRAME (pFrame), GTK_SHADOW_ETCHED_IN);
  gtk_frame_set_label_align (GTK_FRAME (pFrame), fXAlign, 0.5);
  gtk_widget_set_size_request(pFrame, w, h); 
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pFrame, x0, y0);
  gtk_widget_show(pFrame);		

  
	///-----------------------------------------------------------------------///
	/// FRAME#5
	///-----------------------------------------------------------------------///
	x0 = FORM6_FRAME5_LEFT;
	y0 = FORM6_FRAME5_TOP;
  w  = FORM6_FRAME5_WIDTH;
  h  = FORM6_FRAME5_HEIGHT;
	sprintf(strFrameName, "%s", "Lead Off Compare Threshold (%)");

  pFrame = gtk_frame_new (strFrameName);
  gtk_frame_set_shadow_type (GTK_FRAME (pFrame), GTK_SHADOW_ETCHED_IN);
  gtk_frame_set_label_align (GTK_FRAME (pFrame), fXAlign, 0.5);
  gtk_widget_set_size_request(pFrame, w, h); 
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pFrame, x0, y0);
  gtk_widget_show(pFrame);		

	///-----------------------------------------------------------------------///
	/// FRAME#6
	///-----------------------------------------------------------------------///
	x0 = FORM6_FRAME6_LEFT;
	y0 = FORM6_FRAME6_TOP;
  w  = FORM6_FRAME6_WIDTH;
  h  = FORM6_FRAME6_HEIGHT;
	sprintf(strFrameName, "%s", "Lead Off Current Level");

  pFrame = gtk_frame_new (strFrameName);
  gtk_frame_set_shadow_type (GTK_FRAME (pFrame), GTK_SHADOW_ETCHED_IN);
  gtk_frame_set_label_align (GTK_FRAME (pFrame), fXAlign, 0.5);
  gtk_widget_set_size_request(pFrame, w, h); 
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pFrame, x0, y0);
  gtk_widget_show(pFrame);		
    
  
  ///-----------------------------------------------------------------------///
  /// FRAME#7
  ///-----------------------------------------------------------------------///
  x0 = FORM6_FRAME7_LEFT;
  y0 = FORM6_FRAME7_TOP;
  w  = FORM6_FRAME7_WIDTH;
  h  = FORM6_FRAME7_HEIGHT;
  sprintf(strFrameName, "%s", "Motion Artifacts Removal Function");
  
  pFrame = gtk_frame_new (strFrameName);
  gtk_frame_set_shadow_type (GTK_FRAME (pFrame), GTK_SHADOW_ETCHED_IN);
  gtk_frame_set_label_align (GTK_FRAME (pFrame), fXAlign, 0.5);
  gtk_widget_set_size_request(pFrame, w, h); 
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pFrame, x0, y0);
  gtk_widget_show(pFrame);    

	return iRet;  
}

static JINT TimerInit()
{
	ViewDataForm6Type * pViewDataPtr = &ViewDataForm6;	

	g_timeout_add(1000, CallbackForm6Timer1, (gpointer)pViewDataPtr->pView);	
	
	return TRUE;
}

static JINT ListInit()
{	
	return TRUE;
}

static JINT ChartInit()
{


	return TRUE;
}

///------------------------------------------------------------------------------------///
/// Function area
///------------------------------------------------------------------------------------///
static JINT FuncOnShow()
{
	ViewDataForm6Type * pViewDataPtr = &ViewDataForm6;	
	gtk_widget_show(pViewDataPtr->pView);
	pViewDataPtr->bShow = TRUE;	
	return TRUE;
}

static JINT FuncOnHide()
{
	ViewDataForm6Type * pViewDataPtr = &ViewDataForm6;	
	gtk_widget_hide(pViewDataPtr->pView);
	pViewDataPtr->bShow = FALSE;	
	return TRUE;
}

static JINT FuncInit()
{
	ViewDataForm6Type * pViewDataPtr = &ViewDataForm6;	

 	///-----------------------------------------------------------------------///
	///  View init
	///-----------------------------------------------------------------------///
	pViewDataPtr->pView = gtk_fixed_new();
 	
 	///-----------------------------------------------------------------------///
	///  Label init
	///-----------------------------------------------------------------------///
	LabelInit();

 	///-----------------------------------------------------------------------///
	///  Entry init
	///-----------------------------------------------------------------------///
 	EntryInit();

 	///-----------------------------------------------------------------------///
	///  Button init
	///-----------------------------------------------------------------------///	
	ButtonInit();

	///-----------------------------------------------------------------------///
	///  Progress bar init
	///-----------------------------------------------------------------------///	
	FrameInit();
	
	///-----------------------------------------------------------------------///
	///  Progress bar init
	///-----------------------------------------------------------------------///	
	TimerInit();

	///-----------------------------------------------------------------------///
	///  Progress bar init
	///-----------------------------------------------------------------------///	
	ListInit();

	gtk_container_add(GTK_CONTAINER(AppPtr->pBox),   pViewDataPtr->pView);

  AppMainMenuSet(pViewDataPtr->pView);
	return TRUE;
}

///--------------------------------------------------------------------------------///
///   Form6 
///--------------------------------------------------------------------------------///
JView JVForm6 = 
{
	"Form6",										///< char text[32];							  ///< form name
	(void *)&ViewDataForm6,			///< void *pViewData;							///< #00 View Data	
	FuncOnShow,     						///< JINT (*OnShow)();   					///< #02 show view
	FuncOnHide,     						///< JINT (*OnHide();   					///< #03 hide view
	FuncInit,										///< JINT (*Init)();  				  	///< #05 Init event
};


