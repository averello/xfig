//
//  memory_management.h
//  xfig
//
//  Created by George Boumis on 12/10/13.
//  Copyright (c) 2013 George Boumis. All rights reserved.
//

#ifndef xfig_memory_management_h
#define xfig_memory_management_h

#define _XOPEN_SOURCE 700

#include <pthread.h>

struct _memory_management_attributes {
	unsigned long long retainCount;
	pthread_mutex_t lock;
	void *(*retain)(void *);
	void (*release)(void *);
	void (*destroy)(void *);
};

extern struct _memory_management_attributes _objectPrototype;

void *retain(void *);
void release(void *);
void destroy(void *);


#endif
