//  Catapult Ultra Synthesis 10.5c/896140 (Production Release) Sun Sep  6 22:45:38 PDT 2020
//  
//  Copyright (c) Mentor Graphics Corporation, 1996-2020, All Rights Reserved.
//                        UNPUBLISHED, LICENSED SOFTWARE.
//             CONFIDENTIAL AND PROPRIETARY INFORMATION WHICH IS THE
//                 PROPERTY OF MENTOR GRAPHICS OR ITS LICENSORS
//  
//  Running on Linux xph3sei709@cimeld26.cime.inpg.fr 3.10.0-1160.105.1.el7.x86_64 x86_64 aol
//  
//  Package information: SIFLIBS v23.5_3.0, HLS_PKGS v23.5_3.0, 
//                       SIF_TOOLKITS v23.5_3.0, SIF_XILINX v23.5_3.0, 
//                       SIF_ALTERA v23.5_3.0, CCS_LIBS v23.5_3.0, 
//                       CDS_PPRO v10.3c_2, CDS_DesigChecker v10.5c, 
//                       CDS_OASYS v19.1_3.7, CDS_PSR v20.1_0.0, 
//                       DesignPad v2.78_1.0
//  
//  Start time Wed Jan 17 23:32:53 2024
solution file add ./src/DispProcTest_bkp.cpp
solution file add ./src/DispProcTest.cpp
solution file add ./src/DispProcTest_bench.cpp -exclude true
solution file add ./src/convolution.cpp
solution file add ./src/maxpool.cpp
solution file add ./src/last_stage_net.cpp
solution file remove /tp-fmr/xph3sei709/demo_CC/projet_CNN/src/DispProcTest_bkp.cpp
go analyze
go compile
solution library add mgc_Xilinx-ARTIX-7-2L_beh -- -rtlsyntool Precision -manufacturer Xilinx -family ARTIX-7 -speed -2L -part xc7a12tcsg325-2L
solution library add Xilinx_RAMS
solution library add Xilinx_ROMS
go libraries
directive set -CLOCKS {clk {-CLOCK_PERIOD 20 -CLOCK_EDGE rising -CLOCK_HIGH_TIME 10 -CLOCK_OFFSET 0.000000 -CLOCK_UNCERTAINTY 0.0 -RESET_KIND sync -RESET_SYNC_NAME rst -RESET_SYNC_ACTIVE high -RESET_ASYNC_NAME arst_n -RESET_ASYNC_ACTIVE low -ENABLE_NAME {} -ENABLE_ACTIVE high}}
logfile save_commands /tp-fmr/xph3sei709/demo_CC/projet_CNN/src/yy_commands.tcl
