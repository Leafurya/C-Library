#include <stdio.h>
#include <stdlib.h>
#include "strproc.h"

int main() {
	char *str1="hello world";
	char *str2="123/123456/123456789/123456789123/123456789123456/";
	char *str3="123/123/123\n123456/123456/123456\n123456789/123456789/123456789\n";
	char *tstr;
	int i,j;
	StrBlocks sb;
	Lines ln;
	char signs[]={'/','/','\n'};
	
	printf("%d\n",sizeof(signs));
	
	StringCopy(str1,&tstr);
	printf("%s\n",tstr);
	sb=StringSplittoSingleSign(str2,'/');
	
	for(i=0;i<sb.nofStrs;i++){
		printf("%s\n",sb.str[i]);
	}
	
	ln=StringSplittoMultiSigns(str3,signs,sizeof(signs));
	
	for(j=0;j<ln.nofStrBlck;j++){
		for(i=0;i<ln.sb[j].nofStrs;i++){
			printf("%s\n",ln.sb[j].str[i]);
		}
	}
	
	Lines_ReleaseMem(&ln);
	StringBlocks_ReleaseMem(&sb);
	free(tstr);
	
	getch();
	
	return 0;
}
