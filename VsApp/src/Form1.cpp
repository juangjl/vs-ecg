/**
 * @file Form1.cpp
 *
 *   Form1 function
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
#include "Form1.h"

static ViewDataForm1Type  	ViewDataForm1;

///------------------------------------------------------------------------------------///
/// Variable area
///------------------------------------------------------------------------------------///
static JView *pThis = &JVForm1;

///------------------------------------------------------------------------------------///
/// Function Area
///------------------------------------------------------------------------------------///
static void InvalidateForm1DrawAreaDS0()
{
	ViewDataForm1Type * pViewDataPtr = (ViewDataForm1Type * ) pThis->pViewData;		
}

void Form1LabelInfoUpdate(void)
{
	ViewDataForm1Type * pViewDataPtr = (ViewDataForm1Type * ) pThis->pViewData;		
	JINT iTimeMS  = 0;
	JINT idx      = 0;
	VscInfoType * pVscInfo   = NULL;
	static JINT iTimeMSPre = -1;

	char strValue[256];

	iTimeMS  = GlobalVar.iFileTimeMSNow;
	if(iTimeMS <= 0)
	{
		iTimeMS = 0;
	}
	idx = (iTimeMS / 1000);

	if(idx >= GlobalVar.iVscInfoCnt)
	{
		return;	
	}
	
	if(iTimeMSPre == iTimeMS)
	{
		return;
	}
	iTimeMSPre = iTimeMS;	
	pVscInfo = &GlobalVar.VscInfoArr[idx];
	///-----------------------------------------------------------------//
	/// 1. date
	///-----------------------------------------------------------------//	
	sprintf(strValue, "%04d/%02d/%02d", 
										pVscInfo->jtm.iYear, 
										pVscInfo->jtm.iMonth, 
										pVscInfo->jtm.iDay); 
	gtk_label_set_text(GTK_LABEL(pViewDataPtr->pLabelDate), strValue);

	///-----------------------------------------------------------------//
	/// 1. time
	///-----------------------------------------------------------------//	
	sprintf(strValue, "%02d:%02d:%02d", 
										pVscInfo->jtm.iHour, 
										pVscInfo->jtm.iMin, 
										pVscInfo->jtm.iSec); 
	gtk_label_set_text(GTK_LABEL(pViewDataPtr->pLabelTime), strValue);

	///-----------------------------------------------------------------//
	/// 2. fTemp
	///-----------------------------------------------------------------//	
	sprintf(strValue, "%0.3f", pVscInfo->fTemp);
	gtk_label_set_text(GTK_LABEL(pViewDataPtr->pLabelTemp), strValue);
	
	///-----------------------------------------------------------------//
	/// 3. fHRNow
	///-----------------------------------------------------------------//	
	sprintf(strValue, "%0.1f", pVscInfo->fHRNow);
	gtk_label_set_text(GTK_LABEL(pViewDataPtr->pLabelEcgHR), strValue);
		
	///-----------------------------------------------------------------//
	/// 4.  fLeadOff
	///-----------------------------------------------------------------//	
	sprintf(strValue, "%0.0f", pVscInfo->fLeadOff);
	gtk_label_set_text(GTK_LABEL(pViewDataPtr->pLabelEcgLeadOff), strValue);

	///-----------------------------------------------------------------//
	/// 5.  fGsenXNow
	/// 6.  fGsenYNow
	/// 7.  fGsenZNow
	///-----------------------------------------------------------------//	
	sprintf(strValue, "%0.0f", pVscInfo->fGsenXNow);
	gtk_label_set_text(GTK_LABEL(pViewDataPtr->pLabelGSenXNow), strValue);
	sprintf(strValue, "%0.0f", pVscInfo->fGsenYNow);
	gtk_label_set_text(GTK_LABEL(pViewDataPtr->pLabelGSenYNow), strValue);
	sprintf(strValue, "%0.0f", pVscInfo->fGsenZNow);
	gtk_label_set_text(GTK_LABEL(pViewDataPtr->pLabelGSenZNow), strValue);

	///-----------------------------------------------------------------//
	/// 8.  fBattSoc
	/// 9.  fBattTotalSec
	///-----------------------------------------------------------------//
	sprintf(strValue, "%0.0f", pVscInfo->fBattSoc);
	gtk_label_set_text(GTK_LABEL(pViewDataPtr->pLabelBattSoc), strValue);

	sprintf(strValue, "%0.0f", pVscInfo->fBattTotalSec);
	gtk_label_set_text(GTK_LABEL(pViewDataPtr->pLabelBattSec), strValue);


	///-----------------------------------------------------------------//
	/// 10.  fHrvSDNN
	/// 11.  fHrvNN50
	/// 12.  fHrvRMSSD
	/// 13.  fHrvRR
	///-----------------------------------------------------------------//
  sprintf(strValue, "%0.3f", pVscInfo->fHrvSDNN);
	gtk_label_set_text(GTK_LABEL(pViewDataPtr->pLabelHrvSDNN), strValue);

  sprintf(strValue, "%0.3f", pVscInfo->fHrvNN50);
	gtk_label_set_text(GTK_LABEL(pViewDataPtr->pLabelHrvNN50), strValue);

  sprintf(strValue, "%0.3f", pVscInfo->fHrvRMSSD);
	gtk_label_set_text(GTK_LABEL(pViewDataPtr->pLabelHrvRMSSD), strValue);

  sprintf(strValue, "%0.3f", pVscInfo->fHrvRR);
	gtk_label_set_text(GTK_LABEL(pViewDataPtr->pLabelHrvRR), strValue);

	///-----------------------------------------------------------------//
	/// 14.  fHrvVLF
	/// 15.  fHrvLF
	/// 16.  fHrvHF
	/// 17.  fHrvLFHF
	///-----------------------------------------------------------------//

	sprintf(strValue, "%0.0f", pVscInfo->fHrvVLF);
	gtk_label_set_text(GTK_LABEL(pViewDataPtr->pLabelHrvVLF), strValue);

  sprintf(strValue, "%0.0f", pVscInfo->fHrvLF);
	gtk_label_set_text(GTK_LABEL(pViewDataPtr->pLabelHrvLF), strValue);

  sprintf(strValue, "%0.0f", pVscInfo->fHrvHF);
	gtk_label_set_text(GTK_LABEL(pViewDataPtr->pLabelHrvHF), strValue);

  sprintf(strValue, "%0.3f", pVscInfo->fHrvLFHF);
	gtk_label_set_text(GTK_LABEL(pViewDataPtr->pLabelHrvLFHF), strValue);

	///-----------------------------------------------------------------//
	/// 18.  fHrvTP
	/// 19.  fHrvLFTP
	/// 20.  fHrvHFTP
	///-----------------------------------------------------------------//
	sprintf(strValue, "%0.0f", pVscInfo->fHrvTP);
	gtk_label_set_text(GTK_LABEL(pViewDataPtr->pLabelHrvTP), strValue);

  sprintf(strValue, "%0.0f", pVscInfo->fHrvLFTP);
	gtk_label_set_text(GTK_LABEL(pViewDataPtr->pLabelHrvLFTP), strValue);

  sprintf(strValue, "%0.0f", pVscInfo->fHrvHFTP);
	gtk_label_set_text(GTK_LABEL(pViewDataPtr->pLabelHrvHFTP), strValue);

	return;
}



///------------------------------------------------------------------------------------///
/// Callback area
///------------------------------------------------------------------------------------///
static void CallbackForm1BtnBrowseClicked(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	ViewDataForm1Type * pViewDataPtr = (ViewDataForm1Type * ) pThis->pViewData;
	GtkWidget *dialog = NULL;
	GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
	JINT  iRet = 0;
  char *pFileName = NULL;
	JDataSet *pDataSet = &GlobalVar.dataSet[DATASET_LOAD_ECG_DS0];

	JINT iTimeMS = 0;
	char strTime[256];
	char strFolderName[256];
	char strInfoFileName[256];
	char msg[256];
	
	dialog = gtk_file_chooser_dialog_new ("Open File",
	                                      GTK_WINDOW(AppPtr->pWindow),
	                                      action,
	                                      "_Cancel",
	                                      GTK_RESPONSE_CANCEL,
	                                      "_Open",
	                                      GTK_RESPONSE_ACCEPT,
	                                      NULL);

	iRet = gtk_dialog_run (GTK_DIALOG (dialog));
	if(iRet == GTK_RESPONSE_ACCEPT)
  {
    GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
    pFileName = gtk_file_chooser_get_filename (chooser);
	  gtk_entry_set_text(GTK_ENTRY(pViewDataPtr->pEntryFileName), pFileName);    

		
		GlobalVar.bChartEcgRun = FALSE;
	
		///-----------------------------------------------------------------------------///
		/// Draw Chart
		///-----------------------------------------------------------------------------///	
		FuncEcgFileDataLoad(pFileName);
		iTimeMS = 0;

	  ///-----------------------------------------------------------------------------///
		/// File Folder Name get
		///-----------------------------------------------------------------------------///
		UtilFileFolderGet(pFileName, strFolderName);
		sprintf(strInfoFileName,  "%s/info.csv", strFolderName);				
		FuncVscInfoDataLoad(strInfoFileName);

		///-----------------------------------------------------------------------------///
		/// update the now time string
		///-----------------------------------------------------------------------------///	
		UtilTimeStrGet(iTimeMS, strTime);
		gtk_entry_set_text(GTK_ENTRY(pViewDataPtr->pEntryChartEcgTime), strTime);  
	  
		///-----------------------------------------------------------------------------///
		/// update the total time string
		///-----------------------------------------------------------------------------///	
		UtilTimeStrGet(GlobalVar.iFileTimeMSTotal, strTime);
		gtk_entry_set_text(GTK_ENTRY(	pViewDataPtr->pEntryChartEcgTimeTotal), strTime);  	
    g_free (pFileName);   
  }

	gtk_widget_destroy (dialog);
}

static void CallbackForm1BtnChartEcgReverseClicked(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	GlobalVar.bChartEcgRun 		 = TRUE;	
	GlobalVar.bChartEcgReverse = TRUE;	
	DBG_PRINTF("[Form1][BTN] CHART Reverse\r\n");
}

static void CallbackForm1BtnChartEcgStopClicked(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	GlobalVar.bChartEcgRun 		 = FALSE;	
	GlobalVar.bChartEcgReverse = FALSE;	
	DBG_PRINTF("[FORM1][BTN] CHART STOP\r\n");
}

static void CallbackForm1BtnChartEcgPlayClicked(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	GlobalVar.bChartEcgRun 		 = TRUE;	
	GlobalVar.bChartEcgReverse = FALSE;	
	DBG_PRINTF("[FORM1][BTN] CHART RUN\r\n");
}

static void CallbackForm1EntryFileNameActive(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	ViewDataForm1Type * pViewDataPtr = (ViewDataForm1Type * ) pThis->pViewData;
	printf("entry activate\r\n");
	/// let the widget not focused
	gtk_widget_grab_focus(pViewDataPtr->pBtnBrowse);
}

static void CallbackForm1ChartEcgTimeActive(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	ViewDataForm1Type * pViewDataPtr = (ViewDataForm1Type * ) pThis->pViewData;
	
	char *pStrTime = NULL;
	JINT iTimeMS = 0;
	char strTime2[256];
	JINT iMS = 0;

	pStrTime = (char *) gtk_entry_get_text(GTK_ENTRY(pViewDataPtr->pEntryChartEcgTime));    
	UtilTimeMsGet(pStrTime, &iTimeMS);

	iTimeMS = iTimeMS - (iTimeMS %2);
	iMS = iTimeMS % 1000;
	if(iMS > 0)
	{
		UtilTimeStrGet(iTimeMS, strTime2);
		gtk_entry_set_text(GTK_ENTRY(pViewDataPtr->pEntryChartEcgTime), strTime2);    
	}
	
	/// Set back to file time ms now
	if((iTimeMS > 0) &&(iTimeMS < GlobalVar.iFileTimeMSTotal))
	{
		GlobalVar.iFileTimeMSNow = iTimeMS;
	}
	gtk_widget_queue_draw(widget);
}

gint CallbackForm1Timer1 (gpointer data)
{    
	ViewDataForm1Type * pViewDataPtr = (ViewDataForm1Type * ) pThis->pViewData;
	GtkWidget *  pProgressBar = pViewDataPtr->pProgressBar;

	return TRUE;
}

gint CallbackForm1Timer2 (gpointer data)
{
	ViewDataForm1Type * pViewDataPtr = (ViewDataForm1Type * ) pThis->pViewData;

	char strTime[256];
	JINT iTimeMS = 0;
	JDataSet *pDataSet = &GlobalVar.dataSet[DATASET_LOAD_ECG_DS0];
	JINT iSpeed = 1;
	JINT iMS = 100;

	if(GlobalVar.iVscInfoCnt > 0)
	{
		if(pViewDataPtr->bShow == TRUE)
		{
			Form1LabelInfoUpdate();
		}
	}

	if(GlobalVar.bChartEcgRun == FALSE)
	{
		return TRUE;
	}	

	iTimeMS = GlobalVar.iFileTimeMSNow;
	
	///-----------------------------------------------------------------------------------///
	/// Delta Speed
	///-----------------------------------------------------------------------------------///	
	iSpeed = gtk_combo_box_get_active((GtkComboBox*)pViewDataPtr->pComboBoxSpeed);
	if(iSpeed == 0)
	{
		iMS = 50;
	}
	else if(iSpeed == 1)
	{
		iMS = 100;
	}
	else if(iSpeed == 2)
	{
		iMS = 200;
	}
	else if(iSpeed == 3)
	{
		iMS = 500;
	}
	else if(iSpeed == 4)
	{
		iMS = 1000;
	}
		
	///-----------------------------------------------------------------------------------///
	/// Set back the time string
	///-----------------------------------------------------------------------------------///
	UtilTimeStrGet(iTimeMS, strTime);
	gtk_entry_set_text(GTK_ENTRY(pViewDataPtr->pEntryChartEcgTime), strTime);
	if(	GlobalVar.bChartEcgReverse == FALSE)
	{
		if(GlobalVar.iFileTimeMSNow < GlobalVar.iFileTimeMSTotal - 6000)
		{
			GlobalVar.iFileTimeMSNow = GlobalVar.iFileTimeMSNow + iMS;
		}
		else
		{
			GlobalVar.iFileTimeMSNow =  GlobalVar.iFileTimeMSTotal - 6000;
		}
	}
	else
	{
		if(GlobalVar.iFileTimeMSNow - iMS > 0)
		{
			GlobalVar.iFileTimeMSNow = GlobalVar.iFileTimeMSNow - iMS;
		}
		else
		{
			GlobalVar.iFileTimeMSNow =  0;
		}
	}

	return TRUE;
}

gboolean CallbackForm1DrawArea0 (GtkWidget *widget, cairo_t *cr, gpointer data)
{	
	char msg[256];
	JINT iWidth  = 0;
	JINT iHeight = 0;	
	JDOUBLE x[10];
	JDOUBLE y[10];	

	ViewDataForm1Type * pViewDataPtr = (ViewDataForm1Type * ) pThis->pViewData;
	
	JDraw *pDC         = NULL; 
	JChart *pChart     = &pViewDataPtr->ChartDS0;
	JDataSet *pDataSet = &GlobalVar.dataSet[DATASET_LOAD_ECG_DS0];

	JINT iTimeMS = 0;

	char strStart[64];
	char strCenter[64];
	char strEnd[64];
	static JINT iTimeMSPre = -1;
	JBOOL bRet = FALSE;
		
	JINT i = 0 ;
	JFLOAT fXVal = 0;
	JINT iXPos = 0;
	JINT iYPos = 0;
	JDWORD dwColor = 0;
	char strAtrAbbrev[32];
	
	JFLOAT fTimeSec = -1;

	static JBOOL bDrawing = FALSE;

	if(bDrawing == TRUE)
	{
		return FALSE;
	}
	bDrawing = TRUE;

	if(GlobalVar.bChartEcgRun == FALSE)
	{
		iTimeMSPre = -1;
		fTimeSec   = -1;
	}	
				
	iWidth  = gtk_widget_get_allocated_width(widget);
	iHeight = gtk_widget_get_allocated_height(widget);
	
	pDC  = new JDraw(cr); 
	
	iTimeMS = GlobalVar.iFileTimeMSNow;
	if(iTimeMSPre != iTimeMS)
	{
		bRet = FuncEcgFileDataGet(iTimeMS, pDataSet);		
		iTimeMSPre = iTimeMS;
	}

	JChartDataSet(pChart, pDataSet);

	JChartDCSet(pChart, pDC);
	JChartGridDraw(pChart);
	JChartLineEcgDraw(pChart);

	/// draw Y label
	JChartLabelYDraw(pChart);		

	/// draw X label
	UtilTimeStrGet(iTimeMS, strStart);
	UtilTimeStrGet(iTimeMS + 3000, strCenter);	
	UtilTimeStrGet(iTimeMS + 6000, strEnd);		
	JChartLabelXDrawEx(pChart, strStart, strCenter, strEnd);

	
	gtk_widget_queue_draw(widget);

	delete(pDC);

	UtilMsSleep(20);
	bDrawing = FALSE;

	return  TRUE;
}	

///------------------------------------------------------------------------------------///
/// Form1 Function
///------------------------------------------------------------------------------------///
static JINT LabelInit(void)
{
	ViewDataForm1Type * pViewDataPtr = &ViewDataForm1;
	JINT iRet = TRUE;
	GtkWidget *pLabel 	= NULL;

	JINT x0 = 0;
	JINT y0 = 0;	
	JINT w  = 200;
	JINT h  = 30;

	JINT iCol0 	= FORM1_FRAME3_LEFT + 20;
	JINT iCol1 	= FORM1_FRAME3_LEFT + 300;
	JINT iCol2	= FORM1_FRAME3_LEFT + 580;
	JINT iCol3 	= FORM1_FRAME3_LEFT + 860;

	JINT iRow0  = FORM1_FRAME3_TOP  + FORM1_FRAME3_ROW ;
	JINT iRow1  = FORM1_FRAME3_TOP  + FORM1_FRAME3_ROW * 2;
	JINT iRow2  = FORM1_FRAME3_TOP  + FORM1_FRAME3_ROW * 3;
	JINT iRow3  = FORM1_FRAME3_TOP  + FORM1_FRAME3_ROW * 4;
	JINT iRow4  = FORM1_FRAME3_TOP  + FORM1_FRAME3_ROW * 5;
	JINT iRow5  = FORM1_FRAME3_TOP  + FORM1_FRAME3_ROW * 6;		
	JINT iRow6  = FORM1_FRAME3_TOP  + FORM1_FRAME3_ROW * 7;
	JINT iRow7  = FORM1_FRAME3_TOP  + FORM1_FRAME3_ROW * 8;
	JINT iRow8  = FORM1_FRAME3_TOP  + FORM1_FRAME3_ROW * 9;

	GtkStyleContext * pContext = NULL;

	///-----------------------------------------------------------------------///
	/// Label main
	///-----------------------------------------------------------------------///
	x0 = FORM1_FRAME0_LEFT + FORM1_FRAME0_XGAP;
	y0 = FORM1_FRAME0_TOP  + FORM1_FRAME0_YGAP;  	
	pLabel = gtk_label_new_with_mnemonic("Select a file to load");
	gtk_label_set_xalign(GTK_LABEL(pLabel), 0.00);
  gtk_widget_set_name(pLabel, "form1_label_main");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pLabel, x0, y0);
	gtk_widget_set_size_request(pLabel, w, h); 
  gtk_widget_show(pLabel);
	  
 	///-----------------------------------------------------------------------///
	/// Label: TIME NOW
	///-----------------------------------------------------------------------///
	x0 = FORM1_FRAME1_LEFT + FORM1_FRAME1_XGAP;
	y0 = FORM1_FRAME1_TOP  + FORM1_FRAME1_ROW;  
	pLabel =  gtk_label_new_with_mnemonic("Time:");	
	pContext = gtk_widget_get_style_context(pLabel);	
	gtk_style_context_add_class(pContext, "");  	
  gtk_widget_set_name(pLabel, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pLabel, x0, y0);
  gtk_widget_show(pLabel);

 	///-----------------------------------------------------------------------///
	/// Label: TIME NOW
	///-----------------------------------------------------------------------///
	x0 = FORM1_FRAME1_LEFT + FORM1_FRAME1_XGAP + 220;
	y0 = FORM1_FRAME1_TOP  + FORM1_FRAME1_ROW + 10;  
	pLabel =  gtk_label_new_with_mnemonic("/");	
	pContext = gtk_widget_get_style_context(pLabel);	
	gtk_style_context_add_class(pContext, "label_time");  	
  gtk_widget_set_name(pLabel, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pLabel, x0, y0);
  gtk_widget_show(pLabel);


	///-----------------------------------------------------------------------///
	/// Label: DATE
	///-----------------------------------------------------------------------///
	x0 = iCol0;
	y0 = iRow0;  
	w  = 120;
	h  = 30;	
		
	pLabel = gtk_label_new_with_mnemonic("DATE");
	pContext = gtk_widget_get_style_context(pLabel);	
	gtk_style_context_add_class(pContext, CSS_CLASS_LABEL_TITLE);  	
  gtk_widget_set_name(pLabel, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pLabel, x0, y0);
	gtk_widget_set_size_request(pLabel, w, h);  
  gtk_widget_show(pLabel);

 	///-----------------------------------------------------------------------///
	/// Label: DATE
	///-----------------------------------------------------------------------///
	x0 = x0 + w;
	y0 = y0;  
	w  = 120;
	h  = 30;	
		
	pLabel = gtk_label_new_with_mnemonic("");
	pContext = gtk_widget_get_style_context(pLabel);	
	gtk_style_context_add_class(pContext, CSS_CLASS_LABEL_VALUE);  	
  gtk_widget_set_name(pLabel, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pLabel, x0, y0);
	gtk_widget_set_size_request(pLabel, w, h);  
  gtk_widget_show(pLabel);

  pViewDataPtr->pLabelDate = pLabel;


	///-----------------------------------------------------------------------///
	/// Label: TIME
	///-----------------------------------------------------------------------///
	x0 = iCol1;
	y0 = iRow0;  
	w  = 120;
	h  = 30;	
		
	pLabel = gtk_label_new_with_mnemonic("TIME");
	pContext = gtk_widget_get_style_context(pLabel);	
	gtk_style_context_add_class(pContext, CSS_CLASS_LABEL_TITLE);  	
  gtk_widget_set_name(pLabel, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pLabel, x0, y0);
	gtk_widget_set_size_request(pLabel, w, h);  
  gtk_widget_show(pLabel);

 	///-----------------------------------------------------------------------///
	/// Label: TIME
	///-----------------------------------------------------------------------///
	x0 = x0 + w;
	y0 = y0;  
	w  = 120;
	h  = 30;	
		
	pLabel = gtk_label_new_with_mnemonic("");
	pContext = gtk_widget_get_style_context(pLabel);	
	gtk_style_context_add_class(pContext, CSS_CLASS_LABEL_VALUE);  	
  gtk_widget_set_name(pLabel, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pLabel, x0, y0);
	gtk_widget_set_size_request(pLabel, w, h);  
  gtk_widget_show(pLabel);

  pViewDataPtr->pLabelTime = pLabel;

	///-----------------------------------------------------------------------///
	/// Label: ECG-HR
	///-----------------------------------------------------------------------///
	x0 = iCol0;
	y0 = iRow1;  
	w  = 120;
	h  = 30;	
		
	pLabel = gtk_label_new_with_mnemonic("HR");
	pContext = gtk_widget_get_style_context(pLabel);	
	gtk_style_context_add_class(pContext, CSS_CLASS_LABEL_TITLE);  	
  gtk_widget_set_name(pLabel, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pLabel, x0, y0);
	gtk_widget_set_size_request(pLabel, w, h);  
  gtk_widget_show(pLabel);

 	///-----------------------------------------------------------------------///
	/// Label: ECG-HR
	///-----------------------------------------------------------------------///
	x0 = x0 + w;
	y0 = y0;  
	w  = 120;
	h  = 30;	
		
	pLabel = gtk_label_new_with_mnemonic("");
	pContext = gtk_widget_get_style_context(pLabel);	
	gtk_style_context_add_class(pContext, CSS_CLASS_LABEL_VALUE);  	
  gtk_widget_set_name(pLabel, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pLabel, x0, y0);
	gtk_widget_set_size_request(pLabel, w, h);  
  gtk_widget_show(pLabel);  

  pViewDataPtr->pLabelEcgHR = pLabel;

	///-----------------------------------------------------------------------///
	/// Label: TEMP
	///-----------------------------------------------------------------------///
	x0 = iCol1;
	y0 = iRow1;  
	w  = 120;
	h  = 30;	
		
	pLabel = gtk_label_new_with_mnemonic("TEMP");
	pContext = gtk_widget_get_style_context(pLabel);	
	gtk_style_context_add_class(pContext, CSS_CLASS_LABEL_TITLE);  	
  gtk_widget_set_name(pLabel, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pLabel, x0, y0);
	gtk_widget_set_size_request(pLabel, w, h);  
  gtk_widget_show(pLabel);

 	///-----------------------------------------------------------------------///
	/// Label: TEMP
	///-----------------------------------------------------------------------///
	x0 = x0 + w;
	y0 = y0;  
	w  = 120;
	h  = 30;	
		
	pLabel = gtk_label_new_with_mnemonic("");
	pContext = gtk_widget_get_style_context(pLabel);	
	gtk_style_context_add_class(pContext, CSS_CLASS_LABEL_VALUE);  	
  gtk_widget_set_name(pLabel, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pLabel, x0, y0);
	gtk_widget_set_size_request(pLabel, w, h);  
  gtk_widget_show(pLabel);

  pViewDataPtr->pLabelTemp = pLabel;

	///-----------------------------------------------------------------------///
	/// Label: ECG-LEAD-OFF
	///-----------------------------------------------------------------------///
	x0 = iCol2;
	y0 = iRow1;  
	w  = 120;
	h  = 30;	
		
	pLabel = gtk_label_new_with_mnemonic("LEAD-OFF");
	pContext = gtk_widget_get_style_context(pLabel);	
	gtk_style_context_add_class(pContext, CSS_CLASS_LABEL_TITLE);  	
  gtk_widget_set_name(pLabel, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pLabel, x0, y0);
	gtk_widget_set_size_request(pLabel, w, h);  
  gtk_widget_show(pLabel);

	///-----------------------------------------------------------------------///
	/// Label: ECG-LEAD-OFF
	///-----------------------------------------------------------------------///
	x0 = x0 + w;
	y0 = y0;  
	w  = 120;
	h  = 30;	
		
	pLabel = gtk_label_new_with_mnemonic("");
	pContext = gtk_widget_get_style_context(pLabel);	
	gtk_style_context_add_class(pContext, CSS_CLASS_LABEL_VALUE);  	
  gtk_widget_set_name(pLabel, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pLabel, x0, y0);
	gtk_widget_set_size_request(pLabel, w, h);  
  gtk_widget_show(pLabel);    

	pViewDataPtr->pLabelEcgLeadOff = pLabel;


	///-----------------------------------------------------------------------///
	/// Label: GSEN-X
	///-----------------------------------------------------------------------///
	x0 = iCol0;
	y0 = iRow2;  
	w  = 120;
	h  = 30;	
		
	pLabel = gtk_label_new_with_mnemonic("GSEN-X");
	pContext = gtk_widget_get_style_context(pLabel);	
	gtk_style_context_add_class(pContext, CSS_CLASS_LABEL_TITLE);  	
  gtk_widget_set_name(pLabel, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pLabel, x0, y0);
	gtk_widget_set_size_request(pLabel, w, h);  
  gtk_widget_show(pLabel);

	///-----------------------------------------------------------------------///
	/// Label: GSEN-X
	///-----------------------------------------------------------------------///
	x0 = x0 + w;
	y0 = y0;  
	w  = 120;
	h  = 30;	
		
	pLabel = gtk_label_new_with_mnemonic("");
	pContext = gtk_widget_get_style_context(pLabel);	
	gtk_style_context_add_class(pContext, CSS_CLASS_LABEL_VALUE);  	
  gtk_widget_set_name(pLabel, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pLabel, x0, y0);
	gtk_widget_set_size_request(pLabel, w, h);  
  gtk_widget_show(pLabel);   
  pViewDataPtr->pLabelGSenXNow = pLabel;

	///-----------------------------------------------------------------------///
	/// Label: GSEN-Y
	///-----------------------------------------------------------------------///
	x0 = iCol1;
	y0 = iRow2;  
	w  = 120;
	h  = 30;	
		
	pLabel = gtk_label_new_with_mnemonic("GSEN-Y");
	pContext = gtk_widget_get_style_context(pLabel);	
	gtk_style_context_add_class(pContext, CSS_CLASS_LABEL_TITLE);  	
  gtk_widget_set_name(pLabel, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pLabel, x0, y0);
	gtk_widget_set_size_request(pLabel, w, h);  
  gtk_widget_show(pLabel);

	///-----------------------------------------------------------------------///
	/// Label: GSEN-Y
	///-----------------------------------------------------------------------///
	x0 = x0 + w;
	y0 = y0;  
	w  = 120;
	h  = 30;	
		
	pLabel = gtk_label_new_with_mnemonic("");
	pContext = gtk_widget_get_style_context(pLabel);	
	gtk_style_context_add_class(pContext, CSS_CLASS_LABEL_VALUE);  	
  gtk_widget_set_name(pLabel, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pLabel, x0, y0);
	gtk_widget_set_size_request(pLabel, w, h);  
  gtk_widget_show(pLabel);     

	pViewDataPtr->pLabelGSenYNow = pLabel; 

	///-----------------------------------------------------------------------///
	/// Label: GSEN-Z
	///-----------------------------------------------------------------------///
	x0 = iCol2;
	y0 = iRow2;  
	w  = 120;
	h  = 30;	
		
	pLabel = gtk_label_new_with_mnemonic("GSEN-Z");
	pContext = gtk_widget_get_style_context(pLabel);	
	gtk_style_context_add_class(pContext, CSS_CLASS_LABEL_TITLE);  	
  gtk_widget_set_name(pLabel, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pLabel, x0, y0);
	gtk_widget_set_size_request(pLabel, w, h);  
  gtk_widget_show(pLabel);

	///-----------------------------------------------------------------------///
	/// Label: GSEN-Z
	///-----------------------------------------------------------------------///
	x0 = x0 + w;
	y0 = y0;  
	w  = 120;
	h  = 30;	
		
	pLabel = gtk_label_new_with_mnemonic("");
	pContext = gtk_widget_get_style_context(pLabel);	
	gtk_style_context_add_class(pContext, CSS_CLASS_LABEL_VALUE);  	
  gtk_widget_set_name(pLabel, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pLabel, x0, y0);
	gtk_widget_set_size_request(pLabel, w, h);  
  gtk_widget_show(pLabel);    

	pViewDataPtr->pLabelGSenZNow = pLabel;	
	  
	///-----------------------------------------------------------------------///
	/// Label: BATT-SOC
	///-----------------------------------------------------------------------///
	x0 = iCol0;
	y0 = iRow3;  
	w  = 120;
	h  = 30;	
		
	pLabel = gtk_label_new_with_mnemonic("BATT-SOC");
	pContext = gtk_widget_get_style_context(pLabel);	
	gtk_style_context_add_class(pContext, CSS_CLASS_LABEL_TITLE);  	
  gtk_widget_set_name(pLabel, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pLabel, x0, y0);
	gtk_widget_set_size_request(pLabel, w, h);  
  gtk_widget_show(pLabel);

	///-----------------------------------------------------------------------///
	/// Label: BATT-SOC
	///-----------------------------------------------------------------------///
	x0 = x0 + w;
	y0 = y0;  
	w  = 120;
	h  = 30;	
		
	pLabel = gtk_label_new_with_mnemonic("");
	pContext = gtk_widget_get_style_context(pLabel);	
	gtk_style_context_add_class(pContext, CSS_CLASS_LABEL_VALUE);  	
  gtk_widget_set_name(pLabel, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pLabel, x0, y0);
	gtk_widget_set_size_request(pLabel, w, h);  
  gtk_widget_show(pLabel);     

	pViewDataPtr->pLabelBattSoc = pLabel;

	///-----------------------------------------------------------------------///
	/// Label: BATT-TTL-SEC
	///-----------------------------------------------------------------------///
	x0 = iCol1;
	y0 = iRow3;  
	w  = 120;
	h  = 30;	
		
	pLabel = gtk_label_new_with_mnemonic("BAT-SEC");
	pContext = gtk_widget_get_style_context(pLabel);	
	gtk_style_context_add_class(pContext, CSS_CLASS_LABEL_TITLE);  	
  gtk_widget_set_name(pLabel, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pLabel, x0, y0);
	gtk_widget_set_size_request(pLabel, w, h);  
  gtk_widget_show(pLabel);

	///-----------------------------------------------------------------------///
	/// Label: BATT-SEC
	///-----------------------------------------------------------------------///
	x0 = x0 + w;
	y0 = y0;  
	w  = 120;
	h  = 30;	
		
	pLabel = gtk_label_new_with_mnemonic("");
	pContext = gtk_widget_get_style_context(pLabel);	
	gtk_style_context_add_class(pContext, CSS_CLASS_LABEL_VALUE);  	
  gtk_widget_set_name(pLabel, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pLabel, x0, y0);
	gtk_widget_set_size_request(pLabel, w, h);  
  gtk_widget_show(pLabel);    

	pViewDataPtr->pLabelBattSec = pLabel;

	///-----------------------------------------------------------------------///
	/// Label: HRV-SDNN
	///-----------------------------------------------------------------------///
	x0 = iCol0;
	y0 = iRow4;  
	w  = 120;
	h  = 30;	
		
	pLabel = gtk_label_new_with_mnemonic("HRV-SDNN");
	pContext = gtk_widget_get_style_context(pLabel);	
	gtk_style_context_add_class(pContext, CSS_CLASS_LABEL_TITLE);  	
  gtk_widget_set_name(pLabel, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pLabel, x0, y0);
	gtk_widget_set_size_request(pLabel, w, h);  
  gtk_widget_show(pLabel);

	///-----------------------------------------------------------------------///
	/// Label: HRV-SDNN
	///-----------------------------------------------------------------------///
	x0 = x0 + w;
	y0 = y0;  
	w  = 120;
	h  = 30;	
		
	pLabel = gtk_label_new_with_mnemonic("");
	pContext = gtk_widget_get_style_context(pLabel);	
	gtk_style_context_add_class(pContext, CSS_CLASS_LABEL_VALUE);  	
  gtk_widget_set_name(pLabel, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pLabel, x0, y0);
	gtk_widget_set_size_request(pLabel, w, h);  
  gtk_widget_show(pLabel);    

	pViewDataPtr->pLabelHrvSDNN = pLabel;
 

	///-----------------------------------------------------------------------///
	/// Label: HRV-NN50
	///-----------------------------------------------------------------------///
	x0 = iCol1;
	y0 = iRow4;  
	w  = 120;
	h  = 30;	
		
	pLabel = gtk_label_new_with_mnemonic("HRV-NN50");
	pContext = gtk_widget_get_style_context(pLabel);	
	gtk_style_context_add_class(pContext, CSS_CLASS_LABEL_TITLE);  	
  gtk_widget_set_name(pLabel, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pLabel, x0, y0);
	gtk_widget_set_size_request(pLabel, w, h);  
  gtk_widget_show(pLabel);

	///-----------------------------------------------------------------------///
	/// Label: HRV-NN50
	///-----------------------------------------------------------------------///
	x0 = x0 + w;
	y0 = y0;  
	w  = 120;
	h  = 30;	
		
	pLabel = gtk_label_new_with_mnemonic("");
	pContext = gtk_widget_get_style_context(pLabel);	
	gtk_style_context_add_class(pContext, CSS_CLASS_LABEL_VALUE);  	
  gtk_widget_set_name(pLabel, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pLabel, x0, y0);
	gtk_widget_set_size_request(pLabel, w, h);  
  gtk_widget_show(pLabel);   
	
	pViewDataPtr->pLabelHrvNN50 = pLabel;

	///-----------------------------------------------------------------------///
	/// Label: HRV-RMSSD
	///-----------------------------------------------------------------------///
	x0 = iCol2;
	y0 = iRow4;  
	w  = 120;
	h  = 30;	
		
	pLabel = gtk_label_new_with_mnemonic("HRV-RMSSD");
	pContext = gtk_widget_get_style_context(pLabel);	
	gtk_style_context_add_class(pContext, CSS_CLASS_LABEL_TITLE);  	
  gtk_widget_set_name(pLabel, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pLabel, x0, y0);
	gtk_widget_set_size_request(pLabel, w, h);  
  gtk_widget_show(pLabel);

	///-----------------------------------------------------------------------///
	/// Label: HRV-RMSSD
	///-----------------------------------------------------------------------///
	x0 = x0 + w;
	y0 = y0;  
	w  = 120;
	h  = 30;	
		
	pLabel = gtk_label_new_with_mnemonic("");
	pContext = gtk_widget_get_style_context(pLabel);	
	gtk_style_context_add_class(pContext, CSS_CLASS_LABEL_VALUE);  	
  gtk_widget_set_name(pLabel, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pLabel, x0, y0);
	gtk_widget_set_size_request(pLabel, w, h);  
  gtk_widget_show(pLabel);   
	
	pViewDataPtr->pLabelHrvRMSSD = pLabel;

	///-----------------------------------------------------------------------///
	/// Label: HRV-RR
	///-----------------------------------------------------------------------///
	x0 = iCol0;
	y0 = iRow5;  
	w  = 120;
	h  = 30;	
		
	pLabel = gtk_label_new_with_mnemonic("HRV-RR");
	pContext = gtk_widget_get_style_context(pLabel);	
	gtk_style_context_add_class(pContext, CSS_CLASS_LABEL_TITLE);  	
  gtk_widget_set_name(pLabel, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pLabel, x0, y0);
	gtk_widget_set_size_request(pLabel, w, h);  
  gtk_widget_show(pLabel);

	///-----------------------------------------------------------------------///
	/// Label: HRV-RR
	///-----------------------------------------------------------------------///
	x0 = x0 + w;
	y0 = y0;  
	w  = 120;
	h  = 30;	
		
	pLabel = gtk_label_new_with_mnemonic("");
	pContext = gtk_widget_get_style_context(pLabel);	
	gtk_style_context_add_class(pContext, CSS_CLASS_LABEL_VALUE);  	
  gtk_widget_set_name(pLabel, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pLabel, x0, y0);
	gtk_widget_set_size_request(pLabel, w, h);  
  gtk_widget_show(pLabel);      

	
	pViewDataPtr->pLabelHrvRR = pLabel;	
	

	///-----------------------------------------------------------------------///
	/// Label: HRV-VLF
	///-----------------------------------------------------------------------///
	x0 = iCol0;
	y0 = iRow6;  
	w  = 120;
	h  = 30;	
		
	pLabel = gtk_label_new_with_mnemonic("HRV-VLF");
	pContext = gtk_widget_get_style_context(pLabel);	
	gtk_style_context_add_class(pContext, CSS_CLASS_LABEL_TITLE);  	
  gtk_widget_set_name(pLabel, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pLabel, x0, y0);
	gtk_widget_set_size_request(pLabel, w, h);  
  gtk_widget_show(pLabel);

	///-----------------------------------------------------------------------///
	/// Label: HRV-VLF
	///-----------------------------------------------------------------------///
	x0 = x0 + w;
	y0 = y0;  
	w  = 120;
	h  = 30;	
		
	pLabel = gtk_label_new_with_mnemonic("");
	pContext = gtk_widget_get_style_context(pLabel);	
	gtk_style_context_add_class(pContext, CSS_CLASS_LABEL_VALUE);  	
  gtk_widget_set_name(pLabel, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pLabel, x0, y0);
	gtk_widget_set_size_request(pLabel, w, h);  
  gtk_widget_show(pLabel);     

  pViewDataPtr->pLabelHrvVLF = pLabel;		


	///-----------------------------------------------------------------------///
	/// Label: HRV-LF
	///-----------------------------------------------------------------------///
	x0 = iCol1;
	y0 = iRow6;  
	w  = 120;
	h  = 30;	
		
	pLabel = gtk_label_new_with_mnemonic("HRV-LF");
	pContext = gtk_widget_get_style_context(pLabel);	
	gtk_style_context_add_class(pContext, CSS_CLASS_LABEL_TITLE);  	
  gtk_widget_set_name(pLabel, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pLabel, x0, y0);
	gtk_widget_set_size_request(pLabel, w, h);  
  gtk_widget_show(pLabel);

	///-----------------------------------------------------------------------///
	/// Label: HRV-LF
	///-----------------------------------------------------------------------///
	x0 = x0 + w;
	y0 = y0;  
	w  = 120;
	h  = 30;	
		
	pLabel = gtk_label_new_with_mnemonic("");
	pContext = gtk_widget_get_style_context(pLabel);	
	gtk_style_context_add_class(pContext, CSS_CLASS_LABEL_VALUE);  	
  gtk_widget_set_name(pLabel, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pLabel, x0, y0);
	gtk_widget_set_size_request(pLabel, w, h);  
  gtk_widget_show(pLabel);    

  pViewDataPtr->pLabelHrvLF = pLabel;	 

	///-----------------------------------------------------------------------///
	/// Label: HRV-HF
	///-----------------------------------------------------------------------///
	x0 = iCol2;
	y0 = iRow6;  
	w  = 120;
	h  = 30;	
		
	pLabel = gtk_label_new_with_mnemonic("HRV-HF");
	pContext = gtk_widget_get_style_context(pLabel);	
	gtk_style_context_add_class(pContext, CSS_CLASS_LABEL_TITLE);  	
  gtk_widget_set_name(pLabel, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pLabel, x0, y0);
	gtk_widget_set_size_request(pLabel, w, h);  
  gtk_widget_show(pLabel);

	///-----------------------------------------------------------------------///
	/// Label: HRV-HF
	///-----------------------------------------------------------------------///
	x0 = x0 + w;
	y0 = y0;  
	w  = 120;
	h  = 30;	
		
	pLabel = gtk_label_new_with_mnemonic("");
	pContext = gtk_widget_get_style_context(pLabel);	
	gtk_style_context_add_class(pContext, CSS_CLASS_LABEL_VALUE);  	
  gtk_widget_set_name(pLabel, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pLabel, x0, y0);
	gtk_widget_set_size_request(pLabel, w, h);  
  gtk_widget_show(pLabel);  
  
  pViewDataPtr->pLabelHrvHF = pLabel;	 

	///-----------------------------------------------------------------------///
	/// Label: HRV-LFHF	
	///-----------------------------------------------------------------------///
	x0 = iCol0;
	y0 = iRow7;  
	w  = 120;
	h  = 30;	
		
	pLabel = gtk_label_new_with_mnemonic("HRV-LFHF");
	pContext = gtk_widget_get_style_context(pLabel);	
	gtk_style_context_add_class(pContext, CSS_CLASS_LABEL_TITLE);  	
  gtk_widget_set_name(pLabel, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pLabel, x0, y0);
	gtk_widget_set_size_request(pLabel, w, h);  
  gtk_widget_show(pLabel);

	///-----------------------------------------------------------------------///
	/// Label: HRV-LFHF	
	///-----------------------------------------------------------------------///
	x0 = x0 + w;
	y0 = y0;  
	w  = 120;
	h  = 30;	
		
	pLabel = gtk_label_new_with_mnemonic("");
	pContext = gtk_widget_get_style_context(pLabel);	
	gtk_style_context_add_class(pContext, CSS_CLASS_LABEL_VALUE);  	
  gtk_widget_set_name(pLabel, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pLabel, x0, y0);
	gtk_widget_set_size_request(pLabel, w, h);  
  gtk_widget_show(pLabel);    

	  
  pViewDataPtr->pLabelHrvLFHF = pLabel;	 
  
	///-----------------------------------------------------------------------///
	/// Label: HRV-TP	
	///-----------------------------------------------------------------------///
	x0 = iCol0;
	y0 = iRow8;  
	w  = 120;
	h  = 30;	
		
	pLabel = gtk_label_new_with_mnemonic("HRV-TP");
	pContext = gtk_widget_get_style_context(pLabel);	
	gtk_style_context_add_class(pContext, CSS_CLASS_LABEL_TITLE);  	
  gtk_widget_set_name(pLabel, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pLabel, x0, y0);
	gtk_widget_set_size_request(pLabel, w, h);  
  gtk_widget_show(pLabel);


	///-----------------------------------------------------------------------///
	/// Label: HRV-TP
	///-----------------------------------------------------------------------///
	x0 = x0 + w;
	y0 = y0;  
	w  = 120;
	h  = 30;	
		
	pLabel = gtk_label_new_with_mnemonic("");
	pContext = gtk_widget_get_style_context(pLabel);	
	gtk_style_context_add_class(pContext, CSS_CLASS_LABEL_VALUE);  	
  gtk_widget_set_name(pLabel, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pLabel, x0, y0);
	gtk_widget_set_size_request(pLabel, w, h);  
  gtk_widget_show(pLabel);    


  pViewDataPtr->pLabelHrvTP = pLabel;	 
  
	///-----------------------------------------------------------------------///
	/// Label: HRV-LFTP	
	///-----------------------------------------------------------------------///
	x0 = iCol1;
	y0 = iRow8;  
	w  = 120;
	h  = 30;	
		
	pLabel = gtk_label_new_with_mnemonic("HRV-LFTP");
	pContext = gtk_widget_get_style_context(pLabel);	
	gtk_style_context_add_class(pContext, CSS_CLASS_LABEL_TITLE);  	
  gtk_widget_set_name(pLabel, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pLabel, x0, y0);
	gtk_widget_set_size_request(pLabel, w, h);  
  gtk_widget_show(pLabel);

	///-----------------------------------------------------------------------///
	/// Label: HRV-LFTP	
	///-----------------------------------------------------------------------///
	x0 = x0 + w;
	y0 = y0;  
	w  = 120;
	h  = 30;	
		
	pLabel = gtk_label_new_with_mnemonic("");
	pContext = gtk_widget_get_style_context(pLabel);	
	gtk_style_context_add_class(pContext, CSS_CLASS_LABEL_VALUE);  	
  gtk_widget_set_name(pLabel, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pLabel, x0, y0);
	gtk_widget_set_size_request(pLabel, w, h);  
  gtk_widget_show(pLabel);   

  pViewDataPtr->pLabelHrvLFTP = pLabel;	 

	///-----------------------------------------------------------------------///
	/// Label: HRV-HFTP	
	///-----------------------------------------------------------------------///
	x0 = iCol2;
	y0 = iRow8;  
	w  = 120;
	h  = 30;	
		
	pLabel = gtk_label_new_with_mnemonic("HRV-HFTP");
	pContext = gtk_widget_get_style_context(pLabel);	
	gtk_style_context_add_class(pContext, CSS_CLASS_LABEL_TITLE);  	
  gtk_widget_set_name(pLabel, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pLabel, x0, y0);
	gtk_widget_set_size_request(pLabel, w, h);  
  gtk_widget_show(pLabel);

	///-----------------------------------------------------------------------///
	/// Label: HRV-LFTP	
	///-----------------------------------------------------------------------///
	x0 = x0 + w;
	y0 = y0;  
	w  = 120;
	h  = 30;	
		
	pLabel = gtk_label_new_with_mnemonic("");
	pContext = gtk_widget_get_style_context(pLabel);	
	gtk_style_context_add_class(pContext, CSS_CLASS_LABEL_VALUE);  	
  gtk_widget_set_name(pLabel, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pLabel, x0, y0);
	gtk_widget_set_size_request(pLabel, w, h);  
  gtk_widget_show(pLabel);   

  pViewDataPtr->pLabelHrvHFTP = pLabel;	 

	return TRUE;
}

static JINT EntryInit(void) 
{
	ViewDataForm1Type * pViewDataPtr = &ViewDataForm1;
	JINT iRet = TRUE;
	GtkWidget *pEntry	= NULL;
	JINT x0 = 0;
	JINT y0 = 0;	
	JINT w  = 0;
	JINT h  = 0;

	///-----------------------------------------------------------------------///
	/// Entry: file path
	///-----------------------------------------------------------------------///
	x0 = FORM1_FRAME0_LEFT + FORM1_FRAME0_XGAP;
	y0 = FORM1_FRAME0_TOP  + FORM1_FRAME0_ROW;
	w  = 710;
	h  = 20;

	pViewDataPtr->pEntryFileName =  gtk_entry_new(); 
	pEntry = pViewDataPtr->pEntryFileName;
  gtk_entry_set_placeholder_text(GTK_ENTRY(pEntry), "please browse the input file");
  gtk_widget_set_name(pEntry, "form1_entry_filepath");  
  gtk_widget_set_size_request(pEntry, w, h); 
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pEntry, x0, y0);
  g_signal_connect(G_OBJECT(pEntry),   "activate",   G_CALLBACK(CallbackForm1EntryFileNameActive), NULL);
  gtk_widget_show(pEntry);

	///-----------------------------------------------------------------------///
	/// Entry: time
	///-----------------------------------------------------------------------///
	x0 = FORM1_FRAME1_LEFT + 60;
	y0 = FORM1_FRAME1_TOP  + FORM1_FRAME1_ROW;  
	w = 100;
	h = 16;
	pEntry = gtk_entry_new(); 	
  gtk_entry_set_placeholder_text(GTK_ENTRY(pEntry), "HH:MM:SS");
  gtk_widget_set_name(pEntry, "form1_entry_chart_ecg_time");  
	gtk_entry_set_text(GTK_ENTRY(pEntry), "00:00:00");    
  gtk_widget_set_size_request(pEntry, w, h); 
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pEntry, x0, y0);
  g_signal_connect(G_OBJECT(pEntry),   "activate",   G_CALLBACK(CallbackForm1ChartEcgTimeActive), NULL);
  gtk_widget_show(pEntry);  	
	pViewDataPtr->pEntryChartEcgTime = pEntry;

	///-----------------------------------------------------------------------///
	/// Entry: time
	///-----------------------------------------------------------------------///
	x0 = FORM1_FRAME1_LEFT + 260;
	y0 = FORM1_FRAME1_TOP  + FORM1_FRAME1_ROW;  
	w = 100;
	h = 16;
	pEntry =  gtk_entry_new(); 	
  gtk_entry_set_placeholder_text(GTK_ENTRY(pEntry), "HH:MM:SS");
	gtk_entry_set_text(GTK_ENTRY(pEntry), "00:00:00");
  gtk_widget_set_name(pEntry, "form1_entry_chart_ecg_time_end");  
  gtk_widget_set_size_request(pEntry, w, h); 
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pEntry, x0, y0);
  gtk_widget_set_sensitive(pEntry, FALSE); 
  gtk_widget_show(pEntry);  
	pViewDataPtr->pEntryChartEcgTimeTotal = pEntry;

	return iRet;	
}

static JINT ButtonInit(void)
{
	ViewDataForm1Type * pViewDataPtr = &ViewDataForm1;
	JINT iRet = TRUE;
	GtkWidget *pButton 	= NULL;
	JINT x0 = 0;
	JINT y0 = 0;
	JINT w = 80;
	JINT h = 30;

	///-----------------------------------------------------------------------///
	/// Button -> Browse
	///-----------------------------------------------------------------------///	
	x0 = FORM1_FRAME0_LEFT + 740;
	y0 = FORM1_FRAME0_TOP  + FORM1_FRAME0_ROW;
  w = 80;
	h = 30;

	pViewDataPtr->pBtnBrowse = gtk_button_new_with_label("Browse");
	pButton = pViewDataPtr->pBtnBrowse;
  gtk_widget_set_size_request(pButton, w, h); 
  g_signal_connect(G_OBJECT(pButton), "clicked",   G_CALLBACK(CallbackForm1BtnBrowseClicked), NULL);
  gtk_widget_set_name(pButton, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pButton, x0, y0);
  gtk_widget_show(pButton);

	///-----------------------------------------------------------------------///
	/// Button -> Reverse
	///-----------------------------------------------------------------------///
	x0 = FORM1_FRAME1_LEFT + 640;
	y0 = FORM1_FRAME1_TOP  + FORM1_FRAME1_ROW;
  w = 80;
	h = 30;

	pButton= gtk_button_new_with_label("◀");	
	gtk_widget_set_name(pButton, "");  
  g_signal_connect(G_OBJECT(pButton), "clicked",   G_CALLBACK(CallbackForm1BtnChartEcgReverseClicked), NULL);
  gtk_widget_set_size_request(pButton, w, h); 
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pButton, x0, y0);
  gtk_widget_show(pButton);  
	pViewDataPtr->pBtnChartEcgReverse = pButton;


	///-----------------------------------------------------------------------///
	/// Button -> Stop
	///-----------------------------------------------------------------------///
	x0 = FORM1_FRAME1_LEFT + 740;
	y0 = FORM1_FRAME1_TOP  + FORM1_FRAME1_ROW;
  w = 80;
	h = 30;

	pButton= gtk_button_new_with_label("▇");	
	gtk_widget_set_name(pButton, "");  
  g_signal_connect(G_OBJECT(pButton), "clicked",   G_CALLBACK(CallbackForm1BtnChartEcgStopClicked), NULL);
  gtk_widget_set_size_request(pButton, w, h); 
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pButton, x0, y0);
  gtk_widget_show(pButton);  
	pViewDataPtr->pBtnChartEcgStop = pButton;

	///-----------------------------------------------------------------------///
	/// Button -> Play
	///-----------------------------------------------------------------------///
	x0 = FORM1_FRAME1_LEFT + 840;
	y0 = FORM1_FRAME1_TOP  + FORM1_FRAME1_ROW;
  w = 80;
	h = 30;

	pButton= gtk_button_new_with_label("▶");	
	gtk_widget_set_name(pButton, "");  
  g_signal_connect(G_OBJECT(pButton), "clicked",   G_CALLBACK(CallbackForm1BtnChartEcgPlayClicked), NULL);
  gtk_widget_set_size_request(pButton, w, h); 
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pButton, x0, y0);
  gtk_widget_show(pButton);  
	pViewDataPtr->pBtnChartEcgPlay = pButton;	

	return iRet;
}

static JINT FrameInit(void)
{
	JINT iRet = TRUE;
	ViewDataForm1Type * pViewDataPtr = &ViewDataForm1;	
	GtkWidget * pFrame = NULL;  

  JINT x0 = 0;
  JINT y0 = 0;
  JINT w  = 0;
  JINT h  = 0;
	
	GtkStyleContext *pContext = NULL;

	///-----------------------------------------------------------------------///
	/// Frame: File Browse
	///-----------------------------------------------------------------------///
	x0 = FORM1_FRAME0_LEFT;
	y0 = FORM1_FRAME0_TOP;
  w  = FORM1_FRAME0_WIDTH;
  h  = FORM1_FRAME0_HEIGHT;

  pFrame = gtk_frame_new("Load File");
	pContext = gtk_widget_get_style_context(pFrame);	
	gtk_style_context_add_class(pContext, "frame_default");  
  gtk_frame_set_shadow_type(GTK_FRAME (pFrame), GTK_SHADOW_ETCHED_IN);
  gtk_frame_set_label_align(GTK_FRAME (pFrame), 0.02, 0.5);
  gtk_widget_set_size_request(pFrame, w, h); 
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pFrame, x0, y0);
  gtk_widget_show(pFrame);

	///-----------------------------------------------------------------------///
	/// Frame: Chart
	///-----------------------------------------------------------------------///
	x0 = FORM1_FRAME1_LEFT;
	y0 = FORM1_FRAME1_TOP;
  w  = FORM1_FRAME1_WIDTH;
  h  = FORM1_FRAME1_HEIGHT;

  pFrame = gtk_frame_new("Control");
	pContext = gtk_widget_get_style_context(pFrame);	
	gtk_style_context_add_class(pContext, "frame_default");  	
  gtk_frame_set_shadow_type(GTK_FRAME (pFrame), GTK_SHADOW_ETCHED_IN);
  gtk_frame_set_label_align(GTK_FRAME (pFrame), 0.02, 0.5);
  gtk_widget_set_size_request(pFrame, w, h); 
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pFrame, x0, y0);
  gtk_widget_show(pFrame);

	///-----------------------------------------------------------------------///
	/// Frame: ECG Chart
	///-----------------------------------------------------------------------///
	x0 = FORM1_FRAME2_LEFT;
	y0 = FORM1_FRAME2_TOP;
  w  = FORM1_FRAME2_WIDTH;
  h  = FORM1_FRAME2_HEIGHT;

  pFrame = gtk_frame_new("Ecg Chart");
	pContext = gtk_widget_get_style_context(pFrame);	
	gtk_style_context_add_class(pContext, "frame_default");  	
  gtk_frame_set_shadow_type(GTK_FRAME (pFrame), GTK_SHADOW_ETCHED_IN);
  gtk_frame_set_label_align(GTK_FRAME (pFrame), 0.02, 0.5);
  gtk_widget_set_size_request(pFrame, w, h); 
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pFrame, x0, y0);
  gtk_widget_show(pFrame);

	///-----------------------------------------------------------------------///
	/// Frame: Info
	///-----------------------------------------------------------------------///
	x0 = FORM1_FRAME3_LEFT;
	y0 = FORM1_FRAME3_TOP;
  w  = FORM1_FRAME3_WIDTH;
  h  = FORM1_FRAME3_HEIGHT;

  pFrame = gtk_frame_new("Information");
	pContext = gtk_widget_get_style_context(pFrame);	
	gtk_style_context_add_class(pContext, "frame_default");  	
  gtk_frame_set_shadow_type(GTK_FRAME (pFrame), GTK_SHADOW_ETCHED_IN);
  gtk_frame_set_label_align(GTK_FRAME (pFrame), 0.02, 0.5);
  gtk_widget_set_size_request(pFrame, w, h); 
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pFrame, x0, y0);
  gtk_widget_show(pFrame);	

  return iRet;  
}

static JINT ProgressBarInit()
{
	JINT x0		 	= 0;
	JINT y0 		= 0;	
	JINT width 	= 0;
	JINT height	= 0;	
	GtkWidget * pProgressBar = NULL;
	ViewDataForm1Type * pViewDataPtr = &ViewDataForm1;	
	
	///-----------------------------------------------------------------------------------///
	/// Progress bar init
	///-----------------------------------------------------------------------------------///
	pProgressBar = gtk_progress_bar_new();

	x0 			= FORM1_FRAME0_LEFT + FORM1_FRAME0_XGAP;
	y0 			= FORM1_FRAME0_TOP  + FORM1_FRAME0_ROW;	
	width 	= 600;
	height 	= 60;

 	gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pProgressBar, x0, y0);
  gtk_widget_set_size_request(pProgressBar, width, height);  	
  gtk_widget_show(pProgressBar);
  gtk_progress_bar_set_fraction((GtkProgressBar *)pProgressBar, 0);
  gtk_widget_set_name(pProgressBar, "form1_progress_bar1");  
  gtk_widget_show(pProgressBar);  
  pViewDataPtr->pProgressBar = pProgressBar;

  return TRUE;
}

static JINT ComboBoxInit()
{
	ViewDataForm1Type * pViewDataPtr = &ViewDataForm1;
	GtkWidget	*pComboBox = NULL;
	JINT x0 = 0;
	JINT y0 = 0;	

	///-----------------------------------------------------------------------///
	/// ComboBox -> Speed
	///-----------------------------------------------------------------------///
	x0 = FORM1_FRAME1_LEFT + 480;
	y0 = FORM1_FRAME1_TOP  + FORM1_FRAME1_ROW;
  pComboBox = gtk_combo_box_text_new();
  gtk_widget_set_size_request(pComboBox, 80, 30);   
  gtk_widget_set_name(pComboBox, "");  
  gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(pComboBox), NULL, "Slow: 50ms");
  gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(pComboBox), NULL, "Normal: 100ms");
  gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(pComboBox), NULL, "High: 200ms");
  gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(pComboBox), NULL, "Very High: 500ms");  
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(pComboBox), NULL, "Highest: 1000ms");  
  gtk_combo_box_set_active(GTK_COMBO_BOX(pComboBox), 1);
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pComboBox, x0, y0);
	gtk_widget_show(pComboBox);
  pViewDataPtr->pComboBoxSpeed = pComboBox;
  
	return TRUE;
}

static JINT ImageInit(void)
{
	ViewDataForm1Type * pViewDataPtr = &ViewDataForm1;
	GtkWidget *pImage;
	GtkWidget *event_box;
	JINT x0 = 530;
	JINT y0 = 1200;

	char strFileName[256];
	sprintf(strFileName, "%s", "img/logo-black.png");

	if(UtilFileExisted(strFileName) == FALSE)
	{
		if(GlobalVar.iOSType == OS_TYPE_MAC_OS)
		{
			sprintf(strFileName, "/Users/Shared/VsEcg/img/logo-black.png");
		}
		if(GlobalVar.iOSType == OS_TYPE_UBUNTU)
		{
			sprintf(strFileName, "/usr/share/VsEcg/img/logo-black.png");
		}
		if(UtilFileExisted(strFileName) == FALSE)
		{
			return FALSE;
		}
	}

	pImage = gtk_image_new_from_file (strFileName);

	gtk_widget_set_size_request(pImage, 0, 10); 
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pImage, x0, y0);
  
  gtk_widget_show(pImage);

	return TRUE;
}


static JINT TimerInit()
{
	ViewDataForm1Type * pViewDataPtr = &ViewDataForm1;	
	
	g_timeout_add(100, CallbackForm1Timer1, (gpointer)pViewDataPtr->pView);	
	g_timeout_add(100, CallbackForm1Timer2, (gpointer)pViewDataPtr->pDrawAreaDS0);	
	
	return TRUE;
}

static JINT DrawAreaInit()
{
	JINT x0 = 0;
	JINT y0 = 0;	
	JINT wd = 0;
	JINT ht = 0;	
	GtkWidget * pDrawArea = NULL; 
	ViewDataForm1Type * pViewDataPtr = (ViewDataForm1Type *)pThis->pViewData;	

	///---------------------------------------------------------------------------------///
	/// DrawAreaDS0
	///---------------------------------------------------------------------------------///
	x0 = FORM1_FRAME2_LEFT + FORM1_FRAME2_XGAP;
	y0 = FORM1_FRAME2_TOP  + FORM1_FRAME2_YGAP;	
	wd = FORM1_DRAW_AREA_DS0_WIDTH;
	ht = FORM1_DRAW_AREA_DS0_HEIGHT;
	
 	pDrawArea = gtk_drawing_area_new(); 		
 	gtk_widget_set_size_request(pDrawArea, wd, ht);  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pDrawArea, x0, y0);	
  g_signal_connect (G_OBJECT(pDrawArea), "draw", G_CALLBACK (CallbackForm1DrawArea0), NULL);
	gtk_widget_show(pDrawArea); 
  pViewDataPtr->pDrawAreaDS0 = pDrawArea;
	return TRUE;
}

static JINT ChartDS0Init()
{
	JINT 	x 		 = FORM1_CHART_ECG_CANVAS_LEFT;
	JINT 	y 		 = FORM1_CHART_ECG_CANVAS_TOP;		
	JINT 	width  = FORM1_CHART_ECG_CANVAS_WIDTH;
	JINT 	height = FORM1_CHART_ECG_CANVAS_HEIGHT;	

	JINT iRowCnt = 12 * 5 ;
	JINT iColCnt = 6 * 5 * 5 ;

	ViewDataForm1Type * pViewDataPtr = (ViewDataForm1Type * ) pThis->pViewData;
	
	JChart *pChart = &pViewDataPtr->ChartDS0;
	
	JChartInit(pChart);
	JChartCellSet(pChart,  iRowCnt,  iColCnt);
	
	JChartCanvasPosSet(pChart, x, y,  width, height);	
	JChartChartPosSet(pChart,  x,	y, 	width, height);		

	return TRUE;
}

static JINT ChartInit()
{
	ChartDS0Init();
	return TRUE;
}

///------------------------------------------------------------------------------------///
/// Function area
///------------------------------------------------------------------------------------///
static JINT FuncOnShow()
{
	ViewDataForm1Type * pViewDataPtr = &ViewDataForm1;	
	gtk_widget_show(pViewDataPtr->pView);
	pViewDataPtr->bShow = TRUE;	
	return TRUE;
}

static JINT FuncOnHide()
{
	ViewDataForm1Type * pViewDataPtr = &ViewDataForm1;	
	gtk_widget_hide(pViewDataPtr->pView);
	pViewDataPtr->bShow = FALSE;	
	return TRUE;
}

static JINT FuncInit()
{
	ViewDataForm1Type * pViewDataPtr = &ViewDataForm1;	

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
	/// Frame init
	///-----------------------------------------------------------------------///
	FrameInit();

 	///-----------------------------------------------------------------------///
	///  Button init
	///-----------------------------------------------------------------------///	
	ButtonInit();

	///-----------------------------------------------------------------------///
	///  Progress bar init
	///-----------------------------------------------------------------------///	
 	ProgressBarInit();

	///-----------------------------------------------------------------------///
	///  ComboBox Init
	///-----------------------------------------------------------------------///	
	ComboBoxInit();

	///-----------------------------------------------------------------------///
	///  Image Init
	///-----------------------------------------------------------------------///	
	ImageInit();

	///-----------------------------------------------------------------------///
	///  Progress bar init
	///-----------------------------------------------------------------------///	
	TimerInit();

	///-----------------------------------------------------------------------///
	///  Draw Init
	///-----------------------------------------------------------------------///	
  DrawAreaInit();

	///-----------------------------------------------------------------------///
	///  Chart Init
	///-----------------------------------------------------------------------///	
	ChartInit();

	gtk_container_add(GTK_CONTAINER(AppPtr->pBox),   pViewDataPtr->pView);

  AppMainMenuSet(pViewDataPtr->pView);
	return TRUE;
}

///--------------------------------------------------------------------------------///
///   Form1 
///--------------------------------------------------------------------------------///
JView JVForm1 = 
{
	"Form1",										///< char text[32];							  ///< form name
	(void *)&ViewDataForm1,			///< void *pViewData;							///< #00 View Data	
	FuncOnShow,     						///< JINT (*OnShow)();   					///< #02 show view
	FuncOnHide,     						///< JINT (*OnHide();   					///< #03 hide view
	FuncInit,										///< JINT (*Init)();  				  	///< #05 Init event
};


