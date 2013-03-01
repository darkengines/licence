#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "crypto.c"

void vtransform(char* string, unsigned int index, void* vigenereParams);

typedef struct {
	char* key;
	unsigned int length;
	char mode;
} VigenereParams;

int main(int argc, char** argv) {
	char mode;
	char *fileIn, *fileOut, *key;
	
	mode = argv[1][0];
	key = argv[2];
	
	fileIn = argv[3];
	fileOut = argv[4];
	
	FILE* in = fopen(fileIn, "r");
	if (!in) return -1;
	FILE* out = fopen(fileOut, "w");
	if (!out) return -1;
	
	char* buffer = (char*)malloc(1024);
	
	VigenereParams param;
	param.key = key;
	param.mode = mode == 'd';
	param.length = strlen(key);
	
	ftransform(in, out, buffer, 1024, vtransform, &param);	
	
	free(buffer);
	
	return 0;
}


void vtransform(char* string, unsigned int index, void* vigenereParams) {
	char c = string[index];
	VigenereParams* params = (VigenereParams*)vigenereParams;
	unsigned int keyIndex = (index) % (params->length);
	if (c >= 'A' && c <= 'Z') {
		if (params->mode == 0) {
			c = (c + params->key[keyIndex] - 2*'A') % 26;
			c += 'A';
		}
		if (params->mode == 1) {
			printf("%c\n", params->key[keyIndex]);
			c = (c - params->key[keyIndex] + 26) % 26;
			c += 'A';
		}
		string[index] = c;
	}
}
