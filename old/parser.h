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



typedef enum{
	T_WORD     =  0,
	T_OPEN     =  1,
	T_CLOSE    =  2,
	T_FUNCTION =  3,
	T_PERCENT  =  4,
	T_STRVAR   =  5,
	T_OPTION   =  6,
	T_INDENT   =  7,
	T_ARROW    =  8,
	T_TAG      =  9,
	T_OR       = 10,
	T_END      = 11,
	T_ERROR    = 12
}TokenType;

typedef struct{
	char*     word;
	uint64_t  hash;
	TokenType type;
}Token;


Str*   getLines   (char*, int*);
int    indentation(Str);
Token* lineTokens (Str, int*);



#endif
