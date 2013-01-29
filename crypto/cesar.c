#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char key;
} CesarParams;

typedef struct {
	int* key;
	unsigned int length;
} VigenereParams;

void ctransform(char* c, unsigned int index, void*);
void vtransform(char* string, unsigned int index, void* vigenereParams);
void stransform(char* string, unsigned int length, void (*transform) (char*, unsigned int index, void*), void*);
int ftransform(FILE* in, FILE* fout, char* mout, int count, void (*ctransform) (char*, unsigned int index, void*), void* params);

int main(int argc, char** argv) {
	char* string = (char*)malloc(256);
	sprintf(string, "ASCII");
	printf("%s\n", string);
	
	VigenereParams params;
	params.key = malloc(4 * 1);
	params.key[0] = 1;
	params.length = 1;
	
	stransform(string, 19, vtransform, &params);
	printf("%s\n", string);
	
	params.key[0] = -1;
	
	stransform(string, 19, vtransform, &params);
	printf("%s\n", string);
	
	FILE *fin, *fout;
	
	fin = fopen("fin", "r");
	fout = fopen("fout", "w");
	
	char* buffer = (char*)malloc(255);
	
	params.key[0] = 1;
	
	unsigned int out = ftransform(fin, fout, buffer, 255, vtransform, &params);
	
	printf("encoded %d characters from fin\n", out);
	
	free(string);
	free(buffer);
	
	fclose (fout);
	fclose (fin);
	
	return 0;
}

int ftransform(FILE* in, FILE* fout, char* mout, int count, void (*ctransform) (char*, unsigned int index, void*), void* params) {
	unsigned int i = 0u;
	char c;
	while ((c = fgetc(in))!=EOF && i < count) {
		mout[i] = c;
		++i;
	}
	
	stransform(mout, i, ctransform, params);
	
	if (fout) {
		fprintf(fout, "%s", mout);
	}
	return i;
}

void stransform(char* string, unsigned int length, void (*ctransform) (char*, unsigned int index, void*), void* params) {
	unsigned int i = 0u;
	while (i < length) {
		ctransform(string, i, params);
		++i;
	}
}

void ctransform(char* string, unsigned int index, void* cesarParams) {
	char c = string[index];
	CesarParams* params = (CesarParams*)cesarParams;
	if (c >= 65 && c <= 90) {
		c = (c + params->key - 64) % 90;
		if (c < 0) c += 90;
		c += 64;
		string[index] = c;
	}
}

void vtransform(char* string, unsigned int index, void* vigenereParams) {
	char c = string[index];
	VigenereParams* params = (VigenereParams*)vigenereParams;
	unsigned int keyIndex = (index+1) % (params->length);
	if (c >= 65 && c <= 90) {
		c = (c + params->key[keyIndex] - 64) % 90;
		if (c < 0) c += 90;
		c += 64;
		string[index] = c;
	}
}
