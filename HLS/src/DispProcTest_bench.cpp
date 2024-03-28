
// Include files for data types
#include "math.h"
#include <fstream>
#include <iostream>
#include <iomanip>
using namespace std ;
#include "mc_scverify.h"
#include "ac_fixed.h"
#include "DispProcTest.h"

#include "all_includes.h"

/* Pour  Compilation et exécution sur PC */
#ifndef CCS_MAIN
#define CCS_MAIN int main
#define CCS_DESIGN(d) d
#endif

CCS_MAIN(int argc, char **argv) {

  d_type img_out[IMG_SIZE_COL*IMG_SIZE_ROW];

 
  /* Execute traitement */
  printf( "Start verification DispProcTest\n");
  CCS_DESIGN(DispProcTest)(img_out) ;

  /*
    Fichier sortie
  */
  ofstream simg_out("my_hls_18.pgm");
  simg_out << "P2" << endl;
  simg_out << IMG_SIZE_COL<< " ";
  simg_out <<  IMG_SIZE_ROW<< endl;
  simg_out <<  255 << endl;
  for(int i=0; i<IMG_SIZE_ROW*IMG_SIZE_COL;i++)
    {
        //cout << img_out[i].to_int() << endl; 
      simg_out <<  img_out[i].to_int() << endl; 
    }

}
  
