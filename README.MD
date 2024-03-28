
THIS GUIDE FILE CONTAINS SOME DISCREPTIONS OF EACH DIRECTORY IN THIS PROJECT AND SOME NOTES TO HAVE IN MIND.

IN THIS DIRECOTRY, ALL THE PROJECT FILES ARE ORGANIZED IS SUCH MANNER, THE PROJECT HIERARCHY IS EASY TO DEAL WITH, ALL THE FILES ARE ORGANIZED AS THE FOLLOWING:

------------------------------------------- PYTHON ---------------------------------------------
- ALL THE PY FILES ARE IN THE DIRECTORY, AND THE USED BINARY FILE OF TEST SET FOR THE CNN.
- THE TEST DONE BY PYTHON IN ORDER TO DETERMINE THE ACCURACY OF THE CNN, IS DONE ON 1000 PICTURE IN TEST SET DATA, WHICH GIVES AT THE END AN ACCURACY OF 70%.
	
+---PYTHON
    |   Convolutions.py
    |   Extracting_Weights.py
    |   Images_processing.py
    |   Maxpoolings.py
    |   Network_Tests.py
    |   README.MD
    |   Reshape_percetrons.py
    |     
    +---project_data
    |       batches.meta.txt
    |       CNN_coeff_3x3.txt
    |       test_batch.bin
    |       
    +---result_operation_images
    |       feature_map_ch1.png
    |       feature_map_ch2.png
    |       feature_map_ch3.png
    |       feature_map_ch4.png
    |       Figure_1-2.png
    |       Figure_1-3.png
    |       Figure_1.png
    +---output_matrices
    |       biases1_matrice_file.txt
    |       biases2_matrice_file.txt
    |       ...
	


--------------------------------------------- C PLUS PLUS ----------------------------------------------------------
- ALL THE NEEDED FILES, HEADERS AND SOURCE FILES ARE IN SEPARATE DIRECTORY.
- THE COMPILATION IS BASED ON CMAKE TOOL TO GENERATE THE MAKEFILE.
- THE TEST DONE IN THE MAIN, IS JUST ABOUT ONE IMAGE, AND THE RESULT OF EACH STAGE IS COMPRED TO THE CORRESPONDING RESULT OF THE PYTHON CODE, WHICH MEANS OUR REFERENCE HERE IS PYTHON.

+---CPP
|   |   CMakeLists.txt
|   +---include
|   |       Conv1_weights.h
|   |       Conv2_weights.h
|   |       Conv3_weights.h
|   |       convolution.h
|   |       images.h
|   |       image_processing.h
|   |       ImgProcTest.h
|   |       last_stage_net.h
|   |       macros.h
|   |       maxpool.h
|   |       Perceptron.h
|   |       
|   \---src
|           convolution.cpp
|           Image_processing.cpp
|           ImgProcTest.cpp
|           img_in.pgm
|           last_stage_net.cpp
|           main.cpp
|           maxpool.cpp
|   +---ac_fixed
|   |       ac_array.h
|   |       ac_assert.h
|   |       ac_buffer_2d.h
|   |       ac_chandup.h
|   |       ac_channel.h
|   |       ac_complex.h
|   |       ac_dsp_utils.h
|   |       ac_fixed.h
|   |       ac_float.h
|   |       ac_int.h
|   |       ac_matlab.h
|   |       ac_probe.h
|   |       ac_reset_signal_is.h
|   |       ac_sc.h
|   |       ac_sync.h
|   |       ac_wait.h
|   |       ac_window.h
|   |       ac_window_1d_array.h
|   |       ac_window_1d_flag.h
|   |       ac_window_1d_stream.h
|   |       ac_window_2d_flag.h
|   |       ac_window_2d_stream.h
|   |       ac_window_structs.h
|   |       mc_scverify.h
|   |       
|   +---build
|   |   |   CMakeCache.txt
|   |   |   cmake_install.cmake
|   |   |   compile_commands.json
|   |   |   CPackConfig.cmake
|   |   |   CPackSourceConfig.cmake
|   |   |   CTestTestfile.cmake
|   |   |   DartConfiguration.tcl
|   |   |   Makefile
|   |   |   unit_test                 
|   |   | 	...


------------------------------------------ CPP / HLS ANALYSIS ------------------------------------------------

- THIS DIRECTORY IS A PART THE ANALYSIS DONE IN THE PROJECT, COMPARING BETWEEN THE CPP CODE AS THE REFERENCE MODEL, AND THE CPP AS THE CODE THAT WILL BE SYNTHESISED. 
- THE COMPARAISON IS BASED ON THE CALCULATING THE ERROR BETWEEN THE TWO, ON EACH STAGE OF THE CNN, IN ORDER TO DEFINE BETTER PARAMTERS FOR THE DATA TYPES FOR THE SYNTHESISED CODE.
- ALL THE FILES NEEDED FOR THE COMPILATION INCLUDING THE ONES USED BY THE CATAPULT FOR DATA TYPE ARE INCLUDED (ac_int.h and ac_fixed.h).

+---Diff_error
|   |   ac_fixed.h
|   |   ac_int.h
|   |   CMakeLists.txt
|   |   CNN_Design.cpp
|   |   CNN_Design.h
|   |   Conv1_weights.h
|   |   Conv2_weights.h
|   |   Conv3_weights.h
|   |   convolution.cpp
|   |   convolution.h
|   |   data_types.h
|   |   disp_hls.cpp
|   |   images.h
|   |   Image_processing.cpp
|   |   image_processing.h
|   |   last_stage_net.cpp
|   |   last_stage_net.h
|   |   maxpool.cpp
|   |   maxpool.h
|   |   mc_scverify.h
|   |   Perceptron.h
|   |   Reference_design.cpp
|   |   Reference_design.h
|   |   Ref_Conv1_weights.h
|   |   Ref_Conv2_weights.h
|   |   Ref_Conv3_weights.h
|   |   ref_images.h
|   |   Ref_Perceptron.h
|   |   TB_design_test.cpp
|   |   TB_design_test.exe
|   +---ac_fixed
|   |       ac_array.h
|   |       ac_assert.h
|   |       ac_buffer_2d.h
|   |       ac_chandup.h
|   |       ac_channel.h
|   |       ac_complex.h
|   |       ac_dsp_utils.h
|   |       ac_fixed.h
|   |       ac_float.h
|   |       ac_int.h
|   |       ac_matlab.h
|   |       ac_probe.h
|   |       ac_reset_signal_is.h
|   |       ac_sc.h
|   |       ac_sqrt.h
|   |       ac_sync.h
|   |       ac_wait.h
|   |       ac_window.h
|   |       ac_window_1d_array.h
|   |       ac_window_1d_flag.h
|   |       ac_window_1d_stream.h
|   |       ac_window_2d_flag.h
|   |       ac_window_2d_stream.h
|   |       ac_window_structs.h
|   |       mc_scverify.h
|   |       
|   +---build
|   |   |   CMakeCache.txt
|   |   |   cmake_install.cmake
|   |   |   compile_commands.json
|   |   |   CPackConfig.cmake
|   |   |   CPackSourceConfig.cmake
|   |   |   CTestTestfile.cmake
|   |   |   DartConfiguration.tcl
|   |   |   Makefile
|   |   |   ...


         
------------------------------------------ HLS ------------------------------------------------

- THIS DIRECOTRY OBVIOUSLY, IS CONTAINING THE HLS CODE THAT WILL BE SYNTHESISED BY CATAPULT.
- THE DESIGN SUPPOSED TO BE SYNTHESISED BY CATAPULT IS OUTPUTING A TABLE (IMAGE) OF IMG_SIZE_COL*IMG_SIZE_ROW (320x240) ON ITS DIMENSIONS.
- THE IMAGES, WHICH ARE 3x24x24, WILL BE STORED IN THE RAM IN ORDER TO BE PROCESSED AND OUTPUT THE TABLE TO THE HDMI, WHICH WILL CONTAIN THE IMAGE ITSELF AND THE LABEL OF IMAGE, WHICH DETERMENED BY THE CNN CODE INSIDE THE DESIGN.
- THE IMAGES STORED IN THE RAM, ARE NORMALIZED, BECAUSE THE STEP OF NORMALIZATION OF IMAGES IS COMPLICATED TO BE SYNTHESISED, BECAUSE OF THE SQRT CALCULATION INCLUDED IN THE OPERATION OF NORMALIZATION.

+---HLS
|   |   my_hls_18.pgm
|   |   
|   +---include
|   |       all_includes.h
|   |       Conv1_weights.h
|   |       Conv2_weights.h
|   |       Conv3_weights.h
|   |       convolution.h
|   |       data_types.h
|   |       DispProcTest.h
|   |       images.h
|   |       last_stage_net.h
|   |       maxpool.h
|   |       num_label.h
|   |       Perceptron.h
|   |       
|   \---src
|           Catapult_commands.tcl
|           convolution.cpp
|           DispProcTest.cpp
|           DispProcTest_bench.cpp
|           last_stage_net.cpp
|           maxpool.cpp
|           my_commands.tcl
|           yy_commands.tcl
| 

------------------------------------------ FPGA ------------------------------------------------
- THIS DIRECTORY, MAINLY CONTAINS TWO FILES, A FILE WITH edf EXTENSION WHICH WILL CONNECT OUR SYNTHESISED VHDL WITH THE HDMI IP, WHICH GENERATED BY CATAPULT, AND A FILE WITH .bit EXTENSION WHICH IS THE BIT STREAM FOR THE FPGA, GENERATED BY VIVADO.

+---FPGA
|       bkp_system_wrapper.bit
|       DispProcTest.edf


------------------------------------------ Python Scripts ------------------------------------------------
- THIS DIRECTORY, BISACLY IS CONTAINING ALL THE SCRIPTS USED TO EXTRACT WEIGHTS FOR THE CPP, AND FOR GENERATING TABLE OF NORMALIZED IMAGES.
- IT CONTAINS SOME OF THE RESULTS OF SCRIPTS, OR MAYBE ALL USED ONES.


+---PY_scripts
    |   cmp_cpp.py
    |   colv_relu_valid.py
    |   comp_drari.py
    |   conv2_ones.py
    |   Drari_maxpool.py
    |   Ext2_Mtrx_Files.py
    |   Extracting_weights.py
    |   final_test.py
    |   gen_acfixed_parameters.py
    |   image_processing.py
    |   max_pool.py
    |   
    +---data_project
    |       batches.meta.txt
    |       CNN_coeff_3x3.txt
    |       test_batch.bin
    |       
    +---header_weights_conv
    |       Conv1_weights.h
    |       Conv2_weights.h
    |       Conv3_weights.h
    |       
    +---images_matrices
    |       image_0.txt
    |       image_4.txt
    |       
    +---norm_images
    |       normImg_0.txt
    |       normImg_30.txt
    |       normImg_40_mx.txt
    |       normImg_7.txt
    |       normImg_tes.txt
    |       normImg_x.txt
    |       
    +---result_operation_images
    |       feature_map_ch1.png
    |       feature_map_ch2.png
    |       feature_map_ch3.png
    |       feature_map_ch4.png
    |       Figure_1-2.png
    |       Figure_1-3.png
    |       Figure_1.png
    |       
    +---weights
            biases_1_weights.txt
            biases_2_weights.txt
            biases_3_weights.txt
            biases_local_weights.txt
            conv1_weights.txt
            conv2_weights.txt
            conv3_weights.txt
            local_weights.txt


--------------------- THANK YOU  FOR YOUR  READING  -----------------------
------------------------- EL HAMZI ABDERRAHIM -----------------------------
---------------------------------------------------------------------------