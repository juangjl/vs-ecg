/**
 * @file form1.cpp
 *
 *   View function
 *
 * @version $Revision$
 * @author JLJuang <jl_juang@vsigntek.com>
 * @note Copyright (c) 2021, VitalSigns Technology Co., Ltd.,, all rights reserved.
 * @note
*/
///------------------------------------------///
///  Include Area
///------------------------------------------///
#include "Global.h"
#include "Form1.h"

ViewDataForm1Type  	ViewDataForm1;

///------------------------------------------------------------------------------------///
/// Variable area
///------------------------------------------------------------------------------------///
static JView *pThis = &JVForm1;

///------------------------------------------------------------------------------------///
/// Callback area
///------------------------------------------------------------------------------------///

///------------------------------------------------------------------------------------///
/// Form1 Function
///------------------------------------------------------------------------------------///
static JINT LabelInit(void)
{
	ViewDataForm1Type * pViewDataPtr = &ViewDataForm1;
	JINT iRet = TRUE;
	GtkWidget *pLabel 	= NULL;

	///-----------------------------------------------------------------------///
	/// Label main
	///-----------------------------------------------------------------------///
	pViewDataPtr->pLabelMain =gtk_label_new_with_mnemonic("Label1");
	pLabel = pViewDataPtr->pLabelMain;
  gtk_widget_set_name(pLabel, "");  
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pLabel, 20, 50);
  gtk_widget_show(pLabel);
 

	return TRUE;
}

static JINT EntryInit(void) 
{
	ViewDataForm1Type * pViewDataPtr = &ViewDataForm1;
	JINT iRet = TRUE;
	GtkWidget *pEntry 	= NULL;
	JINT x0 = 0;
	JINT y0 = 0;	

	return iRet;	
}

static JINT ButtonInit(void)
{
	ViewDataForm1Type * pViewDataPtr = &ViewDataForm1;
	JINT iRet = TRUE;
	GtkWidget *pButton 	= NULL;
	JINT x0 = 0;
	JINT y0 = 0;

	
	return iRet;
}

static JINT FrameInit(void)
{
	JINT iRet = TRUE;
	ViewDataForm1Type * pViewDataPtr = &ViewDataForm1;	
  GtkWidget * pFrame = gtk_frame_new ("");
  
  gtk_frame_set_shadow_type (GTK_FRAME (pFrame), GTK_SHADOW_ETCHED_IN);
  gtk_frame_set_label_align (GTK_FRAME (pFrame), 0, 0.5);
  gtk_widget_set_size_request(pFrame, 600, 120); 
  gtk_fixed_put(GTK_FIXED(pViewDataPtr->pView), pFrame, 10, 10);
  gtk_widget_show(pFrame);

  return iRet;  
}


static JINT TimerInit()
{
	ViewDataForm1Type * pViewDataPtr = &ViewDataForm1;	
		
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
	ViewDataForm1Type * pViewDataPtr = &ViewDataForm1;	
	gtk_widget_show(pViewDataPtr->pView);
	pViewDataPtr->bShow = TRUE;
	printf("%s show\r\n", pThis->name);
	return TRUE;
}

static JINT FuncOnHide()
{
	ViewDataForm1Type * pViewDataPtr = &ViewDataForm1;	
	gtk_widget_hide(pViewDataPtr->pView);
	pViewDataPtr->bShow = FALSE;
	printf("%s hide\r\n", pThis->name);
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


