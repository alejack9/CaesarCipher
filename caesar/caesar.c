#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "caesar.h"

// protoypes
char shift( char , int );
char toupper ( int ); // there's in ctype, but why include a library for a simple, easy, function?

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
	/* first version
	 * static const char alph[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
	 * if(toupper(c) >= 65 && toupper(c) <= 90) {
	 *	if(toupper(c) == c) return alph[(c-65+k)%26];
	 *	return alph[(c-97+k)%26]+32;
	 * }	
	 * return c;
	 */
	/* second version
	  * if(toupper(c) >= 65 && toupper(c) <= 90) {
	  *  if(toupper(c) == c) return ((c-65+k)%26)+65;
	  *  return (c-97+k)%26+97;
	  * }
	  * return c;
	  * */
	/* third version
	 if(toupper(c) < 65 || toupper(c) > 90) return c; // if it's not a letter don't modify it.
	 //( toupper(c) == c ) ? (c = ((c - 65 + k) % 26) + 65) : (c = (c - 97 + k) % 26 + 97); // if it's a letter and it's upper, return the value minus 65 (the letter's position) and sum the key,
	 // then mod 26 (number of alphabetic's letters plus 65 (ascii upper letters position), similar speech to lower letters
	 return c;
	*/
	if(toupper(c) < 'A' || toupper(c) > 'Z') return c; // if it's not a letter don't modify it.
	if(toupper(c) == c) return ((26 + (c - 'A' + k)) % 26) + 'A';
	return ((26 + (c - 'a' + k)) % 26) + 'a';
}

char toupper(int c) {
	if(c >= 'a' && c <= 'z') return c - 32;
	return c;
}

/*int main(int argc, char **argv)
{
	argc = 4;
	argv[1] = "-e";
	argv[2] = "test";
	argv[3] = "42";
	if(!okArgs(argc, argv)) {
		printf("Usage:\n\t./caesar [-d|-e] filename key\n\t-d:\tDecrypt\n\t-e:\tEncrypt");
		return 1;
	}
	char ps[100];
	printf("Insert the text to decrypt: ");
	scanf ("%[^\n]%*c", ps);
	int key = 0;
	printf("Insert the key: ");
	scanf("%d",&key);
	//"A B C D E F G H I J K L M N O P Q R S T U V W X Y Z\na b c d e f g h i j k l m n o p q r s t u v w x y z"
	char *p = CCenc(ps, key);
	printf("Coded:\n");
	printf("%s",p);
	printf("\n\n");
	printf("Decoded:\n");
	char *p2 = CCdec(p,key);
	free(p); p = NULL;
	printf("%s",p2);
	return 0;
}*/
