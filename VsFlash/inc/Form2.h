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
		
	///--------------------------------------------------------///
	/// Progress bar
	///--------------------------------------------------------///

	///--------------------------------------------------------///
	/// List Box
	///--------------------------------------------------------///

} ViewDataForm2Type;


extern JINT Form2List1RowDeleteAll(void);
extern JINT Form2List1RowAdd(char *strName, JINT iRSSI, JBYTE *pbMacAddr);

#endif ///< for __CMD_H__

