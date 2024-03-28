

#include "image_processing.h"

#include <fstream>
#include <iostream>
//#include <cmath>
//#include "ac_math.h"
#include "ac_fixed.h"

using namespace std;


// Centrer un cannal 
mat_24_struct centeredChannel(d_type matrix32x32[ROW_SIZE_32*COLUMN_SIZE_32]) {
    mat_24_struct matrix24x24;

    int start_row = (ROW_SIZE_32 - ROW_SIZE_24) / 2;
    int start_col = (COLUMN_SIZE_32 - COLUMN_SIZE_24) / 2;

    // Boucles pour extraire la sous-matrice 24x24
    for (int i = 0; i < ROW_SIZE_24; ++i) {
        for (int j = 0; j < COLUMN_SIZE_24; ++j) {
            matrix24x24.matrice_24[mat_24(i, j)] = matrix32x32[mat_32(start_row + i, start_col + j)];
            
        }
    }

    return matrix24x24;
}

ImageTuple_24 centeringImage(d_type nonCenteredImage[ROW_SIZE_32*COLUMN_SIZE_32*CHANNEL_SIZE])
{
    ImageTuple_24 centered_Image;

    // Extract red, green, and blue channels from nonCenteredImage
    d_type red_ch_32x32[ROW_SIZE_32 * COLUMN_SIZE_32];
    d_type green_ch_32x32[ROW_SIZE_32 * COLUMN_SIZE_32];
    d_type blue_ch_32x32[ROW_SIZE_32 * COLUMN_SIZE_32];

    mat_24_struct red_ch_24x24;
    mat_24_struct green_ch_24x24;
    mat_24_struct blue_ch_24x24;


    // Extracting red channel from nonCenteredImage
    for (size_t i = 0; i < ROW_SIZE_32; ++i) {
        for (size_t j = 0; j < COLUMN_SIZE_32; ++j) {
            red_ch_32x32[mat_32(i, j)]  = nonCenteredImage[pixel_32(i, j, 0)]; // Red channel
        }
    }

    for (size_t i = 0; i < ROW_SIZE_32; ++i) {
        for (size_t j = 0; j < COLUMN_SIZE_32; ++j) {
            green_ch_32x32[mat_32(i, j)]  = nonCenteredImage[pixel_32(i, j, 1)]; // Green channel
        }
    }

    // Extracting blue channel from nonCenteredImage
    for (size_t i = 0; i < ROW_SIZE_32; ++i) {
        for (size_t j = 0; j < COLUMN_SIZE_32; ++j) {
            blue_ch_32x32[mat_32(i, j)]  = nonCenteredImage[pixel_32(i, j, 2)]; // Blue channel
        }
    }

    // Convert 32x32 channels to 24x24 channels using centeredChannel function

    red_ch_24x24    = centeredChannel(red_ch_32x32);
    green_ch_24x24  = centeredChannel(green_ch_32x32); 
    blue_ch_24x24   = centeredChannel(blue_ch_32x32); 
   
    // Fill the ImageTuple_24 with centered channels
    for (size_t i = 0; i < ROW_SIZE_24; ++i) {
        for (size_t j = 0; j < COLUMN_SIZE_24; ++j) {
            centered_Image.image_24x24[pixel_24(i, j, 0)]  = red_ch_24x24.matrice_24[mat_24(i, j)];   // Red channel
            centered_Image.image_24x24[pixel_24(i, j, 1)]  = green_ch_24x24.matrice_24[mat_24(i, j)]; // Green channel
            centered_Image.image_24x24[pixel_24(i, j, 2)]  = blue_ch_24x24.matrice_24[mat_24(i, j)];  // Blue channel
        }
    }

    return centered_Image;
}


