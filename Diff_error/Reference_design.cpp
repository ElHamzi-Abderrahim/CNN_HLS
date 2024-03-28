

#include "convolution.h"

#include "Reference_design.h"
#include "Ref_Perceptron.h"


C1_ref_struct REF_Conv_RELU_1 (
                    double image_in[C1_IMAGE_IN_ZISE], 
                    double kernel_w[C1_KERNEL_ZISE], 
                    double biases_w[C1_B_ZISE])
{

    int num_kernels     = C1_OUT_CHANNELS_ZISE;
    static int x_out    = C1_OUT_COLUMNS_ZISE;
    static int y_out    = C1_OUT_ROWS_ZISE;

    double cnv_calc[C1_OUT_ZISE] ;

    C1_ref_struct out_cnv ; 

    double result_widnow_3x3[3*3] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

    double padded_image_in[(C1_OUT_ROWS_ZISE+2)*(C1_OUT_COLUMNS_ZISE+2)];

    double sum_win ;
    
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


C2_ref_struct   REF_Conv_RELU_2(
                    double image_in[C2_IMAGE_IN_ZISE], 
                    double kernel_w[C2_KERNEL_ZISE], 
                    double biases_w[C2_B_ZISE])
{

    int num_kernels     = C2_OUT_CHANNELS_ZISE;
    static int x_out    = C2_OUT_COLUMNS_ZISE;
    static int y_out    = C2_OUT_ROWS_ZISE;

    double cnv_calc[C2_OUT_ZISE] ;

    C2_ref_struct out_cnv ; 

    double result_widnow_3x3[3*3] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

    double padded_image_in[(C2_OUT_ROWS_ZISE+2)*(C2_OUT_COLUMNS_ZISE+2)];

    double sum_win ;

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


C3_ref_struct REF_Conv_RELU_3(
                    double image_in[C3_IMAGE_IN_ZISE], 
                    double kernel_w[C3_KERNEL_ZISE], 
                    double biases_w[C3_B_ZISE])
{

    int num_kernels     = C3_OUT_CHANNELS_ZISE;
    static int x_out    = C3_OUT_COLUMNS_ZISE;
    static int y_out    = C3_OUT_ROWS_ZISE;

    double cnv_calc[C3_OUT_ZISE] ;

    C3_ref_struct out_cnv ; 

    double result_widnow_3x3[3*3] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

    double padded_image_in[(C3_OUT_ROWS_ZISE+2)*(C3_OUT_COLUMNS_ZISE+2)];


    double sum_win ;

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





REF_MXP_1_struct REF_MAXPOOL_1( double (&image_in)[MXP_1_IMAGE_IN_ZISE])
{
    REF_MXP_1_struct output_FM ;
    for(int channel = 0; channel<MXP_1_I_IN_CHANNELS_ZISE; channel++)
    {
        for(int row = 0; row<MXP_1_I_IN_ROWS_ZISE; row=row+2)
        {
            for(int column = 0; column<MXP_1_I_IN_COLUMNS_ZISE; column=column+2)
            {
                double temp_max_val = 0 ;
                
                int row_window = (row == MXP_1_I_IN_ROWS_ZISE-2) ? 2 : 3 ;  
                int column_window = (column == MXP_1_I_IN_ROWS_ZISE-2) ? 2 : 3 ;
                
                for(int ty=0 ; ty < row_window; ty++) 
                    for(int tx=0 ; tx < column_window; tx++)
                    {   
                        temp_max_val = (image_in[fmap_MAX1_in(row+ty,column+tx, channel)] > temp_max_val) ? image_in[fmap_MAX1_in(row+ty,column+tx, channel)] : temp_max_val  ;   
                    }
                output_FM.out_fmap[out_MAX1(row/2,column/2,channel)] = temp_max_val ;
            }
        }
    }
    return output_FM ;
}

REF_MXP_2_struct REF_MAXPOOL_2( double (&image_in)[MXP_2_IMAGE_IN_ZISE])
{
    REF_MXP_2_struct output_FM ;
    for(int channel = 0; channel<MXP_2_I_IN_CHANNELS_ZISE; channel++)
    {
        for(int row = 0; row<MXP_2_I_IN_ROWS_ZISE; row=row+2)
        {
            for(int column = 0; column<MXP_2_I_IN_COLUMNS_ZISE; column=column+2)
            {
                double temp_max_val = 0 ;
                
                int row_window = (row == MXP_2_I_IN_ROWS_ZISE-2) ? 2 : 3 ;  
                int column_window = (column == MXP_2_I_IN_ROWS_ZISE-2) ? 2 : 3 ;
                
                for(int ty=0 ; ty < row_window; ty++) 
                    for(int tx=0 ; tx < column_window; tx++)
                    {   
                        temp_max_val = (image_in[fmap_MAX2_in(row+ty,column+tx, channel)] > temp_max_val) ? image_in[fmap_MAX2_in(row+ty,column+tx, channel)] : temp_max_val  ;   
                    }
                output_FM.out_fmap[out_MAX2(row/2,column/2,channel)] = temp_max_val ;
            }
        }
    }

    return output_FM ;
}

REF_MXP_3_struct REF_MAXPOOL_3( double (&image_in)[MXP_3_IMAGE_IN_ZISE])
{

    REF_MXP_3_struct output_FM ;
    for(int channel = 0; channel<MXP_3_I_IN_CHANNELS_ZISE; channel++)
    {
        for(int row = 0; row<MXP_3_I_IN_ROWS_ZISE; row=row+2)
        {
            for(int column = 0; column<MXP_3_I_IN_COLUMNS_ZISE; column=column+2)
            {
                double temp_max_val = 0 ;
                
                int row_window = (row == MXP_3_I_IN_ROWS_ZISE-2) ? 2 : 3 ;  
                int column_window = (column == MXP_3_I_IN_ROWS_ZISE-2) ? 2 : 3 ;
                
                for(int ty=0 ; ty < row_window; ty++) 
                    for(int tx=0 ; tx < column_window; tx++)
                    {   
                        temp_max_val = (image_in[fmap_MAX3_in(row+ty,column+tx, channel)] > temp_max_val) ? image_in[fmap_MAX3_in(row+ty,column+tx, channel)] : temp_max_val  ;   
                    }
                output_FM.out_fmap[out_MAX3(row/2,column/2,channel)] = temp_max_val ;
            }
        }
    }
    return output_FM ;
}


REF_Reshape_struct REF_Reshape(double matrice_in[MXP_3_OUT_ZISE])
{
    REF_Reshape_struct reshaped_matrice ;

    for(int row = 0; row<3; row++)
    {
        for(int column = 0; column<3; column++)
        {
            for(int channel = 0; channel<20; channel++)
            {
                reshaped_matrice.out_fmap[channel + 20*column + 3*row*20 ] = matrice_in[out_MAX3(row, column, channel)] ;
            }
        }
    }
    return reshaped_matrice ;
}


REF_Percep_struct REF_Perceptron(double matrice_in[180])
{

    REF_Percep_struct percept_results ;
    double sum_result ;

    for(int j = 0; j<10; j++)
    {
        sum_result = 0 ;
        for(int i = 0; i<180; i++)
        {
            sum_result += matrice_in[i] * local_weights[i*10+j].to_double() ;
        }
        percept_results.out_fmap[j] = sum_result + biases_local_weights[j].to_double() ;
    }
    return percept_results ;
}
