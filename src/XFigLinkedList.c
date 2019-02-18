//
//  LinkedList.c
//  xfig
//
//  Created by George Boumis on 12/10/13.
//  Copyright (c) 2013 George Boumis. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "XFigLinkedList.h"
#include <memory_management/memory_management.h>

static void _XFig_LinkedListDestroy(void *);

XFigLinkedList *XFigLinkedListAppendData(XFigLinkedList *list, void *data) {
	XFigLinkedList *restrict ns = (XFigLinkedList *)MEMORY_MANAGEMENT_ALLOC(sizeof(XFigLinkedList));
	if (NULL == ns) {
		return NULL;
	}
	
	MEMORY_MANAGEMENT_ATTRIBUTE_SET_DEALLOC_FUNCTION(ns, _XFig_LinkedListDestroy);
	
	ns->data = retain(data);
	ns->next = NULL;
	
	if (list == NULL) {
		list = ns;
	}
	else {
		XFigLinkedList *tmp = list;
		while (tmp->next != NULL) {
			tmp = tmp->next;
		}
		tmp->next = ns;
	}
	return list;
}

static void _XFig_LinkedListDestroy(void *l) {
	XFigLinkedList *restrict list = l;
	if (list == NULL) {
		return;
	}

	list->data = (release(list->data), NULL);
	release(list->next);
	
	return;
}
