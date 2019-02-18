//
//  LinkedList.h
//  xfig
//
//  Created by George Boumis on 12/10/13.
//  Copyright (c) 2013 George Boumis. All rights reserved.
//

#ifndef xfig_LinkedList_h
#define xfig_LinkedList_h

typedef struct _xfig_linkedList XFigLinkedList;

/*
 * PointList
 * A list of Points.
 */
struct _xfig_linkedList {
	void *data;
	XFigLinkedList *next;
};

/*
 * PointList Functions
 */
XFigLinkedList *XFigLinkedListAppendData(XFigLinkedList *list, void *data);

#endif
