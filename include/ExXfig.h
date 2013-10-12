/*
 *  ExXfig.h
 *  Via Minimization
 *
 *  Created by George Boumis on 26/03/2011.
 *  Copyright 2011 georgeboumis. All rights reserved.
 *
 */

#ifndef _ExXfig_
#define _ExXfig_

#include <stdio.h>
#include "Point.h"
#include "LinkedList.h"
//#include "LinkedList.h"
//#include "NetList.h"
//#include "Graph.h"

/**
 * Xfig Format (.fig)
 * Version			#FIG 3.2
 * Orientation		Landscape|Portrait
 * Justification	Center|Flush Left
 * Unit				Metric|Inches
 * Paper Size		Letter|A4|A3|...
 * Zoom Level		100.0(%)
 * Number of Pages	Single|Multiple
 * Background Color -2 (no color)
 * Resolutiom (ppi)	1200 2 ( 2 = origin is upper left corner )
 */

/**
 * Xfig Type :
 * 1	Ellipse
 * 2	Rectangle
 * 4	Text
 */
typedef enum xfig_type {
	XFTypeEllipse	=1,
	XFTypeLine		=2,
	XFTypeText		=4
} XFType;

/**
 * Xfig Line Subtypes :
 * 1	Line
 * 2	Rectangle
 * 3	Polygone
 */
typedef enum xfig_line_subtype {
	XFLineSubtypeLine		=1,
	XFLineSubtypeRectangle	=2,
	XFLineSubtypePolygone	=3
} XFLineSubtype;

/**
 * Xfig Ellipse Subtypes :
 * 2	Ellipse
 * 4	Cycle
 */
typedef enum xfig_ellipse_subtype {
	XFEllipseSubtypeEllipse	=2,
	XFEllipseSubtypeCycle	=4
} XFEllipseSubtype;

/**
 * Xfig Colors :
 * -1		default
 *  0		black
 *	1		blue
 *	2		green
 *	3		cyan
 *	4		red
 *	5		magenta
 *	6		yellow
 *	7		white
 *	8-11	blue	level
 *	12-14	green	level
 *	15-17	cyan	level
 *	18-20	red		level
 *	21-23	magenta level
 *	24-26	brown	level
 *	27-30	pink	level
 *	31		gold
 */
typedef enum xfig_color {
	XFColorDefault	= -1,
	XFColorBlack,
	XFColorBlue,
	XFColorGreen,
	XFColorCyan,
	XFColorRed,
	XFColorMagenta,
	XFColorYellow,
	XFColorWhite,
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
	XFColorPinkL4,
	XFColorGold
} XFColor;

/**
 * Xfig Line Styles :
 * -1		default
 *	0		plain
 *	1		dashed
 *	2		dotted
 *	3,4,5	combinasion of the above
 */
typedef enum xfig_line_style {
	XFLineStyleDefault	= -1,
	XFLineStylePlain,
	XFLineStyleDashed,
	XFLineStyleDotted,
	XFLineStyleC1,
	XFLineStyleC2,
	XFLineStyleC3
} XFLineStyle;

/**
 * Xfig Fill Style :
 * -1	NoFill
 *	20	Fill
 */
typedef enum xfig_fill_style {
	XFFillStyleNoFill=-1,
	XFFillStyleFill=20
} XFFillStyle;

/**
 * Xfig Text Alignement :
 * 0	Left Alignement
 * 1	Center Alignement
 * 2	Right Alignement
 */
typedef enum xfig_text_alignement {
	XFTextAlignementLeft=0,
	XFTextAlignementCenter,
	XFTextAlignementRight
} XFTextAlignement;

typedef enum xfig_latex_text_fonts {
	XFTextFontDefault=0,
	XFTextFontRoman,
	XFTextFontItalic,
	XFTextFontSansSerif,
	XFTextFontTypewriter
} XFTextFont;

typedef struct xfigObject {
	XFType type;		/*
						 * 1 ellipse
						 * 2 line
						 * 4 text
						 */
						 
	short subtype;		/*
						 * 1.2	ellipse
						 * 1.4	circle
						 * ================
						 * 2.1	broken line
						 * 2.2	rectangle
						 * 2.3	polygone
						 * ================
						 * Non existant for text
						 */
	
	XFLineStyle lineStyle;
	
	short thickness;	/* 0...999 */
	
	XFColor color;
	
	XFColor fillColor;
	
	short depth;		/* 50 */
	
	short fixedData;	/* 0 */
	
	XFFillStyle fillType;		/*
						 * -1	noFill
						 * 20	plenty and black
						 */
	
	float dotSpace;		/* 4.000 | 0.000 for a line */
	
	short fixedDatas;	/* 0 0 0 0 */
	
	/* Ellipse */
	short direction;	/* 1 */
		/* Center Coordinates */
	Point *center;
		/* Rays of the ellipse */
	short verticalRay;	
	short horizontalRay;

	/* Line */
	int endArrow;					/* 1 yes, 0 no */
	int startArrow;				/* 1 yes, 0 no */
	short numberOfPoints;			/* Number of point of the broken line (5 for rectangle) */
	
	/* Text */
	XFTextAlignement alignement;	/* 0 left, 1 center, 2 right */
	XFTextFont font;						/* 0 Times Roman */
	short fontSize;					/* 12 in general */
	float angle;					/* radians */
	short flag;						/* 4 */
	short height;					/* e.g. 90 */
	short width;					/* e.g. 90 */
		/* Coordinates */
	Point *startPoint;
	char *text;
	
	LinkedList *list;
	
} Xfig;



/*
 * Xfig Functions
 */

void cree_xfig(const char *nom);

Xfig *XFcreateCycle(XFLineStyle lineStyle,
				   short thickness,
				   XFColor color,
				   XFColor fillColor,
				   XFFillStyle fillType,
				   float dotSpace,
				   float angle,
				   const Point *center,
				   short ray);

Xfig *XFcreateEllipse(XFLineStyle lineStyle,
					short thickness,
					XFColor color,
					XFColor fillColor,
					XFFillStyle fillType,
					float dotSpace,
					float angle,
					const Point *center,
					short rayH,
					short rayV);

/*
 * The number of arguments passed in parameters in ... must be 
 * terminated by NULL and must be equal to numberOfPoints.
 */
Xfig *XFcreateLine(XFLineStyle lineStyle,
				 short thickness,
				 XFColor color,
				 XFColor fillColor,
				 XFFillStyle fillType,
				 float dotSpace,
				 int startArrow,
				 int endArrow,
				 short numberOfPoints,
				 ...);

Xfig *XFcreateRectangle(XFLineStyle lineStyle,
					  short thickness,
					  XFColor color,
					  XFColor fillColor,
					  XFFillStyle fillType,
					  float dotSpace, 
					  Point *p1,
					  Point *p2,
					  Point *p3,
					  Point *p4);

/*
 * The number of arguments passed in parameters in ... must be 
 * terminated by NULL and must be equal to numberOfPoints.
 */
Xfig *XFcreatePolygone(XFLineStyle lineStyle,
					 short thickness,
					 XFColor color,
					 XFColor fillColor,
					 XFFillStyle fillType,
					 float dotSpace, 
					 ...);

Xfig *XFcreateTexte(XFTextAlignement alignement,
				  XFColor color,
				  XFTextFont font,
				  short fontSize,
				  float angle,
				  short height,
				  short width,
				  const Point *startPoint,
				  const char *text);

void *XFdeleteXfig(void *xfig); /* Release the memory of a Xfig object */
void XFwritePrealamble(FILE *flux); /* Writes the Xfig format prealamble in the FILE* flux */
//void XFwriteListOfXfig(LinkedList list, FILE *flux); /* Writes a LinkedList containing Xfig objects to flux. */
void XFwrite(FILE *flux, const Xfig* xfig); /* Write any Xfig object to flux. */


/**
 * Project's Specific Functions
 */

/* Paints the NetList* in tje FILE *flux */
//void XFwriteNetList(FILE *flux, const NetList *netlist);

/* Paints the Graph* in tje FILE *flux */
//void XFwriteGraph(FILE *flux, const Graph *graph);

/* Paints the intersection of painting of a NetList* and a Graph* */
//void XFwriteNetlistAndGraph(FILE *flux, const NetList *netlist, const Graph *graph);

#endif

