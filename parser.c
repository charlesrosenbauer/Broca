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
		if     (text.str[i] == '\t') ct += 3;
		else if(text.str[i] !=  ' ') return ct;
		ct++;
	}
	return ct;
}



int isAlpha(char c){
	return ((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z'));
}


int isNumber(char c){
	return (c >= '0') && (c <= '9');
}


int isAlphaNum(char c){
	return isAlpha(c) || isNumber(c);
}


int isText(char c){
	return isAlphaNum(c) || (c == '!') || (c == '?') || (c == '.') || (c == ',') || (c == '-') || (c == '\'') || (c == '\"') || (c == '(') || (c == ')');
}


uint64_t hashStr(char* str){
	uint64_t ret = 138175091781;
	int i = 0;
	while(str[i] != '\0'){
		ret    ^= (str[i] * 13257109);
		ret    += (str[i] * 90819881);
		int rot = str[i] >> 2;
		ret     = (ret >> rot) | (ret << (64 - rot));
		i++;
	}
	return ret;
}



Token* lineTokens(Str text, int* tksct){
	Token* ret = malloc(sizeof(Token) * text.len);
	int indent = indentation(text);
	int tkct   = 0;
	if(indent){	ret[tkct] = (Token){NULL, indent, T_INDENT}; tkct++; }
	
	for(int i = 0; i < text.len; i++){
		char c = text.str[i];
		if       (c == '{'){
			ret[tkct] = (Token){"{", 0, T_OPEN  }; tkct++;
		}else if (c == '}'){
			ret[tkct] = (Token){"}", 0, T_CLOSE }; tkct++;
		}else if (c == '|'){
			ret[tkct] = (Token){"|", 0, T_OR    }; tkct++;
		}else if (c == '*'){
			ret[tkct] = (Token){"*", 0, T_OPTION}; tkct++;
		}else if (c == '@'){
			// parse tag
			int len = 0;
			for(int j = i+1; j < text.len; j++){
				char v = text.str[j];
				if(!isAlphaNum(v)) j = text.len;
				len++;
			}
			char* id = malloc(sizeof(char) * (len+2));
			id[0]    = '@';
			for(int j = 0; j < (len+1); j++)	id[j] = text.str[j+i];
			id[len+1]  = '\0';
			ret[tkct] = (Token){id, hashStr(id), T_GOTO}; tkct++;
			i += len;
		}else if(c == '#'){
			// comment
			break;
		}else if((c != ' ') && (c != '\t')){
			// more complex symbols
			if((c == '-') && (i+1 < text.len) && (text.str[i+1] == '>')){
				ret[tkct] = (Token){"->", 0, T_ARROW}; tkct++;
				i += 2;
			}else if(isText(c)){
				// Words
				int len = 1;
				for(int j = i+1; j < text.len; j++){
					char v = text.str[j];
					if(!isText(v)) j = text.len;
					len++;
				}
				char* id = malloc(sizeof(char) * (len+1));
				for(int j = 0; j < len; j++) id[j] = text.str[j+i];
				id[len]  = '\0';
				ret[tkct] = (Token){id, hashStr(id), T_WORD}; tkct++;
				i += len-1;
			}else if(c == '%'){
				int len = 0;
				for(int j = i+1; j < text.len; j++){
					char v = text.str[j];
					if(!isNumber(v)) j = text.len;
					len++;
				}
				char* id   = malloc(sizeof(char) * (len+2));
				id[0]      = '%';
				uint64_t x = 0;
				for(int j  = 0; j < (len+1); j++){ id[j] = text.str[j+i]; x = (x * 10) + (text.str[j+i]-'0'); }
				id[len+1]  = '\0';
				ret[tkct]  = (Token){id, x, T_PERCENT}; tkct++;
				i += len;
			}
		}
	}
	*tksct = tkct;
	return ret;
}

