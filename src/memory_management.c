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

struct _memory_management_attributes_internal {
	unsigned long long retainCount;
	//	pthread_mutex_t lock;
	void *(*retain)(void *);
	void (*release)(void *);
	void (*destroy)(void *);
};

struct _memory_management_attributes _objectPrototype = {
	1UL,
//	PTHREAD_MUTEX_INITIALIZER,
	retain,
	release,
	NULL
};

void *retain(void *o) {
	struct _memory_management_attributes_internal *object = (struct _memory_management_attributes_internal *)o;
	
	if (NULL == object)
		return NULL;
//	pthread_mutex_lock(&(object->lock));
	__sync_fetch_and_add(&(object->retainCount), 1);
//	pthread_mutex_unlock(&(object->lock));
	return object;
}

void release(void *o) {
	struct _memory_management_attributes_internal *object = (struct _memory_management_attributes_internal *)o;
	
	if (NULL == object)
		return;
	
//	pthread_mutex_t *lock = &(object->lock);
//	pthread_mutex_lock(lock);
	int result = __sync_fetch_and_sub(&(object->retainCount), 1);
		if ( result <= 0) {
			if (NULL != object->destroy)
				object->destroy(object);
//			pthread_mutex_unlock(lock);
			free(o);
			return;
		}
//	pthread_mutex_unlock(lock);
}

void memory_management_attributes_set_dealloc_function(void *o, void (*deallocf)(void *)) {
	struct _memory_management_attributes_internal *object = (struct _memory_management_attributes_internal *)o;
	object->destroy = deallocf;
}

unsigned long long getRetainCount(void *o) {
	struct _memory_management_attributes_internal *object = (struct _memory_management_attributes_internal *)o;
	return object->retainCount;
}
