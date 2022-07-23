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
    int32_t x_resolution;       // The x pixel per meter
    int32_t y_resolution;       // The y pixel per meter
    uint32_t n_colours;         // Numbers of colours
    uint32_t important_colours; // Important colours
} __attribute__ ((packed)) BMPINFOHEADER;

int main(int argc, char** argv) {
    FILE *image;
    BMPFILEHEADER header;
    BMPINFOHEADER info_header;

    image = fopen("assets/campo.bmp", "rb");
    if (!image) {
        printf("Could not open the file %s", "assets/campo.bmp");
        fclose(image);
        return -1;
    }

    fread(&header, sizeof(BMPFILEHEADER), 1, image);
    if (header.type != 0x4D42) {
        printf("The file %s is not a valid BMP.\n", "assets/campo.bmp");
        fclose(image);
        return -1;
    }

    fread(&info_header, sizeof(BMPINFOHEADER), 1, image);
    if (info_header.bits != 24) {
        printf("The file %s is not a valid BMP.\n", "assets/campo.bmp");
        fclose(image);
        return -1;
    }

    return 0;
}
