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


typedef void(*FunctionPointer)(void);

void testPoint();
void testLinkedList();
void testXfig();

int main(int argc, const char * argv[])
{
	FunctionPointer tests[] = {
		testPoint,
		testLinkedList,
		testXfig
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
	release(point);
	
	point = createPoint(3, 3);
	list = linkedListAppendData(list, point);
	release(point);

	release(list);
	puts("testLinkedList -- successfull");
}

void testXfig() {
	Xfig *xfig;
}


