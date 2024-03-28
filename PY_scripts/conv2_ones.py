import matplotlib.pyplot as plt
import numpy as np


from image_processing import *
from Extracting_weights import *
# from Ext2_Mtrx_Files import *


def extract_conv1_weights():
    with open("data_project/CNN_coeff_3x3.txt", 'r') as file:
        lines = file.readlines()

    dimensions_step1 = [64, 3, 3, 3]
    dimensions = dimensions_step1
    start_line = 0
    label_conv = "tensor_name:  conv1/weights"

    kernel_dim  = 64
    channel_dim = 3
    row_dim     = 3
    column_dim  = 3

    m3x3_row        = 0
    m3x3_column     = 0
    m3x3_channel    = 0
    m3x3_kernel     = 0
    weights_in_file = np.zeros((column_dim, row_dim, channel_dim, kernel_dim))
    kernel_weights  = np.zeros((kernel_dim, channel_dim,row_dim, column_dim))

    im_in = False
    for line_indx in range(start_line, len(lines)):
        text_line = lines[line_indx][5:71]
        if not lines[line_indx].find(label_conv) and not im_in :
            im_in = True
            continue
        elif(im_in):
            for x in text_line.split():
                if(x == "_name:"):
                    break
                weights_in_file[m3x3_column][m3x3_row][m3x3_channel][m3x3_kernel] = float(x)
                kernel_weights[m3x3_kernel][m3x3_channel][m3x3_row][m3x3_column] = float(x)
                
                index_1dim += 1
                if index_1dim > kernel_dim-1 :
                    index_2dim += 1
                    index_1dim = 0
                    if index_2dim >  channel_dim-1 :
                        index_2dim = 0
                        index_3dim += 1
                        if index_3dim > row_dim-1 :
                            index_3dim = 0
                            index_4dim += 1
                            if index_4dim == column_dim :
                                break
        if column_dim == 3 :
            break
    return weights_in_file


matrice_conv1 = extract_conv1_weights()
matrice_biases_1 = extract_biases("tensor_name:  conv1/biases", 0)


def Calc_Conv_RELU_2(image_in, kernel_w, biases_w):
    num_kernels         = 32
    x_out, y_out        = 12, 12

    # image_in = image_in.tolist()

    cnv_calc            = np.zeros(( num_kernels, x_out, y_out))
    result_widnow_3x3   = np.zeros((3, 3))
    padded_image_in     = np.zeros((y_out+2, x_out+2))

    for iter_kernel in range(32):
        cnv_calc[iter_kernel,:,:] += biases_w[iter_kernel]
        for iter_channel in range(64):
            padded_image_in[1:y_out+1,1:x_out+1] =  image_in[iter_channel][:][:]
            for y in range(12):             # loop the rows
                for x in range(12):         # loop the columns
                    sum_win = 0
                    result_widnow_3x3 = padded_image_in[y:y+3,x:x+3] * kernel_w[:,:,iter_channel,iter_kernel]
                    for ty in range(3):     # loop to calculte the multiplication of each element with the window
                        for tx in range(3):
                            sum_win += result_widnow_3x3[ty][tx]
                    cnv_calc[iter_kernel][y][x] += sum_win
    # cnv_calc = np.transpose(cnv_calc, [2,0,1])
    cnv_calc = np.maximum(0, cnv_calc)       
    return cnv_calc     # image shape : channel=64, columns=24, rows=24


def convo2(image_in, kernel_2, bais_2):
    image_out = np.zeros((32, 12, 12))
    for c in range(32):
        for i in range(12):
            for j in range(12):
                res = bais_2[c]
                for l in range(64):
                    for m in range(3):
                        for n in range(3):
                            res += image_in[l][i+m][j+n] * kernel_2[m][n][l][c]
                image_out[c][i][j] = max(res, 0)
    return image_out

def padding_2(img):
    n=0
    l=[[[0 for i in range(14)] for j in range(14) ]for j in range(64)]
    for i in range(64):
        for j in range(12):
            for k in range(12):
                l[i][j+1][k+1]=img[i][j][k]
    return l

image = np.ones((64, 24, 24)) 
kernel = np.ones((3, 3, 3, 63))
biases  = np.ones((64))

padded_input_d = padding_2(image)

print(np.shape(image), " ----- ", np.shape(padded_input_d))

perfect = convo1(padded_input_d, kernel, biases) # out shape: kernel=64, rows=24, columns=24

mine    = Calc_Conv_RELU_1(image, kernel, biases) # out shape: columns=24, rows=24, kernel=64

print(perfect[0])
print("______________________________")
print("______________________________")
print("______________________________")

print(mine[0])


print("The result of the comparison : ")

print(np.array_equal(mine, perfect))

