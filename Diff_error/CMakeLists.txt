cmake_minimum_required(VERSION 3.28.1)
project(disp_hls VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_library(disp_hls disp_hls.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
