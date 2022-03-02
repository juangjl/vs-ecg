/**
 * @file Form2.h
 *
 *  Form2 Definition
 *
 * @version $Revision$
 * @author JL Juang <jl_juang@vsigntek.com>
 * @note Copyright (c) 2021,  VitalSigns Technology CO., LTD., all rights reserved.
 * @note
*/
#ifndef __FORM2_H__
#define __FORM2_H__

#define FORM2_FRAME0_LEFT								(20)
#define FORM2_FRAME0_TOP								(50)
#define FORM2_FRAME0_WIDTH							(1020)
#define FORM2_FRAME0_HEIGHT							(150)
#define FORM2_FRAME0_XGAP								(20)
#define FORM2_FRAME0_YGAP								(20)
#define FORM2_FRAME0_ROW								(30 + FORM2_FRAME0_YGAP)

#define FORM2_FRAME1_LEFT								(20)
#define FORM2_FRAME1_TOP								(210)
#define FORM2_FRAME1_WIDTH							(545)
#define FORM2_FRAME1_HEIGHT							(640)
#define FORM2_FRAME1_XGAP								(20)
#define FORM2_FRAME1_YGAP								(20)
#define FORM2_FRAME1_ROW								(30 + FORM2_FRAME0_YGAP)

#define FORM2_FRAME2_LEFT								(580)
#define FORM2_FRAME2_TOP								(210)
#define FORM2_FRAME2_WIDTH							(460)
#define FORM2_FRAME2_HEIGHT							(220)
#define FORM2_FRAME2_XGAP								(20)
#define FORM2_FRAME2_YGAP								(20)
#define FORM2_FRAME2_ROW								(30 + FORM2_FRAME0_YGAP)

#define FORM2_FRAME3_LEFT								(580)
#define FORM2_FRAME3_TOP								(450)
#define FORM2_FRAME3_WIDTH							(460)
#define FORM2_FRAME3_HEIGHT							(120)
#define FORM2_FRAME3_XGAP								(20)
#define FORM2_FRAME3_YGAP								(20)
#define FORM2_FRAME3_ROW								(30 + FORM2_FRAME0_YGAP)

typedef struct GtkDataForm2St
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
	GtkWidget * pLabelCom;

	GtkWidget * pLabelBleScanOn;

	GtkWidget * pLabelBleDeviceName;	
	GtkWidget * pLabelBleDeviceMac;		

	GtkWidget * pLabelBleStatus;

	///--------------------------------------------------------///
	/// Entry
	///--------------------------------------------------------///
	GtkWidget * pEntryCom;	
		
	///--------------------------------------------------------///
	/// Button
	///--------------------------------------------------------///
	GtkWidget * pBtnComBrowse;	
	GtkWidget * pBtnComOpen;		
	GtkWidget * pBtnComClose;			

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

} ViewDataForm2Type;


extern JINT Form2List1RowDeleteAll(void);
extern JINT Form2List1RowAdd(char *strName, JINT iRSSI, JBYTE *pbMacAddr);

#endif ///< for __CMD_H__

