#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "caesar.h"

// protoypes
char shift( char , int );
char toupper ( int );

char *CCenc(const char *string, int key) {
	char *p = malloc(sizeof(char)*strlen(string));
	p = strcpy(p,string);
	for(int i = 0; i < strlen(p); i++)
		p[i] = shift(p[i],key);
	return p;
}

char *CCdec(const char *string, int key) {
	return CCenc(string, -key);
}

char shift(char c, int k) {
	if(toupper(c) < 'A' || toupper(c) > 'Z') return c; // if it's not a letter don't modify it.
	if(toupper(c) == c) return ((26 + (c - 'A' + k)) % 26) + 'A';
	return ((26 + (c - 'a' + k)) % 26) + 'a';
}

char toupper(int c) {
	if(c >= 'a' && c <= 'z') return c - 32;
	return c;
}
