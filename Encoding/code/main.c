#include <stdio.h>
#include <stdlib.h>
#include <encode.h>

int main() {
	FILE *file=fopen("omok.exe","rb");
	FILE *newFile;
	int size;
	char *fileBin;
	char *encBin;
	char *decBin;
	keytype key=CreateKey();
	
	fseek(file,0,SEEK_END);
	size=ftell(file);
	rewind(file);
	
	fileBin=(char *)malloc(size*sizeof(char));
	fread(fileBin,size,1,file);
	
	encBin=EncodeToHex(fileBin,key);
	decBin=DecodeFromHex(encBin,key);
	
	newFile=fopen("newomok.exe","wb");
	fwrite(fileBin,size,1,newFile);
	
	free(encBin);
	free(decBin);
	free(fileBin);
	
	fclose(file);
	fclose(newFile);
	
	return 0;
}
