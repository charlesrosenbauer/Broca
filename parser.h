#ifndef __PARSER_HEADER__
#define __PARSER_HEADER__


#include "stdint.h"


typedef struct{
	char* text;
	int   head, size;
}ParseHead;

typedef struct{
	char* str;
	int   len;
}Str;


Str* getLines   (char*, int*);
int  indentation(Str);



#endif
