#include <stdio.h>
#include <stdlib.h>
#include "crypto.c"

typedef struct {
	char key;
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
	key = atoi(argv[2]);
	
	fileIn = argv[3];
	fileOut = argv[4];
	
	FILE* in = fopen(fileIn, "r");
	if (!in) return -1;
	FILE* out = fopen(fileOut, "w");
	if (!out) return -1;
	
	char* buffer = (char*)malloc(1024000);
	
	CesarParams param;
	param.key = key;
	
	ftransform(in, out, buffer, 1024000, ctransform, &param);	
	
	free(buffer);
	
	return 0;
}

void ctransform(char* string, unsigned int index, void* cesarParams) {
	char c = string[index];
	if (c != '\n') {
		CesarParams* params = (CesarParams*)cesarParams;
		int sum = c + params->key;
		int sign = sum < 0 ? -1 : 1;
		c = (sign*sum) % (sign*255);
		string[index] = c;
	}
}




