#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct {
    uint16_t type;       // Magic identifier, 0x4d42 is the type of bmp
    uint32_t size;       // Size of BMP file
    uint16_t reserved1;  //
    uint16_t reserved2;  //
    uint32_t offset;     // Offset to image data, bytes 
} __attribute__ ((packed)) BMPFILEHEADER;

typedef struct {
    uint32_t size;              // The size of this header
    int32_t width;              // The width of the image
    int32_t height;             // The height of the image
    uint16_t planes;            // The number of color planes
    uint16_t bits;              // The number of bits per pixel
    uint32_t compression;       // The compression type
    uint32_t img_size;          // The image size in bytes
    int32_t x_pixelpermeter;    // The x pixel per meter
    int32_t y_pixelpermeter;    // The y pixel per meter
    uint32_t n_colours;         // Numbers of colours
    uint32_t important_colours; // Important colours
} __attribute__ ((packed)) BMPINFOHEADER;

typedef struct {
    uint32_t R;
    uint32_t G;
    uint32_t B;
    uint32_t reserved; 
} PIXEL;

int main(int argc, char** argv) {
    
    // Open the bmp image
    FILE *image = fopen(argv[1], "rb");
    if (image == NULL) {
        printf("Could not open the file %s", argv[1]);
        fclose(image);
        return -1;
    }

    // Give to the header var the image data
    BMPFILEHEADER header;
    fread(&header, sizeof(BMPFILEHEADER), 1, image);
    if (header.type != 0x4D42) {
        printf("The file %s is not a valid BMP.\n", argv[1]);
        fclose(image);
        return -1;
    }

    // Give to the info header var the image data
    BMPINFOHEADER info_header;
    fread(&info_header, sizeof(BMPINFOHEADER), 1, image);
    if (info_header.bits != 24) {
        printf("The file %s is not a valid BMP.\n", argv[1]);
        fclose(image);
        return -1;
    }

    // Open's or create the image that contains the updated image
    FILE *result = fopen(argv[3], "wb");
    if (result == NULL) {
        printf("Could not create or update the file %s", argv[3]);
        fclose(result);
        fclose(image);
        return -1;
    }
    
    // Copy the image data to the result data
    fwrite(&header, sizeof(BMPFILEHEADER), 1, result);
    fwrite(&info_header, sizeof(BMPINFOHEADER), 1, result);
    
    // Goes through all the pixels in the image and replace their colors
    PIXEL color;
    for (int i = 0; i < info_header.height; i++) {
        for (int j = 0; j < info_header.width; j++) {
            // Get the pixel data
            fread(&color, sizeof(PIXEL), 1, image);
            color.R = color.B;
            color.G = color.B;
            color.B = color.R;
            // Give the updated pixel data to the result image
            fwrite(&color, sizeof(PIXEL), 1, result);
        }
    }
    
    fclose(image);
    fclose(result);
    return 0;
}
