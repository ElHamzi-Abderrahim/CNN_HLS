
// Include files for data types
#include <cmath>
#include <fstream>
#include <iostream>

using namespace std ;

#include "mc_scverify.h"
#include "ac_fixed.h"
#include "ImgProcTest.h"
#include "convolution.h"
#include "maxpool.h"

#include "macros.h"
#include "images.h"

#include "image_processing.h"
#include "Conv1_weights.h"
#include "Conv2_weights.h"
#include "Conv3_weights.h"
#include "last_stage_net.h"

/* Pour  Compilation et exécution sur PC */

#ifndef CCS_MAIN
#define CCS_MAIN int main
#define CCS_DESIGN(d) d
#define CCS_RETURN(a)  return a
#endif


CCS_MAIN(int argc, char **argv) {
    
    /*       Processing image bloc         */

    ImageTuple_24 centered_image ;
    ImageTuple_24 normalized_Image ;

    centered_image      = centeringImage(image_0);

    normalized_Image    = normalizeImage(centered_image.image_24x24);


    /*      Convolution RELU 1 bloc       */
    C1_out_struct conv_1_result ;
    conv_1_result = Calc_Conv_RELU_1(   normalized_Image.image_24x24, 
                                        convolution_1_weights, 
                                        biases_1_weights    );


    /*      Maxpooling 1      */
    MXP_1_out_struct maxp_1_result ;
    maxp_1_result = MAXPOOL_1( (conv_1_result.out_fmap)) ;


    /*      Convolution RELU 2 bloc       */
    C2_out_struct conv_2_result ;
    conv_2_result = Calc_Conv_RELU_2(   maxp_1_result.out_fmap, 
                                        convolution_2_weights, 
                                        biases_2_weights    );


    /*      Maxpooling 2      */
    MXP_2_out_struct maxp_2_result ;
    maxp_2_result = MAXPOOL_2( (conv_2_result.out_fmap)) ;


    /*      Convolution RELU 3 bloc       */
    C3_out_struct conv_3_result ;
    conv_3_result = Calc_Conv_RELU_3(   maxp_2_result.out_fmap, 
                                        convolution_3_weights, 
                                        biases_3_weights    );

    /*       Maxpooling 3      */
    MXP_3_out_struct maxp_3_result ;
    maxp_3_result = MAXPOOL_3( (conv_3_result.out_fmap)) ;


    /*       Reshaping         */
    Reshape_out_struct reshaped_result ;
    reshaped_result = Reshape(maxp_3_result.out_fmap) ;

    /*      Fully connecting - perpectron / softmax   */

    Percep_out_struct perceptron_result ;
    perceptron_result = Perceptron(reshaped_result.out_fmap) ;
    

    
    SoftMax_out_struct softmax_result ;
    softmax_result = Softmax(perceptron_result.out_fmap) ;
    

    /*          Result of the stages         */

#ifdef NET_TESTING


// original image //
    for (int channel=0; channel < 3; channel++)
    {
        cout << "Original image : \n [ " ;
        for (int y=0; y < 32; y++)
        {
            for (int x=0; x < 32; x++)
            {
                cout << image_0[pixel_32(y,x,channel)] << " , " ;
            }
            cout << "]\n" << endl ;
            cout << "[{ " << y << " }]" << "\n" ; 
        }
        cout << " ++++++++++++++++++++++++++ " << endl ;
    }


// centered image //
    for (int channel=0; channel < 3; channel++)
    {
        cout << "Centered image : \n [ " ;
        for (int y=0; y < C1_OUT_ROWS_ZISE; y++)
        {
            for (int x=0; x < C1_OUT_ROWS_ZISE; x++)
            {
                cout << centered_image.image_24x24[out_1(y,x,channel)] << " , " ;
            }
            cout << "]\n" << endl ;
            cout << "[{ " << y << " }]" << "\n" ; 
        }
        cout << " ++++++++++++++++++++++++++ " << endl ;
    }

// normalized image //
    for (int channel=0; channel < 1; channel++)
    {
        cout << "Normalized image : \n [ " ;
        for (int y=0; y < 24; y++)
        {
            for (int x=0; x < 24; x++)
            {
                cout << normalized_Image.image_24x24[out_1(y,x,channel)] << " , " ;
            }
            cout << "]\n" << endl ;
            cout << "[{ " << y << " }]" << "\n" ; 
        }
        cout << " ++++++++++++++++++++++++++ " << endl ;
    }

// convolution 1 result //
    for (int channel=0; channel < 1; channel++)
    {
        cout << "Convolution 1 result : \n [ " ;
        for (int y=0; y < 24; y++)
        {
            for (int x=0; x < 24; x++)
            {
                cout << conv_1_result.out_fmap[out_1(y,x,channel)] << " , " ;
            }
            cout << "]\n" << endl ;
            cout << "[{ " << y << " }]" << "\n" ; 
        }
        cout << " ++++++++++++++++++++++++++ " << endl ;
    }


// maxpool 1 result //
    for (int channel=0; channel < 1; channel++)
    {
        cout << "maxpool 1 result : \n [ " ;
        for (int y=0; y < 12; y++)
        {
            for (int x=0; x < 12; x++)
            {
                cout << maxp_1_result.out_fmap[out_MAX1(y,x,channel)] << " , " ;
            }
            cout << "]\n" << endl ;
            cout << "[{ " << y << " }]" << "\n" ; 
        }
        cout << " ++++++++++++++++++++++++++ " << endl ;
    }


// convolution 2 result //
    for (int channel=0; channel < 1; channel++)
    {
        cout << "convolution 2 result : \n [ " ;
        for (int y=0; y < 12; y++)
        {
            for (int x=0; x < 12; x++)
            {
                cout << conv_2_result.out_fmap[out_2(y,x,channel)] << " , " ;
            }
            cout << "]\n" << endl ;
            cout << "[{ " << y << " }]" << "\n" ; 
        }
        cout << " ++++++++++++++++++++++++++ " << endl ;
    }


// maxpool 2 result //
    for (int channel=0; channel < 32; channel++)
    {
        cout << "maxpool 2 result : \n [ " ;
        for (int y=0; y < 6; y++)
        {
            for (int x=0; x < 6; x++)
            {
                cout << maxp_2_result.out_fmap[out_MAX2(y,x,channel)] << " , " ;
            }
            cout << "]\n" << endl ;
            cout << "[{ " << y << " }]" << "\n" ; 
        }
        cout << " ++++++++++++++++++++++++++ " << endl ;
    }



// convolution 3 result //
    for (int channel=0; channel < 20 ; channel++)
    {
        cout << "convolution 3 result : \n [ " ;
        for (int y=0; y < 6; y++)
        {
            for (int x=0; x < 6; x++)
            {
                cout << conv_3_result.out_fmap[out_3(y,x,channel)] << " , " ;
            }
            cout << "]\n" << endl ;
            cout << "[{ " << y << " }]" << "\n" ; 
        }
        cout << " ++++++++++++++++++++++++++ " << endl ;
    }

// maxpool 3 result //
    for (int channel=0; channel < 19; channel++)
    {
        cout << "maxpool 3 result : \n [ " ;
        for (int y=0; y < 3; y++)
        {
            for (int x=0; x < 3; x++)
            {
                cout << maxp_3_result.out_fmap[out_MAX3(y,x,channel)] << " , " ;
            }
            cout << "]\n" << endl ;
            cout << "[{ " << y << " }]" << "\n" ; 
        }
        cout << "\n ++++++++++++++++++++++++++ " << endl ;
    }

    
 #endif   
    // reshaping result //
    cout << "reshaping result : \n " ;
    for (int i=0; i < 180; i++)
    {
        cout << reshaped_result.out_fmap[i] << " , " ;
    }
    cout << "\n ++++++++++++++++++++++++++ " << endl ;


    // perceptron result //
    cout << "perceptron result : \n " ;
    for (int i=0; i < 10; i++)
    {
        cout << perceptron_result.out_fmap[i] << " , " ;
    }
    cout << "\n ++++++++++++++++++++++++++ " << endl ;


    // perceptron result //
    cout << "softmax result : \n " ;
    for (int i=0; i < 10; i++)
    {
        cout << softmax_result.out_fmap[i] << " , " ;
    }
    cout << "\n ++++++++++++++++++++++++++ " << endl ;


    double temp_max=0 ;
    int activated_class ;

    for (int i=0; i < 10; i++)
    {
        if(softmax_result.out_fmap[i]>temp_max)
        {
            activated_class = i ;
            temp_max = softmax_result.out_fmap[i] ;
        }

    }
    cout << "The activated class : " << activated_class << endl ;

    /*****************************************/

    CCS_RETURN(0);
}
  
