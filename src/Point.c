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
#include <memory_management/memory_management.h>

Point *createPoint(int x, int y) {
	Point *restrict point = (Point *)MEMORY_MANAGEMENT_ALLOC(sizeof(Point));
	if (point == NULL)
		return NULL;
	
	point->x = x;
	point->y = y;
	return point;
}

