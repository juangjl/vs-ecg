/**
 * @file Form3.h
 *
 *  Form3 header
 *
 * @version $Revision$
 * @author JL Juang <jl_juang@vsigntek.com>
 * @note Copyright (c) 2021,  VitalSigns Technology CO., LTD., all rights reserved.
 * @note
*/
#ifndef __FORM3_H__
#define __FORM3_H__
#include "Global.h"

#define FORM3_FRAME0_LEFT								(20)
#define FORM3_FRAME0_TOP								(50)
#define FORM3_FRAME0_WIDTH							(600)
#define FORM3_FRAME0_HEIGHT							(640)
#define FORM3_FRAME0_XGAP								(20)
#define FORM3_FRAME0_YGAP								(10)
#define FORM3_FRAME0_ROW								(30 + FORM3_FRAME0_YGAP)

#define FORM3_FRAME1_LEFT								(640)
#define FORM3_FRAME1_TOP								(50)
#define FORM3_FRAME1_WIDTH							(400)
#define FORM3_FRAME1_HEIGHT							(180)
#define FORM3_FRAME1_XGAP								(20)
#define FORM3_FRAME1_YGAP								(10)
#define FORM3_FRAME1_ROW								(30 + FORM3_FRAME1_YGAP)

#define FORM3_FRAME2_LEFT								(640)
#define FORM3_FRAME2_TOP								(250)
#define FORM3_FRAME2_WIDTH							(400)
#define FORM3_FRAME2_HEIGHT							(70)
#define FORM3_FRAME2_XGAP								(20)
#define FORM3_FRAME2_YGAP								(20)
#define FORM3_FRAME2_ROW								(30 + FORM3_FRAME2_YGAP)

#define FORM3_FRAME3_LEFT								(640)
#define FORM3_FRAME3_TOP								(340)
#define FORM3_FRAME3_WIDTH							(400)
#define FORM3_FRAME3_HEIGHT							(140)
#define FORM3_FRAME3_XGAP								(20)
#define FORM3_FRAME3_YGAP								(20)
#define FORM3_FRAME3_ROW								(30 + FORM3_FRAME3_YGAP)

#define FORM3_FRAME4_LEFT								(640)
#define FORM3_FRAME4_TOP								(500)
#define FORM3_FRAME4_WIDTH							(400)
#define FORM3_FRAME4_HEIGHT							(180)
#define FORM3_FRAME4_XGAP								(20)
#define FORM3_FRAME4_YGAP								(20)
#define FORM3_FRAME4_ROW								(30 + FORM3_FRAME4_YGAP)

#define FORM3_FRAME5_LEFT								(20)
#define FORM3_FRAME5_TOP								(610)
#define FORM3_FRAME5_WIDTH							(600)
#define FORM3_FRAME5_HEIGHT							(70)
#define FORM3_FRAME5_XGAP								(20)
#define FORM3_FRAME5_YGAP								(20)
#define FORM3_FRAME5_ROW								(30 + FORM3_FRAME4_YGAP)

typedef struct ViewDataForm3St
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
	GtkWidget * pLabelBleScanOn;
	
	GtkWidget * pLabelBleDeviceName;	
	GtkWidget * pLabelBleDeviceMac;
			
	GtkWidget * pLabelBleModelName;	
	GtkWidget * pLabelBleVersion;	

	GtkWidget * pLabelBleStatus;
	
	///--------------------------------------------------------///
	/// Text (entry)
	///--------------------------------------------------------///
	GtkWidget * pEntrySsn;	
	
	///--------------------------------------------------------///
	/// Button
	///--------------------------------------------------------///
	GtkWidget * pBtnBleScanStart;	
	GtkWidget * pBtnBleScanStop;	

	GtkWidget * pBtnBleOpen;	
	GtkWidget * pBtnBleClose;		

	GtkWidget * pBtnVscModeStart;	
	GtkWidget * pBtnVscModeStop;		
			
	///--------------------------------------------------------///
	/// Progress bar
	///--------------------------------------------------------///
	GtkWidget *pProgressBar;
	
	///--------------------------------------------------------///
	/// List Box
	///--------------------------------------------------------///
	GtkWidget * pListBox1;

	///--------------------------------------------------------///
	/// Custom function
	///--------------------------------------------------------///

	JBOOL bScanStart;

} ViewDataForm3Type;

extern JINT Form3List1RowDeleteAll();
extern JINT Form3List1RowAdd(char *strName, JINT iRSSI, JBYTE *pbMacAddr);

#endif ///< __FORM3_H__
