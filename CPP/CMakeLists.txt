cmake_minimum_required(VERSION 3.12)

project(debug VERSION 0.1.0 LANGUAGES C CXX)

# project(cnn)
include(CTest)
enable_testing(CTest)

set(CMAKE_CXX_STANDARD 11)

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/ac_fixed)


# Add your source files
set(SOURCES
    src/main.cpp
    src/Image_processing.cpp
    src/ImgProcTest.cpp
    src/convolution.cpp
    src/maxpool.cpp
    src/last_stage_net.cpp
)


set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

# Create an executable
add_executable(unit_test ${SOURCES} ${HEADERS} )


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
