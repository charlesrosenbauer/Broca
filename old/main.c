#include "stdint.h"
#include "string.h"
#include "stdlib.h"
#include "stdio.h"

#include "parser.h"
#include "struct.h"




void loadFile(char* fname, char** buffer, int* fsize){
  FILE*  pFile = fopen (fname,"r");
  size_t result;
  if (pFile == NULL){ printf("Cannot locate script file."); exit(1); }
  fseek (pFile , 0 , SEEK_END);
  *fsize = ftell (pFile);
  rewind (pFile);

  // allocate memory to contain the whole file:
  *buffer = malloc (sizeof(uint8_t)*(*fsize));
  if (buffer == NULL) { printf("Memory error",stderr); exit(2); }

  // copy the file into the buffer:
  result = fread (*buffer,1,(*fsize),pFile);
  if (result != (*fsize)) { printf("Reading error",stderr); exit(3); }

  fclose(pFile);
}


int main(){
	char* text;
	int   fsize;
	loadFile("script.pen", &text, &fsize);
	
	int  linect;
	Str* lines  = getLines(text, &linect);
	Token** tks = malloc(sizeof(Token*) * linect);
	int*  tcts  = malloc(sizeof(int)    * linect);
	
	for(int i = 0; i < linect; i++){
		tks[i] = lineTokens(lines[i], &tcts[i]);
		for(int j = 0; j < tcts[i]; j++) printf("%i | TK: %i, X: %lu, STR: %s\n", i+1, tks[i][j].type, tks[i][j].hash, tks[i][j].word);
	}
}
