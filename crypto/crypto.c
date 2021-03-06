#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "quicksort.c"

void stransform(char* string, unsigned int length, void (*transform) (char*, unsigned int index, void*), void*);
float coin(char* text, int length, char* alpha, int alength);

int ftransform(FILE* in, FILE* fout, char* mout, int count, void (*ctransform) (char*, unsigned int index, void*), void* params);

void count(char* string, int stringLen, int* counts, int countLen);

void load(char* filename, char** buffer, int* length);
void sortedOccurences(char* arrayString, int length, int* arrayOccurences, int ocLength);

void modsubset(char* text, int length, int mod, int k, char** subset, int* subsetlength);
float moymodsubsetscoin(char* text, int length, int mod, char* alpha, int alphalength);

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

void count(char* string, int stringLen, int* counts, int countLen) {
	memset(counts, 0, countLen);
	while (stringLen--) {
		counts[string[stringLen]]++;
	}
}

void load(char* filename, char** buffer, int* length) {
	int count = 0;
	FILE* file = fopen(filename, "r");
	if (file) {
		char c = 0;
		while ((c = fgetc(file)) != EOF && c != 10) {
			count++;
		}
		*length = count;
		fseek(file, 0, SEEK_SET);
		*buffer = (char*)malloc(count);
		int i=0;
		while (i<count) {
			(*buffer)[i] = fgetc(file);
			i++;
		}
	}
}

void sortedOccurences(char* arrayString, int length, int* arrayOccurences, int ocLength) {
	int* counta = (int*)malloc(sizeof(int)*ocLength);
	count(arrayString, length, counta, ocLength);
	quicksorti(counta, arrayOccurences, ocLength);
	free(counta);
}

float coin(char* text, int length, char* alpha, int alength) {
	int* countbuffer = (int*)calloc(256, sizeof(int));
	int i = 0;
	while (i<length) {
		countbuffer[text[i]]++;
		i++;
	}
	float sum = 0.0f;
	int total = 0;
	i = 0;
	while (i < alength) {
		total += countbuffer[alpha[i]];
		sum += countbuffer[alpha[i]] * (countbuffer[alpha[i]] - 1);
		i++;
	}
	free(countbuffer);
	return (sum / (total*(total-1)));
}

void modsubset(char* text, int length, int mod, int k, char** subset, int* subsetlength) {
	int rest = (length % mod);
	*subsetlength = (length / mod) + (k < rest);
	*subset = (char*)malloc(*subsetlength);
	int i = 0;
	while (i < *subsetlength) {
		(*subset)[i] = text[i*mod];
		i++;
	}
}

float moymodsubsetscoin(char* text, int length, int mod, char* alpha, int alphalength) {
	int i = 0;
	float sum = 0.0f;
	char* subset = 0;
	while (i < mod) {
		int subsetlength = 0;
		modsubset(text, length, mod, i, &subset, &subsetlength);
		sum += coin(subset, subsetlength, alpha, alphalength);
		free(subset);
		i++;
	}
	return sum/mod;
}
