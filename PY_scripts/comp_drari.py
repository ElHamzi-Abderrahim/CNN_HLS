
import numpy as np

from colv_relu_valid import *
from image_processing import *
from Extracting_weights import *

from Drari_maxpool import *

out_dim_step1 = [64, 24, 24]
out_dim_step2 = [32, 12, 12]
out_dim_step3 = [20, 6, 6]
maxP_filter = [3, 3]
maxP_stride = [2, 2]

W = [3, 64, 32, 180]
B = [64, 32, 20, 10]
def get_kernel_matrix(kernel, conv_type, bias, weights):
    cnt = 0
    kernel.seek(0, 0)
    b = []
    w = []

    for line in kernel:
        mot = line.split(': ')
        if mot[0] == 'tensor_name':
            cnt += 1    
        if cnt == (2 * conv_type) - 1:
            # get biases
            for i in range(bias[conv_type - 1] // 6 + 1):
                line = kernel.readline()
                line = line[1:]
                mot = line.split()
                if line[-2] == ']':
                    line = line[:-2]
                    mot = line.split()
                b += [float(elm) for elm in mot] 
            # get weights
            if(conv_type<=3):
                line = kernel.readline()
                for n in range(3):
                    x = []
                    for m in range(3):
                        y = []
                        for l in range(weights[conv_type - 1]):
                            z = []
                            for i in range(bias[conv_type - 1] // 4):
                                line = kernel.readline()
                                line = line[5:]
                                mot = line.split()
                                index = line.find(']')
                                if index != -1:
                                    line = line[:index]
                                    mot = line.split()
                                z += [float(elm) for elm in mot]
                            y.append(z)
                        line = kernel.readline()
                        x.append(y)
                    line = kernel.readline()
                    w.append(x)
            else:
                line = kernel.readline()
                for l in range(180):
                    z = []
                    for i in range(3):
                        line = kernel.readline()
                        line = line[2:]
                        mot = line.split()
                        if line[-3] == ']':
                            line = line[:-3]
                            mot = line.split()
                        if line[-2] == ']':
                            line = line[:-2]
                            mot = line.split()
                        z += [float(elm) for elm in mot]
                    w.append(z)
            return b, w
W = [3, 64, 32, 180]
B = [64, 32, 20, 10]
kernel=open("data_project/CNN_coeff_3x3.txt",'r')
#print(get_kernel_matrix(kernel,3,B,W)[1])
kernel_1=get_kernel_matrix(kernel,1,B,W)[1]
kernel_2=get_kernel_matrix(kernel,2,B,W)[1]
kernel_3=get_kernel_matrix(kernel,3,B,W)[1]
bais_1=get_kernel_matrix(kernel,1,B,W)[0]
bais_2=get_kernel_matrix(kernel,2,B,W)[0]
bais_3=get_kernel_matrix(kernel,3,B,W)[0]

def convo1(image_in, kernel_1, bais_1):
    image_out = np.zeros((64, 24, 24))
    for c in range(64):
        for i in range(24):
            for j in range(24):
                res = bais_1[c]
                for l in range(3):
                    for m in range(3):
                        for n in range(3):
                            res += image_in[l][i+m][j+n] * kernel_1[m][n][l][c]
                image_out[c][i][j] = max(res, 0)
    return image_out

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

def convo3(image_in, kernel_3, bais_3):
    image_out = np.zeros((20, 6, 6))
    for c in range(20):
        for i in range(6):
            for j in range(6):
                res = bais_3[c]
                for l in range(32):
                    for m in range(3):
                        for n in range(3):
                            res += image_in[l][i+m][j+n] * kernel_3[m][n][l][c]
                image_out[c][i][j] = max(res, 0)
    return image_out

def get_kernel_matrix(kernel, conv_type, bias, weights):
    cnt = 0
    kernel.seek(0, 0)
    b = []
    w = []

    for line in kernel:
        mot = line.split(': ')
        if mot[0] == 'tensor_name':
            cnt += 1    
        if cnt == (2 * conv_type) - 1:
            # get biases
            for i in range(bias[conv_type - 1] // 6 + 1):
                line = kernel.readline()
                line = line[1:]
                mot = line.split()
                if line[-2] == ']':
                    line = line[:-2]
                    mot = line.split()
                b += [float(elm) for elm in mot] 
            # get weights
            if(conv_type<=3):
                line = kernel.readline()
                for n in range(3):
                    x = []
                    for m in range(3):
                        y = []
                        for l in range(weights[conv_type - 1]):
                            z = []
                            for i in range(bias[conv_type - 1] // 4):
                                line = kernel.readline()
                                line = line[5:]
                                mot = line.split()
                                index = line.find(']')
                                if index != -1:
                                    line = line[:index]
                                    mot = line.split()
                                z += [float(elm) for elm in mot]
                            y.append(z)
                        line = kernel.readline()
                        x.append(y)
                    line = kernel.readline()
                    w.append(x)
            else:
                line = kernel.readline()
                for l in range(180):
                    z = []
                    for i in range(3):
                        line = kernel.readline()
                        line = line[2:]
                        mot = line.split()
                        if line[-3] == ']':
                            line = line[:-3]
                            mot = line.split()
                        if line[-2] == ']':
                            line = line[:-2]
                            mot = line.split()
                        z += [float(elm) for elm in mot]
                    w.append(z)
            return b, w

def rehape(tab_in):
    tab_out=[0 for i in range(180)]
    for i in range(3):
        for j in range(3):
            for k in range(20):
                tab_out[k+i*2*20+j*20]=tab_in[k][i][j]
    return tab_out

W = [3, 64, 32, 180]
B = [64, 32, 20, 10]
def perception(tab_in):
    ker=open("CNN_coeff_3x3.txt",'r')
    tab_out=[0 for i in range(10)]
    kernel=get_kernel_matrix(ker,4,B,W)[1]
    bais=get_kernel_matrix(ker,4,B,W)[0]
    for i in range(10):
        tmp=0
        for j in range(180):
            tmp+=kernel[j][i]*tab_in[j]
        tmp+=bais[i]
        tab_out[i]=tmp
    return tab_out


kernel=open("data_project/CNN_coeff_3x3.txt",'r')
kernel_1=get_kernel_matrix(kernel,1,B,W)[1]
biase1 =get_kernel_matrix(kernel,1,B,W)[0]



def Calc_Conv_RELU_1(image_in, kernel_w, biases_w):
    num_kernels         = 64
    x_out, y_out        = 24, 24
    
    cnv_calc            = np.zeros(( x_out, y_out, num_kernels))
    result_widnow_3x3   = np.zeros((3, 3))
    padded_image_in     = np.zeros((y_out+2, x_out+2))

    for iter_kernel in range(num_kernels):
        cnv_calc[:,:, iter_kernel] += biases_w[iter_kernel]
        for iter_channel in range(len(kernel_w[0])):
            padded_image_in[1:y_out+1,1:x_out+1] =  image_in[iter_channel][:][:]
            for y in range(24):             # loop the rows
                for x in range(24):         # loop the columns
                    sum_win = 0
                    result_widnow_3x3 = padded_image_in[y:y+3,x:x+3] * kernel_w[:,:,iter_channel,iter_kernel]
                    for ty in range(3):     # loop to calculte the multiplication of each element with the window
                        for tx in range(3):
                            sum_win += result_widnow_3x3[ty][tx]
                    cnv_calc[y][x][iter_kernel] += sum_win
    cnv_calc = np.transpose(cnv_calc, [2,0,1])
    cnv_calc = np.maximum(0, cnv_calc)       
    return cnv_calc     # image shape : channel=64, columns=24, rows=24

def padding(img):
    n=0
    l=[[[0 for i in range(26)] for j in range(26) ]for j in range(3)]
    for i in range(3):
        for j in range(24):
            for k in range(24):
                l[i][j+1][k+1]=img[i][j][k]
    return l

################################################################################
################################################################################
################################################################################
################################################################################
################################################################################
################################################################################

images = Binary_to_Tuple()
centered_image = centering_image(images[4])
normalized_image = normalizing_image(centered_image)

padded_input_d      = padding(normalized_image)




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



# print(maxpooledDrari_1[0])
# print("_________________________________________________")
# print("_________________________________________________")
# print("_________________________________________________")
# print("_________________________________________________")
# print("_________________________________________________")

# print(max_pooled_1[0])




kernel_1=get_kernel_matrix(kernel,1,B,W)[1]
kernel_2=get_kernel_matrix(kernel,2,B,W)[1]
kernel_3=get_kernel_matrix(kernel,3,B,W)[1]
bais_1=get_kernel_matrix(kernel,1,B,W)[0]
bais_2=get_kernel_matrix(kernel,2,B,W)[0]
bais_3=get_kernel_matrix(kernel,3,B,W)[0]
n=3
c=0
NUM=4
mat_max=[]
mat_max1=[]
mat_max2=[]

def padding_2(img):
    n=0
    l=[[[0 for i in range(14)] for j in range(14) ]for j in range(64)]
    for i in range(64):
        for j in range(12):
            for k in range(12):
                l[i][j+1][k+1]=img[i][j][k]
    return l

drari_conv_1          = convo1(padded_input_d,kernel_1, biase1)
result_convolution1   = Calc_Conv_RELU_1(normalized_image, matrice_conv1, matrice_biases_1)

maxpooledDrari_1    = maxpool_1(drari_conv_1)
result_maxPool_1    = Max_Pool(result_convolution1, maxP_filter, maxP_stride)

def padding_2(img):
    n=0
    l=[[[0 for i in range(14)] for j in range(14) ]for j in range(64)]
    for i in range(64):
        for j in range(12):
            for k in range(12):
                l[i][j+1][k+1]=img[i][j][k]
    return l
def padding_3(img):
    n=0
    l=[[[0 for i in range(8)] for j in range(8) ]for j in range(32)]
    for i in range(32):
        for j in range(6):
            for k in range(6):
                l[i][j+1][k+1]=img[i][j][k]
    return l

def padding_4(img):
    n=0
    l=[[[0 for i in range(8)] for j in range(8) ]for j in range(32)]
    for i in range(32):
        for j in range(6):
            for k in range(6):
                l[i][j+1][k+1]=img[i][j][k]
    return l


drari_conv_2        = convo2(maxpooledDrari_1,kernel_2,bais_2)
result_convolution2 = Calc_Conv_RELU_2(result_maxPool_1, matrice_conv2, matrice_biases_2)

# print(drari_conv_2[1])
# print("_________________________________________________")
# print("_________________________________________________")
# print("_________________________________________________")
# print("_________________________________________________")
# print("_________________________________________________")
# print(result_convolution2[1])

# # result_convolution2 = padding_3(result_convolution2)





maxpooledDrari_2    = maxpool_2(drari_conv_2)
result_maxPool_2    = Max_Pool(result_convolution2, maxP_filter, maxP_stride)


drari_conv_3        = convo3(maxpooledDrari_2,kernel_3,bais_3)
result_convolution3 = Calc_Conv_RELU_3(result_maxPool_2, matrice_conv3, matrice_biases_3)

maxpooledDrari_3    = maxpool_3(drari_conv_3)
result_maxPool_3    = Max_Pool(result_convolution3, maxP_filter, maxP_stride)

reshaped_drari = rehape(maxpooledDrari_3)
result_reshaped = Reshape_180_to_10(result_maxPool_3)

#++++++++++++++++++++++++++#
#++++++++++++++++++++++++++#
#++++++++++++++++++++++++++#
#++++++++++++++++++++++++++#



print("Drari dim ", np.shape(maxpooledDrari_3))
print("Dyalna dim ",np.shape(result_maxPool_3))


reshaped_drari = np.array(reshaped_drari)
result_reshaped = np.array(result_reshaped)


mse = np.mean((reshaped_drari - result_reshaped)**2)
differences = np.abs(reshaped_drari - result_reshaped)

max_diff_index = np.unravel_index(np.argmax(differences), differences.shape)
max_diff_value = differences[max_diff_index]


print("Location of the maximum absolute difference:", max_diff_index)
print("Value of the maximum absolute difference:", max_diff_value)




# drari_conv_3        = convo3(maxpooledDrari_2,kernel_3,bais_3)
# result_convolution3 = Calc_Conv_RELU_3(result_maxPool_2, matrice_conv3, matrice_biases_3)

# maxpooledDrari_3    = maxpool_3(drari_conv_3)
# result_maxPool_3    = Max_Pool(result_convolution3, maxP_filter, maxP_stride)



# mat5=convo3(mat4,kernel_3,bais_3)
# mat6=maxpool_3(mat5)
# mat7=rehape(mat6)
# result=perception(mat7)

def padding_2(img):
    n=0
    l=[[[0 for i in range(14)] for j in range(14) ]for j in range(64)]
    for i in range(64):
        for j in range(12):
            for k in range(12):
                l[i][j+1][k+1]=img[i][j][k]
    return l


# result_convolution2 = padding_2(result_convolution2)

# bais_2 = np.array(bais_2)
# matrice_biases_2 = np.array(matrice_biases_2)

# mse = np.mean((bais_2 - matrice_biases_2)**2)
# differences = np.abs(bais_2 - matrice_biases_2)
# max_diff_index = np.unravel_index(np.argmax(differences), differences.shape)
# max_diff_value = differences[max_diff_index]


# print(drari_conv_2[1])
# print("_________________________________________________")
# print("_________________________________________________")
# print("_________________________________________________")
# print("_________________________________________________")
# print("_________________________________________________")
# print(result_convolution2[1])

# result_convolution1 = padding(result_convolution1)

# maxpooledDrari_1 = np.array(maxpooledDrari_1)

# result_maxPool_1 = padding_2(result_maxPool_1)
# result_maxPool_1 = np.array(result_maxPool_1)

# mse = np.mean((maxpooledDrari_1 - result_maxPool_1)**2)
# differences = np.abs(maxpooledDrari_1 - result_maxPool_1)

# max_diff_index = np.unravel_index(np.argmax(differences), differences.shape)
# max_diff_value = differences[max_diff_index]


# print("Location of the maximum absolute difference:", max_diff_index)
# print("Value of the maximum absolute difference:", max_diff_value)



# drari_file = open(r"output_matrices/drari_file_matrice_file.txt", "w")
# for element in drari_conv_2:
#     drari_file.write(str(element))
# drari_file.close()

# dyalna_file = open(r"output_matrices/dyalna_file_matrice_file.txt", "w")
# for element in result_convolution2:
#     dyalna_file.write(str(element))
# dyalna_file.close()