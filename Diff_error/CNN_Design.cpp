
// Include files for data types
//#include "math.h"
#include <fstream>
#include <iostream>
#include <iomanip>
using namespace std ;

#include "data_types.h"

#include "mc_scverify.h"
#include "ac_fixed.h"

#include "CNN_Design.h"
#include "Conv1_weights.h"
#include "Conv2_weights.h"
#include "Conv3_weights.h"


#include "convolution.cpp"
#include "maxpool.cpp"
#include "last_stage_net.cpp"



#pragma hls_design top

void CNN_Network(
               acc_type image_in[24*24*3], 
                ca_type &design_result) {
               //  acc_type design_result[ROW*COLUMN*CHANN]) {

                  
    ca_type activated_calss ;

    C1_out_struct conv_1_result ;
    conv_1_result = Calc_Conv_RELU_1(   image_in, 
                                        convolution_1_weights, 
                                        biases_1_weights    );

    MXP_1_out_struct maxp_1_result ;
    maxp_1_result = MAXPOOL_1(conv_1_result.out_fmap) ;

    C2_out_struct conv_2_result ;
    conv_2_result = Calc_Conv_RELU_2(   maxp_1_result.out_fmap, 
                                        convolution_2_weights, 
                                        biases_2_weights    );

    MXP_2_out_struct maxp_2_result ;
    maxp_2_result = MAXPOOL_2(conv_2_result.out_fmap) ;

    C3_out_struct conv_3_result ;
    conv_3_result = Calc_Conv_RELU_3(   maxp_2_result.out_fmap, 
                                        convolution_3_weights, 
                                        biases_3_weights    );

    MXP_3_out_struct maxp_3_result ;
    maxp_3_result = MAXPOOL_3(conv_3_result.out_fmap) ;  

    Reshape_out_struct reshaped_result ;
    reshaped_result = Reshape(maxp_3_result.out_fmap) ;

    
    Percep_out_struct perceptron_result ;
    perceptron_result = Perceptron(reshaped_result.out_fmap) ;
    
    acc_type temp_max = 0 ;
    acc_type iter = 0 ;

    for(int i=0; i<10;i++)
    {
      // temp_max = (perceptron_result.out_fmap[i] > temp_max) ? perceptron_result.out_fmap[i] : temp_max ;
      if (perceptron_result.out_fmap[i] > temp_max)
      {
         temp_max = perceptron_result.out_fmap[i] ;
         activated_calss = iter ;
      }else 
         temp_max = temp_max ;
      iter += 1 ;
      
    }
   cout << activated_calss.to_ac_int() << endl ;
   design_result =  activated_calss ;
   cout << "design result " << design_result << endl ;

   // for (int i=0; i<4;i++)
   //    design_result[i] =  temp_max[i];





    // for(int ch=0; ch<CHANN;ch++)
    //     for(int row=0; row<ROW;row++)
    //         for(int col=0; col<COLUMN;col++)
    //         {
    //             design_result[out_MAX3(row, col, ch)] =  maxp_3_result.out_fmap[out_MAX3(row, col, ch)];
    //         }
}
  
