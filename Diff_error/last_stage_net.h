
#ifndef LST_NET
#define LST_NET

#include "data_types.h"


struct Reshape_out_struct {
    acc_type out_fmap[180];
    };

struct Percep_out_struct {
    acc_type out_fmap[10];
    };


struct SoftMax_out_struct {
    acc_type out_fmap[10];
    };


Reshape_out_struct Reshape(acc_type matrice_in[3*3*20]);


Percep_out_struct Perceptron(acc_type matrice_in[180]) ;


// SoftMax_out_struct Softmax(coef_type matrice_in[10]) ;


#endif