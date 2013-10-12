//
//  memory_management.c
//  xfig
//
//  Created by George Boumis on 12/10/13.
//  Copyright (c) 2013 George Boumis. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "memory_management.h"

struct _memory_management_attributes _objectPrototype = {
	0,
	PTHREAD_MUTEX_INITIALIZER,
	retain,
	release
};

void *retain(void *o) {
	struct _memory_management_attributes *object = (struct _memory_management_attributes *)o;
	
	if (NULL == object)
		return NULL;
	pthread_mutex_lock(&(object->lock));
		object->retainCount++;
	pthread_mutex_unlock(&(object->lock));
	return object;
}

void release(void *o) {
	struct _memory_management_attributes *object = (struct _memory_management_attributes *)o;
	
	if (NULL == object)
		return;
	
	pthread_mutex_lock(&(object->lock));
	if ( --(object->retainCount) <= 0) {
		if (NULL != object->destroy)
			object->destroy(object);
		else
			free(object);
	}
	pthread_mutex_unlock(&(object->lock));
}
