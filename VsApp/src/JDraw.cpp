/**
 * @file Draw.h
 * @brief draw interface
 * @version $Revision$
 * @author JL JUANG
 * @note Copyright 2021, VitalSigns Technology CO., LTD., all rights reserved.
 * @note
*/ 

#include "Global.h"

JDraw::JDraw()
{
	this->cr = NULL;
}

JDraw::JDraw(cairo_t *cr)
{
	this->cr = cr;
}

JDraw::~JDraw()
{

}

void JDraw::Set(cairo_t *cr)
{
	this->cr = cr;
}

void JDraw::TextOut(JWORD x,  JWORD y, char * str)
{
	cairo_t *cr = this->cr;
	cairo_move_to(cr, x, y);
  cairo_show_text(cr, str);
}

void JDraw::FontSize(JINT iSize)
{
	cairo_t *cr = this->cr;
	cairo_set_font_size(cr, iSize);
}

void JDraw::StrokeColor(COLORREF color)
{
	cairo_t *cr = this->cr;

	JDOUBLE r   = (JDOUBLE)R(color) / 255.0;
	JDOUBLE g = (JDOUBLE)G(color) / 255.0;
	JDOUBLE b  = (JDOUBLE)B(color) / 255.0;

	cairo_set_source_rgb(cr, r, g, b);	
}

void JDraw::FillColor(COLORREF color, JDOUBLE alpha)
{
	cairo_t *cr = this->cr;
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

void JDraw::ForegroundColor(COLORREF color, JDOUBLE alpha)
{
	cairo_t *cr = this->cr;

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

void JDraw::ForegroundColorSet(COLORREF color)
{
	this->ForegroundColor(color, 1);
}

void JDraw::TextColor(COLORREF color)
{
	cairo_t *cr = this->cr;
	
	JDOUBLE r = (JDOUBLE)R(color) / 255.0;
	JDOUBLE g = (JDOUBLE)G(color) / 255.0;
	JDOUBLE b = (JDOUBLE)B(color) / 255.0;
	
	cairo_set_source_rgb(cr, r, g, b);	
}

void JDraw::RectFill(JDOUBLE x0, JDOUBLE y0, JDOUBLE fWidth, JDOUBLE fHeight)
{
	cairo_t *cr = this->cr;

	cairo_rectangle(cr, x0, y0, fWidth, fHeight);
	cairo_stroke_preserve(cr);
	cairo_fill(cr);
}

void JDraw::RectDraw(JDOUBLE x0, JDOUBLE y0, JDOUBLE fWidth, JDOUBLE fHeight)

{
	cairo_t *cr = this->cr;

	cairo_rectangle(cr, x0, y0, fWidth, fHeight);
	cairo_stroke_preserve(cr);
	cairo_stroke(cr);
}

void JDraw::LineWidth(JDOUBLE fWidth)
{
	cairo_t *cr = this->cr;

	cairo_set_line_width(cr, fWidth);	
}

void JDraw::MoveTo(JDOUBLE x0, JDOUBLE y0)
{
	cairo_t *cr = this->cr;

	cairo_move_to(cr, x0, y0);	
}
void JDraw::LineTo(JDOUBLE x0, JDOUBLE y0)
{
	cairo_t *cr = this->cr;

	cairo_line_to(cr, x0, y0);	
}

void JDraw::LineDraw(JDOUBLE x0, JDOUBLE y0, JDOUBLE x1, JDOUBLE y1)
{
	cairo_t *cr = this->cr;
	cairo_move_to(cr, x0, y0);	
	cairo_line_to(cr, x1, y1);	
	cairo_stroke (cr);	
}

void JDraw::PathDraw(JDOUBLE *x, JDOUBLE *y, JINT iPointCnt)
{
	cairo_t *cr = this->cr;
	
	JINT i = 0;
	for(i = 0;i < iPointCnt; i = i + 1)
	{
		if(i ==0)
		{
			cairo_move_to(cr, x[i], y[i]);
		}
		else
		{
			cairo_line_to(cr, x[i], y[i]);
		}
	}
	cairo_stroke (cr);	
}

void JDraw::Stroke()
{
	cairo_t *cr = this->cr;
	
	cairo_stroke (cr);	
}
void JDraw::Fill()
{
	cairo_t *cr = this->cr;

	cairo_fill(cr);
}

void JDraw::ShapeDraw(JDOUBLE *x, JDOUBLE *y, JINT iPointCnt)
{
	cairo_t *cr = this->cr;

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
void JDraw::ShapeFill(JDOUBLE *x, JDOUBLE *y, JINT iPointCnt)
{
	cairo_t *cr = this->cr;
	
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



void JDraw::ArcDraw(JDOUBLE x0, JDOUBLE y0,   JDOUBLE radius,  JDOUBLE angle1,  JDOUBLE angle2)
{
	cairo_t *cr = this->cr;

	cairo_arc(cr,x0, y0, radius, angle1, angle2);
  cairo_stroke_preserve(cr);
	cairo_stroke (cr);	
}
void JDraw::ArcFill(JDOUBLE x0, JDOUBLE y0,   JDOUBLE radius,  JDOUBLE angle1,  JDOUBLE angle2)
{
	cairo_t *cr = this->cr;
	
	cairo_move_to(cr, x0, y0);
	cairo_arc(cr,x0, y0, radius, angle1, angle2);
  cairo_stroke_preserve(cr);
	cairo_fill (cr);	
}

void JDraw::CircleDraw(JDOUBLE x0, JDOUBLE y0,   JDOUBLE radius)
{
	cairo_t *cr = this->cr;
	
	cairo_arc(cr,x0, y0, radius, 0, 2 * G_PI);
  cairo_stroke_preserve(cr);
	cairo_stroke (cr);	
}
void JDraw::CircleFill(JDOUBLE x0, JDOUBLE y0,   JDOUBLE radius)
{
	cairo_t *cr = this->cr;

	cairo_arc(cr,x0, y0, radius, 0, 2 * G_PI);
  cairo_stroke_preserve(cr);
	cairo_fill (cr);
	
}

void JDraw::TriangleDraw(JDOUBLE *x, JDOUBLE *y)
{
	cairo_t *cr = this->cr;

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
void JDraw::TriangleFill(JDOUBLE *x, JDOUBLE *y)
{
	cairo_t *cr = this->cr;

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


