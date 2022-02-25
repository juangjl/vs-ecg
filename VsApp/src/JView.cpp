/**
 * @file serial.cpp
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

gboolean CallbackJViewDialogMessageDelete(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	printf("reponse\r\n");
  gtk_widget_destroy(GTK_WIDGET(widget));
	return TRUE;
}

void JViewButtonDisable(GtkWidget *pButton)
{
	//GtkStyleContext *context = NULL;
	//context = gtk_widget_get_style_context(pButton);	
	//gtk_style_context_add_class(context, CSS_CLASS_BUTTON_DISABLED);
	gtk_widget_set_sensitive(pButton, FALSE);
}

void JViewButtonEnable(GtkWidget *pButton)
{
	//GtkStyleContext *context = NULL;
	//context = gtk_widget_get_style_context(pButton);	
	//gtk_style_context_remove_class(context, CSS_CLASS_BUTTON_DISABLED);
	gtk_widget_set_sensitive(pButton, TRUE);		
}

JBOOL JViewDialogMessageShow(char *pMessage)
{
	GtkWidget *pDialog = NULL;
	GtkWidget *label = NULL;
	GtkWidget *content_area = NULL;

	GtkDialogFlags flags;

	// Create the widgets
	flags = GTK_DIALOG_DESTROY_WITH_PARENT;
	pDialog = gtk_dialog_new_with_buttons("Message",
	                                     	(GtkWindow *)AppPtr->pWindow,
	                                     	flags,
	                                     	"_OK",
	                                     	GTK_RESPONSE_NONE,
	                                     	NULL);
	content_area = gtk_dialog_get_content_area (GTK_DIALOG (pDialog));
	
	label = gtk_label_new (pMessage);

	g_signal_connect_swapped (pDialog,
	                         "response",
	                         G_CALLBACK (CallbackJViewDialogMessageDelete),
	                         pDialog);
  gtk_window_set_default_size(GTK_WINDOW(pDialog), 200, 120);
  
	gtk_container_add (GTK_CONTAINER (content_area), label);
	gtk_widget_show_all (pDialog);


	return TRUE;
}



