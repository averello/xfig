/*!
 *  Point.h
 *  Via Minimization
 *
 *  Created by George Boumis on 04/04/2011.
 *  Copyright 2011 georgeboumis. All rights reserved.
 *
 */

#ifndef _XFIG_POINT_
#define _XFIG_POINT_

typedef struct _xfig_point XFigPoint;

/*!
 * Point
 *
 * Un point du circuit peut être donnée
 * par son numéro de réseau suivi de son
 * numéro de point.
 */
struct _xfig_point {
	int x, y;	/* Coordonnées du point */
};

/*
 * Point Functions
 */
XFigPoint *XFigCreatePoint(int x, int y);	/* Creates a pointer to a Point with coordinates x and y */


#endif /* _XFIG_POINT_ */

