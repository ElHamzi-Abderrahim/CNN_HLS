import numpy as np
import matplotlib.pyplot as plt

image_number = 10000
image_size = 3073


################################################
################ EXTRACT BIASES ################
################################################
def extract_biases(label_biases, start_line):
    with open("data_project/CNN_coeff_3x3.txt", 'r') as file:
        lines = file.readlines()

    biases_list = []
    biase1 = open(r"weights/biases_local_weights.txt", "w")
    
    count_col = 0

    im_in = False
    for line_indx in range(start_line, len(lines)):
        text_line = lines[line_indx][2:72]

        if not lines[line_indx].find(label_biases) and not im_in :
            im_in = True
            continue
        elif(im_in):
            endx = lines[line_indx].find(']')
            if endx == -1:
                text_line = lines[line_indx][1:]
            else:
                text_line = lines[line_indx][1:endx]

            for x in text_line.split():
                biases_list.append(float(x))


                biase1.write(str(float(x)))
                biase1.write(" , ")
                count_col += 1
                if (count_col >= 10 ):
                    biase1.write('\n')
                    count_col = 0
                
            if endx != -1 :
                break
    #print(biases_list)
    biase1.close()
    
    return biases_list


####################################################
################ EXTRACT KERNEL WIEGHTS ############
####################################################
def extract_local_weights():
    with open("data_project/CNN_coeff_3x3.txt", 'r') as file:
        lines = file.readlines()

    label_local_weights = "tensor_name:  local3/weights"
    start_line = 6536

    local_W = open(r"weights/local_weights.txt", "w")
    
    count_col = 0

    biases_list = np.empty((180, 10))

    im_in = False
    index_180x = 0
    index_10x = 0
    for line_indx in range(start_line, len(lines)):
        text_line = lines[line_indx][4:69]
        if not lines[line_indx].find(label_local_weights) and not im_in :
            im_in = True
            continue
        elif(im_in):
            endx = lines[line_indx].find(']')
            if endx == -1:
                text_line = lines[line_indx][3:]
            else:
                text_line = lines[line_indx][3:endx]

            for x in text_line.split():
                #print(x)
                biases_list[index_180x][index_10x] = float(x)
                index_10x += 1

                local_W.write(str(float(x)))
                local_W.write(" , ")
                count_col += 1
                if (count_col >= 10 ):
                    local_W.write('\n')
                    count_col = 0
                    
            if endx != -1 :
                index_180x += 1
                index_10x = 0
                if index_180x == 180 :
                    break
    return biases_list


########################################################
################ EXTRACT Conv 1 weights ################
########################################################
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

    conv1 = open(r"output_matrices/conv1_weights.txt", "w")

    count_col = 0

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
                weights_in_file[m3x3_row][m3x3_column][m3x3_channel][m3x3_kernel] = float(x)
                #kernel_weights[m3x3_kernel][m3x3_channel][m3x3_row][m3x3_column] = float(x)
                conv1.write(str(float(x)))
                conv1.write(" , ")
                
                count_col += 1
                if (count_col >= 10 ):
                    conv1.write('\n')
                    count_col = 0

                m3x3_kernel += 1
                if m3x3_kernel > kernel_dim-1 :
                    m3x3_channel += 1
                    m3x3_kernel = 0
                    if m3x3_channel >  channel_dim-1 :
                        m3x3_channel = 0
                        m3x3_row += 1
                        if m3x3_row > row_dim-1 :
                            m3x3_row = 0
                            m3x3_column += 1
                            if m3x3_column == column_dim :
                                break
        if m3x3_column == 3 :
            break
    conv1.close()
        
    return weights_in_file


########################################################
################ EXTRACT Conv 2 weights ################
########################################################
def extract_conv2_weights():
    with open("data_project/CNN_coeff_3x3.txt", 'r') as file:
        lines = file.readlines()
    start_line = 452
    label_conv = "tensor_name:  conv2/weights"

    kernel_dim  = 32
    channel_dim = 64
    row_dim     = 3
    column_dim  = 3

    m3x3_row        = 0
    m3x3_column     = 0
    m3x3_channel    = 0
    m3x3_kernel     = 0
    weights_in_file = np.zeros((column_dim, row_dim, channel_dim, kernel_dim))
    kernel_weights  = np.zeros((kernel_dim, channel_dim,row_dim, column_dim))

    conv2 = open(r"weights/conv2_weights.txt", "w")

    count_col = 0


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
                weights_in_file[m3x3_row][m3x3_column][m3x3_channel][m3x3_kernel] = float(x)
                #kernel_weights[m3x3_kernel][m3x3_channel][m3x3_row][m3x3_column] = float(x)
                
                conv2.write(str(float(x)))
                conv2.write(" , ")
                
                count_col += 1
                if (count_col >= 10 ):
                    conv2.write('\n')
                    count_col = 0

                m3x3_kernel += 1
                if m3x3_kernel > kernel_dim-1 :
                    m3x3_channel += 1
                    m3x3_kernel = 0
                    if m3x3_channel >  channel_dim-1 :
                        m3x3_channel = 0
                        m3x3_row += 1
                        if m3x3_row > row_dim-1 :
                            m3x3_row = 0
                            m3x3_column += 1
                            if m3x3_column == column_dim :
                                break
        if m3x3_column == 3 :
            break
    
    conv2.close()
        
    return weights_in_file


########################################################
################ EXTRACT Conv 3 weights ################
########################################################
def extract_conv3_weights():
    with open("data_project/CNN_coeff_3x3.txt", 'r') as file:
        lines = file.readlines()

    dimensions_step3 = [20, 32, 3, 3]
    dimensions = dimensions_step3
    start_line = 5080
    label_conv = "tensor_name:  conv3/weights"

    kernel_dim  = 20
    channel_dim = 32
    row_dim     = 3
    column_dim  = 3

    m3x3_row        = 0
    m3x3_column     = 0
    m3x3_channel    = 0
    m3x3_kernel     = 0
    weights_in_file = np.zeros((column_dim, row_dim, channel_dim, kernel_dim))
    kernel_weights  = np.zeros((kernel_dim, channel_dim,row_dim, column_dim))

    conv3 = open(r"weights/conv3_weights.txt", "w")

    count_col = 0

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
                weights_in_file[m3x3_row][m3x3_column][m3x3_channel][m3x3_kernel] = float(x)
                #kernel_weights[m3x3_kernel][m3x3_channel][m3x3_row][m3x3_column] = float(x)

                conv3.write(str(float(x)))
                conv3.write(" , ")
                
                count_col += 1
                if (count_col >= 10 ):
                    conv3.write('\n')
                    count_col = 0

                m3x3_kernel += 1
                if m3x3_kernel > kernel_dim-1 :
                    m3x3_channel += 1
                    m3x3_kernel = 0
                    if m3x3_channel >  channel_dim-1 :
                        m3x3_channel = 0
                        m3x3_row += 1
                        if m3x3_row > row_dim-1 :
                            m3x3_row = 0
                            m3x3_column += 1
                            if m3x3_column == column_dim :
                                break
        if m3x3_column == 3 :
            break

    conv3.close() 
    return weights_in_file



#######++++++++++++++++ EXTRACTING MATRICES +++++++++++++++++++#######

#####################################################
################ EXTRACT KERNEL_L1 TEST ################
#####################################################
matrice_conv1 = extract_conv1_weights()
conv1 = open(r"output_matrices/extr_file.txt", "w")

for element in matrice_conv1:
    conv1.write(str(element))
conv1.close()





########################################################
################ EXTRACT KERNEL_L2 TEST ################
########################################################
matrice_conv2 = extract_conv2_weights()
conv2 = open(r"output_matrices/conv2_matrice_file.txt", "w")

for element in matrice_conv2:
    conv2.write(str(element))
conv2.close()



########################################################
################ EXTRACT KERNEL_L3 TEST ################
########################################################
matrice_conv3 = extract_conv3_weights()
conv3 = open(r"output_matrices/conv3_matrice_file.txt", "w")

for element in matrice_conv3:
    conv3.write(str(element))
conv3.close()



#####################################################
################ EXTRACT LOCAL TEST #################
#####################################################
matrice_local = extract_local_weights()
local3 = open(r"output_matrices/local3_matrice_file.txt", "w")

for element in matrice_local:
    local3.write(str(element))
local3.close()


#####################################################
################ EXTRACT BIASES_1 #################
#####################################################
matrice_biases_1 = extract_biases("tensor_name:  conv1/biases", 0)
biases_1 = open(r"output_matrices/biases1_matrice_file.txt", "w")

for element in matrice_biases_1:
    biases_1.write(str(element))
biases_1.close()


#####################################################
################ EXTRACT BIASES_2 #################
#####################################################
matrice_biases_2 = extract_biases("tensor_name:  conv2/biases", 453)
biases_2 = open(r"output_matrices/biases2_matrice_file.txt", "w")

for element in matrice_biases_2:
    biases_2.write(str(element))
biases_2.close()

#####################################################
################ EXTRACT BIASES_3 #################
#####################################################
matrice_biases_3 = extract_biases("tensor_name:  conv3/biases", 5080)
biases_3 = open(r"output_matrices/biases3_matrice_file.txt", "w")

for element in matrice_biases_3:
    biases_3.write(str(element))
biases_3.close()



#########################################################
################ EXT
def opening_file_batch() :
    with open("data_project/data_batch_3.bin", "rb") as file :
            binary_data = file.read()
    return binary_data


 #################
#########################################################
matrice_biases_local = extract_biases("tensor_name:  local3/biases", 6530)
biases_local = open(r"output_matrices/biases3_local_matrice_file.txt", "w")

for element in matrice_biases_local:
    biases_local.write(str(element))
biases_local.close()







