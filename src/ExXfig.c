/*
 *  ExXfig.c
 *  Via Minimization
 *
 *  Created by George Boumis on 26/03/2011.
 *  Copyright 2011 georgeboumis. All rights reserved.
 *
 */

#include "ExXfig.h"
#include"entree_sortie.h"
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

static const char *prealamble = "#FIG 3.2\nLandscape\nCenter\nMetric\nA4\n100.00\nSingle\n-2\n1200 2\n";

const static short XFIG_DEPTH = 50;
const static short XFIF_FIXED_DATA = 1;
#define XFIG_DIRECTION 1
#define XFIG_NUMBER_OF_POINTS 5
#define XFIG_TEXT_FLAG 4

static Xfig *createXfig();
static void XFwriteCycle(FILE *flux, const Xfig *cycle);
static void XFwriteEllipse(FILE *flux, const Xfig *ellipse);
static void XFwriteLine(FILE *flux, const Xfig *line);
static void XFwriteRectangle(FILE *flux, const Xfig *rectangle);
static void XFwritePolygone(FILE *flux, const Xfig *polygone);
static void XFwriteText(FILE *flux, const Xfig *text);

void cree_xfig(const char *nom){
	int * tabcol, epais, couleur;
	int x1,x2,y1,y2, diam;
	
	tabcol=(int*) calloc(sizeof(int), 16);
	
	tabcol[1]=1;  // bleu
	tabcol[2]=2;  // vert
	tabcol[3]=4;  // rouge
	tabcol[4]=5;  // magenta
	tabcol[5]=31; // gold
	tabcol[6]=24; // marron
	tabcol[7]=8;  // bleu fonce
	tabcol[8]=26; // marron clair
	tabcol[9]=6;  // jaune
	tabcol[10]=27;// rose 
	tabcol[11]=21;// magenta fonce
	tabcol[12]=12;// vert fonce

	FILE *F=fopen(nom,"w");
	fprintf(F, "%s", prealamble);
	
	epais=1;
	couleur=tabcol[3];
	x1=10; y1=20;
	x2=150; y2=20;
	diam=5;
	// Dessine deux ronds pleins noirs
	fprintf(F,"1 4 0 1 0 0 99 0 -1 0.000 1 0.0000 %d %d %d %d 2047 967 2273 967\n",x1,y1,diam,diam);
	
	fprintf(F,"1 4 0 1 0 0 99 0 -1 0.000 1 0.0000 %d %d %d %d 2047 967 2273 967\n",x2,y2,diam,diam);
	
	// Dessine un trait
	
	fprintf(F,"2 1 0 %d %d 7 100 0 -1 0.000 0 0 -1 0 0 2\n",epais, couleur );
	fprintf(F,"	 %d %d %d %d\n", x1, y1, x2, y2);
	
	fclose(F);
	
}

static Xfig *createXfig() {
	Xfig *xfig = (Xfig *)calloc(sizeof(Xfig), 1);
	if (xfig == NULL) {
		fprintf(stderr, "createXfig() : calloc FAILED!\n");
		return NULL;
	}
	return xfig;
}

/**
 * Creating a Xfig
 */

Xfig *XFcreateCycle(XFLineStyle lineStyle, short thickness, XFColor color, XFColor fillColor, XFFillStyle fillType, float dotSpace, float angle, const Point *center, short ray) {
	Xfig *cycle = createXfig();
	if (cycle == NULL) {
		fprintf(stderr, "XFcreateCycle : malloc failed\n");
		return NULL;
	}
	
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

Xfig *XFcreateEllipse(XFLineStyle lineStyle, short thickness, XFColor color, XFColor fillColor, XFFillStyle fillType, float dotSpace, float angle, const Point *center, short rayH, short rayV) {
	Xfig *ellipse = createXfig();
	if (ellipse == NULL) {
		fprintf(stderr, "XFcreateEllipse : malloc failed\n");
		return NULL;
	}
	
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

Xfig *XFcreateLine(XFLineStyle lineStyle, short thickness, XFColor color, XFColor fillColor, XFFillStyle fillType, float dotSpace, int startArrow, int endArrow, short numberOfPoints, ...) {
	Xfig *restrict line = createXfig();
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

Xfig *XFcreateRectangle(XFLineStyle lineStyle, short thickness, XFColor color, XFColor fillColor, XFFillStyle fillType, float dotSpace, Point *p1, Point *p2, Point *p3, Point *p4) {
	Xfig *rectangle = createXfig();
	if (rectangle == NULL) {
		fprintf(stderr, "XFcreateRectangle : malloc failed\n");
		return NULL;
	}	
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
	
	rectangle->list = linkedListAppendData(rectangle->list, p1);
	rectangle->list = linkedListAppendData(rectangle->list, p2);
	rectangle->list = linkedListAppendData(rectangle->list, p3);
	rectangle->list = linkedListAppendData(rectangle->list, p4);
	rectangle->list = linkedListAppendData(rectangle->list, p1);
	
	return rectangle;
}

Xfig *XFcreatePolygone(XFLineStyle lineStyle, short thickness, XFColor color, XFColor fillColor, XFFillStyle fillType, float dotSpace, ...) {
	
	Xfig *polygone = createXfig();
	if (polygone == NULL) {
		fprintf(stderr, "XFcreateLine : malloc failed\n");
		return NULL;
	}
	
	va_list list;
	Point *p = NULL;
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
	
	while ((p = va_arg(list, Point*)) != NULL) {
		polygone->list = appendPoint(polygone->list, p);
	}
		
	va_end(list);
	
	return polygone;
	
}

Xfig *XFcreateTexte(XFTextAlignement alignement, XFColor color, XFTextFont font, short fontSize, float angle, short height, short width, const Point *startPoint, const char *text) {
	Xfig *textO = createXfig();
	if (textO == NULL) {
		fprintf(stderr, "XFcreateTexte : malloc failed\n");
		return NULL;
	}
	
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
	textO->text			= strdup(text);
	textO->center		= NULL;
	
	return textO;
}

void *XFdeleteXfig(void *xf) {
	Xfig *xfig = (Xfig *)xf;
	xfig->list = deletePointList(xfig->list);
	
	if (xfig->startPoint) {
		xfig->startPoint = deletePoint(xfig->startPoint);
	}
	
	if (xfig->center) {
		xfig->center = deletePoint(xfig->center);
	}
	
	if (xfig->text) {
		free(xfig->text);
	}
	
	free(xfig);
	
	xfig = NULL;
	return NULL;
}

/**
 * Writing
 */
static void XFwriteCycle(FILE *flux, const Xfig *cycle) {
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

static void XFwriteEllipse(FILE *flux, const Xfig *ellipse) {
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

static void XFwriteLine(FILE *flux, const Xfig *line) {
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
	LinkedList *list = line->list;
	while (list != NULL) {
		fprintf(flux, "%d %d ", list->point->x, list->point->y);
		list = list->next;
	}
	fprintf(flux, "\n");
}

static void XFwriteRectangle(FILE *flux, const Xfig *rectangle) {
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
	
	PointList *list = rectangle->list;
	while (list != NULL) {
		fprintf(flux, "%d %d ", list->point->x, list->point->y);
		list = list->next;
	}
	fprintf(flux, "\n");
}

static void XFwritePolygone(FILE *flux, const Xfig *polygone) {
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
	
	PointList *list = polygone->list;
	while (list != NULL) {
		fprintf(flux, "%d %d ", list->point->x, list->point->y);
		list = list->next;
	}
	fprintf(flux, "\n");
}

static void XFwriteText(FILE *flux, const Xfig *text) {
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

void XFwrite(FILE *flux, const Xfig* xfig) {
	switch (xfig->type) {
		case XFTypeEllipse:
			switch (xfig->subtype) {
				case XFEllipseSubtypeCycle:
					XFwriteCycle(flux, xfig);
					break;
				case XFEllipseSubtypeEllipse:
					XFwriteEllipse(flux, xfig);
					break;

				default:
					break;
			}
			break;
		case XFTypeLine:
			switch (xfig->subtype) {
				case XFLineSubtypeLine:
					XFwriteLine(flux, xfig);
					break;
				case XFLineSubtypeRectangle:
					XFwriteRectangle(flux, xfig);
					break;
				case XFLineSubtypePolygone:
					XFwritePolygone(flux, xfig);
					break;
				default:
					break;
			}
			break;
		case XFTypeText:
			XFwriteText(flux, xfig);
			break;

		default:
			break;
	}
}

void XFwritePrealamble(FILE *flux) {
	fprintf(flux, "%s", prealamble);
}

void XFwriteListOfXfig(LinkedList list, FILE *flux) {
	LinkedList l = list;
	while (l != NULL) {
		Xfig *xfig = (Xfig*)l->data;
		XFwrite(flux, xfig);
		l = l->next;
	}
}

/**
 * NetList Specific Functions
 */


#define SCALE 200
#define THICKNESS 3
#define RAY 30
#define LEFT_SEGMENT_POINT(seg) createPoint(seg->point1->x * SCALE, seg->point1->y * SCALE)
#define RIGHT_SEGMENT_POINT(seg) createPoint(seg->point2->x * SCALE, seg->point2->y * SCALE)
#define VERTICE_POINT(ver) createPoint(ver->point->x * SCALE, ver->point->y * SCALE)

void XFwriteNetList(FILE *flux, const NetList *netlist) {
	int colors[] =  {
		XFColorBlack,
		XFColorBlue,
		XFColorGreen,
		XFColorCyan,
		XFColorRed,
		XFColorMagenta,
		XFColorYellow,
		XFColorBlueL1,
		XFColorBlueL2,
		XFColorBlueL3,
		XFColorBlueL4,
		XFColorGreenL1,
		XFColorGreenL2,
		XFColorGreenL3,
		XFColorCyanL1,
		XFColorCyanL2,
		XFColorCyanL3,
		XFColorRedL1,
		XFColorRedL2,
		XFColorRedL3,
		XFColorMagentaL1,
		XFColorMagentaL2,
		XFColorMagentaL3,
		XFColorBrownL1,
		XFColorBrownL2,
		XFColorBrownL3,
		XFColorPinkL1,
		XFColorPinkL2,
		XFColorPinkL3,
		XFColorGold
	};
	
	SegmentCell *sc;
	LinkedList l = NULL;
	XFColor color;
	for (sc=netlist->segments; sc; sc=sc->next) {
		color = colors[sc->segment->NumRes%30];
		
		Point *leftP = LEFT_SEGMENT_POINT(sc->segment);
		Point *rightP = RIGHT_SEGMENT_POINT(sc->segment);
		
		Xfig *leftSpoint = XFcreateCycle(XFLineStyleDefault, THICKNESS, XFColorBlack, XFColorBlack, XFFillStyleFill, 0.000f, 0.000f, leftP, RAY);
		
		Xfig *rightSpoint = XFcreateCycle(XFLineStyleDefault, THICKNESS, XFColorBlack, XFColorBlack, XFFillStyleFill, 0.000f, 0.000f, rightP, RAY);
		
		Xfig *line = XFcreateLine(XFLineStylePlain, THICKNESS, color, color, XFFillStyleNoFill, 0.000f, false, false, 2, leftP, rightP, NULL);
		
		l = insertDataInLinkedList(leftSpoint, l, NULL);
		l = insertDataInLinkedList(rightSpoint, l, NULL);
		l = insertDataInLinkedList(line, l, NULL);
		
		deletePoint(leftP);
		deletePoint(rightP);
	}
	
	XFwriteListOfXfig(l, flux);
	
	l = deleteLinkedList(l, XFdeleteXfig);
}

static Point *getPointFromVertice(Vertex *vertex) {
	Point *point = NULL;
	switch (vertex->type) {
		case VertexTypePoint:
			point = VERTICE_POINT(vertex);
			break;
		case VertexTypeSegment:
			1;
			Point *left = LEFT_SEGMENT_POINT(vertex->segment);
			Point *right = RIGHT_SEGMENT_POINT(vertex->segment);
			int x = (left->x + right->x)/2;
			int y = (left->y + right->y)/2;
			deletePoint(left);
			deletePoint(right);
			point = createPoint(x, y);
			break;
		default:
			break;
	}
	return point;
}

void XFwriteGraph(FILE *flux, const Graph *graph) {
	unsigned i=0;
	LinkedList l = NULL;
	for (i=0; i<graph->numberOfVertices; i++) {
		Vertex *vertex = graph->vertices[i];
		Xfig *xfig = NULL;
		switch (vertex->type) {
			case VertexTypePoint:
				1;
				Point *center = VERTICE_POINT(vertex);
				xfig = XFcreateCycle(XFLineStylePlain, THICKNESS, XFColorGold, XFColorGold, XFFillStyleFill, 0.000f, 0.000f, center, RAY * 2);
				deletePoint(center);
				break;
			case VertexTypeSegment:
				1;
				Point *left = LEFT_SEGMENT_POINT(vertex->segment);
				Point *right = RIGHT_SEGMENT_POINT(vertex->segment);
				Point p;
				p.x = (left->x + right->x)/2;
				p.y = (left->y + right->y)/2;
				xfig = XFcreateCycle(XFLineStylePlain, THICKNESS, XFColorGold, XFColorGold, XFFillStyleFill, 0.000f, 0.000f, &p, RAY * 2);
				deletePoint(left);
				deletePoint(right);
				break;
			default:
				break;
		}
		l = insertDataInLinkedList(xfig, l, NULL);
	}
	
	for (i=0; i<graph->numberOfEdges; i++) {
		Edge *edge = graph->edges[i];
		
		Point *leftP = getPointFromVertice(edge->vu);
		Point *rightP = getPointFromVertice(edge->vv);
		
		Xfig *xfig = XFcreateLine(XFLineStyleDefault, THICKNESS, XFColorGold, XFColorGold, XFFillStyleFill, 0.000f, false, false, 2, leftP, rightP,NULL);
		
		l = insertDataInLinkedList(xfig, l, NULL);
		
		deletePoint(leftP);
		deletePoint(rightP);
	}

	XFwriteListOfXfig(l, flux);
	
	l = deleteLinkedList(l, XFdeleteXfig);
}


void XFwriteNetlistAndGraph(FILE *flux, const NetList *netlist, const Graph *graph) {
	XFwritePrealamble(flux);
	XFwriteNetList(flux, netlist);
	XFwriteGraph(flux, graph);
}



