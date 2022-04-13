/**
 * @file App.h
 *
 *  APP library
 *
 * @version $Revision$
 * @author JLJuang <jl_juang@vsigntek.com>
 * @note Copyright (c) 2021, VitalSigns Technology Co., Ltd., all rights reserved.
 * @note
*/
#ifndef __APP_H__
#define __APP_H__ 

#define APP_TITLE										"VS-APP (V1.10) - VitalSigns Technology"

#define JVIEW_IDX_FORM1       			(0)
#define JVIEW_IDX_FORM2       			(1)
#define JVIEW_IDX_FORM3       			(2)
#define JVIEW_IDX_FORM4       			(3)
#define JVIEW_IDX_FORM5       			(4)
#define JVIEW_IDX_FORM6       			(5)
#define JVIEW_IDX_FORM7       			(6)
#define JVIEW_IDX_FORM8       			(7)

#define JVIEW_IDX_END		       			(JVIEW_IDX_FORM6)
#define JVIEW_CNT  									(JVIEW_IDX_END + 1)
typedef struct AppST
{
  GtkWidget *pWindow;
  GtkWidget *pScrollWindow;  
  GtkWidget *pBox;  

  char 	strCSS[32];
  JView *pViewArr[JVIEW_CNT];  

  JView  *pViewActive;
  JView  *pViewPrevious;
	GtkCssProvider  *pProvider;  
} AppType;


extern AppType 	App;
extern AppType * AppPtr;

extern int GtkTest(); ///< for test

extern void AppCssLoad();
extern void AppInit(void);
extern void AppMainMenuSet(GtkWidget *pView);
extern void AppActiveViewSet(JView *pView);


#endif ///<  __APP_H__

