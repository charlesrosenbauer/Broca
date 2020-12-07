#include "stdint.h"
#include "string.h"
#include "stdlib.h"
#include "stdio.h"

#include "parser.h"



int main(){
	char* text = "\n\
Hello\n\
    There\n\
        Who\n\
            Are\n\
                You?";
	
	int  linect;
	Str* lines = getLines(text, &linect);
	
	for(int i = 0; i < linect; i++){
		printf("LINE %i. SIZE: %i. LEN: %i : \"%s\"\n", i, strlen(lines[i].str), lines[i].len, lines[i].str);
	}
}
