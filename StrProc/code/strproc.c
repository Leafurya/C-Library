#include "strproc.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void StringCopy(char *origStr,char **pStr){
	*pStr=(char *)malloc(sizeof(char)*(strlen(origStr)+1));
	strcpy(*pStr,origStr);
}
	char *GetStringBlock(char *origStr,int start,int len){
		char *strBlock;
		int i,strLen=0;
		
		strBlock=(char *)malloc(sizeof(char)*(len+1));
		for(i=start;i<start+len;i++,strLen++){
			strBlock[strLen]=origStr[i];
		}
		strBlock[strLen]=0;
		
		return strBlock;
	}
	void StrBlocks_Init(StrBlocks *sb){
		sb->str=(char **)malloc(sizeof(char *));
		sb->nofStrs=0;
	}
	void StrBlocks_Sizeup(StrBlocks *sb){
		sb->str=(char **)realloc(sb->str,sizeof(char *)*(sb->nofStrs+1));
		sb->nofStrs++;
	}
StrBlocks StringSplittoSingleSign(char *origStr,char sign){
	int i=0;
	int strLen=0;
	int startPoint;
	char *strBlock;
	int *nofStrs=NULL;
	
	StrBlocks sb;
	StrBlocks_Init(&sb);
	nofStrs=&sb.nofStrs;
	
	while(origStr[i]!=0){
		startPoint=i;
		StrBlocks_Sizeup(&sb);
		for(strLen=0;origStr[i]!=sign;i++,strLen++);
		strBlock=GetStringBlock(origStr,startPoint,strLen);
		StringCopy(strBlock,&sb.str[*nofStrs-1]);
		i++;
		free(strBlock);
	}
	
	return sb;
}
void StringBlocks_ReleaseMem(StrBlocks *sb){
	int i;
	
	for(i=0;i<sb->nofStrs;i++){
		memset(sb->str[i],0,strlen(sb->str[i]));
		free(sb->str[i]);
	}
	free(sb->str);
}
	void Lines_Init(Lines *ln){
		ln->nofStrBlck=0;
		ln->sb=(StrBlocks *)malloc(sizeof(StrBlocks));
		StrBlocks_Init(&ln->sb[0]);
	}
	void Lines_Sizeup(Lines *ln){
		ln->sb=(StrBlocks *)realloc(ln->sb,sizeof(StrBlocks)*(ln->nofStrBlck+1));
		StrBlocks_Init(&ln->sb[ln->nofStrBlck]);
		ln->nofStrBlck++;
	}
Lines StringSplittoMultiSigns(char *origStr,char *signs,int nofSigns){
	Lines ln;
	int i=0,j,strLen;
	int startPoint;
	char *strBlock;
	int *nofStrs=NULL;
	int *nofStrBlck=NULL;
	
	Lines_Init(&ln);
	strBlock=(char *)malloc(sizeof(char));
	nofStrBlck=&ln.nofStrBlck;
	
	while(origStr[i]!=0){
		Lines_Sizeup(&ln);
		nofStrs=&ln.sb[*nofStrBlck-1].nofStrs;
		for(j=0;j<nofSigns;j++){
			StrBlocks_Sizeup(&ln.sb[*nofStrBlck-1]);
			for(startPoint=i;origStr[i]!=signs[j];i++);
			strBlock=GetStringBlock(origStr,startPoint,i-startPoint);
			StringCopy(strBlock,&ln.sb[*nofStrBlck-1].str[*nofStrs-1]);
			i++;
			free(strBlock);
		}
	}
	
	return ln;
}
void Lines_ReleaseMem(Lines *ln){
	int i;
	
	for(i=0;i<ln->nofStrBlck;i++){
		StringBlocks_ReleaseMem(&ln->sb[i]);
	}
	free(ln->sb);
}
