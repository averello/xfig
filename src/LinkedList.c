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

LinkedList *linkedListAppendData(LinkedList *list, void *data) {
	LinkedList *restrict ns = (LinkedList *)calloc(sizeof(LinkedList), 1);
	if (NULL == ns)
		return NULL;
	
	ns->isa = _objectPrototype;
	ns = retain(ns);
	
	ns->data = retain(data);
	ns->next = NULL;
	
	if (list == NULL) {
		list = ns;
	}
	else {
		LinkedList *tmp = list;
		while (tmp->next != NULL) {
			tmp = tmp->next;
		}
		tmp->next = ns;
	}
	return list;
}

LinkedList *deletePointList(LinkedList *list) {
	if (list == NULL) {
		return NULL;
	}
	
	while (list != NULL) {
		LinkedList *tmp = list;
		release(list->data);
		list = list->next;
		release(tmp);
		tmp = NULL;
	}
	return NULL;
}

