//
//  LinkedList.c
//  xfig
//
//  Created by George Boumis on 12/10/13.
//  Copyright (c) 2013 George Boumis. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"

static void _LinkedListDestroy(void *);

LinkedList *linkedListAppendData(LinkedList *list, void *data) {
	LinkedList *restrict ns = (LinkedList *)MEMORY_MANAGEMENT_ALLOC(sizeof(LinkedList));
	if (NULL == ns)
		return NULL;
	
	MEMORY_MANAGEMENT_ATTRIBUTE_SET_DEALLOC_FUNCTION(ns, _LinkedListDestroy);
	
	ns->data = retain(data);
	ns->next = NULL;
	
	if (list == NULL)
		list = ns;
	else {
		LinkedList *tmp = list;
		while (tmp->next != NULL) {
			tmp = tmp->next;
		}
		tmp->next = ns;
	}
	return list;
}

static void _LinkedListDestroy(void *l) {
	LinkedList *restrict list = l;
	if (list == NULL)
		return;

	list->data = (release(list->data), NULL);
	release(list->next);
	
	return;
}
