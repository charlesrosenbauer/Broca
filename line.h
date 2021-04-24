#ifndef __LINE_HEADER__
#define __LINE_HEADER__


#include "stdint.h"


typedef struct{
	// Fill this out
}Param;

typedef enum{
	LT_TEXT = 0,
	LT_OPTN = 1,
	LT_LOCT = 2
}LineType;

typedef struct{
	int      fileId, line, offset, next, parct;
	char*    text;
	Param*   pars;
	LineType type;
}Line;


int  splitLines(char*, int, int, Line**); 
void printLines(Line*, int);
int  parseLine (Line*);


#endif
