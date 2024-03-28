#include <iostream>

#include "convolution.h"


using namespace std ;

C1_out_struct Calc_Conv_RELU_1(
                    acc_type image_in[C1_IMAGE_IN_ZISE], 
                    coef_type kernel_w[C1_KERNEL_ZISE], 
                    coef_type biases_w[C1_B_ZISE])
{

    int num_kernels     = C1_OUT_CHANNELS_ZISE;
    static int x_out    = C1_OUT_COLUMNS_ZISE;
    static int y_out    = C1_OUT_ROWS_ZISE;

    acc_type cnv_calc[C1_OUT_ZISE] ;

    C1_out_struct out_cnv ; 

    acc_type result_widnow_3x3[3*3] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
   
    acc_type padded_image_in[(C1_OUT_ROWS_ZISE+2)*(C1_OUT_COLUMNS_ZISE+2)];

    acc_type sum_win ;
    
    for(int y=0 ; y < y_out+2; y++){ // fill the padded image with zeros
        for(int x=0 ; x < x_out+2; x++){
            padded_image_in[indx_pad_1(y,x)] = 0 ;}}

    for (int iter_kernel=0 ; iter_kernel < num_kernels ; iter_kernel++)
    {
        for(int y=0 ; y < y_out; y ++){ // fill the cnv_clac with biases[kernel_index] 
            for(int x=0 ; x < x_out; x++){
                out_cnv.out_fmap[out_1(y,x,iter_kernel)] = 0 ;
                out_cnv.out_fmap[out_1(y,x,iter_kernel)] += biases_w[iter_kernel];
                }}

        for (int iter_channel=0 ; iter_channel < C1_K_CHANNELS_ZISE; iter_channel++)
        {
            for(int i=1 ; i < y_out+1; i++){
                for(int j=1 ; j < x_out+1; j++){
                    padded_image_in[indx_pad_1(i,j)] = image_in[img_in(i-1,j-1,iter_channel)];
                    }}

            for(int y=0 ; y < y_out; y++)
            {
                for(int x=0 ; x < x_out; x++)
                {
                    sum_win = 0 ;
                    for(int my=0 ; my < 3; my++) // loop to calculte the multiplication of each element with the window
                        for(int mx=0 ; mx < 3; mx++)
                        {
                            result_widnow_3x3[3*my+mx] = padded_image_in[indx_pad_1(y+my,x+mx)] * kernel_w[ker1(my,mx,iter_channel,iter_kernel)] ;                             
                        }
                    for(int ty=0 ; ty < 3; ty++){   // loop to calculte the multiplication of each element with the window
                        for(int tx=0 ; tx < 3; tx++){
                            sum_win = sum_win + result_widnow_3x3[3*ty+tx];}}
      
                    out_cnv.out_fmap[out_1(y,x,iter_kernel)] += sum_win ;
                    cnv_calc[out_1(y,x,iter_kernel)] += sum_win ;
                }
            }
        }
    }
    for (int iter_kernel=0 ; iter_kernel < num_kernels ; iter_kernel++)
        for(int y=0 ; y < y_out; y++)
                for(int x=0 ; x < x_out; x++)
                {
                    if(out_cnv.out_fmap[out_1(y,x,iter_kernel)] <= 0)
                        out_cnv.out_fmap[out_1(y,x,iter_kernel)] = 0 ;
                    else if (out_cnv.out_fmap[out_1(y,x,iter_kernel)] > 0)
                    {
                        out_cnv.out_fmap[out_1(y,x,iter_kernel)] = out_cnv.out_fmap[out_1(y,x,iter_kernel)] ;
                    }  
                }

    return out_cnv ;    // image shape : channel=64, columns=24, rows=24
}



C2_out_struct Calc_Conv_RELU_2(
                    acc_type image_in[C2_IMAGE_IN_ZISE], 
                    coef_type kernel_w[C2_KERNEL_ZISE], 
                    coef_type biases_w[C2_B_ZISE])
{

    int num_kernels     = C2_OUT_CHANNELS_ZISE;
    static int x_out    = C2_OUT_COLUMNS_ZISE;
    static int y_out    = C2_OUT_ROWS_ZISE;

    acc_type cnv_calc[C2_OUT_ZISE] ;

    C2_out_struct out_cnv ; 

    acc_type result_widnow_3x3[3*3] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

    acc_type padded_image_in[(C2_OUT_ROWS_ZISE+2)*(C2_OUT_COLUMNS_ZISE+2)];

    acc_type sum_win ;

    for(int y=0 ; y < y_out+2; y++){ // fill the padded image with zeros
        for(int x=0 ; x < x_out+2; x++){
            padded_image_in[indx_pad_2(y,x)] = 0 ;}}

    for (int iter_kernel=0 ; iter_kernel < num_kernels ; iter_kernel++)
    {
        for(int y=0 ; y < y_out; y ++){ // fill the cnv_clac with biases[kernel_index] 
            for(int x=0 ; x < x_out; x++){
                out_cnv.out_fmap[out_2(y,x,iter_kernel)] = 0 ;
                out_cnv.out_fmap[out_2(y,x,iter_kernel)] += biases_w[iter_kernel];
                }}

        for (int iter_channel=0 ; iter_channel < C2_K_CHANNELS_ZISE; iter_channel++)
        {
            for(int i=1 ; i < y_out+1; i++){
                for(int j=1 ; j < x_out+1; j++){
                    padded_image_in[indx_pad_2(i,j)] = image_in[fmap_2_in(i-1,j-1,iter_channel)];
                    }}

            for(int y=0 ; y < y_out; y++)
            {
                for(int x=0 ; x < x_out; x++)
                {
                    sum_win = 0 ;
                    
                    for(int my=0 ; my < 3; my++) // loop to calculte the multiplication of each element with the window
                        for(int mx=0 ; mx < 3; mx++)
                        {
                            result_widnow_3x3[3*my+mx] = padded_image_in[indx_pad_2(y+my,x+mx)] * kernel_w[ker2(my,mx,iter_channel,iter_kernel)] ;         
                        }
                    for(int ty=0 ; ty < 3; ty++){   // loop to calculte the multiplication of each element with the window
                        for(int tx=0 ; tx < 3; tx++){
                            sum_win += result_widnow_3x3[3*ty+tx];}}
      
                    out_cnv.out_fmap[out_2(y,x,iter_kernel)] += sum_win ;
                    cnv_calc[out_2(y,x,iter_kernel)] += sum_win ;
                }
            }
        }
    }
    for (int iter_kernel=0 ; iter_kernel < num_kernels ; iter_kernel++)
        for(int y=0 ; y < y_out; y++)
                for(int x=0 ; x < x_out; x++)
                {
                    if(out_cnv.out_fmap[out_2(y,x,iter_kernel)] <= 0)
                        out_cnv.out_fmap[out_2(y,x,iter_kernel)] = 0 ;
                    else if (out_cnv.out_fmap[out_2(y,x,iter_kernel)] > 0)
                    {
                        out_cnv.out_fmap[out_2(y,x,iter_kernel)] = out_cnv.out_fmap[out_2(y,x,iter_kernel)] ;
                    }  
                }

    return out_cnv ;    // image shape : channel=64, columns=24, rows=24
}



C3_out_struct Calc_Conv_RELU_3(
                    acc_type image_in[C3_IMAGE_IN_ZISE], 
                    coef_type kernel_w[C3_KERNEL_ZISE], 
                    coef_type biases_w[C3_B_ZISE])
{

    int num_kernels     = C3_OUT_CHANNELS_ZISE;
    static int x_out    = C3_OUT_COLUMNS_ZISE;
    static int y_out    = C3_OUT_ROWS_ZISE;

    acc_type cnv_calc[C3_OUT_ZISE] ;

    C3_out_struct out_cnv ; 

    acc_type result_widnow_3x3[3*3] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

    acc_type padded_image_in[(C3_OUT_ROWS_ZISE+2)*(C3_OUT_COLUMNS_ZISE+2)];


    acc_type sum_win ;

    for(int y=0 ; y < y_out+2; y++){ // fill the padded image with zeros
        for(int x=0 ; x < x_out+2; x++){
            padded_image_in[indx_pad_3(y,x)] = 0 ;}}

    for (int iter_kernel=0 ; iter_kernel < num_kernels ; iter_kernel++)
    {
        for(int y=0 ; y < y_out; y ++){ // fill the cnv_clac with biases[kernel_index] 
            for(int x=0 ; x < x_out; x++){
                out_cnv.out_fmap[out_3(y,x,iter_kernel)] = 0 ;
                out_cnv.out_fmap[out_3(y,x,iter_kernel)] += biases_w[iter_kernel];
                }}

        for (int iter_channel=0 ; iter_channel < C3_K_CHANNELS_ZISE; iter_channel++)
        {
            for(int i=1 ; i < y_out+1; i++){
                for(int j=1 ; j < x_out+1; j++){
                    padded_image_in[indx_pad_3(i,j)] = image_in[fmap_3_in(i-1,j-1,iter_channel)];
                    }}

            for(int y=0 ; y < y_out; y++)
            {
                for(int x=0 ; x < x_out; x++)
                {
                    sum_win = 0 ;

                    for(int my=0 ; my < 3; my++) // loop to calculte the multiplication of each element with the window
                        for(int mx=0 ; mx < 3; mx++)
                        {
                            result_widnow_3x3[3*my+mx] = padded_image_in[indx_pad_3(y+my,x+mx)] * kernel_w[ker3(my,mx,iter_channel,iter_kernel)] ;                             
                        }
                    for(int ty=0 ; ty < 3; ty++){   // loop to calculte the multiplication of each element with the window
                        for(int tx=0 ; tx < 3; tx++){
                            sum_win += result_widnow_3x3[3*ty+tx];}}
      
                    out_cnv.out_fmap[out_3(y,x,iter_kernel)] += sum_win ;
                    cnv_calc[out_3(y,x,iter_kernel)] += sum_win ;
                }
            }
        }
    }
    for (int iter_kernel=0 ; iter_kernel < num_kernels ; iter_kernel++)
        for(int y=0 ; y < y_out; y++)
                for(int x=0 ; x < x_out; x++)
                {
                    if(out_cnv.out_fmap[out_3(y,x,iter_kernel)] <= 0)
                        out_cnv.out_fmap[out_3(y,x,iter_kernel)] = 0 ;
                    else if (out_cnv.out_fmap[out_3(y,x,iter_kernel)] > 0)
                    {
                        out_cnv.out_fmap[out_3(y,x,iter_kernel)] = out_cnv.out_fmap[out_3(y,x,iter_kernel)] ;
                    }  
                }

    return out_cnv ;    // image shape : channel=64, columns=24, rows=24
}


