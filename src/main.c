//
//  main.c
//  xfi
//
//  Created by George Boumis on 12/10/13.
//  Copyright (c) 2013 George Boumis. All rights reserved.
//

#include <stdio.h>
#include <assert.h>
#include "ExXfig.h"


//void (*tabular)[] = {
//	NULL
//};

typedef void(*FunctionPointer)(void);

void testPoint();
void testLinkedList();

int main(int argc, const char * argv[])
{
	FunctionPointer tests[] = {
		testPoint,
		testLinkedList
	};
	
	for (int i=0; i<sizeof(tests)/sizeof(FunctionPointer); i++) {
		tests[i]();
	}
    return 0;
}


void testPoint() {
	Point *point = createPoint(5, 5);
	assert(point != NULL);
	assert(point->isa.retainCount == 1);
	
	assert(point->x == 5);
	assert(point->y == 5);
	
	release(point);
	puts("testPoint -- successfull");
}

void testLinkedList() {
	Point *point = createPoint(2, 2);
	LinkedList *list = linkedListAppendData(NULL, point);
	assert(NULL != list);
	assert(list->isa.retainCount == 1);
	assert(point->isa.retainCount == 2);
	assert(list->data == point);
	
	list = linkedListAppendData(list, createPoint(3, 3));
	
	release(list->data);
	release(point);
	release(list);
	puts("testPoint -- successfull");
}

