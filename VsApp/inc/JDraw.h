/**
 * @file Draw.h
 * @brief Draw controller
 * @version $Revision$
 * @author JL JUANG
 * @note Copyright 2021, VitalSigns Technology CO., LTD., all rights reserved.
 * @note
*/ 
#ifndef __DRAW_H__
#define __DRAW_H__

#include "Global.h"

#define JDRAW_FONT_SMALL 		(8)
#define JDRAW_FONT_MEDIUM 	(12)
#define JDRAW_FONT_MAJOR 		(16)
#define JDRAW_FONT_BIG 			(20)
#define JDRAW_FONT_LARGE 		(24)
#define JDRAW_FONT_LARGEX		(28)

class JDraw
{
public:
	cairo_t *cr;
	JDraw(cairo_t *cr);
	JDraw();
	~JDraw();	

	void Set(cairo_t *cr);

	void TextOut(JWORD x,  JWORD y, char * str);	
	void FontSize(JINT iSize);


	void RectFill(JDOUBLE x0, JDOUBLE y0, JDOUBLE fWidth, JDOUBLE fHeight);
	void RectDraw(JDOUBLE x0, JDOUBLE y0, JDOUBLE fWidth, JDOUBLE fHeight);

	void TextColor(COLORREF color);
	void StrokeColor(COLORREF color);
	void FillColor(COLORREF color, JDOUBLE alpha);
	void ForegroundColor(COLORREF color, JDOUBLE alpha);
	void ForegroundColorSet(COLORREF color);


	void LineWidth(JDOUBLE fWidth);

	void MoveTo(JDOUBLE x0, JDOUBLE y0);
	void LineTo(JDOUBLE x0, JDOUBLE y0);
	void LineDraw(JDOUBLE x0, JDOUBLE y0, JDOUBLE x1, JDOUBLE y1);	
	void PathDraw(JDOUBLE *x, JDOUBLE *y, JINT iPointCnt);

	void ShapeDraw(JDOUBLE *x, JDOUBLE *y, JINT iPointCnt);
	void ShapeFill(JDOUBLE *x, JDOUBLE *y, JINT iPointCnt);

	void Stroke();
	void Fill();

	void ArcDraw(JDOUBLE x0, JDOUBLE y0,   JDOUBLE radius,  JDOUBLE angle1,  JDOUBLE angle2);
	void ArcFill(JDOUBLE x0, JDOUBLE y0,   JDOUBLE radius,  JDOUBLE angle1,  JDOUBLE angle2);

	void CircleDraw(JDOUBLE x0, JDOUBLE y0,   JDOUBLE radius);
	void CircleFill(JDOUBLE x0, JDOUBLE y0,   JDOUBLE radius);

	void TriangleDraw(JDOUBLE *x, JDOUBLE *y);
	void TriangleFill(JDOUBLE *x, JDOUBLE *y);
	
};

#endif ///< __DRAW_H__

