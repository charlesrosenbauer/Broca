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
	T_WORD,
	T_OPEN,
	T_CLOSE,
	T_PERCENT,
	T_STRVAR,
	T_OPTION,
	T_OFFSET,
	T_GOTO,
	T_TAG,
	T_OR,
	T_END,
	T_ERROR
}TokenType;

typedef struct{
	char*     word;
	uint64_t  hash;
	TokenType type;
}Token;


Str* getLines   (char*, int*);
int  indentation(Str);



#endif
