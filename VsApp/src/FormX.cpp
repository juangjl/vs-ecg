/**
 * @file FormX.cpp
 *
 *   FormX function
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
#include "FormX.h"

static ViewDataFormXType  	ViewDataFormX;

///------------------------------------------------------------------------------------///
/// Variable area
///------------------------------------------------------------------------------------///
static JView *pThis = &JVFormX;

///------------------------------------------------------------------------------------///
/// Function Area
///------------------------------------------------------------------------------------///

///------------------------------------------------------------------------------------///
/// Callback area
///------------------------------------------------------------------------------------///

///------------------------------------------------------------------------------------///
/// FormX Function
///------------------------------------------------------------------------------------///
static JINT LabelInit(void)
{
	ViewDataFormXType * pViewDataPtr = &ViewDataFormX;
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
	ViewDataFormXType * pViewDataPtr = &ViewDataFormX;
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
	ViewDataFormXType * pViewDataPtr = &ViewDataFormX;
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
	ViewDataFormXType * pViewDataPtr = &ViewDataFormX;	
	GtkWidget * pFrame = NULL;  

  JINT x0 = 0;
  JINT y0 = 0;
  JINT w  = 0;
  JINT h  = 0;
	
	GtkStyleContext *pContent = NULL;

	
  return iRet;  
}

static JINT ProgressBarInit()
{
	JINT x0		 	= 0;
	JINT y0 		= 0;	
	JINT width 	= 0;
	JINT height	= 0;	
	GtkWidget * pProgressBar = NULL;
	ViewDataFormXType * pViewDataPtr = &ViewDataFormX;	
		
  return TRUE;
}

static JINT ComboBoxInit()
{
	ViewDataFormXType * pViewDataPtr = &ViewDataFormX;
	GtkWidget	*pComboBox = NULL;
	JINT x0 = 0;
	JINT y0 = 0;	
	
	return TRUE;
}

static JINT ImageInit(void)
{
	ViewDataFormXType * pViewDataPtr = &ViewDataFormX;
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
	ViewDataFormXType * pViewDataPtr = &ViewDataFormX;	
	
	//g_timeout_add(100, CallbackFormXTimer1, (gpointer)pViewDataPtr->pView);	
	//g_timeout_add(100, CallbackFormXTimer2, (gpointer)pViewDataPtr->pDrawAreaDS0);	
	
	return TRUE;
}

static JINT DrawAreaInit()
{
	JINT x0 = 0;
	JINT y0 = 0;	
	JINT wd = 0;
	JINT ht = 0;	
	GtkWidget * pDrawArea = NULL; 
	ViewDataFormXType * pViewDataPtr = (ViewDataFormXType *)pThis->pViewData;	

	
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
	ViewDataFormXType * pViewDataPtr = &ViewDataFormX;	
	gtk_widget_show(pViewDataPtr->pView);
	pViewDataPtr->bShow = TRUE;	
	return TRUE;
}

static JINT FuncOnHide()
{
	ViewDataFormXType * pViewDataPtr = &ViewDataFormX;	
	gtk_widget_hide(pViewDataPtr->pView);
	pViewDataPtr->bShow = FALSE;	
	return TRUE;
}

static JINT FuncInit()
{
	ViewDataFormXType * pViewDataPtr = &ViewDataFormX;	

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
///   FormX 
///--------------------------------------------------------------------------------///
JView JVFormX = 
{
	"FormX",										///< char text[32];							  ///< form name
	(void *)&ViewDataFormX,			///< void *pViewData;							///< #00 View Data	
	FuncOnShow,     						///< JINT (*OnShow)();   					///< #02 show view
	FuncOnHide,     						///< JINT (*OnHide();   					///< #03 hide view
	FuncInit,										///< JINT (*Init)();  				  	///< #05 Init event
};


