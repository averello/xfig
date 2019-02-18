//
//  main.c
//  xfi
//
//  Created by George Boumis on 12/10/13.
//  Copyright (c) 2013 George Boumis. All rights reserved.
//

#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include "XFig.h"
#include <memory_management/memory_management.h>


typedef void(*FunctionPointer)(void);

void testPoint(void);
void testLinkedList(void);
void testXfig(void);

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
	XFigPoint *point = XFigCreatePoint(5, 5);
	assert(point != NULL);
	assert(MEMORY_MANAGEMENT_GET_RETAIN_COUNT(point) == 1);
	
	assert(point->x == 5);
	assert(point->y == 5);
	
	release(point);
	printf("%s -- successfull\n", __FUNCTION__);
}

void testLinkedList() {
	XFigPoint *point = XFigCreatePoint(2, 2);
	XFigLinkedList *list = XFigLinkedListAppendData(NULL, point);
	assert(NULL != list);
	assert(MEMORY_MANAGEMENT_GET_RETAIN_COUNT(list) == 1);
	assert(MEMORY_MANAGEMENT_GET_RETAIN_COUNT(point) == 2);
	assert(list->data == point);
	
	release(point);
	
	point = XFigCreatePoint(3, 3);
	list = XFigLinkedListAppendData(list, point);
	release(point);

	release(list);
	printf("%s -- successfull\n", __FUNCTION__);
}

void testXfig() {
	char cwd[BUFSIZ];
	printf("%s\n" ,getcwd(cwd, sizeof(cwd)));
	FILE *xfigFile = fopen("test.fig", "w");
	assert(NULL != xfigFile);
	XFigPoint *cycleCenter = XFigCreatePoint(200, 200);
	XFig *xfig = XFCreateCycle(XFLineStyleDefault,
							   1,
							   XFColorBlack,
							   XFColorRed,
							   XFFillStyleFill,
							   0.0f,
							   0.0f,
							   cycleCenter,
							   100);

	XFWritePrealamble(xfigFile);
	XFWrite(xfigFile, xfig);

	assert(NULL != xfig);
	release(cycleCenter);
	release(xfig);
	fclose(xfigFile);
	printf("%s -- successfull\n", __FUNCTION__);
}


