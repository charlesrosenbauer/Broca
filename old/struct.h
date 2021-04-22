#ifndef __STRUCT_HEADER__
#define __STRUCT_HEADER__


#include "stdint.h"



typedef struct{
	char* str;
	int   len;
}Text;

typedef struct{
	Text  txt;
	int   next;
}Option;

typedef struct{
	Option* opts;
	int     optct;
}Fork;




#endif
