/**
 * @file JView.cpp
 *
 *   JView frame for Window / MAC/ Linux create by JL Juang
 *
 * @version $Revision$
 * @author JLJuang <jl_juang@vsigntek.com>
 * @note Copyright (c) 2021, VitalSigns Technology Co., Ltd.,, all rights reserved.
 * @note
*/
#include "Global.h"


#ifndef __JVIEW_H__
#define __JVIEW_H__

#define CSS_CLASS_BUTTON_DISABLED			"button_disabled"

#define CSS_CLASS_LABEL_TITLE					"label_title"
#define CSS_CLASS_LABEL_VALUE					"label_value"
#define CSS_CLASS_LABEL_UNIT					"label_unit"

#define MESSAGE_BOX(x) JViewDialogMessageShow((char *)x)

typedef struct JViewST
{
	char  name[32];
	void *pViewData;						   ///< #00 View Data	
	JINT (*OnShow)(); 					///< #02 update Data save
	JINT (*OnHide)(); 					///< #03 update Data save	
	JINT (*Init)();  						///< #05 Init event
}JView;	

extern JView 	JVForm1;
extern JView 	JVForm2;

//extern JView 	JVForm3;
//extern JView 	JVForm4;
//extern JView 	JVForm5;

extern void 	JViewButtonEnable(GtkWidget *pButton);
extern void 	JViewButtonDisable(GtkWidget *pButton);
extern JBOOL 	JViewDialogMessageShow(char *pMessage);

#endif ///< __JVIEW_H__

