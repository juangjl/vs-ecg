/**
 * @file cairo.c
 * @brief Cairo
 * @version $Revision$
 * @author JL JUANG
 * @note Copyright 2021, VitalSigns Technology CO., LTD., all rights reserved.
 * @note
*/ 

#include "Global.h"

void CairoTextOut(cairo_t *cr, JWORD x,  JWORD y, char * str)
{
	cairo_move_to(cr, x, y);
  cairo_show_text(cr, str);
}

void CairoFontSize(cairo_t *cr, JINT iSize)
{
	cairo_set_font_size(cr, iSize);
}

void CairoStrokeColor(cairo_t *cr, COLORREF color)
{
	JDOUBLE r   = (JDOUBLE)R(color) / 255.0;
	JDOUBLE g = (JDOUBLE)G(color) / 255.0;
	JDOUBLE b  = (JDOUBLE)B(color) / 255.0;

	cairo_set_source_rgb(cr, r, g, b);
}

void CairoFillColor(cairo_t *cr, COLORREF color, JDOUBLE alpha)
{
	GdkRGBA gtkColor;
	
	JDOUBLE red   = (JDOUBLE)R(color) / 255.0;
	JDOUBLE green = (JDOUBLE)G(color) / 255.0;
	JDOUBLE blue  = (JDOUBLE)B(color) / 255.0;

	gtkColor.red   = red;
	gtkColor.green = green;
	gtkColor.blue  = blue;
	gtkColor.alpha = alpha;	
	gdk_cairo_set_source_rgba(cr, &gtkColor);
}

void CairoForegroundColor(cairo_t *cr, COLORREF color, JDOUBLE alpha)
{
	GdkRGBA gtkColor;
	
	JDOUBLE red   = (JDOUBLE)R(color) / 255.0;
	JDOUBLE green = (JDOUBLE)G(color) / 255.0;
	JDOUBLE blue  = (JDOUBLE)B(color) / 255.0;

	gtkColor.red   = red;
	gtkColor.green = green;
	gtkColor.blue  = blue;
	gtkColor.alpha = alpha;	
	gdk_cairo_set_source_rgba(cr, &gtkColor);
}

void CairoTextColor(cairo_t *cr, COLORREF color)
{
	JDOUBLE r = (JDOUBLE)R(color) / 255.0;
	JDOUBLE g = (JDOUBLE)G(color) / 255.0;
	JDOUBLE b = (JDOUBLE)B(color) / 255.0;
	cairo_set_source_rgb(cr, r, g, b);
}

void CairoRectFill(cairo_t *cr, JWORD x0, JWORD y0, JWORD iWidth, JWORD iHeight)
{
	cairo_rectangle(cr, x0, y0, iWidth, iHeight);
	cairo_stroke_preserve(cr);
	cairo_fill(cr);
}

void CairoRectDraw(cairo_t *cr, JWORD x0, JWORD y0, JWORD iWidth, JWORD iHeight)
{
	cairo_rectangle(cr, x0, y0, iWidth, iHeight);
	cairo_stroke_preserve(cr);
	cairo_stroke(cr);
}

void CairoLineWidth(cairo_t *cr, JDOUBLE fWidth)
{
	cairo_set_line_width(cr, fWidth);
}

void CairoLineDraw(cairo_t *cr, JDOUBLE *x, JDOUBLE *y, JINT iPointCnt)
{
	JINT i = 0;
	for(i = 0;i < iPointCnt; i = i + 1)
	{
		if(i ==0)
		{
			cairo_move_to (cr, x[i], y[i]);
		}
		else
		{
			cairo_line_to (cr, x[i], y[i]);
		}
	}
	cairo_stroke (cr);
}

void CairoMoveTo(cairo_t *cr, JDOUBLE x0, JDOUBLE y0)
{
	cairo_move_to(cr, x0, y0);
}

void CairoLineTo(cairo_t *cr, JDOUBLE x0, JDOUBLE y0)
{
	cairo_line_to(cr, x0, y0);
}

void CairoStroke(cairo_t *cr)
{
	cairo_stroke (cr);
}

void CairoFill(cairo_t *cr)
{
	cairo_fill(cr);
}

void CairoShapeDraw(cairo_t *cr, JDOUBLE *x, JDOUBLE *y, JINT iPointCnt)
{
	JINT i = 0;
	for(i = 0;i < iPointCnt; i = i + 1)
	{
		if(i == 0)
		{
			cairo_move_to (cr, x[i], y[i]);
		}
		else
		{
			cairo_line_to (cr, x[i], y[i]);
		}
	}
  cairo_close_path(cr);
  cairo_stroke_preserve(cr);
	cairo_stroke (cr);
}

void CairoShapeFill(cairo_t *cr, JDOUBLE *x, JDOUBLE *y, JINT iPointCnt)
{
	JINT i = 0;
	for(i = 0;i < iPointCnt; i = i + 1)
	{
		if(i == 0)
		{
			cairo_move_to (cr, x[i], y[i]);
		}
		else
		{
			cairo_line_to (cr, x[i], y[i]);
		}
	}
  cairo_close_path(cr);
  cairo_stroke_preserve(cr);
	cairo_fill(cr);
}

void CairoArcDraw(cairo_t *cr, JDOUBLE x0, JDOUBLE y0,   JDOUBLE radius,  JDOUBLE angle1,  JDOUBLE angle2)
{
	cairo_arc(cr,x0, y0, radius, angle1, angle2);
  cairo_stroke_preserve(cr);
	cairo_stroke (cr);
}

void CairoArcFill(cairo_t *cr, JDOUBLE x0, JDOUBLE y0,   JDOUBLE radius,  JDOUBLE angle1,  JDOUBLE angle2)
{
	cairo_move_to(cr, x0, y0);
	cairo_arc(cr,x0, y0, radius, angle1, angle2);
  cairo_stroke_preserve(cr);
	cairo_fill (cr);
}

void CairoCircleDraw(cairo_t *cr, JDOUBLE x0, JDOUBLE y0,   JDOUBLE radius)
{
	cairo_arc(cr,x0, y0, radius, 0, 2 * G_PI);
  cairo_stroke_preserve(cr);
	cairo_stroke (cr);
}

void CairoCircleFill(cairo_t *cr, JDOUBLE x0, JDOUBLE y0,   JDOUBLE radius)
{
	cairo_arc(cr,x0, y0, radius, 0, 2 * G_PI);
  cairo_stroke_preserve(cr);
	cairo_fill (cr);
}


void CairoTriangleDraw(cairo_t *cr, JDOUBLE *x, JDOUBLE *y)
{
	JINT i = 0;
	for(i = 0;i < 3; i = i + 1)
	{
		if(i == 0)
		{
			cairo_move_to (cr, x[i], y[i]);
		}
		else
		{
			cairo_line_to (cr, x[i], y[i]);
		}
	}
  cairo_close_path(cr);
  cairo_stroke_preserve(cr);
	cairo_stroke (cr);
}

void CairoTriangleFill(cairo_t *cr, JDOUBLE *x, JDOUBLE *y)
{
	JINT i = 0;
	for(i = 0;i < 3; i = i + 1)
	{
		if(i == 0)
		{
			cairo_move_to (cr, x[i], y[i]);
		}
		else
		{
			cairo_line_to (cr, x[i], y[i]);
		}
	}
  cairo_close_path(cr);
  cairo_stroke_preserve(cr);
	cairo_fill(cr);
}
