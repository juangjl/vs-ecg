/*
* @file cairo.h
* @brief Cairo
* @version $Revision$
* @author JL JUANG
* @note Copyright 2021, VitalSigns Technology CO., LTD., all rights reserved.
* @note
*/ 
#ifndef __CAIRO_H__
#define __CAIRO_H__

#include "Global.h"

extern void CairoFontSize(cairo_t *cr, JINT iSize);
extern void CairoTextOut(cairo_t *cr, JWORD x,  JWORD y, char * str);


extern void CairoRectFill(cairo_t *cr, JWORD x0, JWORD y0, JWORD x1, JWORD y1);
extern void CairoRectDraw(cairo_t *cr, JWORD x0, JWORD y0, JWORD x1, JWORD y1);

extern void CairoTextColor(cairo_t *cr, COLORREF color);
extern void CairoStrokeColor(cairo_t *cr, COLORREF color);
extern void CairoFillColor(cairo_t *cr, COLORREF color, JDOUBLE alpha);
extern void CairoForegroundColor(cairo_t *cr, COLORREF color, JDOUBLE alpha);


extern void CairoLineWidth(cairo_t *cr, JDOUBLE fWidth);
extern void CairoLineDraw(cairo_t *cr, JDOUBLE *x, JDOUBLE *y, JINT iPointCnt);
extern void CairoMoveTo(cairo_t *cr, JDOUBLE x0, JDOUBLE y0);
extern void CairoLineTo(cairo_t *cr, JDOUBLE x0, JDOUBLE y0);

extern void CairoShapeDraw(cairo_t *cr, JDOUBLE *x, JDOUBLE *y, JINT iPointCnt);
extern void CairoShapeFill(cairo_t *cr, JDOUBLE *x, JDOUBLE *y, JINT iPointCnt);

extern void CairoStroke(cairo_t *cr);
extern void CairoFill(cairo_t *cr);

extern void CairoArcDraw(cairo_t *cr, JDOUBLE x0, JDOUBLE y0,   JDOUBLE radius,  JDOUBLE angle1,  JDOUBLE angle2);
extern void CairoArcFill(cairo_t *cr, JDOUBLE x0, JDOUBLE y0,   JDOUBLE radius,  JDOUBLE angle1,  JDOUBLE angle2);

extern void CairoCircleDraw(cairo_t *cr, JDOUBLE x0, JDOUBLE y0,   JDOUBLE radius);
extern void CairoCircleFill(cairo_t *cr, JDOUBLE x0, JDOUBLE y0,   JDOUBLE radius);

extern void CairoTriangleDraw(cairo_t *cr, JDOUBLE *x, JDOUBLE *y);
extern void CairoTriangleFill(cairo_t *cr, JDOUBLE *x, JDOUBLE *y);

#endif ///< __CAIRO_H__

