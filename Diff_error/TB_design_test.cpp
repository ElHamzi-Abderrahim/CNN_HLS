
// Include files for data types
#include <fstream>
#include <iostream>

using namespace std ;

#include "mc_scverify.h"
#include "ac_fixed.h"

#include "CNN_Design.cpp"

#include "data_types.h"

#include "images.h"
#include "convolution.h"
#include "maxpool.h"



#include "Reference_design.cpp"
#include "Ref_Conv1_weights.h"
#include "Ref_Conv2_weights.h"
#include "Ref_Conv3_weights.h"
#include "ref_images.h"

/* Pour  Compilation et exécution sur PC */

#ifndef CCS_MAIN
#define CCS_MAIN int main
#define CCS_DESIGN(d) d
#define CCS_RETURN(a)  return a
#endif

CCS_MAIN(int argc, char **argv) {

    // acc_type result[CHANN*ROW*COLUMN] ;
    ca_type result ;
    
    REF_Percep_struct REF_result ;

    double worst_diff = 0 ;
    double diff ;

    double out_design ;
    double out_ref ;

    C1_ref_struct ref_Conv_1 ;
    ref_Conv_1 = REF_Conv_RELU_1(   ref_norm_image_0, 
                                    ref_convolution_1_weights, 
                                    ref_biases_1_weights    );

    REF_MXP_1_struct maxp_1_result ;
    maxp_1_result = REF_MAXPOOL_1(ref_Conv_1.out_fmap) ;

    C2_ref_struct ref_Conv_2 ;
    ref_Conv_2 = REF_Conv_RELU_2(   maxp_1_result.out_fmap, 
                                    ref_convolution_2_weights, 
                                    ref_biases_2_weights    );

    REF_MXP_2_struct maxp_2_result ;
    maxp_2_result = REF_MAXPOOL_2(ref_Conv_2.out_fmap) ;

    C3_ref_struct ref_Conv_3 ;
    ref_Conv_3 = REF_Conv_RELU_3(   maxp_2_result.out_fmap, 
                                    ref_convolution_3_weights, 
                                    ref_biases_3_weights    );

    REF_MXP_3_struct maxp_3_result ;
    maxp_3_result = REF_MAXPOOL_3(ref_Conv_3.out_fmap) ;

    REF_Reshape_struct reshaped_result ;
    reshaped_result = REF_Reshape(maxp_3_result.out_fmap) ;


    REF_Percep_struct perceptron_result ;
    perceptron_result = REF_Perceptron(reshaped_result.out_fmap) ;
    

    REF_result = perceptron_result ;


    CCS_DESIGN(CNN_Network)(norm_image_0, result) ;

    cout << "Starting verificatin" << endl ;

    ofstream simg_out("perceptron_out.txt");
    ofstream ref_simg_out("perceptron_out_1ref.txt");

    cout << "The activated calss is : " <<  result.to_ac_int() << endl ;

#ifdef EXCLUDE_PART 
    for(int i =0; i<10 ; i++)
    {
        cout << result[i].to_double() << endl; 
        simg_out << result[i].to_double() << endl;

        cout << REF_result.out_fmap[i] << endl; 
        ref_simg_out <<  REF_result.out_fmap[i] << endl;

        out_design = result[i].to_double() ;
        out_ref = REF_result.out_fmap[i] ;

        diff = out_ref - out_design ;

        diff = (diff<0) ? -diff : diff ;
        worst_diff = (diff > worst_diff) ? diff : worst_diff ;
    }

  
    cout << " ***********************************" << endl ;   
    // cout << "-DATA TYPES : " << endl ;
    cout << " + Coef type       : { " << (COEF_WIDTH) << " , " << (3) << "}" << endl ;
    cout << " + Data int type   : { " << (DATA_WIDTH) << " , " << (DATA_WIDTH) << "}" << endl ;
    cout << " + Mult/Acc type   : { " << DATA_WIDTH+COEF_WIDTH+HEAD_ROOM_WIDTH+2 << " , " << (DATA_WIDTH+HEAD_ROOM_WIDTH) << "}" << endl ;

    cout << "The worst difference (REF/DESIGN) is : " << worst_diff << endl ;   
#endif

    CCS_RETURN(0);

}
  
    // for(int ch=0; ch<3;ch++)
    //     for(int row=0; row<ROW;row++)
    //         for(int col=0; col<COLUMN;col++)
    //         {
    //             cout << result[out_MAX3(row, col, ch)].to_double() << endl; 
    //             simg_out << result[out_MAX3(row, col, ch)].to_double() << endl;

    //             cout << REF_result.out_fmap[out_MAX3(row, col, ch)] << endl; 
    //             ref_simg_out <<  REF_result.out_fmap[out_MAX3(row, col, ch)] << endl;

    //             out_design = result[out_MAX3(row, col, ch)].to_double() ;
    //             out_ref = REF_result.out_fmap[out_MAX3(row, col, ch)] ;

    //             diff = out_ref - out_design ;
                
    //             diff = (diff<0) ? -diff : diff ;
    //             worst_diff = (diff > worst_diff) ? diff : worst_diff ;
    //         }