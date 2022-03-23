/**
 * @file Form1.h
 *
 *  Form1 header
 *
 * @version $Revision$
 * @author JL Juang <jl_juang@vsigntek.com>
 * @note Copyright (c) 2021,  VitalSigns Technology CO., LTD., all rights reserved.
 * @note
*/
#ifndef __FORM1_H__
#define __FORM1_H__
#include "Global.h"

#define FORM1_FRAME0_LEFT											(20)
#define FORM1_FRAME0_TOP											(50)
#define FORM1_FRAME0_WIDTH										(1000)
#define FORM1_FRAME0_HEIGHT										(150)
#define FORM1_FRAME0_XGAP											(20)
#define FORM1_FRAME0_YGAP											(20)
#define FORM1_FRAME0_ROW											(30 + FORM1_FRAME0_YGAP)

#define FORM1_FRAME1_LEFT											(20)
#define FORM1_FRAME1_TOP											(220)
#define FORM1_FRAME1_WIDTH										(1000)
#define FORM1_FRAME1_HEIGHT										(100)
#define FORM1_FRAME1_XGAP											(20)
#define FORM1_FRAME1_YGAP											(10)
#define FORM1_FRAME1_ROW											(30 + FORM1_FRAME1_YGAP)

#define FORM1_FRAME2_LEFT											(20)
#define FORM1_FRAME2_TOP											(340)
#define FORM1_FRAME2_WIDTH										(1000)
#define FORM1_FRAME2_HEIGHT										(380)
#define FORM1_FRAME2_XGAP											(20)
#define FORM1_FRAME2_YGAP											(10)
#define FORM1_FRAME2_ROW											(30 + FORM1_FRAME2_YGAP)

#define FORM1_FRAME3_LEFT											(20)
#define FORM1_FRAME3_TOP											(740)
#define FORM1_FRAME3_WIDTH										(1000)
#define FORM1_FRAME3_HEIGHT										(420)
#define FORM1_FRAME3_XGAP											(20)
#define FORM1_FRAME3_YGAP											(10)
#define FORM1_FRAME3_ROW											(30 + FORM1_FRAME3_YGAP)

#define FORM1_DRAW_AREA_DS0_LEFT							(20)
#define FORM1_DRAW_AREA_DS0_TOP								(150)
#define FORM1_DRAW_AREA_DS0_WIDTH							(1020)
#define FORM1_DRAW_AREA_DS0_HEIGHT						(400)

#define FORM1_CHART_ECG_CANVAS_LEFT						(80)
#define FORM1_CHART_ECG_CANVAS_TOP						(10)
#define FORM1_CHART_ECG_CANVAS_WIDTH					(900)
#define FORM1_CHART_ECG_CANVAS_HEIGHT					(360)

typedef struct ViewDataFORM1St
{
	JBOOL bShow;
	///--------------------------------------------------------///
	/// Window --> Box --> View(Fixed)
	///--------------------------------------------------------///
	GtkWidget *pWindow;
	GtkWidget *pView;

	///--------------------------------------------------------///
	/// Label
	///--------------------------------------------------------///
  GtkWidget * pLabelDate;
	GtkWidget * pLabelTime;
	
	GtkWidget * pLabelEcgHR;
	GtkWidget * pLabelTemp;
	GtkWidget * pLabelEcgLeadOff;	
	
	GtkWidget * pLabelGSenXNow;
	GtkWidget * pLabelGSenYNow;
	GtkWidget * pLabelGSenZNow;

	GtkWidget * pLabelBattSoc;
	GtkWidget * pLabelBattSec;

	GtkWidget * pLabelHrvSDNN;
	GtkWidget * pLabelHrvNN50;
	GtkWidget * pLabelHrvRMSSD;
	GtkWidget * pLabelHrvRR;
		
	GtkWidget * pLabelHrvVLF;
	GtkWidget * pLabelHrvLF;	
	GtkWidget * pLabelHrvHF;		
	GtkWidget * pLabelHrvLFHF;	

	GtkWidget * pLabelHrvTP;		
	GtkWidget * pLabelHrvLFTP;	
	GtkWidget * pLabelHrvHFTP;		
	  
	///--------------------------------------------------------///
	/// Text (Entry)
	///--------------------------------------------------------///
	GtkWidget * pEntryFileName;
	GtkWidget * pEntryChartEcgTime;	
	GtkWidget * pEntryChartEcgTimeTotal;	
	
	///--------------------------------------------------------///
	/// Button
	///--------------------------------------------------------///
	GtkWidget * pBtnBrowse;
	GtkWidget * pBtnGenerate;	

	GtkWidget * pBtnChartEcgReverse;		
	GtkWidget * pBtnChartEcgStop;		
	GtkWidget * pBtnChartEcgPlay;		


	GtkWidget * pBtnButton1;
	///--------------------------------------------------------///
	/// ComboBox
	///--------------------------------------------------------///	
	GtkWidget * pComboBoxSpeed;
	
	///--------------------------------------------------------///
	/// Frame (group)
	///--------------------------------------------------------///
	
	///--------------------------------------------------------///
	/// Progress bar
	///--------------------------------------------------------///
	GtkWidget 		*pProgressBar;

	///--------------------------------------------------------///
	/// canvas
	///--------------------------------------------------------///
	GtkWidget *pDrawAreaDS0;

	///--------------------------------------------------------///
	/// chart
	///--------------------------------------------------------///
	JChart ChartDS0;	
} ViewDataForm1Type;

#endif ///< __FORM1_H__
