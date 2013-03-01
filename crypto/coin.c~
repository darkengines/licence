#include <stdio.h>
#include <stdlib.h>
#include "crypto.c"

int main(int argc, char** argv) {
	char* text = 0;
	char* alpha = 0;
	char* textfilename = argv[1];
	char* alphafilename = argv[2];
	int modfrom = atoi(argv[3]);
	int modto = atoi(argv[4]);
	int subsetlength = 0;
	int length = 0;
	int alphalength = 0;
	load(alphafilename, &alpha, &alphalength);
	load(textfilename, &text, &length);
	int i = modfrom;
	while (i <= modto) {
		float result = moymodsubsetscoin(text, length, i, alpha, alphalength);
		printf("MCI(mod %d) = %f\n", i, result);
		i++;
	}
	int explodemod = 0;
	
	printf("Select mod: ");
	scanf("%d",&explodemod);
	
	
	
	free(text);
	free(alpha);
	return 0;
}
