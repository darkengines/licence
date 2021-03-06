#include <stdio.h>
#include <stdlib.h>
#include "crypto.c"

typedef struct {
	char key;
	char mode;
} CesarParams;

typedef struct {
	int* key;
	unsigned int length;
} VigenereParams;

void ctransform(char* c, unsigned int index, void*);

int main(int argc, char** argv) {
	char key, mode;
	char *fileIn, *fileOut;
	
	mode = argv[1][0];
	key = argv[2][0];
	
	fileIn = argv[3];
	fileOut = argv[4];
	
	FILE* in = fopen(fileIn, "r");
	if (!in) return -1;
	FILE* out = fopen(fileOut, "w");
	if (!out) return -1;
	
	char* buffer = (char*)malloc(1024000);
	
	CesarParams param;
	param.key = key;
	param.mode = mode == 'd';
	
	ftransform(in, out, buffer, 1024000, ctransform, &param);	
	
	free(buffer);
	
	return 0;
}

void ctransform(char* string, unsigned int index, void* cesarParams) {
	char c = string[index];
	CesarParams* params = (CesarParams*)cesarParams;
	if (c >= 'A' && c <= 'Z') {
		if (params->mode == 0) {
			c = (c + params->key - 2*'A') % 26;
			c += 'A';
		}
		if (params->mode == 1) {
			c = (c - params->key + 26) % 26;
			c += 'A';
		}
		string[index] = c;
	}
}




