

#include <cmath>
#include "last_stage_net.h"
#include "Perceptron.h"
#include "macros.h"


Reshape_out_struct Reshape(double matrice_in[3*3*20])
{
    Reshape_out_struct reshaped_matrice ;

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


Percep_out_struct Perceptron(double matrice_in[180])
{
    Percep_out_struct percept_results ;
    double sum_result ;

    for(int j = 0; j<10; j++)
    {
        sum_result = 0 ;
        for(int i = 0; i<180; i++)
        {
            sum_result += matrice_in[i] * local_weights[i*10+j] ;
        }
        percept_results.out_fmap[j] = sum_result + biases_local_weights[j] ;
    }
    return percept_results ;
}


SoftMax_out_struct Softmax(double matrice_in[10])
{
    SoftMax_out_struct softmax_results ;
    double sum_exp = 0 ;

    for(int j = 0; j<10; j++)
        sum_exp += exp(matrice_in[j]);

    for(int j = 0; j<10; j++)
        softmax_results.out_fmap[j] = exp(matrice_in[j])/sum_exp ;

    return softmax_results ;
}
