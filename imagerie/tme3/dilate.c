/*
 * LI316 - Introduction a l'imagerie numerique
 * Fichier template Inrimage
 */

#include <inrimage/image.h>
#include <stdlib.h>
#include <string.h>

void histogramme(int* hist, unsigned char *buf, int size);
void etire(int* hist, int* table);
void applique(unsigned char* buf, long size, int* table);


static char version[]="1.00";
static char usage[]="[input][output]";
static char detail[]="";

int main( int argc, char **argv) {
  char fname[256];
  struct image *nf;
  Fort_int lfmt[9];
  unsigned char *buf;
  int i, j;

  /* Initialisation */
  inr_init( argc, argv, version, usage, detail);
  
  infileopt( fname);
  
  /* Ouverture et lecture des images */
  nf = image_(fname, "e", "", lfmt);

  /* verification du format */
  if( !(TYPE == FIXE && BSIZE==1))
    imerror( 6, "codage non conforme\n");

  /* allocation memoire adequat */
  buf = (unsigned char*)i_malloc( NDIMX * NDIMY*sizeof(unsigned char));

  /* lecture image */
  c_lect( nf, NDIMY, buf);

  /* fermeture image */
  fermnf_( &nf);
  
  /* Traitement */
  
  int* hist = (int*)calloc(sizeof(int), 256);
  int* table = (int*)calloc(sizeof(int), 256);
  
  histogramme(hist, buf, NDIMX*NDIMY);
  etire(hist, table);
  free(hist);
  applique(buf, NDIMX*NDIMY, table);
  free(table);
  
  /* Ecriture de l'image */
  outfileopt( fname);
  nf = image_(fname, "c", "", lfmt);
  c_ecr( nf, NDIMY, buf);
  fermnf_( &nf);
  
  i_Free( (void*)&buf);
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
