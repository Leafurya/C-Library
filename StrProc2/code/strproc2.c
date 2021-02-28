#include "strproc2.h"
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char *GetString(const char *format,...){
	va_list vaList;
	int len;
	char *str;
	
	va_start(vaList,format);
	len=_vscprintf(format,vaList)+1;
	
	str=(char *)malloc(sizeof(char)*(len));
	vsprintf(str,format,vaList);
	
	va_end(vaList);
	
	return str;
}
STRING Split(char *originStr,char sign){
	STRING newStr;
	char *tOriginStr;
	int *blocks=&newStr.size;
	int i,j;
	int strLen=0;
	int *blockLens=(int *)malloc(strlen(originStr)*sizeof(int));
	
	*blocks=0;
	for(i=0;originStr[i]!=0;i++){
		if(originStr[i]==sign){
			if(strLen!=0){
				blockLens[*blocks]=strLen;
				*blocks+=1;
				strLen=0;
			}
		}
		else{
			strLen++;
		}
	}
	if(strLen!=0){
		blockLens[*blocks]=strLen;
		*blocks+=1;
	}
	
	newStr.strings=(char **)malloc(sizeof(char *)*(*blocks));
	strLen=0;
	tOriginStr=originStr;
	
	for(i=0;i<*blocks;i++){
		newStr.strings[i]=(char *)malloc(sizeof(char)*blockLens[i]+1);
		for(j=0;j<blockLens[i];j++,tOriginStr++){
			newStr.strings[i][j]=*tOriginStr;
		}
		tOriginStr++;
		newStr.strings[i][j]=0;
	}
	free(blockLens);
	
	return newStr;
}
void DeleteString(STRING *pStr){
	int i;
	
	for(i=0;i<pStr->size;i++){
		memset(pStr->strings[i],0,strlen(pStr->strings[i]));
		free(pStr->strings[i]);
	}
	free(pStr->strings);
}
