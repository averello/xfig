/*!
 *  Point.h
 *  Via Minimization
 *
 *  Created by George Boumis on 04/04/2011.
 *  Copyright 2011 georgeboumis. All rights reserved.
 *
 */

#ifndef _POINT_
#define _POINT_

#include "memory_management.h"

typedef struct _point Point;

/*!
 * Point
 *
 * Un point du circuit peut être donnée
 * par son numéro de réseau suivi de son
 * numéro de point.
 */
struct _point {
	struct _memory_management_attributes isa; /* Memory management */
	int x, y;	/* Coordonnées du point */
};

/*
 * Point Functions
 */
Point	*createPoint(int x, int y);	/* Creates a pointer to a Point with coordinates x and y */


#endif /* _POINT_ */

