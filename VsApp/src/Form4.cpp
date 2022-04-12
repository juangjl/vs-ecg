/**
 * @file Form4.cpp
 *
 *   View function
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

#include "Form4.h"

ViewDataForm4Type  	ViewDataForm4;

///------------------------------------------------------------------------------------///
/// Variable area
///------------------------------------------------------------------------------------///
static JView *pThis = &JVForm4;

///------------------------------------------------------------------------------------///
/// Callback area
///------------------------------------------------------------------------------------///
gboolean CallbackForm4DrawArea0(GtkWidget *widget, cairo_t *cr, gpointer data)
{	
	char msg[256];
	
	JINT iWidth  = 0;
	JINT iHeight = 0;	
	JDOUBLE x[10];
	JDOUBLE y[10];	
	
	ViewDataForm4Type * pViewDataPtr = (ViewDataForm4Type * ) pThis->pViewData;
	JDraw *pDC         = new JDraw(cr); 

  /// DataSet works with Chart
	JChart *pChart     = &pViewDataPtr->Chart0;
	JDataSet *pDataSet = &GlobalVar.dataSet[DATASET_MONITOR_ECG_DS0];

	JINT iTimeMS = (GlobalVar.iDataSetTime[DATASET_MONITOR_ECG_DS0] - 6000);

	char strStart[64];
	char strCenter[64];
	char strEnd[64];

	GtkStyleContext *pContext;	
	static JBOOL bDrawing = FALSE;

	///-------------------------------------------------------------------///
	/// ATR Variable : Start
	///-------------------------------------------------------------------///
	AtrCtlType		* pAtrCtl  = &AtrCtlBle;
	AtrDataType		* pAtrData = NULL;
	AtrFindType 		atrFind;
	AtrFindType 	*	pAtrFind = &atrFind;

	JINT i = 0 ;
	JFLOAT fXVal = 0;
	JINT iXPos = 0;
	JINT iYPos = 0;
	JDWORD dwColor = 0;
	char strAtrAbbrev[32];
	
	JFLOAT fAtrTimeSec    = -1;
	static JFLOAT fAtrTimeSecPre = -1;

	JFLOAT fTimeSec = -1;

	///-------------------------------------------------------------------///
	/// ATR Variable : End
	///-------------------------------------------------------------------///

	/// Drawing check
	if(bDrawing == TRUE)
	{
		return FALSE;
	}
	bDrawing = TRUE;

	if((iTimeMS < 0))
	{
		iTimeMS = 0;
	}
	
	pContext = gtk_widget_get_style_context(widget);
	iWidth   = gtk_widget_get_allocated_width(widget);
	iHeight  = gtk_widget_get_allocated_height(widget);

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

  ///-------------------------------------------------------------------///
	/// ATR-DRAW : START
	///-------------------------------------------------------------------///		
	fAtrTimeSec = (JFLOAT)(iTimeMS) / 1000;
	pAtrFind->fTimeSec0 = fAtrTimeSec;
	pAtrFind->fTimeSec1 = pAtrFind->fTimeSec0 + 6;
	pAtrFind->iCnt = 0;
	
	AtrCtlFind(pAtrCtl, pAtrFind);

	if(fAtrTimeSecPre >  fAtrTimeSecPre)
	{
		fAtrTimeSecPre = 0;
	}

#if 0
	if(pAtrFind->iCnt > 0)
	{
		sprintf(msg, "\t [ATR] ATR total = %d,  find_cnt = %d, sec0 = %0.3f, sec1=%0.3f\r\n", pAtrCtl->iAtrDataCnt, pAtrFind->iCnt, pAtrFind->fTimeSec0, pAtrFind->fTimeSec1);
		DBG_PRINTF(msg);
	}
#endif	

	for(i = 0 ; i < pAtrFind->iCnt; i = i + 1)
	{
		pAtrData = &pAtrCtl->atrData[pAtrFind->iIdx + i];
		dwColor  = COLOR_BLUE;		
		fXVal 		= pAtrData->fTimeSec - fAtrTimeSec;

		AtrAbbrevGet(pAtrData->dwA, (char *)&strAtrAbbrev[0], &dwColor);

		JChartXValToXPos(pChart, fXVal, &iXPos);
		iYPos = pChart->iChartY0 + 12;

		JChartTriangleDraw(pChart, iXPos, iYPos, 10, 10, dwColor);
		if(fAtrTimeSec != fAtrTimeSecPre)
		{
			fAtrTimeSecPre = fAtrTimeSec;
		}

		iXPos = iXPos - 3;
		iYPos = pChart->iChartY0 - 2;

		JChartLabelDraw(pChart, strAtrAbbrev, iXPos, iYPos, dwColor);
	}
	///-------------------------------------------------------------------///
	/// ATR-DRAW : END
	///-------------------------------------------------------------------///	
	
	delete(pDC);

	UtilMsSleep(20);

	bDrawing = FALSE;
	
	return  TRUE;
}	

///------------------------------------------------------------------------------------///
/// Chart
///------------------------------------------------------------------------------------///
static JINT Form4Chart0Init()
{
	ViewDataForm4Type * pViewDataPtr = (ViewDataForm4Type * ) pThis->pViewData;
	JINT 	x 		 = Form4_CHART0_LEFT;
	JINT 	y 		 = Form4_CHART0_TOP;		
	JINT 	width  = Form4_CHART0_WIDTH;
	JINT 	height = Form4_CHART0_HEIGHT;	

	JINT iRowCnt = 12 * 5 ;
	JINT iColCnt = 6 * 5 * 5 ;
	
	JChart *pChart = &pViewDataPtr->Chart0;
	
	JChartInit(pChart);
	JChartCellSet(pChart,  iRowCnt,  iColCnt);
	
	JChartCanvasPosSet(pChart, x, y,  width, height);	
	JChartChartPosSet(pChart,  y,	y, 	width, height);		

	return TRUE;
}

JINT CallbackForm4Timer1 (gpointer data)
{    
	Form4LabelInfoUpdate();	
	return TRUE;
}

JINT CallbackForm4Timer2 (gpointer data)
{
	ViewDataForm4Type * pViewDataPtr = (ViewDataForm4Type * ) pThis->pViewData;

	if(pViewDataPtr->bShow == TRUE)
	{
		gtk_widget_queue_draw(pViewDataPtr->pDrawArea0);
		//gtk_widget_queue_draw(pViewDataPtr->pDrawArea1);
		//gtk_widget_queue_draw(pViewDataPtr->pDrawArea2);
		//gtk_widget_queue_draw(pViewDataPtr->pDrawArea3);
		//gtk_widget_queue_draw(pViewDataPtr->pDrawArea4);
	}
	return TRUE;
}

///------------------------------------------------------------------------------------///
/// Label Update
///------------------------------------------------------------------------------------///
void Form4LabelInfoUpdate(void)
{
  ViewDataForm4Type * pViewDataPtr = (ViewDataForm4Type * ) pThis->pViewData;
	VscModeControlType * pVscMode = (VscModeControlType *)&VscModeCtl;	
	char strValue[256];

	///-----------------------------------------------------------------//
	/// 1. date
	///-----------------------------------------------------------------//	
	sprintf(strValue, "%04d/%02d/%02d", 
										pVscMode->jtm.iYear, 
										pVscMode->jtm.iMonth, 
										pVscMode->jtm.iDay); 
	gtk_label_set_text(GTK_LABEL(pViewDataPtr->pLabelDate), strValue);

	///-----------------------------------------------------------------//
	/// 1. time
	///-----------------------------------------------------------------//	
	sprintf(strValue, "%02d:%02d:%02d", 
										pVscMode->jtm.iHour, 
										pVscMode->jtm.iMin, 
										pVscMode->jtm.iSec); 
	gtk_label_set_text(GTK_LABEL(pViewDataPtr->pLabelTime), strValue);

	///-----------------------------------------------------------------//
	/// 2. fTemp
	///-----------------------------------------------------------------//	
	sprintf(strValue, "%0.3f", pVscMode->fTemp);
	gtk_label_set_text(GTK_LABEL(pViewDataPtr->pLabelTemp), strValue);
	
	///-----------------------------------------------------------------//
	/// 3. fHRNow
	///-----------------------------------------------------------------//	
	sprintf(strValue, "%0.1f", pVscMode->fHRNow);
	gtk_label_set_text(GTK_LABEL(pViewDataPtr->pLabelEcgHR), strValue);
		
	///-----------------------------------------------------------------//
	/// 4.  fLeadOff
	///-----------------------------------------------------------------//	
	sprintf(strValue, "%0.0f", pVscMode->fLeadOff);
	gtk_label_set_text(GTK_LABEL(pViewDataPtr->pLabelEcgLeadOff), strValue);

	///-----------------------------------------------------------------//
	/// 5.  fGsenXNow
	/// 6.  fGsenYNow
	/// 7.  fGsenZNow
	///-----------------------------------------------------------------//	
	sprintf(strValue, "%0.0f", pVscMode->fGsenXNow);
	gtk_label_set_text(GTK_LABEL(pViewDataPtr->pLabelGSenXNow), strValue);
	sprintf(strValue, "%0.0f", pVscMode->fGsenYNow);
	gtk_label_set_text(GTK_LABEL(pViewDataPtr->pLabelGSenYNow), strValue);
	sprintf(strValue, "%0.0f", pVscMode->fGsenZNow);
	gtk_label_set_text(GTK_LABEL(pViewDataPtr->pLabelGSenZNow), strValue);

	///-----------------------------------------------------------------//
	/// 8.  fBattSoc
	/// 9.  fBattTotalSec
	///-----------------------------------------------------------------//
	sprintf(strValue, "%0.0f", pVscMode->fBattSoc);
	gtk_label_set_text(GTK_LABEL(pViewDataPtr->pLabelBattSoc), strValue);

	sprintf(strValue, "%0.0f", pVscMode->fBattTotalSec);
	gtk_label_set_text(GTK_LABEL(pViewDataPtr->pLabelBattSec), strValue);

	///-----------------------------------------------------------------//
	/// 10.  fHrvSDNN
	/// 11.  fHrvNN50
	/// 12.  fHrvRMSSD
	/// 13.  fHrvRR
	///-----------------------------------------------------------------//
  sprintf(strValue, "%0.3f", pVscMode->fHrvSDNN);
	gtk_label_set_text(GTK_LABEL(pViewDataPtr->pLabelHrvSDNN), strValue);

  sprintf(strValue, "%0.3f", pVscMode->fHrvNN50);
	gtk_label_set_text(GTK_LABEL(pViewDataPtr->pLabelHrvNN50), strValue);

  sprintf(strValue, "%0.3f", pVscMode->fHrvRMSSD);
	gtk_label_set_text(GTK_LABEL(pViewDataPtr->pLabelHrvRMSSD), strValue);

  sprintf(strValue, "%0.3f", pVscMode->fHrvRR);
	gtk_label_set_text(GTK_LABEL(pViewDataPtr->pLabelHrvRR), strValue);

	///-----------------------------------------------------------------//
	/// 14.  fHrvVLF
	/// 15.  fHrvLF
	/// 16.  fHrvHF
	/// 17.  fHrvLFHF
	///-----------------------------------------------------------------//

	sprintf(strValue, "%0.0f", pVscMode->fHrvVLF);
	gtk_label_set_text(GTK_LABEL(pViewDataPtr->pLabelHrvVLF), strValue);

  sprintf(strValue, "%0.0f", pVscMode->fHrvLF);
	gtk_label_set_text(GTK_LABEL(pViewDataPtr->pLabelHrvLF), strValue);

  sprintf(strValue, "%0.0f", pVscMode->fHrvHF);
	gtk_label_set_text(GTK_LABEL(pViewDataPtr->pLabelHrvHF), strValue);

  sprintf(strValue, "%0.3f", pVscMode->fHrvLFHF);
	gtk_label_set_text(GTK_LABEL(pViewDataPtr->pLabelHrvLFHF), strValue);

	///-----------------------------------------------------------------//
	/// 18.  fHrvTP
	/// 19.  fHrvLFTP
	/// 20.  fHrvHFTP
	///-----------------------------------------------------------------//
	sprintf(strValue, "%0.0f", pVscMode->fHrvTP);
	gtk_label_set_text(GTK_LABEL(pViewDataPtr->pLabelHrvTP), strValue);

  sprintf(strValue, "%0.0f", pVscMode->fHrvLFTP);
	gtk_label_set_text(GTK_LABEL(pViewDataPtr->pLabelHrvLFTP), strValue);

  sprintf(strValue, "%0.0f", pVscMode->fHrvHFTP);
	gtk_label_set_text(GTK_LABEL(pViewDataPtr->pLabelHrvHFTP), strValue);
	
	return;
}

///------------------------------------------------------------------------------------///
/// Form4 Function
///------------------------------------------------------------------------------------///
static JINT LabelInit(void)
{
	ViewDataForm4Type * pViewDataPtr = &ViewDataForm4;
	JINT iRet = TRUE;
	GtkWidget *pLabel 	= NULL;
	GtkStyleContext *pContext = NULL;

	JINT x0 = 0;
	JINT y0 = 0;	
	JINT w = 0;
	JINT h = 0;

	JINT iCol0 	= Form4_FRAME0_LEFT + 20;
	JINT iCol1 	= Form4_FRAME0_LEFT + 300;
	JINT iCol2	= Form4_FRAME0_LEFT + 580;
	JINT iCol3 	= Form4_FRAME0_LEFT + 860;

	JINT iRow0  = Form4_FRAME0_TOP  + 20;
	JINT iRow1  = Form4_FRAME0_TOP  + 60;
	JINT iRow2  = Form4_FRAME0_TOP  + 100;
	JINT iRow3  = Form4_FRAME0_TOP  + 140;	
	JINT iRow4  = Form4_FRAME0_TOP  + 180;		
	JINT iRow5  = Form4_FRAME0_TOP  + 220;			
	JINT iRow6  = Form4_FRAME0_TOP  + 260;			

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
	x0 = iCol3;
	y0 = iRow4;  
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
	y0 = iRow5;  
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
	y0 = iRow5;  
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
	y0 = iRow5;  
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
	x0 = iCol3;
	y0 = iRow5;  
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
	y0 = iRow6;  
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
	y0 = iRow6;  
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
	y0 = iRow6;  
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
	ViewDataForm4Type * pViewDataPtr = &ViewDataForm4;
	JINT iRet = TRUE;
	GtkWidget *pEntry 	= NULL;
	JINT x0 = 0;
	JINT y0 = 0;	

	return iRet;	
}

static JINT ButtonInit(void)
{
	ViewDataForm4Type * pViewDataPtr = &ViewDataForm4;
	JINT iRet = TRUE;
	GtkWidget *pButton 	= NULL;
	JINT x0 = 0;
	JINT y0 = 0;

	
	return iRet;
}

static JINT FrameInit(void)
{
	JINT iRet = TRUE;
	ViewDataForm4Type * pViewDataPtr = &ViewDataForm4;	
  GtkWidget * pFrame = NULL;
	
  JINT x0 = 0;
  JINT y0 = 0;
  JINT w  = 0;
  JINT h  = 0;
  
	///-----------------------------------------------------------------------///
	/// Frame0: ECG Info
	///-----------------------------------------------------------------------///
	x0 = Form4_FRAME0_LEFT;
	y0 = Form4_FRAME0_TOP;
  w  = Form4_FRAME0_WIDTH;
  h  = Form4_FRAME0_HEIGHT;

  pFrame = gtk_frame_new ("Information");
  gtk_frame_set_shadow_type (GTK_FRAME (pFrame), GTK_SHADOW_ETCHED_IN);
  gtk_frame_set_label_align (GTK_FRAME (pFrame), 0.02, 0.5);
  gtk_widget_set_size_request(pFrame, w, h); 
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pFrame, x0, y0);
  gtk_widget_show(pFrame);

	///-----------------------------------------------------------------------///
	/// Frame1: Chart 
	///-----------------------------------------------------------------------///
	x0 = Form4_FRAME1_LEFT;
	y0 = Form4_FRAME1_TOP;
  w  = Form4_FRAME1_WIDTH;
  h  = Form4_FRAME1_HEIGHT;

  pFrame = gtk_frame_new ("Chart");
  gtk_frame_set_shadow_type (GTK_FRAME (pFrame), GTK_SHADOW_ETCHED_IN);
  gtk_frame_set_label_align (GTK_FRAME (pFrame), 0.02, 0.5);
  gtk_widget_set_size_request(pFrame, w, h); 
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pFrame, x0, y0);
  gtk_widget_show(pFrame);

  return iRet;  
}

static JINT ImageInit()
{
	ViewDataForm4Type * pViewDataPtr = &ViewDataForm4;
	GtkWidget *pImage;
	GtkWidget *event_box;
	JINT x0 = 530;
	JINT y0 = 850;

	pImage = gtk_image_new_from_file ("img/logo-black.png");
	gtk_widget_set_size_request(pImage, 0, 10); 
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pImage, x0, y0);
  
  gtk_widget_show(pImage);

	return TRUE;
}

static JINT TimerInit()
{
	ViewDataForm4Type * pViewDataPtr = &ViewDataForm4;	
		
	g_timeout_add(500, CallbackForm4Timer1, (gpointer)pViewDataPtr->pView);	
	g_timeout_add(100, CallbackForm4Timer2, (gpointer)pViewDataPtr->pView);	

	return TRUE;
}

static JINT DrawAreaInit()
{
	ViewDataForm4Type * pViewDataPtr = &ViewDataForm4;
	
	JINT x0 = 0;
	JINT y0 = 0;	
	JINT wd = 0;
	JINT ht = 0;	
	GtkWidget * pDrawArea = NULL; 

	///---------------------------------------------------------------------------------///
	/// DrawArea0
	///---------------------------------------------------------------------------------///
	x0 = Form4_DRAW_AREA0_LEFT;
	y0 = Form4_DRAW_AREA0_TOP;	
	wd = Form4_DRAW_AREA0_WIDTH;
	ht = Form4_DRAW_AREA0_HEIGHT;
	
 	pDrawArea = gtk_drawing_area_new(); 		
 	gtk_widget_set_size_request(pDrawArea, wd, ht);  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pDrawArea, x0, y0);	
  g_signal_connect (G_OBJECT(pDrawArea), "draw", G_CALLBACK (CallbackForm4DrawArea0), NULL);
	gtk_widget_show(pDrawArea); 
  pViewDataPtr->pDrawArea0 = pDrawArea;
	return TRUE;
}

static JINT ChartInit()
{
	/// Chart#0
	Form4Chart0Init();

	return TRUE;
}

///------------------------------------------------------------------------------------///
/// Function area
///------------------------------------------------------------------------------------///
static JINT FuncOnShow()
{
	ViewDataForm4Type * pViewDataPtr = &ViewDataForm4;	
	gtk_widget_show(pViewDataPtr->pView);
	pViewDataPtr->bShow = TRUE;	
	return TRUE;
}

static JINT FuncOnHide()
{
	ViewDataForm4Type * pViewDataPtr = &ViewDataForm4;	
	gtk_widget_hide(pViewDataPtr->pView);
	pViewDataPtr->bShow = FALSE;	
	return TRUE;
}

static JINT FuncInit()
{
	ViewDataForm4Type * pViewDataPtr = &ViewDataForm4;	

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
	///  Frame init
	///-----------------------------------------------------------------------///	
	FrameInit();

	///-----------------------------------------------------------------------///
	///  Image init
	///-----------------------------------------------------------------------///	
	ImageInit();

 	///-----------------------------------------------------------------------///
	///  Button init
	///-----------------------------------------------------------------------///	
	ButtonInit();

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
///   Form4 
///--------------------------------------------------------------------------------///
JView JVForm4 = 
{
	"Form4",										///< char text[32];							  ///< form name
	(void *)&ViewDataForm4,			///< void *pViewData;							///< #00 View Data	
	FuncOnShow,     						///< JINT (*OnShow)();   					///< #02 show view
	FuncOnHide,     						///< JINT (*OnHide();   					///< #03 hide view
	FuncInit,										///< JINT (*Init)();  				  	///< #05 Init event
};


