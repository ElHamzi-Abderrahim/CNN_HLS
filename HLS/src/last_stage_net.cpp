
#include "all_includes.h"


Reshape_out_struct Reshape(acc_type matrice_in[3*3*20])
{
    Reshape_out_struct reshaped_matrice ;

    R_y:for(int row = 0; row<3; row++)
    {
        R_x:for(int column = 0; column<3; column++)
        {
            R_ch:for(int channel = 0; channel<20; channel++)
            {
                reshaped_matrice.out_fmap[channel + 20*column + 3*row*20 ] = matrice_in[out_MAX3(row, column, channel)] ;
            }
        }
    }
    return reshaped_matrice ;
}


Percep_out_struct Perceptron(acc_type matrice_in[180])
{
    Percep_out_struct percept_results ;
    acc_type sum_result ;

    P_y:for(int j = 0; j<10; j++)
    {
        sum_result = 0 ;
        P_x:for(int i = 0; i<180; i++)
        {
            sum_result = sum_result + matrice_in[i] * local_weights[i*10+j] ;
        }
        percept_results.out_fmap[j] = sum_result + biases_local_weights[j] ;
    }
    return percept_results ;
}

