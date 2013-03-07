/*
 * LI316 - Introduction a l'imagerie numerique
 * Fichier template Inrimage
 */

#include <inrimage/image.h>
#include <stdlib.h>
#include <string.h>

static char version[]="1.00";
static char usage[]="[input][output]";
static char detail[]="";

int main( int argc, char **argv) {
  char fname[256];
  struct image *nf;
  Fort_int lfmt[9];
  unsigned char *buf;
  int i,j;

  /* Initialisation */
  inr_init( argc, argv, version, usage, detail);
  
  infileopt(fname);
  
  /* Ouverture et lecture des images */
  nf = image_(fname, "e", "", lfmt);

  /* verification du format */
  if( !(TYPE == FIXE && BSIZE==1 && NDIMV==1))
    imerror( 6, "codage non conforme\n");

  /* allocation memoire adequat */
  buf = (unsigned char*)i_malloc( NDIMX * NDIMY*sizeof(unsigned char));

  /* lecture image */
  c_lect( nf, NDIMY, buf);

  /* fermeture image */
  fermnf_( &nf);
  
  int* hist = (int*)calloc(sizeof(int), 256);
  
  /* Traitement */
  for(j=0; j<NDIMY; j++)
    for(i=0; i<NDIMX; i++) {
      hist[buf[i+j*NDIMX]]++;
	}
  
  outfileopt(fname);
  FILE* out = fopen(fname, "w");
  
  for (i = 0;i<256;i++) {
  	fprintf(out, "%d %d\n", i, hist[i]);
  }
  
  fclose(out);
  
  
  
  i_Free( (void*)&buf);
  return 0;
}
