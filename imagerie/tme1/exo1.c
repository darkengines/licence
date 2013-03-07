#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../src/readpgm.c"
#include "../src/writepgm.c"

void histogramme(int hist[256], unsigned char *buf, int size);
void etire(int* hist, int* table);
void applique(unsigned char* buf, long size, int* table);
void seuillage(unsigned char* buff, long size, int bas, int haut);

int main(int argc, char** argv) {
	char* filename = argv[1];
	char* out  = argv[2];
	int w,h,i;
	
	int bas = atoi(argv[3]);
	int haut = atoi(argv[4]);
	
	i = 0;
	
	unsigned char* buffer = readpgm(filename, &w, &h);
	
	assert(buffer != 0);
	
	seuillage(buffer, w*h, bas, haut);
	/*int* hist = (int*)malloc(256*4);
	histogramme(hist, buffer, w*h);
	
	int* corres = (int*)malloc(256*4);
	etire(hist, corres);
	
	applique(buffer, w*h, corres);
	*/
	writepgm(out, buffer, w, h);
	
	//histogramme(hist, buffer, w*h);
	
	free(buffer);
	
	return 0;
}


void histogramme(int* hist, unsigned char *buf, int size) {
	memset(hist, 0, 256*4);
	while (size--) hist[buf[size]]++;
}

void etire(int* hist, int* table) {
	int A,B,i;
	i = 0;
	while (hist[i++] == 0);
	A = i-1;
	i = 255;
	while (hist[i--] == 0);
	B = i-1;
	i = 0;
	while (i<256) {
		table[i] = (255/(B-A)) * (i-A);
		i++;
	}	
}

void applique(unsigned char* buf, long size, int* table) {
	while (size--) {
		buf[size] = table[buf[size]];
	}
}

void seuillage(unsigned char* buff, long size, int bas, int haut) {
	printf("%d %d", bas, haut);
	while (size--) {
		if (buff[size] <= bas) buff[size] = 0;
		if (buff[size] >= haut) buff[size] = 255;
	}
}
