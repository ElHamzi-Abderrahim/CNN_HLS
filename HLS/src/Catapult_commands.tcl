//  Catapult Ultra Synthesis 10.4b/841621 (Production Release) Thu Oct 24 17:20:07 PDT 2019
//  
//  Copyright (c) Mentor Graphics Corporation, 1996-2019, All Rights Reserved.
//                        UNPUBLISHED, LICENSED SOFTWARE.
//             CONFIDENTIAL AND PROPRIETARY INFORMATION WHICH IS THE
//                 PROPERTY OF MENTOR GRAPHICS OR ITS LICENSORS
//  
//  Running on Linux xph3sei709@cimeld26.cime.inpg.fr 3.10.0-1160.105.1.el7.x86_64 x86_64 aol
//  
//  Package information: SIFLIBS v23.4_2.0, HLS_PKGS v23.4_2.0, 
//                       SIF_TOOLKITS v23.4_2.0, SIF_XILINX v23.4_2.0, 
//                       SIF_ALTERA v23.4_2.0, CCS_LIBS v23.4_2.0, 
//                       CDS_PPRO v10.3a_3, CDS_DesigChecker v10.4b, 
//                       CDS_OASYS v19.1_2.4, CDS_PSR v19.1_1.16, 
//                       DesignPad v2.78_1.0
//  
//  Start time Wed Jan 17 21:22:10 2024
solution file add ./src/last_stage_net.cpp
solution file add ./src/convolution.cpp
solution file add ./src/DispProcTest_bench.cpp -exclude true
solution file add ./src/maxpool.cpp
solution file add ./src/DispProcTest.cpp
options set Input/CppStandard c++98
options save
options set Input/SearchPath /tp-fmr/xph3sei709/demo_CC/DispProcTest/include -remove
options set Input/SearchPath /tp-fmr/xph3sei709/demo_CC/projet_CNN/include -append
options save
go analyze
logfile save_commands /tp-fmr/xph3sei709/demo_CC/projet_CNN/src/Catapult_commands.tcl
