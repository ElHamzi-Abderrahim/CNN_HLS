import numpy as np

#####################################################
###################   MAX POOLING ###################
#####################################################
def Max_Pool(input_FM ,filter_size, stride) :
    dim_Fx = int(len(input_FM[0])/2.0)
    dim_Fy = int(len(input_FM[0])/2.0)
    dim_ch = len(input_FM)

    output_FM               = np.empty( (dim_ch, dim_Fx, dim_Fy) )
    nbre_iteration_column   = len(input_FM[0][0]) - filter_size[0] + 3
    nbre_iteration_row      = len(input_FM[0]) - filter_size[1] + 3

    for index_channel in range(len(input_FM)):
        for row in range(0, nbre_iteration_row, stride[1]):
            for column in range(0 , nbre_iteration_column, stride[0]):
                Filter_mat = input_FM[index_channel][ row: row+filter_size[1] , column: column+filter_size[0] ]
                # print(Filter_mat)
                column_out = int(column/stride[1])
                row_out = int(row/stride[0])

                output_FM[index_channel][row_out][column_out] = np.max(Filter_mat) 
                #print("The max of the frame: ", output_FM[index_channel][row_out][column_out])
    return output_FM


#####################################################
################ RESHAPING OPERATION ################
#####################################################
def Reshape_180_to_10(matrices_20x3x3):
    reshaped_matrice = np.zeros(20*3*3)

    for rows in range (3):
        for columns in range(3):
            for ch in range(20):
                reshaped_matrice[ch + 20*columns + 2*rows*20 ] = matrices_20x3x3[ch][rows][columns]
    
    return reshaped_matrice



#####################################################
################## FULLY CONNECTING #################
#####################################################
def Perceptrons(I_1x180, M_180x10, Biases_1x10):
    result_1x10 = np.empty(10)
    for j in range(10) :
        result_sum_Mult = 0
        for i in range(180) :
            result_sum_Mult += I_1x180[i] * M_180x10[i][j]
        result_1x10[j] = result_sum_Mult + Biases_1x10[j]
    return result_1x10

#####################################################
##################### SOFT MAX #####################
#####################################################
def Soft_max(matrice_10x1):
    Prob_appart_10x1 = np.empty(10)
    sum = 0 
    for inter in range(len(matrice_10x1)):
            sum += np.exp(matrice_10x1[inter])

    for iter in range(len(matrice_10x1)):
        Prob_appart_10x1[iter] = np.exp(matrice_10x1[iter])/sum

    return Prob_appart_10x1