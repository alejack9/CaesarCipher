#include <stdio.h>
#include <stdlib.h>
#include "caesar/caesar.c"

int okArgs (int argc, char ** argv) {
	if(argc != 4) return 0;
	if(strcmp(argv[1],"-e") != 0 && strcmp(argv[1],"-d") != 0) return 0;
	return 1;	
}

int string2int(const char *s) {
	int r = 0;
	for(int i = 0; i < strlen(s); i++) {
		r *= 10;
		r += s[i]-'0';
	}
	printf("%d",r);
	return r;
}

void printUsage() { printf("Usage:\n\t./CC [-d|-e] filename key\n\t-d:\tDecrypt\n\t-e:\tEncrypt"); }

int modifyAll ( FILE *fp, int key, char *(*modifier)(const char *c,int key) ) {
	char *c = malloc(sizeof(char));
	while((*c = fgetc(fp)) != EOF) {
		fseek(fp,-1,SEEK_CUR);
		fputs(modifier(c,key),fp);
	}
	free(c);
	fflush(fp);
	fclose(fp);
	return 0;
}

int main(int argc, char **argv)
{
	if(!okArgs(argc, argv)) {
		printUsage();
		return 1;
	}
	FILE *fp = fopen(argv[2], "r+");
	if(fp == NULL) {
		perror("Error opening file");
		return -1;
	}
	
	if(strcmp(argv[1],"-e") == 0)
		modifyAll(fp,string2int(argv[3]),CCenc);
	else
		modifyAll(fp,string2int(argv[3]),CCdec);
	return 0;
}
