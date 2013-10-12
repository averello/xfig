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

void test1();
void test2();

int main(int argc, const char * argv[])
{
	FunctionPointer tests[] = {
		test1,
		test2
	};
	
	for (int i=0; i<sizeof(tests)/sizeof(FunctionPointer); i++) {
		tests[i]();
	}
    return 0;
}


void test1() {
	Point *point = createPoint(5, 5);
	assert(point != NULL);
	
	assert(point->x == 5);
	assert(point->y == 5);
	
	release(point);
	puts("test1 -- successfull");
}

void test2() {
	puts("test2");
}

