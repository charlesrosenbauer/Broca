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
	lnct      = 0;
	int  lnix = 0;
	int  init = 0;
	int  dark = 0;
	last = 0;
	for(int i = 0; i < fsize; i++){
		if((text[i] == '\n') && (last != text[i]) && dark){
			ls[lnix].text = malloc(sizeof(char) * (1+i-init));
			for(int j = init; j <= i; j++) ls[lnix].text[j-init] = text[j];
			ls[lnix].text[i-init] = 0;
			ls[lnix].fileId = fileId;
			ls[lnix].line   = lnix;
			lnix++;
			init = i+1;
			dark = 0;
			lnct++;
		}else if (text[i] == '\n'){
			init = i+1;
		}else if((text[i] != ' ') && (text[i] != '\t')){
			dark = 1;
		}
		last = text[i];	
	}
	
	return lnct;
}


void printLines(Line* ls, int lnct){
	char* texts[3];
	texts[LT_TEXT] = "TEXT";
	texts[LT_OPTN] = "OPTN";
	texts[LT_LOCT] = "LOCT";
	for(int i = 0; i < lnct; i++){
		printf("L%i %s: %i:%i@%i | %s\n", i, texts[ls[i].type], ls[i].line, ls[i].offset, ls[i].fileId, ls[i].text);
	}
}


int  skipWhite(Line* l, int ix){
	while(1){
		if( l->text[ix] ==  0 ) return -1;
		if((l->text[ix] != ' ') && (l->text[ix] != '\t')) return ix;
		ix++;
	}
	return 0;
}

int parseLine(Line* l){
	/*
		*			is option
		Name:		is name
		Name(pose):	is name with pose
		->			is goto
		@			is location
		#			is signal
	*/
	int ix = 0;
	ix = skipWhite(l, ix);
	l->offset = ix;
	
	if(l->text[ix] == '*'){
		// Option
		l->type = LT_OPTN;
	}else if(l->text[ix] == '@'){
		// Location
		l->type = LT_LOCT;
	}else{
		l->type = LT_TEXT;
	}
	return 1;
}
