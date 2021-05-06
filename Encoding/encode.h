#ifndef _encode__h_
#define _encode__h_

#ifdef __cplusplus
extern "C"{
#endif

#include <string.h>

#ifdef custom_key
	#include "custom_key.h"
	#ifndef keytype
		#error not defined custom keytype
	#endif
#else
	#ifndef keytype
		typedef unsigned int uint;
		#define keytype uint
	#endif
#endif

#define KEYBIT (sizeof(keytype)*8)

typedef struct _code{
	unsigned char *str;
	int len;
}Code;

Code CreateCodePack(char *str,int len);
void DestroyCodePack(Code *c);
keytype CreateKey();
Code Encode(Code cd,keytype key);
Code Decode(Code cd,keytype key);

char *EncodeToHex(char *str,keytype key);
char *DecodeFromHex(char *enc,keytype key);

#ifdef __cplusplus
}
#endif
#endif
