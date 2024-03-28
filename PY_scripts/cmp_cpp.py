import numpy as np

out_dim_step1 = [64, 24, 24]
out_dim_step2 = [32, 12, 12]
out_dim_step3 = [20, 6, 6]
maxP_filter = [3, 3]
maxP_stride = [2, 2]


def Calc_Conv_RELU_1(image_in, kernel_w, biases_w):
    num_kernels         = 64
    x_out, y_out        = 24, 24
    
    cnv_calc            = np.zeros(( y_out, x_out, num_kernels))
    result_widnow_3x3   = np.zeros((3, 3))
    padded_image_in     = np.zeros((y_out+2, x_out+2))

    for iter_kernel in range(64):
        cnv_calc[:,:, iter_kernel] += biases_w[iter_kernel]
        for iter_channel in range(3):
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
    # cnv_calc = np.maximum(0, cnv_calc)    
    cnv_calc = np.array(cnv_calc)   
    return cnv_calc     # image shape : channel=64, columns=24, rows=24


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


def Calc_Conv_RELU_3(image_in, kernel_w, biases_w):
    num_kernels         = 20
    x_out, y_out        = 6, 6

    image_in = image_in.tolist()

    cnv_calc            = np.zeros(( num_kernels, x_out, y_out))
    result_widnow_3x3   = np.zeros((3, 3))
    padded_image_in     = np.zeros((y_out+2, x_out+2))

    for iter_kernel in range(20):
        cnv_calc[iter_kernel,:,:] += biases_w[iter_kernel]
        for iter_channel in range(32):
            padded_image_in[1:y_out+1,1:x_out+1] =  image_in[iter_channel][:][:]
            for y in range(6):             # loop the rows
                for x in range(6):         # loop the columns
                    sum_win = 0
                    result_widnow_3x3 = padded_image_in[y:y+3,x:x+3] * kernel_w[:,:,iter_channel,iter_kernel]
                    for ty in range(3):     # loop to calculte the multiplication of each element with the window
                        for tx in range(3):
                            sum_win += result_widnow_3x3[ty][tx]
                    cnv_calc[iter_kernel][y][x] += sum_win
    # cnv_calc = np.transpose(cnv_calc, [2,0,1])
    cnv_calc = np.maximum(0, cnv_calc)       
    return cnv_calc     # image shape : channel=64, columns=24, rows=24


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

image = np.zeros((3,24,24))
kernel = np.zeros((3,3,3,64))
biases  = np.zeros((64))


i = 0
for index_channel in range(3):
    for row in range(24):
        for column in range(24):
            image[index_channel][row][column] = i
            i = i + 1


for ker in range(64):
    for chan in range(3):
        for row in range(3):
            for column in range(3): 
                kernel[ker][chan][row][column] = i+2
                i = i + 1


mine    = Calc_Conv_RELU_1(image, kernel, biases) # out shape: columns=24, rows=24, kernel=64

print(mine[0])
