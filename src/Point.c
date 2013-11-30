/*
 *  Point.c
 *  Via Minimization
 *
 *  Created by George Boumis on 04/04/2011.
 *  Copyright 2011 georgeboumis. All rights reserved.
 *
 */


#include "Point.h"
#include <stdio.h>
#include <stdlib.h>

Point *createPoint(int x, int y) {
	Point *restrict point = (Point *)calloc(sizeof(Point), 1);
	if (point == NULL)
		return NULL;
	point->isa = _objectPrototype;
	
	point->x = x;
	point->y = y;
	return point;
}

