/**
 * @file Form1.h
 *
 *  Form1 Definition
 *
 * @version $Revision$
 * @author JL Juang <jl_juang@vsigntek.com>
 * @note Copyright (c) 2021,  VitalSigns Technology CO., LTD., all rights reserved.
 * @note
*/
#ifndef __FORM1_H__
#define __FORM1_H__

#define FORM1_PROGRESS_BAR_GENERATE_LEFT			(20)
#define FORM1_PROGRESS_BAR_GENERATE_TOP				(80)
#define FORM1_PROGRESS_BAR_GENERATE_WIDTH			(600)
#define FORM1_PROGRESS_BAR_GENERATE_HEIGHT		(60)

#define FORM1_DRAW_AREA_DS0_LEFT							(20)
#define FORM1_DRAW_AREA_DS0_TOP								(150)
#define FORM1_DRAW_AREA_DS0_WIDTH							(1020)
#define FORM1_DRAW_AREA_DS0_HEIGHT						(400)

#define FORM1_CHART_ECG_CANVAS_LEFT						(80)
#define FORM1_CHART_ECG_CANVAS_TOP						(10)
#define FORM1_CHART_ECG_CANVAS_WIDTH					(900)
#define FORM1_CHART_ECG_CANVAS_HEIGHT					(360)

typedef struct ViewDataForm1St
{
	JBOOL bShow;
	///--------------------------------------------------------///
	/// Window --> Box --> View(Fixed)
	///--------------------------------------------------------///
	GtkWidget * pWindow;
	GtkWidget * pView;

	///--------------------------------------------------------///
	/// Label
	///--------------------------------------------------------///
  GtkWidget * pLabelMain;
  
	///--------------------------------------------------------///
	/// Text (Entry)
	///--------------------------------------------------------///
	GtkWidget * pEntryFileName;
	GtkWidget * pEntryChartEcgTime;	
	
	///--------------------------------------------------------///
	/// Button
	///--------------------------------------------------------///
	GtkWidget * pBtnBrowse;
	GtkWidget * pBtnGenerate;	
	GtkWidget * pBtnChartEcgRun;		


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
	GtkWidget * pProgressBar;

	///--------------------------------------------------------///
	/// canvas
	///--------------------------------------------------------///
	GtkWidget * pDrawAreaDS0;

	///--------------------------------------------------------///
	/// chart
	///--------------------------------------------------------///
	
} ViewDataForm1Type;

#endif ///< for __CMD_H__

