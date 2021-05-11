#ifndef _encode__h_
#define _encode__h_

#ifdef __cplusplus
extern "C"{
#endif

#include <string.h>

typedef struct _code{
	unsigned char *str;
	int len;
}Code;

Code CreateCodePack(char *str,int len);
void DestroyCodePack(Code *c);
char *CreateKey(int byte);
Code Encode(Code cd,char *key);
Code Decode(Code cd,char *key);

char *EncodeToHex(char *str,char *key);
char *DecodeFromHex(char *enc,char *key);

#ifdef __cplusplus
}
#endif
#endif
