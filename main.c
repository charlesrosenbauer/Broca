#include "stdio.h"
#include "stdint.h"
#include "stdlib.h"

#include "line.h"





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

int main(int argc, char** args){
	char** filePaths = malloc(sizeof(char*) * argc);
	char** files     = malloc(sizeof(char*) * argc);
	int*   fsizes    = malloc(sizeof(int)   * argc);
	int    filect    = argc-1;
	for(int i = 1; i < argc; i++){
		filePaths[i-1] = args[i];
		loadFile(args[i], &files[i-1], &fsizes[i-1]);
	}
	
	Line* lines;
	int lnct = splitLines(files[0], fsizes[0], 0, &lines);
	for(int i = 0; i < lnct; i++){
		if(!parseLine(&lines[i])){
			printf("Error on line %i\n", lines[i].line);
			return 1;
		}
	}
	printLines(lines, lnct);
}
