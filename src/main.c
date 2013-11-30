//
//  main.c
//  xfi
//
//  Created by George Boumis on 12/10/13.
//  Copyright (c) 2013 George Boumis. All rights reserved.
//

#include <stdio.h>
#include <assert.h>
#include "XFig.h"


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
	assert(memory_management_get_retain_count(point) == 1);
	
	assert(point->x == 5);
	assert(point->y == 5);
	
	release(point);
	printf("%s -- successfull\n", __FUNCTION__);
}

void testLinkedList() {
	Point *point = createPoint(2, 2);
	LinkedList *list = linkedListAppendData(NULL, point);
	assert(NULL != list);
	assert(memory_management_get_retain_count(list) == 1);
	assert(memory_management_get_retain_count(point) == 2);
	assert(list->data == point);
	
	release(point);
	
	point = createPoint(3, 3);
	list = linkedListAppendData(list, point);
	release(point);

	release(list);
	printf("%s -- successfull\n", __FUNCTION__);
}

void testXfig() {
	FILE *xfigFile = fopen("test.fig", "w");
	assert(NULL != xfigFile);
	Point *cycleCenter = createPoint(200, 200);
	XFig *xfig = XFCreateCycle(XFLineStyleDefault, 1, XFColorBlack, XFColorRed, XFFillStyleFill, 0.0f, 0.0f, cycleCenter, 100);

	XFWritePrealamble(xfigFile);
	XFWrite(xfigFile, xfig);

	assert(NULL != xfig);
	release(cycleCenter);
	release(xfig);
	fclose(xfigFile);
	printf("%s -- successfull\n", __FUNCTION__);
}


