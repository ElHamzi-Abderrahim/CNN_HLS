#ifndef IMAGE_PROCESSOR_HPP
#define IMAGE_PROCESSOR_HPP


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
    double image_24x24[ROW_SIZE_24*COLUMN_SIZE_24*CHANNEL_SIZE];
};
struct ImageTuple_32 {
    double image_32x32[ROW_SIZE_32*COLUMN_SIZE_32*CHANNEL_SIZE];
};

struct mat_24_struct {
    double matrice_24[ROW_SIZE_24*COLUMN_SIZE_24];
    };

struct mat_32_struct {
    double matrice_32[ROW_SIZE_32*COLUMN_SIZE_32];
    };


ImageTuple_24 normalizeImage(double centeredImage[ROW_SIZE_24*COLUMN_SIZE_24*3]);

mat_24_struct centeredChannel(double matrix32x32[ROW_SIZE_32*COLUMN_SIZE_32]);

ImageTuple_24  centeringImage(double nonCentered_image[ROW_SIZE_32*COLUMN_SIZE_32*CHANNEL_SIZE]);

// void displayImage(const ImageTuple_24& image);


#endif // IMAGE_PROCESSOR_HPP