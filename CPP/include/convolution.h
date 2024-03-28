

#ifndef CONVOL
#define CONVOL


/////////////////////////////////////////////////////////////////
       //            CONVOLUTION 1 MACROS            //
/////////////////////////////////////////////////////////////////

// IMAGE IN MACROS
#define C1_I_IN_ROWS_ZISE       24    
#define C1_I_IN_COLUMNS_ZISE    24
#define C1_I_IN_CHANNELS_ZISE   3
#define C1_IMAGE_IN_ZISE    C1_I_IN_ROWS_ZISE*C1_I_IN_COLUMNS_ZISE*C1_I_IN_CHANNELS_ZISE

#define img_in(y,x,channel)     (y)*C1_I_IN_ROWS_ZISE+x+(channel)*(C1_I_IN_ROWS_ZISE*C1_I_IN_COLUMNS_ZISE)

// KERNEL IN MACROS
#define C1_K_ROWS_ZISE       3
#define C1_K_COLUMNS_ZISE    3
#define C1_K_CHANNELS_ZISE   3
#define C1_K_KERNEL_ZISE     64
#define C1_KERNEL_ZISE    C1_K_ROWS_ZISE*C1_K_COLUMNS_ZISE*C1_K_CHANNELS_ZISE*C1_K_KERNEL_ZISE

#define ker1(y,x,channel,kernel)     (channel)*C1_K_KERNEL_ZISE+(kernel)+(x)*C1_K_CHANNELS_ZISE*C1_K_KERNEL_ZISE+(y)*C1_K_COLUMNS_ZISE*C1_K_CHANNELS_ZISE*C1_K_KERNEL_ZISE

// BIASES IN
#define C1_B_ZISE     64

// FEATURE MAP OUT
#define C1_OUT_ROWS_ZISE       24
#define C1_OUT_COLUMNS_ZISE    24
#define C1_OUT_CHANNELS_ZISE   64
#define C1_OUT_ZISE         C1_OUT_ROWS_ZISE*C1_OUT_COLUMNS_ZISE*C1_OUT_CHANNELS_ZISE

#define out_1(y,x,channel)     (y)*C1_OUT_ROWS_ZISE+(x)+(channel)*(C1_OUT_ROWS_ZISE* C1_OUT_COLUMNS_ZISE)

#define indx_pad_1(y,x)     (y)*(C1_OUT_ROWS_ZISE+2)+x

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
       //            CONVOLUTION 2 MACROS            //
/////////////////////////////////////////////////////////////////

// IMAGE IN MACROS
#define C2_I_IN_ROWS_ZISE       12    
#define C2_I_IN_COLUMNS_ZISE    12
#define C2_I_IN_CHANNELS_ZISE   64
#define C2_IMAGE_IN_ZISE    C2_I_IN_ROWS_ZISE*C2_I_IN_COLUMNS_ZISE*C2_I_IN_CHANNELS_ZISE

#define fmap_2_in(y,x,channel)     (y)*C2_I_IN_ROWS_ZISE+x+(channel)*(C2_I_IN_ROWS_ZISE*C2_I_IN_COLUMNS_ZISE)

// KERNEL IN MACROS
#define C2_K_ROWS_ZISE       3
#define C2_K_COLUMNS_ZISE    3
#define C2_K_CHANNELS_ZISE   64
#define C2_K_KERNEL_ZISE     32
#define C2_KERNEL_ZISE    C2_K_ROWS_ZISE*C2_K_COLUMNS_ZISE*C2_K_CHANNELS_ZISE*C2_K_KERNEL_ZISE

// #define ker2(y,x,channel,kernel)     (y)*C2_K_ROWS_ZISE+x+(channel)*C2_K_CHANNELS_ZISE+(kernel)*(C2_K_ROWS_ZISE*C2_K_COLUMNS_ZISE*C2_K_CHANNELS_ZISE)

#define ker2(y,x,channel,kernel)     (channel)*C2_K_KERNEL_ZISE+(kernel)+(x)*C2_K_CHANNELS_ZISE*C2_K_KERNEL_ZISE+(y)*C2_K_COLUMNS_ZISE*C2_K_CHANNELS_ZISE*C2_K_KERNEL_ZISE

// BIASES IN
#define C2_B_ZISE     32

// FEATURE MAP OUT
#define C2_OUT_ROWS_ZISE       12
#define C2_OUT_COLUMNS_ZISE    12
#define C2_OUT_CHANNELS_ZISE   32
#define C2_OUT_ZISE         C2_OUT_ROWS_ZISE*C2_OUT_COLUMNS_ZISE*C2_OUT_CHANNELS_ZISE

#define out_2(y,x,channel)     (y)*C2_OUT_ROWS_ZISE+(x)+(channel)*(C2_OUT_ROWS_ZISE* C2_OUT_COLUMNS_ZISE)

#define indx_pad_2(y,x)     (y)*(C2_OUT_ROWS_ZISE+2)+x


///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
       //            CONVOLUTION 3 MACROS            //
/////////////////////////////////////////////////////////////////

// REATURE MAP IN MACROS
#define C3_I_IN_ROWS_ZISE       6    
#define C3_I_IN_COLUMNS_ZISE    6
#define C3_I_IN_CHANNELS_ZISE   32
#define C3_IMAGE_IN_ZISE    C3_I_IN_ROWS_ZISE*C3_I_IN_COLUMNS_ZISE*C3_I_IN_CHANNELS_ZISE

#define fmap_3_in(y,x,channel)     (y)*C3_I_IN_ROWS_ZISE+x+(channel)*(C3_I_IN_ROWS_ZISE*C3_I_IN_COLUMNS_ZISE)

// KERNEL IN MACROS
#define C3_K_ROWS_ZISE       3
#define C3_K_COLUMNS_ZISE    3
#define C3_K_CHANNELS_ZISE   32
#define C3_K_KERNEL_ZISE     20
#define C3_KERNEL_ZISE    C3_K_ROWS_ZISE*C3_K_COLUMNS_ZISE*C3_K_CHANNELS_ZISE*C3_K_KERNEL_ZISE

#define ker3(y,x,channel,kernel)     (channel)*C3_K_KERNEL_ZISE+(kernel)+(x)*C3_K_CHANNELS_ZISE*C3_K_KERNEL_ZISE+(y)*C3_K_COLUMNS_ZISE*C3_K_CHANNELS_ZISE*C3_K_KERNEL_ZISE

// BIASES IN
#define C3_B_ZISE     20

// FEATURE MAP OUT
#define C3_OUT_ROWS_ZISE       6
#define C3_OUT_COLUMNS_ZISE    6
#define C3_OUT_CHANNELS_ZISE   20
#define C3_OUT_ZISE         C3_OUT_ROWS_ZISE*C3_OUT_COLUMNS_ZISE*C3_OUT_CHANNELS_ZISE

#define out_3(y,x,channel)     (y)*C3_OUT_ROWS_ZISE+(x)+(channel)*(C3_OUT_ROWS_ZISE* C3_OUT_COLUMNS_ZISE)

#define indx_pad_3(y,x)     (y)*(C3_OUT_ROWS_ZISE+2)+x

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////


using namespace std ;

struct C1_out_struct {
    double out_fmap[C1_OUT_ZISE];
    };

struct C2_out_struct {
double out_fmap[C2_OUT_ZISE];
};

struct C3_out_struct {
    double out_fmap[C3_OUT_ZISE];
    };


C1_out_struct Calc_Conv_RELU_1(
                    double image_in[C1_IMAGE_IN_ZISE], 
                    double kernel_w[C1_KERNEL_ZISE], 
                    double biases_w[C1_B_ZISE]) ;

C2_out_struct Calc_Conv_RELU_2(
                    double image_in[C2_IMAGE_IN_ZISE], 
                    double kernel_w[C2_KERNEL_ZISE], 
                    double biases_w[C2_B_ZISE]) ;


C3_out_struct Calc_Conv_RELU_3(
                    double image_in[C3_IMAGE_IN_ZISE], 
                    double kernel_w[C3_KERNEL_ZISE], 
                    double biases_w[C3_B_ZISE]) ;

#endif
