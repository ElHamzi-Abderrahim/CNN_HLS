
#from old_files.Extracting_Mtrx_Files import *

import numpy as np
import matplotlib.pyplot as plt

image_number = 10000
image_size = 3073

###################################################
################ OPENING BATCH ####################
###################################################
def opening_file_batch() :
    with open("data_project/test_batch.bin", "rb") as file :
            binary_data = file.read()
    return binary_data


################################################
################ EXTRACT IMAGES ################
################################################
def Binary_to_Tuple(): # (label, red_32x32, green_32x32, blue_32x32)
    start = 0
    images = []

    num_image = 0

    image_0 = open(r"images_matrices/image_4.txt", "w")
    
    count_col = 0


    binary_data = opening_file_batch() 

    for indx in range(30):
        bin_image = np.frombuffer(binary_data[start : start + image_size], dtype=np.uint8)
        label = bin_image[0]
        image_pixs = bin_image[1:]
        
        # str_name_file = "images_ppm/image_" + str(num_image) + ".ppm"
        # fl_imge = open(str_name_file, "w")
        # fl_imge.write("P2 \n")
        # fl_imge.write("32 32 \n")
        # fl_imge.write("255 \n")
        # for element in image_pixs:
        #     fl_imge.write(str(float(element)))
        #     fl_imge.write('\n')
        

        
        if (num_image == 4):        
            for element in image_pixs:
                image_0.write(str(float(element)))
                image_0.write(', ')
                count_col += 1
                if (count_col >= 10 ):
                    image_0.write('\n')
                    count_col = 0
            image_0.close()
        
        num_image += 1

        red_ch_32x32    = image_pixs[:1024].reshape(32, 32)
        green_ch_32x32  = image_pixs[1024:2048].reshape(32, 32)
        blue_ch_32x32   = image_pixs[2048:].reshape(32, 32)
        tuple_image = (label, red_ch_32x32, green_ch_32x32, blue_ch_32x32)
        start = start + 3073
        images.append(tuple_image)

        # fl_imge.close()
    return images # image is : 0 => 9999 which means 10000

Binary_to_Tuple()

###################################################
################ NORMALIZING IMAGE ################
###################################################

# max_value = 0
# mean = 0


def normalizing_image(centered_image):
    red_24x24 = centered_image[1].flatten()
    green_24x24 = centered_image[2].flatten()
    blue_24x24 = centered_image[3].flatten()

    all_values = np.concatenate((red_24x24, green_24x24, blue_24x24))
    global mean 
    mean = np.mean(all_values)
    std_dev = np.std(all_values)
    global max_value
    max_value = max(std_dev, 1 / np.sqrt(1728))

    # print("the max value", max_value)

    normalized_red = ((red_24x24 - mean) / max_value).reshape(24, 24)
    normalized_green = ((green_24x24 - mean) / max_value).reshape(24, 24)
    normalized_blue = ((blue_24x24 - mean) / max_value).reshape(24, 24)

    normalized_image = [normalized_red, normalized_green, normalized_blue]

    return normalized_image

def get_max_val():
    return max_value 
def get_mean_val():
    return mean 


####################################################
################ CENTRALIZING IMAGE ################
####################################################
def centered_channel(matrice_32x32) :
    debut_ligne = (32 - 24) // 2
    fin_ligne = debut_ligne + 24
    debut_colonne = (32 - 24) // 2
    fin_colonne = debut_colonne + 24
    matrice_24x24 = matrice_32x32[debut_ligne:fin_ligne, debut_colonne:fin_colonne]
    return matrice_24x24

def centering_image(nCentered_Image):
    label = nCentered_Image[0]
    red_ch_24x24     =  centered_channel(nCentered_Image[1])
    green_ch_24x24   =  centered_channel(nCentered_Image[2])
    blue_ch_24x24    =  centered_channel(nCentered_Image[3])
    Centered_Image = (label, red_ch_24x24, green_ch_24x24, blue_ch_24x24)
    return Centered_Image




##################################################
################ DISPLAYING IMAGE ################
##################################################
def Display_image(image):
    rgb_image = np.stack(image, axis=-1)
    plt.imshow(rgb_image)
    plt.show()

