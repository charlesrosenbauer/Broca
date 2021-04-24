#ifndef __LINE_HEADER__
#define __LINE_HEADER__


#include "stdint.h"


typedef struct{
	// Fill this out
}Param;

typedef struct{
	int    fileId, line, offset, next, parct;
	char*  text;
	Param* pars;
}Line;


int  splitLines(char*, int, int, Line**); 
void printLines(Line*, int);
int  parseLine (Line*);


#endif
