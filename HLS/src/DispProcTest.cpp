
// Include files for data types

#include "ac_fixed.h"

#include "all_includes.h"
#define DELAY 10000
#define IMG_ITER 12


#pragma hls_design top
void DispProcTest ( d_type img_out[IMG_SIZE]
                  )
{
    int activated_class = 0 ;
    acc_type  Norm_image[24*24*3] ;
    d_type    img_temp[31*31] ;
    d_type    ext_image[217*217] ;


      /////////////////////////////////////////////////////////////////////
      ////////////////////////// READING THE IMAGE /////////////////////////////
      /////////////////////////////////////////////////////////////////////
      for(int iter_img = 0; iter_img<IMG_ITER; iter_img++)
      {
        D_ch:for (int iter_channel=0 ; iter_channel < 3; iter_channel++)
          D_Py:for(int i=0 ; i < 24; i++)
              D_Px:for(int j=0 ; j < 24; j++)
                  Norm_image[img_in(i,j,iter_channel)] = norm_images[24*(j)+(i)+(24*24*iter_channel)*iter_img+2*(iter_img+1)];


      /////////////////////////////////////////////////////////////////////
      ////////////////////////// CNN NETWORK  /////////////////////////////
      /////////////////////////////////////////////////////////////////////

        C1_out_struct conv_1_result ;
        conv_1_result = Calc_Conv_RELU_1( Norm_image, 
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

        CLAS_L:for(int i=0; i<10;i++)
        {
            if (perceptron_result.out_fmap[i] > temp_max)
            {
                temp_max = perceptron_result.out_fmap[i] ;
                activated_class = i ;
            }else 
                temp_max = temp_max ;
        }
      ///////////////////////////////////////////////////////////////////////////
      ///////////////////////////////////////////////////////////////////////////
        

      //////////////////////////////////////////////////////////////////////////////
      ////////////////////////// DISPLAY OF RESULTS IN /////////////////////////////
      //////////////////////////////////////////////////////////////////////////////

        ////////////////////////  31x31 IMAGE PROCESSING //////////////////////////
        lx : for(int y=0; y < 24; y++)
          ly : for(int x=0; x < 24; x++)
            {
                img_temp[31*(y+7)+x] = (norm_images[24*(y)+(x)+(24*24*3)*iter_img+2*(iter_img+1)] * norm_images[(24*24*3+2)*iter_img]) + norm_images[(24*24*3+2)*iter_img+1];
            }
        DPu:for (int y=0; y<7; y++)   // fill the upper side with white
            for (int x=0; x<31; x++)
              img_temp[y*31+x] = 255 ;

        DPr:for (int y=7; y<31; y++)  // fill the right side with white
              for (int x=24; x<31; x++)
                img_temp[y*31 +x] = 255 ;

        DPc:for (int y=0; y<7; y++)   // fill the upper right corner with the class number
            for (int x=0; x<7; x++)
              img_temp[y*31+x+24] = number_label[x+ 7*y+ activated_class*7*7]*255 ;


        //////////////////// FILLING THE LARGE IMAGE ///////////////////////
        DPLwy:for (int y=0; y<IMG_SIZE_ROW; y++)   
          DPLwx:for (int x=0; x<IMG_SIZE_COL; x++)
            img_out[x+IMG_SIZE_COL*y] = 255 ;

        ////////////////// RESISING THE LITTLE IMAGE+LABEL ///////////////////////////
        DPLy:for (int y=0; y<31; y++)   
          DPLx:for (int x=0; x<31; x++)
            DPLyb:for(int yb=0; yb<7; yb++)
              DPLxb:for (int xb=0; xb<7; xb++)
                  ext_image[x*7 + xb + (217*7)*y + yb*217] = img_temp[31*y+x] ;
                  
        //////////////// FILLING THE RESULT IMAGE OF 320x240 /////////////////
        DPL_imy:for(int fy=0 ; fy<217; fy++)
          DPL_imx:for(int fx=0 ; fx<217; fx++)
            img_out[fx+51+IMG_SIZE_COL*fy+IMG_SIZE_COL*10] = ext_image[fx+fy*217] ;

  
      ///////////////////////////////////////////////////////////////////////////
      ///////////////////////////////////////////////////////////////////////////
      

      ////////////////////////////////////////////////////////////////////////////////
      ////////////////////// DELAY BETWEEN THE IMAGES FOR DISPLAYING //////////////////
      ////////////////////////////////////////////////////////////////////////////////
        int d = DELAY ;
        int i = 100 ;
        DPL_dld:while(d) 
        { 
          d -=1; 
          DPL_dli:while(i) 
              i -= 1 ;
        }
        //if(iter_img==IMG_ITER-1) iter_img=0;
      

    } // end of for (img_iter..) loop


    ///////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////



} 

