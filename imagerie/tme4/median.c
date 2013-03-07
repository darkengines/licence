/*
 * LI316 - Introduction a l'imagerie numerique
 * Fichier template Inrimage
 */

#include <inrimage/image.h>
#include "quicksort.c"

static char version[]="1.00";
static char usage[]="[input][output][-sb seuil bas][-sh seuil haut]";
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
  unsigned char *s;
  /* Traitement */
  for( j=0; j<NDIMY; j++) {
    for( i=0; i<NDIMX; i++) {
      // En haut a gauche
      if (i == 0 && j == 0) {
      	s = (unsigned char*)malloc(4);
      	s[0] = buf[0];
      	s[1] = buf[1];
      	s[2] = buf[DIMX];
      	s[3] = buf[1+DIMX];
      	cquicksort(s, 0, 3);
      	buf[0] = s[1];
      	free(s);
      } else
      // En haut a droite
      if (i == DIMX-1 && j == 0) {
      	s = (unsigned char*)malloc(4);
      	s[0] = buf[DIMX-2];
      	s[1] = buf[DIMX-1];
      	s[2] = buf[2*DIMX-2];
      	s[3] = buf[2*DIMX-1];
      	cquicksort(s, 0, 3);
      	buf[DIMX-1] = s[1];
      	free(s);
      } else 
      // En bas a gauche
      if (i == 0 && j == DIMY-1) {
      	s = (unsigned char*)malloc(4);
      	s[0] = buf[(DIMY-2)*DIMX];
      	s[1] = buf[(DIMY-2)*DIMX+1];
      	s[2] = buf[(DIMY-1)*DIMX];
      	s[3] = buf[(DIMY-1)*DIMX+1];
      	cquicksort(s, 0, 3);
      	buf[DIMX*(DIMY-1)] = s[1];
      	free(s);
      } else
      // En bas a droite
      if (i == DIMX-1 && j == DIMY-1) {
      	s = (unsigned char*)malloc(4);
      	s[0] = buf[(DIMY-2)*DIMX+DIMX-2];
      	s[1] = buf[(DIMY-2)*DIMX+DIMX-1];
      	s[2] = buf[(DIMY-1)*DIMX+DIMX-2];
      	s[3] = buf[(DIMY-1)*DIMX+DIMX-1];
      	cquicksort(s, 0, 3);
      	buf[DIMX-1+DIMX*(DIMY-1)] = s[1];
      	free(s);
      } else
      // En haut
      if (i!=0 && i!=DIMX-1 && j == 0) {
      	s = (unsigned char*)malloc(6);
      	s[0] = buf[i-1];
      	s[1] = buf[i];
      	s[2] = buf[i+2];
      	s[3] = buf[DIMX+i-1];
      	s[4] = buf[DIMX+i];
      	s[5] = buf[DIMX+i+1];
      	cquicksort(s, 0, 5);
      	buf[i] = s[2];
      	free(s);
      } else
      // A droite
      if (i==DIMX-1 && j != 0 && j != DIMY-1) {
      	s = (unsigned char*)malloc(6);
      	s[0] = buf[DIMX-2 + (j-1)*DIMX];
      	s[1] = buf[DIMX-1 + (j-1)*DIMX];
      	s[2] = buf[DIMX-2 + (j)*DIMX];
      	s[3] = buf[DIMX-1 + (j)*DIMX];
      	s[4] = buf[DIMX-2 + (j+1)*DIMX];
      	s[5] = buf[DIMX-1 + (j+1)*DIMX];
      	cquicksort(s, 0, 5);
      	buf[DIMX-1+j*DIMX] = s[2];
      	free(s);
      } else
      // En bas
      if (i!=0 && i!=DIMX-1 && j == DIMY-1) {
      	s = (unsigned char*)malloc(6);
      	s[0] = buf[DIMX*(DIMY-2)+i-1];
      	s[1] = buf[DIMX*(DIMY-2)+i];
      	s[2] = buf[DIMX*(DIMY-2)+i+1];
      	s[3] = buf[DIMX*(DIMY-1)+i-1];
      	s[4] = buf[DIMX*(DIMY-1)+i];
      	s[5] = buf[DIMX*(DIMY-1)+i+1];
      	cquicksort(s, 0, 5);
      	buf[(DIMY-1)*DIMX+i] = s[2];
      	free(s);
      } else
      // A gauche
      if (i==0 && j != 0 && j != DIMY-1) {
      	s = (unsigned char*)malloc(6);
      	s[0] = buf[(j-1)*DIMX];
      	s[1] = buf[(j-1)*DIMX+1];
      	s[2] = buf[(j)*DIMX];
      	s[3] = buf[(j)*DIMX+1];
      	s[4] = buf[(j+1)*DIMX];
      	s[5] = buf[(j+1)*DIMX+1];
      	cquicksort(s, 0, 5);
      	printf("i=%d j=%d\n", i, j);
      	buf[j*DIMX] = s[2];
      	free(s);
      } else
      // Et ENFIN:
      {
      	s = (unsigned char*)malloc(9);
      	s[0]=buf[i-1 + DIMX * (j-1)];
      	s[1]=buf[i + DIMX * (j-1)];
      	s[2]=buf[i+1 + DIMX * (j-1)];
      	s[3]=buf[i-1 + DIMX * (j)];
      	s[4]=buf[i + DIMX * (j)];
      	s[5]=buf[i+1 + DIMX * (j)];
      	s[6]=buf[i-1 + DIMX * (j+1)];
      	s[7]=buf[i + DIMX * (j+1)];
      	s[8]=buf[i-1 + DIMX * (j+1)];
      	cquicksort(s, 0, 8);
      	buf[i + DIMX * (j)] = s[4];
      	free(s);
      }
	}
	}
  /* Ecriture de l'image */
  outfileopt( fname);
  nf = image_(fname, "c", "", lfmt);
  c_ecr( nf, NDIMY, buf);
  fermnf_( &nf);
  
  i_Free( (void*)&buf);
  return 0;
}
