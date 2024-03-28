

#include "maxpool.h"


MXP_1_out_struct MAXPOOL_1( acc_type (&image_in)[MXP_1_IMAGE_IN_ZISE])
{
    MXP_1_out_struct output_FM ;
    for(int channel = 0; channel<MXP_1_I_IN_CHANNELS_ZISE; channel++)
    {
        for(int row = 0; row<MXP_1_I_IN_ROWS_ZISE; row=row+2)
        {
            for(int column = 0; column<MXP_1_I_IN_COLUMNS_ZISE; column=column+2)
            {
                acc_type temp_max_val = 0 ;
                
                int row_window = (row == MXP_1_I_IN_ROWS_ZISE-2) ? 2 : 3 ;  
                int column_window = (column == MXP_1_I_IN_ROWS_ZISE-2) ? 2 : 3 ;
                
                for(int ty=0 ; ty < row_window; ty++) 
                    for(int tx=0 ; tx < column_window; tx++)
                    {   
                        temp_max_val = (image_in[fmap_MAX1_in(row+ty,column+tx, channel)] > temp_max_val) ? image_in[fmap_MAX1_in(row+ty,column+tx, channel)] : temp_max_val  ;   
                        // if (image_in[fmap_MAX1_in(row+ty,column+tx, channel)]> temp_max_val)
                        //     temp_max_val = image_in[fmap_MAX1_in(row+ty,column+tx, channel)] ;
                        // else 
                        //     temp_max_val = temp_max_val ;
                    }
                output_FM.out_fmap[out_MAX1(row/2,column/2,channel)] = temp_max_val ;
            }
        }
    }
    return output_FM ;
}


MXP_2_out_struct MAXPOOL_2(acc_type (&image_in)[MXP_2_IMAGE_IN_ZISE])
{
    MXP_2_out_struct output_FM ;
    for(int channel = 0; channel<MXP_2_I_IN_CHANNELS_ZISE; channel++)
    {
        for(int row = 0; row<MXP_2_I_IN_ROWS_ZISE; row=row+2)
        {
            for(int column = 0; column<MXP_2_I_IN_COLUMNS_ZISE; column=column+2)
            {
                acc_type temp_max_val = 0 ;
                
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


MXP_3_out_struct MAXPOOL_3( acc_type (&image_in)[MXP_3_IMAGE_IN_ZISE])
{

    MXP_3_out_struct output_FM ;
    for(int channel = 0; channel<MXP_3_I_IN_CHANNELS_ZISE; channel++)
    {
        for(int row = 0; row<MXP_3_I_IN_ROWS_ZISE; row=row+2)
        {
            for(int column = 0; column<MXP_3_I_IN_COLUMNS_ZISE; column=column+2)
            {
                acc_type temp_max_val = 0 ;
                
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





