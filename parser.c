#include "parser.h"

#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"
#include "string.h"





Str* getLines(char* text, int* linect){
	int len = 0, lines = 1;
	while(text[len] != '\0'){
		lines += (text[len] == '\n');
		len++;
	}
	
	Str* ret = malloc(sizeof(Str) * lines);
	for(int i = 0; i < lines; i++){ ret[i].str = ""; ret[i].len = 0; }
	
	int  lastLine = 0;
	int  line     = 0;
	for(int i = 0; i < len; i++){
		if((text[i] == '\n') || (text[i] == '\0') || ((i+1) == len)){
			int dist            = i - lastLine;
			ret[line].str       = malloc(sizeof(char) * (dist+1));
			for(int j = lastLine; j < i; j++) ret[line].str[j-lastLine] = text[j];
			ret[line].str[dist] = '\0';
			ret[line].len       = dist;
			line++;
			lastLine = i+1;
		}
	}
	
	*linect = lines;
	return ret;
}





int indentation(Str text){
	int ct = 0;
	for(int i = 0; i < text.len; i++){
		if(text.str[i] != ' ') return ct;
		ct++;
	}
	return ct;
}




Token* lineTokens(Str text, int* tksct){
	Token* ret = malloc(sizeof(Token) * text.len);
	int tkct   = 0;
	for(int i = 0; i < text.len; i++){
		char c = text.str[i];
		if       (c == '{'){
			ret[tkct] = (Token){NULL, 0, T_OPEN  }; tkct++;
		}else if (c == '}'){
			ret[tkct] = (Token){NULL, 0, T_CLOSE }; tkct++;
		}else if (c == '|'){
			ret[tkct] = (Token){NULL, 0, T_OR    }; tkct++;
		}else if (c == '*'){
			ret[tkct] = (Token){NULL, 0, T_OPTION}; tkct++;
		}else if (c == '@'){
			// parse tag
		}else if((c != ' ') && (c != '\t')){
			// more complex symbols
		}
	}
	return ret;
}

