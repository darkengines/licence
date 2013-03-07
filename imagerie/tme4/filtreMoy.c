#include <inrimage/image.h>

static char version[]="1.00";
static char usage[]="[input][output][-sb seuil bas][-sh seuil haut]";
static char detail[]="";

int main( int argc, char **argv) {
  char fname[256];
  struct image *nf;
  Fort_int lfmt[9];
  float *buf;
  int d=2;

  /* Initialisation */
  inr_init( argc, argv, version, usage, detail);

  /* Lecture des options */
  igetopt1( "-d", "%d", &d);
  
  DIMX = d;
  DIMY = d;
  BSIZE = 4;
  TYPE = REELLE;
  NDIMX = d;
  NDIMY = d;
  NDIMV = 1;
  NDIMZ = 1;
  
  /* allocation memoire adequat */
  buf = (float*)i_malloc(NDIMX * NDIMY*sizeof(float));
  
  /* Traitement */
  int i = 0;
  while (i < DIMX * DIMY) {
  	buf[i] = 1.0f / (d*d);
  	i++;
  }
  /* Ecriture de l'image */
  
  infileopt(fname);
  nf = image_(fname, "c", "", lfmt);
  c_ecr( nf, NDIMY, buf);
  fermnf_( &nf);
  
  i_Free( (void*)&buf);
  return 0;
}
