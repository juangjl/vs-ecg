/**
 * @file FORM7.h
 *
 *  FORM7 header
 *
 * @version $Revision$
 * @author JL Juang <jl_juang@vsigntek.com>
 * @note Copyright (c) 2021,  VitalSigns Technology CO., LTD., all rights reserved.
 * @note
*/
#ifndef __FORM7_H__
#define __FORM7_H__
#include "Global.h"

#define FORM7_FRAME0_LEFT								(20)
#define FORM7_FRAME0_TOP								(50)
#define FORM7_FRAME0_WIDTH							(600)
#define FORM7_FRAME0_HEIGHT							(700)
#define FORM7_FRAME0_XGAP								(20)
#define FORM7_FRAME0_YGAP								(10)
#define FORM7_FRAME0_ROW								(30 + FORM7_FRAME0_YGAP)

#define FORM7_FRAME1_LEFT								(640)
#define FORM7_FRAME1_TOP								(50)
#define FORM7_FRAME1_WIDTH							(400)
#define FORM7_FRAME1_HEIGHT							(180)
#define FORM7_FRAME1_XGAP								(20)
#define FORM7_FRAME1_YGAP								(10)
#define FORM7_FRAME1_ROW								(30 + FORM7_FRAME1_YGAP)

#define FORM7_FRAME2_LEFT								(640)
#define FORM7_FRAME2_TOP								(250)
#define FORM7_FRAME2_WIDTH							(400)
#define FORM7_FRAME2_HEIGHT							(70)
#define FORM7_FRAME2_XGAP								(20)
#define FORM7_FRAME2_YGAP								(20)
#define FORM7_FRAME2_ROW								(30 + FORM7_FRAME2_YGAP)

#define FORM7_FRAME3_LEFT								(640)
#define FORM7_FRAME3_TOP								(340)
#define FORM7_FRAME3_WIDTH							(400)
#define FORM7_FRAME3_HEIGHT							(140)
#define FORM7_FRAME3_XGAP								(20)
#define FORM7_FRAME3_YGAP								(20)
#define FORM7_FRAME3_ROW								(30 + FORM7_FRAME3_YGAP)

#define FORM7_FRAME4_LEFT								(640)
#define FORM7_FRAME4_TOP								(500)
#define FORM7_FRAME4_WIDTH							(400)
#define FORM7_FRAME4_HEIGHT							(180)
#define FORM7_FRAME4_XGAP								(20)
#define FORM7_FRAME4_YGAP								(20)
#define FORM7_FRAME4_ROW								(30 + FORM7_FRAME4_YGAP)

#define FORM7_FRAME5_LEFT								(20)
#define FORM7_FRAME5_TOP								(610)
#define FORM7_FRAME5_WIDTH							(600)
#define FORM7_FRAME5_HEIGHT							(70)
#define FORM7_FRAME5_XGAP								(20)
#define FORM7_FRAME5_YGAP								(20)
#define FORM7_FRAME5_ROW								(30 + FORM7_FRAME4_YGAP)

typedef struct ViewDataFORM7St
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
	GtkWidget * pLabelGattScanOn;
	
	GtkWidget * pLabelGattDeviceName;	
	GtkWidget * pLabelGattDeviceMac;		
	  
	GtkWidget * pLabelGattStatus;

	///--------------------------------------------------------///
	/// Text (Entry)
	///--------------------------------------------------------///
	
	///--------------------------------------------------------///
	/// Button
	///--------------------------------------------------------///
	GtkWidget * pBtnGattScanStart;	
	GtkWidget * pBtnGattScanStop;	

	GtkWidget * pBtnGattOpen;	
	GtkWidget * pBtnGattClose;

	GtkWidget * pBtnGattVscModeStart;	
	GtkWidget * pBtnGattVscModeStop;	

	///--------------------------------------------------------///
	/// ComboBox
	///--------------------------------------------------------///	
	
	///--------------------------------------------------------///
	/// Frame (group)
	///--------------------------------------------------------///
	
	///--------------------------------------------------------///
	/// Progress bar
	///--------------------------------------------------------///

	///--------------------------------------------------------///
	/// List Box
	///--------------------------------------------------------///
	GtkWidget * pListBox1;

	///--------------------------------------------------------///
	/// canvas
	///--------------------------------------------------------///

	///--------------------------------------------------------///
	/// chart
	///--------------------------------------------------------///

} ViewDataForm7Type;

extern JINT Form7List1Update(void);

#endif ///< __FORM7_H__
