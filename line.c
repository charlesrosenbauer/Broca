#include "stdint.h"
#include "stdlib.h"
#include "stdio.h"
#include "line.h"



int splitLines(char* text, int fsize, int fileId, Line** lines){
	int  lnct = 0;
	char last = 0;
	for(int i = 0; i < fsize; i++){
		lnct += ((text[i] == '\n') && (last != text[i]));
		last  =   text[i];
	}
	
	*lines    = malloc(sizeof(Line) * lnct);
	Line* ls  = *lines;
	int  lnix = 0;
	int  init = 0;
	last = 0;
	for(int i = 0; i < fsize; i++){
		if((text[i] == '\n') && (last != text[i])){
			ls[lnix].text = malloc(sizeof(char) * (1+i-init));
			for(int j = init; j <= i; j++) ls[lnix].text[j-init] = text[j];
			ls[lnix].text[i-init] = 0;
			ls[lnix].fileId = fileId;
			ls[lnix].line   = lnix;
			lnix++;
			init = i;
		}
	}
	
	return lnct;
}


void printLines(Line* ls, int lnct){
	for(int i = 0; i < lnct; i++){
		printf("L%i: %i@%i | %s\n", i, ls[i].line, ls[i].fileId, ls[i].text);
	}
}
