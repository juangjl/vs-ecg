/**
 * @file Form5.cpp
 *
 *   Form5 function
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
#include "Form5.h"

static ViewDataForm5Type  	ViewDataForm5;

///------------------------------------------------------------------------------------///
/// Variable area
///------------------------------------------------------------------------------------///
static JView *pThis = &JVForm5;

///------------------------------------------------------------------------------------///
/// Function Area
///------------------------------------------------------------------------------------///

///------------------------------------------------------------------------------------///
/// Callback area
///------------------------------------------------------------------------------------///

///------------------------------------------------------------------------------------///
/// Form5 Function
///------------------------------------------------------------------------------------///
static JINT LabelInit(void)
{
	ViewDataForm5Type * pViewDataPtr = &ViewDataForm5;
	JINT iRet = TRUE;
	GtkWidget *pLabel 	= NULL;

	JINT x0 = 0;
	JINT y0 = 0;	
	JINT w  = 200;
	JINT h  = 30;

	
	return TRUE;
}

static JINT EntryInit(void) 
{
	ViewDataForm5Type * pViewDataPtr = &ViewDataForm5;
	JINT iRet = TRUE;
	GtkWidget *pEntry	= NULL;
	JINT x0 = 0;
	JINT y0 = 0;	
	JINT w  = 0;
	JINT h  = 0;

	
	return iRet;	
}

static JINT ButtonInit(void)
{
	ViewDataForm5Type * pViewDataPtr = &ViewDataForm5;
	JINT iRet = TRUE;
	GtkWidget *pButton 	= NULL;
	JINT x0 = 0;
	JINT y0 = 0;
	JINT w = 80;
	JINT h = 30;

	return iRet;
}

static JINT FrameInit(void)
{
	JINT iRet = TRUE;
	ViewDataForm5Type * pViewDataPtr = &ViewDataForm5;	
	GtkWidget * pFrame = NULL;  

  JINT x0 = 0;
  JINT y0 = 0;
  JINT w  = 0;
  JINT h  = 0;
	
	GtkStyleContext *pContext = NULL;

	
  return iRet;  
}

static JINT ProgressBarInit()
{
	JINT x0		 	= 0;
	JINT y0 		= 0;	
	JINT width 	= 0;
	JINT height	= 0;	
	GtkWidget * pProgressBar = NULL;
	ViewDataForm5Type * pViewDataPtr = &ViewDataForm5;	
		
  return TRUE;
}

static JINT ComboBoxInit()
{
	ViewDataForm5Type * pViewDataPtr = &ViewDataForm5;
	GtkWidget	*pComboBox = NULL;
	JINT x0 = 0;
	JINT y0 = 0;	
	
	return TRUE;
}

static JINT ImageInit(void)
{
	ViewDataForm5Type * pViewDataPtr = &ViewDataForm5;
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
	ViewDataForm5Type * pViewDataPtr = &ViewDataForm5;	
	
	//g_timeout_add(100, CallbackForm5Timer1, (gpointer)pViewDataPtr->pView);	
	//g_timeout_add(100, CallbackForm5Timer2, (gpointer)pViewDataPtr->pDrawAreaDS0);	
	
	return TRUE;
}

static JINT DrawAreaInit()
{
	JINT x0 = 0;
	JINT y0 = 0;	
	JINT wd = 0;
	JINT ht = 0;	
	GtkWidget * pDrawArea = NULL; 
	ViewDataForm5Type * pViewDataPtr = (ViewDataForm5Type *)pThis->pViewData;	

	
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
	ViewDataForm5Type * pViewDataPtr = &ViewDataForm5;	
	gtk_widget_show(pViewDataPtr->pView);
	pViewDataPtr->bShow = TRUE;	
	return TRUE;
}

static JINT FuncOnHide()
{
	ViewDataForm5Type * pViewDataPtr = &ViewDataForm5;	
	gtk_widget_hide(pViewDataPtr->pView);
	pViewDataPtr->bShow = FALSE;	
	return TRUE;
}

static JINT FuncInit()
{
	ViewDataForm5Type * pViewDataPtr = &ViewDataForm5;	

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
///   Form5 
///--------------------------------------------------------------------------------///
JView JVForm5 = 
{
	"Form5",										///< char text[32];							  ///< form name
	(void *)&ViewDataForm5,			///< void *pViewData;							///< #00 View Data	
	FuncOnShow,     						///< JINT (*OnShow)();   					///< #02 show view
	FuncOnHide,     						///< JINT (*OnHide();   					///< #03 hide view
	FuncInit,										///< JINT (*Init)();  				  	///< #05 Init event
};


