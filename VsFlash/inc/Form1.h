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

///------------------------------------------------------------------------------------------------///
/// FRAME
///------------------------------------------------------------------------------------------------///
#define FORM1_FRAME0_LEFT											(20)
#define FORM1_FRAME0_TOP											(60)
#define FORM1_FRAME0_WIDTH										(1120)
#define FORM1_FRAME0_HEIGHT										(220)
#define FORM1_FRAME0_XGAP											(30)
#define FORM1_FRAME0_YGAP											(10)
#define FORM1_FRAME0_ROW											(30 + FORM1_FRAME0_YGAP)

#define FORM1_FRAME1_LEFT											(20)
#define FORM1_FRAME1_TOP											(390)
#define FORM1_FRAME1_WIDTH										(1120)
#define FORM1_FRAME1_HEIGHT										(250)
#define FORM1_FRAME1_XGAP											(20)
#define FORM1_FRAME1_YGAP											(20)
#define FORM1_FRAME1_ROW											(30 + FORM1_FRAME1_YGAP)

///------------------------------------------------------------------------------------------------///
/// DRAW AREA
///------------------------------------------------------------------------------------------------///
#define FORM1_DRAW_AREA0_LEFT									(FORM1_FRAME1_LEFT + 20)
#define FORM1_DRAW_AREA0_TOP								  (FORM1_FRAME1_TOP + 20)
#define FORM1_DRAW_AREA0_WIDTH								(1020)
#define FORM1_DRAW_AREA0_HEIGHT								(400)

///------------------------------------------------------------------------------------------------///
/// CHART
///------------------------------------------------------------------------------------------------///
#define FORM1_CHART0_LEFT											(80)
#define FORM1_CHART0_TOP											(10)
#define FORM1_CHART0_WIDTH										(1000)
#define FORM1_CHART0_HEIGHT										(200)

///------------------------------------------------------------------------------------------------///
/// PROGRESS
///------------------------------------------------------------------------------------------------///
#define FORM1_PROGRESS_BAR_GENERATE_LEFT			(50)
#define FORM1_PROGRESS_BAR_GENERATE_TOP				(160)
#define FORM1_PROGRESS_BAR_GENERATE_WIDTH			(600)
#define FORM1_PROGRESS_BAR_GENERATE_HEIGHT		(60)


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
  GtkWidget * pLabelDFU;
	
	///--------------------------------------------------------///
	/// Text (Entry)
	///--------------------------------------------------------///	
	GtkWidget * pEntryFileName;

	///--------------------------------------------------------///
	/// Button
	///--------------------------------------------------------///
	GtkWidget * pBtnBrowse;

	GtkWidget * pBtnFlashStart;
	GtkWidget * pBtnFlashCancel;	

	///--------------------------------------------------------///
	/// Frame 
	///--------------------------------------------------------///
	
	///--------------------------------------------------------///
	/// Progress bar
	///--------------------------------------------------------///
	GtkWidget 		*pProgressBar;

	///--------------------------------------------------------///
	/// canvas
	///--------------------------------------------------------///
	
	///--------------------------------------------------------///
	/// chart
	///--------------------------------------------------------///
	
} ViewDataForm1Type;


extern void Form1LabelInfoUpdate(void);

#endif ///< for __CMD_H__

