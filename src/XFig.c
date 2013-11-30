/*
 *  XFig.c
 *  Via Minimization
 *
 *  Created by George Boumis on 26/03/2011.
 *  Copyright 2011 georgeboumis. All rights reserved.
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "XFig.h"

static const char *const __prealamble = "#FIG 3.2\nLandscape\nCenter\nMetric\nA4\n100.00\nSingle\n-2\n1200 2\n";

static const short XFIG_DEPTH = 50;
static const short XFIF_FIXED_DATA = 1;
#define XFIG_DIRECTION 1
#define XFIG_NUMBER_OF_POINTS 5
#define XFIG_TEXT_FLAG 4

static XFig *__createXFig();

static void XFDeleteXFig(void *xf);
static void XFWriteCycle(FILE *flux, const XFig *restrict cycle);
static void XFWriteEllipse(FILE *flux, const XFig *restrict ellipse);
static void XFWriteLine(FILE *flux, const XFig *restrict line);
static void XFWriteRectangle(FILE *flux, const XFig *restrict rectangle);
static void XFWritePolygone(FILE *flux, const XFig *restrict polygone);
static void XFWriteText(FILE *flux, const XFig *restrict text);
static void XFWriteLinkedListOfPoints(FILE *flux, const LinkedList *restrict l);

//void cree_xfig(const char *nom){
//	int * tabcol, epais, couleur;
//	int x1,x2,y1,y2, diam;
//	
//	tabcol=(int*) calloc(sizeof(int), 16);
//	
//	tabcol[1]=1;  // bleu
//	tabcol[2]=2;  // vert
//	tabcol[3]=4;  // rouge
//	tabcol[4]=5;  // magenta
//	tabcol[5]=31; // gold
//	tabcol[6]=24; // marron
//	tabcol[7]=8;  // bleu fonce
//	tabcol[8]=26; // marron clair
//	tabcol[9]=6;  // jaune
//	tabcol[10]=27;// rose 
//	tabcol[11]=21;// magenta fonce
//	tabcol[12]=12;// vert fonce
//
//	FILE *F=fopen(nom,"w");
//	fprintf(F, "%s", __prealamble);
//	
//	epais=1;
//	couleur=tabcol[3];
//	x1=10; y1=20;
//	x2=150; y2=20;
//	diam=5;
//	// Dessine deux ronds pleins noirs
//	fprintf(F,"1 4 0 1 0 0 99 0 -1 0.000 1 0.0000 %d %d %d %d 2047 967 2273 967\n",x1,y1,diam,diam);
//	
//	fprintf(F,"1 4 0 1 0 0 99 0 -1 0.000 1 0.0000 %d %d %d %d 2047 967 2273 967\n",x2,y2,diam,diam);
//	
//	// Dessine un trait
//	
//	fprintf(F,"2 1 0 %d %d 7 100 0 -1 0.000 0 0 -1 0 0 2\n",epais, couleur );
//	fprintf(F,"	 %d %d %d %d\n", x1, y1, x2, y2);
//	
//	fclose(F);
//	
//}

static XFig *__createXFig() {
	XFig *restrict xfig = calloc(sizeof(XFig), 1);
	if (xfig == NULL)
		return NULL;
	xfig->isa = _objectPrototype;
	memory_management_attributes_set_dealloc_function(&(xfig->isa), XFDeleteXFig);
//	xfig->isa.destroy = XFDeleteXFig;
	return xfig;

}

static void XFDeleteXFig(void *xf) {
	XFig *xfig = (XFig *)xf;
	xfig->list = (release(xfig->list), NULL);
	
	if (xfig->startPoint)
		xfig->startPoint = (release(xfig->startPoint), NULL);
	
	if (xfig->center)
		xfig->center = (release(xfig->center), NULL);
	
	if (xfig->text)
		free(xfig->text);
}

/*
 * Creating a XFig
 */

XFig *XFCreateCycle(XFLineStyle lineStyle, short thickness, XFColor color, XFColor fillColor, XFFillStyle fillType, float dotSpace, float angle, const Point *center, short ray) {
	XFig *restrict cycle = __createXFig();
	if (cycle == NULL)
		return NULL;
	
	cycle->type				= XFTypeEllipse;
	cycle->subtype			= XFEllipseSubtypeCycle;
	cycle->lineStyle		= lineStyle;
	cycle->thickness		= thickness;
	cycle->color			= color;
	cycle->fillColor		= fillColor;
	cycle->depth			= XFIG_DEPTH;
	cycle->fixedData		= XFIF_FIXED_DATA;
	cycle->fillType			= fillType;
	cycle->dotSpace			= dotSpace;
	cycle->direction		= XFIG_DIRECTION;
	cycle->angle			= angle;
	cycle->center			= createPoint(center->x, center->y);
	cycle->verticalRay		= ray;
	cycle->horizontalRay	= ray;
	cycle->list				= NULL;
	cycle->text				= NULL;
	
	return cycle;
	
}

XFig *XFCreateEllipse(XFLineStyle lineStyle, short thickness, XFColor color, XFColor fillColor, XFFillStyle fillType, float dotSpace, float angle, const Point *center, short rayH, short rayV) {
	XFig *restrict ellipse = __createXFig();
	if (ellipse == NULL)
		return NULL;
	
	ellipse->type			= XFTypeEllipse;
	ellipse->subtype		= XFEllipseSubtypeEllipse;
	ellipse->lineStyle		= lineStyle;
	ellipse->thickness		= thickness;
	ellipse->color			= color;
	ellipse->fillColor		= fillColor;
	ellipse->depth			= XFIG_DEPTH;
	ellipse->fixedData		= XFIF_FIXED_DATA;
	ellipse->fillType		= fillType;
	ellipse->dotSpace		= dotSpace;
	ellipse->direction		= XFIG_DIRECTION;
	ellipse->angle			= angle;
	ellipse->center			= createPoint(center->x, center->y);
	ellipse->verticalRay	= rayV;
	ellipse->horizontalRay	= rayH;
	ellipse->list			= NULL;
	ellipse->startPoint		= NULL;
	ellipse->text			= NULL;
	
	return ellipse;
}

XFig *XFCreateLine(XFLineStyle lineStyle, short thickness, XFColor color, XFColor fillColor, XFFillStyle fillType, float dotSpace, int startArrow, int endArrow, short numberOfPoints, ...) {
	XFig *restrict line = __createXFig();
	if (line == NULL)
		return NULL;
	
	va_list list;
	Point *restrict p = NULL;
	va_start(list, numberOfPoints);

	line->type				= XFTypeLine;
	line->subtype			= XFLineSubtypeLine;
	line->lineStyle			= lineStyle;
	line->thickness			= thickness;
	line->color				= color;
	line->fillColor			= fillColor;
	line->depth				= XFIG_DEPTH;
	line->fixedData			= XFIF_FIXED_DATA;
	line->fillType			= fillType;
	line->dotSpace			= dotSpace;
	line->startArrow		= startArrow;
	line->endArrow			= endArrow;
	line->numberOfPoints	= numberOfPoints;
	line->text				= NULL;
	line->list				= NULL;

	
	while ((p = va_arg(list, Point*)) != NULL)
		line->list = linkedListAppendData(line->list, p);
	
	va_end(list);
	
	return line;
}

XFig *XFCreateRectangle(XFLineStyle lineStyle, short thickness, XFColor color, XFColor fillColor, XFFillStyle fillType, float dotSpace, Point *p1, Point *p2, Point *p3, Point *p4) {
	XFig *restrict rectangle = __createXFig();
	if (rectangle == NULL)
		return NULL;
	
	rectangle->type				= XFTypeLine;
	rectangle->subtype			= XFLineSubtypeRectangle;
	rectangle->lineStyle		= lineStyle;
	rectangle->thickness		= thickness;
	rectangle->color			= color;
	rectangle->fillColor		= fillColor;
	rectangle->depth			= XFIG_DEPTH;
	rectangle->fixedData		= XFIF_FIXED_DATA;
	rectangle->fillType			= fillType;
	rectangle->dotSpace			= dotSpace;
	rectangle->startArrow		= 0;
	rectangle->endArrow			= 0;
	rectangle->numberOfPoints	= XFIG_NUMBER_OF_POINTS;
	rectangle->fixedData		= 0;
	rectangle->center			= NULL;
	rectangle->startPoint		= NULL;
	rectangle->list				= NULL;
	rectangle->text				= NULL;
	
	Point *point1 = createPoint(p1->x, p1->y), *point2 = createPoint(p2->x, p2->y), *point3 = createPoint(p3->x, p3->y), *point4 = createPoint(p4->x, p4->y);
	rectangle->list = linkedListAppendData(rectangle->list, point1);
	rectangle->list = linkedListAppendData(rectangle->list, point2);
	rectangle->list = linkedListAppendData(rectangle->list, point3);
	rectangle->list = linkedListAppendData(rectangle->list, point4);
	rectangle->list = linkedListAppendData(rectangle->list, point1);

	release(point1), release(point2), release(point3), release(point4);
	
	return rectangle;
}

XFig *XFCreatePolygone(XFLineStyle lineStyle, short thickness, XFColor color, XFColor fillColor, XFFillStyle fillType, float dotSpace, ...) {
	
	XFig *restrict polygone = __createXFig();
	if (polygone == NULL)
		return NULL;
	
	va_list list;
	Point *restrict p = NULL;
	va_start(list, dotSpace);
	
	polygone->type				= XFTypeLine;
	polygone->subtype			= XFLineSubtypePolygone;
	polygone->lineStyle			= lineStyle;
	polygone->thickness			= thickness;
	polygone->color				= color;
	polygone->fillColor			= fillColor;
	polygone->depth				= XFIG_DEPTH;
	polygone->fixedData			= XFIF_FIXED_DATA;
	polygone->fillType			= fillType;
	polygone->dotSpace			= dotSpace;
	polygone->startArrow		= 0;
	polygone->endArrow			= 0;
	polygone->numberOfPoints	= XFIG_NUMBER_OF_POINTS;
	polygone->center			= NULL;
	polygone->startPoint		= NULL;
	polygone->list				= NULL;
	polygone->text				= NULL;
	
	while ((p = va_arg(list, Point*)) != NULL)
		polygone->list = linkedListAppendData(polygone->list, p);
		
	va_end(list);
	
	return polygone;
	
}

XFig *XFCreateText(XFTextAlignement alignement, XFColor color, XFTextFont font, short fontSize, float angle, short height, short width, Point *startPoint, const char *text, size_t length) {
	XFig *restrict textO = __createXFig();
	if (textO == NULL)
		return NULL;
	
	textO->type			= XFTypeText;
	textO->alignement	= alignement;
	textO->color		= color;
	textO->depth		= XFIG_DEPTH;
	textO->fixedData	= XFIF_FIXED_DATA;
	textO->font			= font;
	textO->fontSize		= fontSize;
	textO->angle		= angle;
	textO->flag			= XFIG_TEXT_FLAG;
	textO->height		= height;
	textO->width		= width;
	textO->startPoint	= createPoint(startPoint->x, startPoint->y);
	textO->text			= strndup(text, length);
	textO->center		= NULL;
	
	return textO;
}


/*
 * Writing
 */
static void XFWriteCycle(FILE *flux, const XFig *restrict cycle) {
	fprintf(flux, "%u %hd %d %hd %d %d %hd %hd %d %0.3f %hd %0.3f %d %d %hd %hd 0 0 0 0\n", 
			cycle->type,
			cycle->subtype,
			cycle->lineStyle,
			cycle->thickness,
			cycle->color,
			cycle->fillColor,
			cycle->depth,
			cycle->fixedData,
			cycle->fillType,
			cycle->dotSpace,
			cycle->direction,
			cycle->angle,
			cycle->center->x,
			cycle->center->y,
			cycle->verticalRay,
			cycle->horizontalRay
			);
}

static void XFWriteEllipse(FILE *flux, const XFig *restrict ellipse) {
	fprintf(flux, "%u %hd %d %hd %d %d %hd %hd %d %0.3f %hd %0.3f %d %d %hd %hd 0 0 0 0\n", 
			ellipse->type,
			ellipse->subtype,
			ellipse->lineStyle,
			ellipse->thickness,
			ellipse->color,
			ellipse->fillColor,
			ellipse->depth,
			ellipse->fixedData,
			ellipse->fillType,
			ellipse->dotSpace,
			ellipse->direction,
			ellipse->angle,
			ellipse->center->x,
			ellipse->center->y,
			ellipse->verticalRay,
			ellipse->horizontalRay
			);
}

static void XFWriteLine(FILE *flux, const XFig *restrict line) {
	fprintf(flux, "%u %hd %d %hd %d %d %hd %hd %d %0.3f 0 0 -1 %u %u %hd\n",
			line->type,
			line->subtype,
			line->lineStyle,
			line->thickness,
			line->color,
			line->fillColor,
			line->depth,
			line->fixedData,
			line->fillType,
			line->dotSpace,
			line->startArrow,
			line->endArrow,
			line->numberOfPoints);
	
	if (line->startArrow) {
		fprintf(flux, "        ");
		fprintf(flux, "1 1 2.00 120.00 240.00");
		fprintf(flux, "\n");
	}
	
	if (line->endArrow) {
		fprintf(flux, "        ");
		fprintf(flux, "1 1 2.00 120.00 240.00");
		fprintf(flux, "\n");
	}
	
	fprintf(flux, "         ");
	XFWriteLinkedListOfPoints(flux, line->list);
	fprintf(flux, "\n");
}

static void XFWriteRectangle(FILE *flux, const XFig *restrict rectangle) {
	fprintf(flux, "%u %hd %d %hd %d %d %hd %hd %d %0.3f 0 0 -1 %u %u %hd\n         ",
			rectangle->type,
			rectangle->subtype,
			rectangle->lineStyle,
			rectangle->thickness,
			rectangle->color,
			rectangle->fillColor,
			rectangle->depth,
			rectangle->fixedData,
			rectangle->fillType,
			rectangle->dotSpace,
			rectangle->startArrow,
			rectangle->endArrow,
			rectangle->numberOfPoints);
	
	LinkedList *list = rectangle->list;
	while (list != NULL) {
		Point *restrict point = list->data;
		fprintf(flux, "%d %d ", point->x, point->y);
		list = list->next;
	}
	fprintf(flux, "\n");
}

static void XFWritePolygone(FILE *flux, const XFig *restrict polygone) {
	fprintf(flux, "%u %hd %d %hd %d %d %hd %hd %d %0.3f 0 0 -1 %u %u %hd\n         ",
			polygone->type,
			polygone->subtype,
			polygone->lineStyle,
			polygone->thickness,
			polygone->color,
			polygone->fillColor,
			polygone->depth,
			polygone->fixedData,
			polygone->fillType,
			polygone->dotSpace,
			polygone->startArrow,
			polygone->endArrow,
			polygone->numberOfPoints);
	
	XFWriteLinkedListOfPoints(flux, polygone->list);
	fprintf(flux, "\n");
}

static void XFWriteText(FILE *flux, const XFig *restrict text) {
	fprintf(flux, "%u %d %d %hd %hd %d %hd %0.3f %hd %hd %hd %d %d %s\\001\n",
			text->type,
			text->alignement,
			text->color,
			text->depth,
			text->fixedData,
			text->font,
			text->fontSize,
			text->angle,
			text->flag,
			text->height,
			text->width,
			text->startPoint->x,
			text->startPoint->y,
			text->text);
}

static void XFWriteLinkedListOfPoints(FILE *flux, const LinkedList *restrict l) {
	const LinkedList *restrict list = l;
	while (list != NULL) {
		Point *restrict point = list->data;
		fprintf(flux, "%d %d ", point->x, point->y);
		list = list->next;
	}
}

/*
 * Public API
 */

void XFWrite(FILE *flux, const XFig*restrict xfig) {
	switch (xfig->type) {
		case XFTypeEllipse:
			switch (xfig->subtype) {
				case XFEllipseSubtypeCycle:
					XFWriteCycle(flux, xfig);
					break;
				case XFEllipseSubtypeEllipse:
					XFWriteEllipse(flux, xfig);
					break;

				default:
					break;
			}
			break;
		case XFTypeLine:
			switch (xfig->subtype) {
				case XFLineSubtypeLine:
					XFWriteLine(flux, xfig);
					break;
				case XFLineSubtypeRectangle:
					XFWriteRectangle(flux, xfig);
					break;
				case XFLineSubtypePolygone:
					XFWritePolygone(flux, xfig);
					break;
				default:
					break;
			}
			break;
		case XFTypeText:
			XFWriteText(flux, xfig);
			break;

		default:
			break;
	}
}

void XFWritePrealamble(FILE *flux) {
	fprintf(flux, "%s", __prealamble);
}

void XFWriteListOfXFig(LinkedList *restrict list, FILE *flux) {
	LinkedList *restrict l = list;
	while (l != NULL) {
		XFig *xfig = l->data;
		XFWrite(flux, xfig);
		l = l->next;
	}
}

