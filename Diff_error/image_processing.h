#ifndef IMAGE_PROCESSOR_HPP
#define IMAGE_PROCESSOR_HPP

#include "data_types.h"


#define CHANNEL_SIZE 3 

#define ROW_SIZE_24 24
#define COLUMN_SIZE_24 24 
#define mat_24(y, x) ((y) * COLUMN_SIZE_24 + (x))


#define ROW_SIZE_32 32
#define COLUMN_SIZE_32 32
#define mat_32(y, x) ((y) * COLUMN_SIZE_32 + (x))

#define pixel_32(y, x, z) ((x)+ COLUMN_SIZE_32*(y) + COLUMN_SIZE_32*ROW_SIZE_32*(z))

#define pixel_24(y, x, z) ((x)+ COLUMN_SIZE_24*(y) + COLUMN_SIZE_24*ROW_SIZE_24*(z)) 


struct ImageTuple_24 {
    d_type image_24x24[ROW_SIZE_24*COLUMN_SIZE_24*CHANNEL_SIZE];
};
struct ImageTuple_32 {
    d_type image_32x32[ROW_SIZE_32*COLUMN_SIZE_32*CHANNEL_SIZE];
};

struct mat_24_struct {
    d_type matrice_24[ROW_SIZE_24*COLUMN_SIZE_24];
    };
struct mat_32_struct {
    d_type matrice_32[ROW_SIZE_32*COLUMN_SIZE_32];
    };

struct normResult_struct {
    acc_type image_24x24[ROW_SIZE_24*COLUMN_SIZE_24*CHANNEL_SIZE];
    };



mat_24_struct centeredChannel(d_type matrix32x32[ROW_SIZE_32*COLUMN_SIZE_32]);

ImageTuple_24  centeringImage(d_type nonCentered_image[ROW_SIZE_32*COLUMN_SIZE_32*CHANNEL_SIZE]);




#endif // IMAGE_PROCESSOR_HPP

