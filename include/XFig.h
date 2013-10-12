/*
 *  XFig.h
 *  Via Minimization
 *
 *  Created by George Boumis on 26/03/2011.
 *  Copyright 2011 georgeboumis. All rights reserved.
 *
 */

#ifndef _XFig_
#define _XFig_

#include "Point.h"
#include "LinkedList.h"

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
typedef enum _xfig_type {
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
typedef enum _xfig_line_subtype {
	XFLineSubtypeLine		=1,
	XFLineSubtypeRectangle	=2,
	XFLineSubtypePolygone	=3
} XFLineSubtype;

/**
 * Xfig Ellipse Subtypes :
 * 2	Ellipse
 * 4	Cycle
 */
typedef enum _xfig_ellipse_subtype {
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
typedef enum _xfig_color {
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
typedef enum _xfig_line_style {
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
typedef enum _xfig_fill_style {
	XFFillStyleNoFill=-1,
	XFFillStyleFill=20
} XFFillStyle;

/**
 * Xfig Text Alignement :
 * 0	Left Alignement
 * 1	Center Alignement
 * 2	Right Alignement
 */
typedef enum _xfig_text_alignement {
	XFTextAlignementLeft=0,
	XFTextAlignementCenter,
	XFTextAlignementRight
} XFTextAlignement;

typedef enum _xfig_latex_text_fonts {
	XFTextFontDefault=0,
	XFTextFontRoman,
	XFTextFontItalic,
	XFTextFontSansSerif,
	XFTextFontTypewriter
} XFTextFont;

struct _xfigObject {
	struct _memory_management_attributes isa;
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
	
};

typedef struct _xfigObject XFig;



/*
 * Xfig Functions
 */

XFig *XFCreateCycle(XFLineStyle lineStyle,
					short thickness,
					XFColor color,
					XFColor fillColor,
					XFFillStyle fillType,
					float dotSpace,
					float angle,
					const Point *center,
					short ray);

XFig *XFCreateEllipse(XFLineStyle lineStyle,
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
XFig *XFCreateLine(XFLineStyle lineStyle,
				   short thickness,
				   XFColor color,
				   XFColor fillColor,
				   XFFillStyle fillType,
				   float dotSpace,
				   int startArrow,
				   int endArrow,
				   short numberOfPoints,
				   ...);

XFig *XFCreateRectangle(XFLineStyle lineStyle,
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
XFig *XFCreatePolygone(XFLineStyle lineStyle,
					   short thickness,
					   XFColor color,
					   XFColor fillColor,
					   XFFillStyle fillType,
					   float dotSpace,
					   ...);

XFig *XFCreateText(XFTextAlignement alignement,
				   XFColor color,
				   XFTextFont font,
				   short fontSize,
				   float angle,
				   short height,
				   short width,
				   Point *startPoint,
				   const char *text,
				   size_t length);

void XFWritePrealamble(FILE *flux); /* Writes the Xfig format prealamble in the FILE* flux */
void XFWriteListOfXFig(LinkedList *restrict list, FILE *flux); /* Writes a LinkedList containing Xfig objects to flux. */
void XFWrite(FILE *flux, const XFig*restrict xfig); /* Write any Xfig object to flux. */

#endif

