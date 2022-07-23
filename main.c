#include <stdio.h>
#include <stdint.h>

typedef struct {
    char type[2];        // Magic identifier
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
    printf("Type:                        %c%c\n", header.type[0], header.type[1]);
    printf("Size:                        %d\n", header.size);
    printf("Verify:                      %d %d\n");
    printf("Offset:                      %d\n", header.offset);

    if (header.type[0] != 'B' || header.type[1] != 'M') {
        printf("The file %s is not a valid BMP.", "assets/campo.bmp");
        fclose(image);
        return -1;
    }

    fread(&info_header, sizeof(BMPINFOHEADER), 1, image);
    printf("Size of Header:              %d\n", info_header.size);
    printf("Width:                       %d\n", info_header.width);
    printf("Height:                      %d\n", info_header.height);
    printf("Planes:                      %d\n", info_header.planes);
    printf("Bits:                        %d\n", info_header.bits);
    printf("Compression:                 %d\n", info_header.compression);
    printf("Image Size:                  %d\n", info_header.img_size);
    printf("Preferred x:                 %d\n", info_header.x_resolution);
    printf("Preferred y:                 %d\n", info_header.y_resolution);
    printf("Number of Colours:           %d\n", info_header.n_colours);
    printf("Number of Important Colours: %d\n", info_header.important_colours);

    fclose(image);
    return 0;
}
