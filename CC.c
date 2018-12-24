//#include <sys/types.h>
//#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h> 
#include "caesar/caesar.h"

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
	return r;
}

void printUsage() { printf("Usage:\n\t./CC [-d|-e] filename key\n\t-d:\tDecrypt\n\t-e:\tEncrypt"); }

int modifyAll ( int fd, int key, char *(*modifier)(const char *c,int key)) {
	char *c = malloc(sizeof(char));
	int ret = 0;
	while((ret = read(fd,c,sizeof(char))) != 0) {
		if(ret == -1) {
			if(errno == EINTR) continue;
			perror("Error reading file");
			return -1;
		}
		lseek(fd,-1,SEEK_CUR);
		write(fd,modifier(c,key),sizeof(char));
	}
	c = NULL;
	free(c);
	fdatasync(fd);
	close(fd);
	return 0;
}

int main(int argc, char **argv) {
	if(!okArgs(argc, argv)) {
		printUsage();
		return 1;
	}
	int fd = open(argv[2],O_RDWR);
	if(fd < 0) {
		perror("Error opening file");
		return -1;
	}
	
	if(strcmp(argv[1],"-e") == 0)
		modifyAll(fd,string2int(argv[3]),CCenc);
	else
		modifyAll(fd,string2int(argv[3]),CCdec);
	
	return 0;
}
