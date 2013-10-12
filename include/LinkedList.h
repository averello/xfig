//
//  LinkedList.h
//  xfig
//
//  Created by George Boumis on 12/10/13.
//  Copyright (c) 2013 George Boumis. All rights reserved.
//

#ifndef xfig_LinkedList_h
#define xfig_LinkedList_h

#include "memory_management.h"

typedef struct _linkedList LinkedList;

/*
 * PointList
 * A list of Points.
 */
struct _linkedList {
	struct _memory_management_attributes isa;
	void *data;
	LinkedList *next;
};

/*
 * PointList Functions
 */
LinkedList *linkedListAppendData(LinkedList *list, void *data);

#endif