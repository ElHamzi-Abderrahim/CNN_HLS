

#include "image_processing.h"


#include <fstream>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <random>
#include <ctime>

using namespace std;



// Centrer un cannal 
mat_24_struct centeredChannel(double matrix32x32[ROW_SIZE_32*COLUMN_SIZE_32]) {
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

//centrer une image de taille 32*32

ImageTuple_24 centeringImage(double nonCenteredImage[ROW_SIZE_32*COLUMN_SIZE_32*CHANNEL_SIZE])
{
    ImageTuple_24 centered_Image;

    // Extract red, green, and blue channels from nonCenteredImage
    double red_ch_32x32[ROW_SIZE_32 * COLUMN_SIZE_32];
    double green_ch_32x32[ROW_SIZE_32 * COLUMN_SIZE_32];
    double blue_ch_32x32[ROW_SIZE_32 * COLUMN_SIZE_32];

    mat_24_struct red_ch_24x24;
    mat_24_struct green_ch_24x24;
    mat_24_struct blue_ch_24x24;


    // Extracting red channel from nonCenteredImage
    for (size_t i = 0; i < ROW_SIZE_32; ++i) {
        for (size_t j = 0; j < COLUMN_SIZE_32; ++j) {
            red_ch_32x32[mat_32(i, j)]  = nonCenteredImage[pixel_32(i, j, 0)]; // Red channel
        }
    }


    // Extracting green channel from nonCenteredImage
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


//calculer la moyenne 

double calculerMoyenne(double image[ROW_SIZE_24*COLUMN_SIZE_24*3] ) {
    double totalElements = ROW_SIZE_24 * COLUMN_SIZE_24 * CHANNEL_SIZE;
    double somme = 0.0;

    for (int i = 0; i < ROW_SIZE_24; ++i) {
        for (int j = 0; j < COLUMN_SIZE_24; ++j) {
            for (int k = 0; k < CHANNEL_SIZE; ++k) {
                somme += image[pixel_24(i, j, k)];
            }
        }
    }

    return somme / totalElements;
}

// calculer l'ecart type 

double calculerEcartType(double image[ROW_SIZE_24*COLUMN_SIZE_24*3]) {
    double moyenne = calculerMoyenne(image);
    double totalElements = ROW_SIZE_24 * COLUMN_SIZE_24 * CHANNEL_SIZE;
    double sommeCarresEcarts = 0.0;

    for (int k = 0; k < CHANNEL_SIZE; ++k){
        for (int j = 0; j < COLUMN_SIZE_24; ++j) {
            for (int i = 0; i < ROW_SIZE_24; ++i){
                double ecart = image[pixel_24(i, j, k)] - moyenne;
                sommeCarresEcarts += ecart * ecart;
            }
        }
    }

    double variance = sommeCarresEcarts / totalElements;
    double ecartType = std::sqrt(variance);

    return ecartType;
}


// normalize image 

ImageTuple_24 normalizeImage(double centeredImage[ROW_SIZE_24*COLUMN_SIZE_24*3]) {
    ImageTuple_24 normalized_Image;

    // Calculate mean and standard deviation
    double mean = calculerMoyenne(centeredImage);
    double ecartType = calculerEcartType(centeredImage);
    double sqrt_1728 = 1.0 / std::sqrt(1728.0);
    double max_value = std::max(ecartType, sqrt_1728);

    // Extracting green channel from centeredImage
    for (int channel = 0; channel < 3; ++channel) {
        for (int i = 0; i < ROW_SIZE_24; ++i) {
            for (int j = 0; j < COLUMN_SIZE_24; ++j) {
                normalized_Image.image_24x24[pixel_24(i, j, channel)] = (centeredImage[pixel_24(i, j, channel)] - mean) / max_value; // Red channel
            }
        }
    }
    return normalized_Image;
}

