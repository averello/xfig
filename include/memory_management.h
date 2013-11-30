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
	void *_opaque[8];
};

extern struct _memory_management_attributes _objectPrototype;

void memory_management_attributes_set_dealloc_function(void *, void (*deallocf)(void *));
void *retain(void *);
void release(void *);
void dealloc(void *);
unsigned long long getRetainCount(void *);


#endif
