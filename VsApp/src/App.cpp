/**
 * @file app.cpp
 *
 *  APP function 
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

AppType   App;
AppType * AppPtr = &App;

gboolean CallbackWindowDelete(GtkWidget *widget, GdkEvent *event, gpointer data)
{  
  return FALSE;
}

void CallbackWindowDestroy(GtkWidget *widget, GdkEvent *event, gpointer data)
{
  printf("Window Destroy ...\n");  
 	GlobalVar.bAppExit = TRUE;    
}

static void CallbackMenuItemMain(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	AppActiveViewSet(&JVForm1);
}

static void CallbackMenuItemConfig(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	AppActiveViewSet(&JVForm2);
}

static void CallbackMenuItemClose(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	GlobalVar.bAppExit = TRUE;    
}

void AppCssLoad()
{
  GdkDisplay * pGtkDisplay = NULL;
  GdkScreen  * pGtkScreen  = NULL;

  const gchar *pCssFile = "./css/jstyle.css";
  GError *error = 0;

  AppPtr->pProvider = gtk_css_provider_new();
  pGtkDisplay  					= gdk_display_get_default();
  pGtkScreen   					= gdk_display_get_default_screen(pGtkDisplay);
  gtk_style_context_add_provider_for_screen (pGtkScreen, GTK_STYLE_PROVIDER (AppPtr->pProvider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

  gtk_css_provider_load_from_file(AppPtr->pProvider, g_file_new_for_path(pCssFile), &error);
  g_object_unref(AppPtr->pProvider);
}

JINT AppWindowIconSet()
{
	GdkPixbuf *pPixbuf;
  GError *error = NULL;
  
	char strFileName[512];

	sprintf(strFileName, "%s/img/logo.png", GlobalVar.strCurDir);
	
	UtilWinPathNameSet(strFileName);
	
  pPixbuf = gdk_pixbuf_new_from_file(strFileName, &error);
     
	if(pPixbuf == NULL)
	{       
		printf("%s\n", error->message);
		g_error_free(error);
		return FALSE;
	}

  gtk_window_set_icon(GTK_WINDOW(AppPtr->pWindow), pPixbuf);
  return TRUE;  
}

void AppWindowInit()
{
  AppPtr->pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL); 
    
  gtk_widget_set_name(AppPtr->pWindow, "VsAppWindow");
  gtk_window_set_title(GTK_WINDOW(AppPtr->pWindow), APP_TITLE);

  gtk_window_set_default_size(GTK_WINDOW(AppPtr->pWindow), 1200, 720);
  gtk_window_set_position(GTK_WINDOW(AppPtr->pWindow), GTK_WIN_POS_CENTER);

	/// Box
	AppPtr->pBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_widget_show(AppPtr->pBox);  

  AppPtr->pScrollWindow =  gtk_scrolled_window_new(NULL, NULL);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (AppPtr->pScrollWindow ),   GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
  gtk_widget_set_hexpand (AppPtr->pScrollWindow , TRUE);
  gtk_widget_set_vexpand (AppPtr->pScrollWindow , TRUE);
  gtk_widget_show(AppPtr->pScrollWindow);  

  gtk_container_add(GTK_CONTAINER(AppPtr->pScrollWindow),  AppPtr->pBox);  
  gtk_container_add(GTK_CONTAINER(AppPtr->pWindow), 			 AppPtr->pScrollWindow);  

	AppWindowIconSet();
	
  gtk_widget_show(AppPtr->pWindow);

  g_signal_connect(G_OBJECT(AppPtr->pWindow), "delete_event", G_CALLBACK(CallbackWindowDelete), NULL);
  g_signal_connect(G_OBJECT(AppPtr->pWindow), "destroy",      G_CALLBACK(CallbackWindowDestroy), NULL);
}

void AppMainMenuSet(GtkWidget *pView)
{
	///-----------------------------------------------------------------------///
	///  menu
	///-----------------------------------------------------------------------///	
	GtkWidget * pMenubar  = NULL; 
	GtkWidget * pMenuFile = NULL;

/// Manu Item Root
	GtkWidget * pMenuItemRootVsApp	 = NULL;

  /// Manu Item
  GtkWidget * pMenuItemMain    	 = NULL;
  GtkWidget * pMenuItemControl   = NULL;
	GtkWidget * pMenuItemClose  	 = NULL;
  
	
	
 	pMenubar  = gtk_menu_bar_new();
  pMenuFile = gtk_menu_new();


  pMenuItemRootVsApp  = gtk_menu_item_new_with_label("VS-APP");     
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(pMenuItemRootVsApp), pMenuFile);

  pMenuItemMain				= gtk_menu_item_new_with_label("Main");
  pMenuItemControl		= gtk_menu_item_new_with_label("Control");
  pMenuItemClose 			= gtk_menu_item_new_with_label("Close");
  
  gtk_menu_shell_append(GTK_MENU_SHELL(pMenuFile), pMenuItemMain);  
  gtk_menu_shell_append(GTK_MENU_SHELL(pMenuFile), pMenuItemControl);  
	gtk_menu_shell_append(GTK_MENU_SHELL(pMenuFile), pMenuItemClose);

  g_signal_connect(G_OBJECT(pMenuItemMain),  	  "activate",   G_CALLBACK(CallbackMenuItemMain), 	  NULL);
  g_signal_connect(G_OBJECT(pMenuItemControl),  "activate",   G_CALLBACK(CallbackMenuItemConfig), 	NULL);
	g_signal_connect(G_OBJECT(pMenuItemClose),  	"activate",   G_CALLBACK(CallbackMenuItemClose), 	  NULL);

	/// increase the menu width
  gtk_widget_set_size_request(pMenuItemRootVsApp, 80, 30); 
  
  gtk_menu_shell_append(GTK_MENU_SHELL(pMenubar), pMenuItemRootVsApp);

  gtk_container_add(GTK_CONTAINER(pView), pMenubar);
  gtk_widget_show_all(pMenubar);
}

void AppActiveViewSet(JView *pView)
{
	if(AppPtr->pViewActive != NULL)
	{
		AppPtr->pViewActive->OnHide();
	}
	AppPtr->pViewActive = pView;
	AppPtr->pViewActive ->OnShow();
}

void AppInit(void)
{
	JINT i = 0;
	JView *pView = NULL;

  AppCssLoad();  
	
  AppWindowInit();
  
  ///-------------------------------------------------------///
  /// Set view
  ///-------------------------------------------------------///
  AppPtr->pViewArr[0] = &JVForm1;
  AppPtr->pViewArr[1] = &JVForm2;  

  for(i = 0 ; i < JVIEW_CNT; i = i + 1)
	{
		pView = AppPtr->pViewArr[i];		
		pView->Init();
	}
  
  AppPtr->pViewActive = NULL;  
	AppActiveViewSet(&JVForm1);
}
