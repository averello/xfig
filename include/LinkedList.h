//
//  LinkedList.h
//  xfig
//
//  Created by George Boumis on 12/10/13.
//  Copyright (c) 2013 George Boumis. All rights reserved.
//

#ifndef xfig_LinkedList_h
#define xfig_LinkedList_h

typedef struct _linkedList LinkedList;

/*
 * PointList
 * A list of Points.
 */
struct _linkedList {
	void *data;
	LinkedList *next;
};

/*
 * PointList Functions
 */
LinkedList *LinkedListAppendData(LinkedList *list, void *data);

#endif
