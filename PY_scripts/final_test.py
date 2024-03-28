

from image_processing import *

from colv_relu_valid import *
from Extracting_weights import *
#from max_pool import *
from image_processing import get_max_val, get_mean_val

out_dim_step1 = [64, 24, 24]
out_dim_step2 = [32, 12, 12]
out_dim_step3 = [20, 6, 6]
maxP_filter = [3, 3]
maxP_stride = [2, 2]

normImg_i = open(r"norm_images/normImg_40_mx.txt", "w")

num_test_samples = 30

def testing_network(num_test_samples):
    checked_statistic = 0
    succeed_statistic = 0

    for i in range(num_test_samples):
        images = Binary_to_Tuple()  
        centered_image = centering_image(images[i])

        normalized_image = normalizing_image(centered_image)

        # count_col = 0
        # print("in test max value is : ", get_max_val())
        # print("in test mean value is : ", get_mean_val())
        # # max_value = get_max_val()
        # # mean = get_mean_val()
        # normImg_i.write(" \n")
        # normImg_i.write(str(float(get_max_val())))
        # normImg_i.write(" , \n")
        # normImg_i.write(str(float(get_mean_val())))
        # normImg_i.write(" , \n")

        # for i in range(3):
        #     for j in normalized_image[i]:
        #         for element in j:
        #             normImg_i.write(str(float(element)))
        #             normImg_i.write(" , ")
        #             count_col += 1
        #             if (count_col >= 10 ):
        #                 normImg_i.write('\n')
        #                 count_col = 0
        

        result_convolution1 = Calc_Conv_RELU_1(normalized_image, matrice_conv1, matrice_biases_1)

        # print(result_convolution1[0])
        # print("--------------------")
        # print(result_convolution1[1])
        # print("--------------------")
        # print(result_convolution1[2])
        # print("--------------------")

        max_pooled_1 = Max_Pool(result_convolution1, maxP_filter, maxP_stride)
        # print("---------------MAXPOOL RESULTS-----------------")
        # print(max_pooled_1[0])
        # print("--------------------")
        # print(max_pooled_1[63])
        # print("--------------------")


        result_convolution2 = Calc_Conv_RELU_2(max_pooled_1, matrice_conv2, matrice_biases_2)
        max_pooled_2 = Max_Pool(result_convolution2, maxP_filter, maxP_stride)

        # print(result_convolution2[0])
        # print("--------------------")
        # print(max_pooled_2[0])
        # print("--------------------")
        # print(max_pooled_2[31])
        


        result_convolution3 = Calc_Conv_RELU_3(max_pooled_2, matrice_conv3, matrice_biases_3)
        max_pooled_3 = Max_Pool(result_convolution3, maxP_filter, maxP_stride)

        # print(result_convolution3[0])
        # print("--------------------")
        # print(result_convolution3[19])
        # print("--------------------")
        # for i in range(20):
        #     print(max_pooled_3[i])
        #     print("  --------------------   ")
        # print(max_pooled_3[5])
        

        reshaped = Reshape_180_to_10(max_pooled_3)
        # print("reshaping result : ")
        # for i in range(180):
        #     print(reshaped[i])

        fully_connected = Perceptrons(reshaped, matrice_local, matrice_biases_local)

        # for i in range(10):
        #     print(fully_connected[i])

        result_class = Soft_max(fully_connected)

        activated_class = np.argmax(result_class)
        print(result_class)
        print(f"Activated Class: {activated_class}")

        checked_statistic += 1
        if activated_class == centered_image[0]:  
            succeed_statistic += 1
        success_rate = (succeed_statistic / checked_statistic) * 100
        print(f"Success Rate: {success_rate}%")

testing_network(num_test_samples)
normImg_i.close()