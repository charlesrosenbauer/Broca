#ifndef __HASHTABLE_HEADER__
#define __HASHTABLE_HEADER__


#include "stdint.h"

typedef struct{
	uint64_t hash;
	char*    text;
}Entry;

typedef struct{
	Entry*   entries;
	int      size, fill;
}HashTable;




#endif
