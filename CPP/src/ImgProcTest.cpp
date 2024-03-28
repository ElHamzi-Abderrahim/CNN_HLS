
// Include files for data types
#include "ac_fixed.h"
#define DATA_WIDTH 8
#define IMG_SIZE_0 320
#define IMG_SIZE_1 240
#define IMG_SIZE IMG_SIZE_0*IMG_SIZE_1
// optional pragma to specify the top level of the design
#define c(x,y) x+y*IMG_SIZE_0

#pragma hls_design top
void ImgProcTest (
                  ac_fixed<DATA_WIDTH,DATA_WIDTH,false,AC_RND_INF,AC_SAT> img_in[IMG_SIZE],
                  ac_fixed<DATA_WIDTH,DATA_WIDTH,false,AC_RND_INF,AC_SAT> img_out[IMG_SIZE]
                  )
{
 lx : for(int x=0; x < IMG_SIZE_0; x++)
  ly : for(int y=0; y < IMG_SIZE_1; y++)
      {
        if (x<y)
          img_out[c(x,y)]=255 - img_in[c(x,y)];
        else
          img_out[x+y*IMG_SIZE_0]=img_in[x+y*IMG_SIZE_0];
      }
} 

