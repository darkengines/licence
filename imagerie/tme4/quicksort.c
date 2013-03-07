#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int partition(int* array, int left, int right, int pi);
void array_switch(int* array, int ia, int ib);
void quicksort(int* array, int left, int right);
void quicksorti(int* array, int* arrayi, int length);
void rquicksorti(int* array, int left, int right, int* arrayi);
void array_switchi(int* array, int ia, int ib, int* arrayi);
int partitioni(int* array, int left, int right, int pi, int* arrayi);

int cpartition(unsigned char* array, int left, int right, int pi);
void carray_switch(unsigned char* array, int ia, int ib);
void cquicksort(unsigned char* array, int left, int right);

void quicksort(int* array, int left, int right) {
	if (left < right) {
		int pi = (left+right)/2;
		pi = partition(array, left, right, pi);
		quicksort(array, left, pi-1);
		quicksort(array, pi+1, right);
	}
}

int partition(int* array, int left, int right, int pi) {
	array_switch(array, pi, left);
	pi = right;
	right++;
	while (--right > left) {
		if (array[right] > array[left]) {
			array_switch(array, right, pi--);
		}
	}
	array_switch(array, left, pi);
	return pi;
}

void array_switch(int* array, int ia, int ib) {
	int tmp = array[ia];
	array[ia] = array[ib];
	array[ib] = tmp;
}

void quicksorti(int* array, int* arrayi, int length) {
	int i = 0;
	while (i < length) {
		arrayi[i] = i;
		i++;
	}
	int* arraydump = (int*)malloc(sizeof(int)*length);
	memcpy(arraydump, array, sizeof(int)*length);
	rquicksorti(arraydump, 0, length-1, arrayi);
	free(arraydump);
}

void rquicksorti(int* array, int left, int right, int* arrayi) {
	if (left < right) {
		int pi = (left+right)/2;
		pi = partitioni(array, left, right, pi, arrayi);
		rquicksorti(array, left, pi-1, arrayi);
		rquicksorti(array, pi+1, right, arrayi);
	}
}

int partitioni(int* array, int left, int right, int pi, int* arrayi) {
	array_switchi(array, pi, left, arrayi);
	pi = right;
	right++;
	while (--right > left) {
		if (array[right] > array[left]) {
			array_switchi(array, right, pi--, arrayi);
		}
	}
	array_switchi(array, left, pi, arrayi);
	return pi;
}

void array_switchi(int* array, int ia, int ib, int* arrayi) {
	int tmp = array[ia];
	array[ia] = array[ib];
	array[ib] = tmp;
	tmp = arrayi[ia];
	arrayi[ia] = arrayi[ib];
	arrayi[ib] = tmp;
}

void cquicksort(unsigned char* array, int left, int right) {
	if (left < right) {
		int pi = (left+right)/2;
		pi = cpartition(array, left, right, pi);
		cquicksort(array, left, pi-1);
		cquicksort(array, pi+1, right);
	}
}

int cpartition(unsigned char* array, int left, int right, int pi) {
	carray_switch(array, pi, left);
	pi = right;
	right++;
	while (--right > left) {
		if (array[right] > array[left]) {
			carray_switch(array, right, pi--);
		}
	}
	carray_switch(array, left, pi);
	return pi;
}

void carray_switch(unsigned char* array, int ia, int ib) {
	unsigned char tmp = array[ia];
	array[ia] = array[ib];
	array[ib] = tmp;
}
