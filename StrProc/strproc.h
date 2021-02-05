#ifndef _strproc__h_
#define _strproc__h_

#ifdef __cplusplus
extern "C"{
#endif

typedef struct _strblocks{
	char **str;
	int nofStrs;
}StrBlocks;

typedef struct _lines{
	StrBlocks *sb;
	int nofStrBlck;
}Lines;

void StringCopy(char *origStr,char **pStr);

StrBlocks StringSplittoSingleSign(char *origStr,char sign);
void StringBlocks_ReleaseMem(StrBlocks *sb);

Lines StringSplittoMultiSigns(char *origStr,char *signs,int nofSigns);
void Lines_ReleaseMem(Lines *ln);

#ifdef __cplusplus
}
#endif
#endif
