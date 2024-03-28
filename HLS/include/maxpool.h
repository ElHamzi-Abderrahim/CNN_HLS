
#ifndef MAXPOOL
#define MAXPOOL

#include "all_includes.h"

/////////////////////////////////////////////////////////////////
       //            MAXPOOL 1 MACROS            //
/////////////////////////////////////////////////////////////////

// FEATURE MAP IN MACROS
#define MXP_1_I_IN_ROWS_ZISE       24    
#define MXP_1_I_IN_COLUMNS_ZISE    24
#define MXP_1_I_IN_CHANNELS_ZISE   64
#define MXP_1_IMAGE_IN_ZISE    MXP_1_I_IN_ROWS_ZISE*MXP_1_I_IN_COLUMNS_ZISE*MXP_1_I_IN_CHANNELS_ZISE

#define fmap_MAX1_in(y,x,channel)     (y)*MXP_1_I_IN_ROWS_ZISE+x+(channel)*(MXP_1_I_IN_ROWS_ZISE*MXP_1_I_IN_COLUMNS_ZISE)


// FEATURE MAP OUT
#define MXP_1_OUT_ROWS_ZISE       12
#define MXP_1_OUT_COLUMNS_ZISE    12
#define MXP_1_OUT_CHANNELS_ZISE   64
#define MXP_1_OUT_ZISE         MXP_1_OUT_ROWS_ZISE*MXP_1_OUT_COLUMNS_ZISE*MXP_1_OUT_CHANNELS_ZISE

#define out_MAX1(y,x,channel)     (y)*MXP_1_OUT_ROWS_ZISE+(x)+(channel)*(MXP_1_OUT_ROWS_ZISE* MXP_1_OUT_COLUMNS_ZISE)
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
       //            MAXPOOL 2 MACROS            //
/////////////////////////////////////////////////////////////////

// FEATURE MAP IN MACROS
#define MXP_2_I_IN_ROWS_ZISE       12    
#define MXP_2_I_IN_COLUMNS_ZISE    12
#define MXP_2_I_IN_CHANNELS_ZISE   32
#define MXP_2_IMAGE_IN_ZISE    MXP_2_I_IN_ROWS_ZISE*MXP_2_I_IN_COLUMNS_ZISE*MXP_2_I_IN_CHANNELS_ZISE

#define fmap_MAX2_in(y,x,channel)     (y)*MXP_2_I_IN_ROWS_ZISE+x+(channel)*(MXP_2_I_IN_ROWS_ZISE*MXP_2_I_IN_COLUMNS_ZISE)


// FEATURE MAP OUT
#define MXP_2_OUT_ROWS_ZISE       6
#define MXP_2_OUT_COLUMNS_ZISE    6
#define MXP_2_OUT_CHANNELS_ZISE   32
#define MXP_2_OUT_ZISE         MXP_2_OUT_ROWS_ZISE*MXP_2_OUT_COLUMNS_ZISE*MXP_2_OUT_CHANNELS_ZISE

#define out_MAX2(y,x,channel)     (y)*MXP_2_OUT_ROWS_ZISE+(x)+(channel)*(MXP_2_OUT_ROWS_ZISE* MXP_2_OUT_COLUMNS_ZISE)

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
       //            MAXPOOL 3 MACROS            //
/////////////////////////////////////////////////////////////////

// FEATURE MAP IN MACROS
#define MXP_3_I_IN_ROWS_ZISE       6    
#define MXP_3_I_IN_COLUMNS_ZISE    6
#define MXP_3_I_IN_CHANNELS_ZISE   20
#define MXP_3_IMAGE_IN_ZISE    MXP_3_I_IN_ROWS_ZISE*MXP_3_I_IN_COLUMNS_ZISE*MXP_3_I_IN_CHANNELS_ZISE

#define fmap_MAX3_in(y,x,channel)     (y)*MXP_3_I_IN_ROWS_ZISE+x+(channel)*(MXP_3_I_IN_ROWS_ZISE*MXP_3_I_IN_COLUMNS_ZISE)


// FEATURE MAP OUT
#define MXP_3_OUT_ROWS_ZISE       3
#define MXP_3_OUT_COLUMNS_ZISE    3
#define MXP_3_OUT_CHANNELS_ZISE   20
#define MXP_3_OUT_ZISE         MXP_3_OUT_ROWS_ZISE*MXP_3_OUT_COLUMNS_ZISE*MXP_3_OUT_CHANNELS_ZISE

#define out_MAX3(y,x,channel)     (y)*MXP_3_OUT_ROWS_ZISE+(x)+(channel)*(MXP_3_OUT_ROWS_ZISE* MXP_3_OUT_COLUMNS_ZISE)

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

struct MXP_1_out_struct {
    acc_type out_fmap[MXP_1_OUT_ZISE];
    };

struct MXP_2_out_struct {
    acc_type out_fmap[MXP_2_OUT_ZISE];
    };

struct MXP_3_out_struct {
    acc_type out_fmap[MXP_3_OUT_ZISE];
    };

MXP_1_out_struct MAXPOOL_1( acc_type (&image_in)[MXP_1_IMAGE_IN_ZISE]) ;
MXP_2_out_struct MAXPOOL_2( acc_type (&image_in)[MXP_2_IMAGE_IN_ZISE]) ;
MXP_3_out_struct MAXPOOL_3( acc_type (&image_in)[MXP_3_IMAGE_IN_ZISE]) ;


#endif

