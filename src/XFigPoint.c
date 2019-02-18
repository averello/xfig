/*
 *  Point.c
 *  Via Minimization
 *
 *  Created by George Boumis on 04/04/2011.
 *  Copyright 2011 georgeboumis. All rights reserved.
 *
 */


#include "XFigPoint.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory_management/memory_management.h>

XFigPoint *XFigCreatePoint(int x, int y) {
	XFigPoint *restrict point = (XFigPoint *)MEMORY_MANAGEMENT_ALLOC(sizeof(XFigPoint));
	if (point == NULL) {
		return NULL;
	}
	
	point->x = x;
	point->y = y;
	return point;
}

