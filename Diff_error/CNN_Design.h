
#ifndef DESIGN
#define DESIGN

#include "data_types.h"
#include "image_processing.h"
#include "convolution.h"
#include "maxpool.h"

#define CHANN   1
#define ROW     1
#define COLUMN  4


void CNN_Network(
                acc_type image_in[24*24*3], 
                ca_type &design_result) ;
                // acc_type design_result[CHANN*ROW*COLUMN]) ;

#endif