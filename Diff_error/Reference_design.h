
#ifndef REF_CONVOL
#define REF_CONVOL


#include "convolution.h"
#include "maxpool.h"

struct C1_ref_struct {
    double out_fmap[C1_OUT_ZISE];
    };

struct C2_ref_struct {
    double out_fmap[C2_OUT_ZISE];
    };

struct C3_ref_struct {
    double out_fmap[C3_OUT_ZISE];
    };


C1_ref_struct REF_Conv_RELU_1(
                    double image_in[C1_IMAGE_IN_ZISE], 
                    double kernel_w[C1_KERNEL_ZISE], 
                    double biases_w[C1_B_ZISE]) ;

C2_ref_struct REF_Conv_RELU_2(
                    double image_in[C2_IMAGE_IN_ZISE], 
                    double kernel_w[C2_KERNEL_ZISE], 
                    double biases_w[C2_B_ZISE]) ;

C3_ref_struct REF_Conv_RELU_3(
                    double image_in[C3_IMAGE_IN_ZISE], 
                    double kernel_w[C3_KERNEL_ZISE], 
                    double biases_w[C3_B_ZISE]) ;

struct REF_MXP_1_struct {
    double out_fmap[MXP_1_OUT_ZISE];
    };

struct REF_MXP_2_struct {
    double out_fmap[MXP_2_OUT_ZISE];
    };

struct REF_MXP_3_struct {
    double out_fmap[MXP_3_OUT_ZISE];
    };

struct REF_Reshape_struct {
    double out_fmap[180];
    };

struct REF_Percep_struct {
    double out_fmap[10];
    };

REF_MXP_1_struct REF_MAXPOOL_1( double (&image_in)[MXP_1_IMAGE_IN_ZISE]) ;
REF_MXP_2_struct REF_MAXPOOL_2( double (&image_in)[MXP_2_IMAGE_IN_ZISE]) ;
REF_MXP_3_struct REF_MAXPOOL_3( double (&image_in)[MXP_3_IMAGE_IN_ZISE]) ;

REF_Reshape_struct REF_Reshape(double matrice_in[MXP_3_OUT_ZISE]) ;

REF_Percep_struct REF_Perceptron(double matrice_in[180]) ;

#endif