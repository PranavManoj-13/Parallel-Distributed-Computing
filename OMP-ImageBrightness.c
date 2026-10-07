#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "stb_image.h"
#include "stb_image_write.h"

#define BRIGHTNESS_FACTOR 1.3f

int main(void) {
    int width, height, channels;

    printf("----------------------------------------\n");
    printf("Image Brightness Adjustment using OpenMP\n");
    printf("----------------------------------------\n");

    unsigned char *image = stbi_load("sample-img.jpg", &width, &height, &channels, 0);

    if (image == NULL) {
        printf("ERROR: Could not load image\n");
        return 1;
    }

    printf("Image loaded: %dx%d, Channels: %d\n", width, height, channels);

    size_t total_pixels = (size_t)width * height;
    size_t total_elements = total_pixels * channels;

    unsigned char *serial_image = (unsigned char *)malloc(total_elements);
    unsigned char *static_image = (unsigned char *)malloc(total_elements);
    unsigned char *dynamic_image = (unsigned char *)malloc(total_elements);

    if (serial_image == NULL || static_image == NULL || dynamic_image == NULL) {

        printf("ERROR: Memory allocation failed\n");

        stbi_image_free(image);
        free(serial_image);
        free(static_image);
        free(dynamic_image);

        return 1;
    }

    double start, end;

    start = omp_get_wtime();

    for (size_t i = 0; i < total_elements; i++) {
        int value = (int)(image[i] * BRIGHTNESS_FACTOR);

        if (value > 255)
            value = 255;

        serial_image[i] = (unsigned char)value;
    }

    end = omp_get_wtime();

    double serial_time = end - start;

    start = omp_get_wtime();

    #pragma omp parallel for schedule(static)
    for (size_t i = 0; i < total_elements; i++) {
        int value = (int)(image[i] * BRIGHTNESS_FACTOR);

        if (value > 255)
            value = 255;

        static_image[i] = (unsigned char)value;
    }

    end = omp_get_wtime();

    double static_time = end - start;

    start = omp_get_wtime();

    #pragma omp parallel for schedule(dynamic)
    for (size_t i = 0; i < total_elements; i++) {
        int value = (int)(image[i] * BRIGHTNESS_FACTOR);

        if (value > 255)
            value = 255;

        dynamic_image[i] = (unsigned char)value;
    }

    end = omp_get_wtime();

    double dynamic_time = end - start;

    stbi_write_jpg("bright_serial.jpg", width, height, channels, serial_image, 100);
    stbi_write_jpg("bright_static.jpg", width, height, channels, static_image, 100);
    stbi_write_jpg("bright_dynamic.jpg", width, height, channels, dynamic_image, 100);

    printf("\nPerformance Results\n");
    printf("----------------------------------\n");
    printf("Serial          : %.6f seconds\n", serial_time);
    printf("OpenMP Static   : %.6f seconds\n", static_time);
    printf("OpenMP Dynamic  : %.6f seconds\n", dynamic_time);

    printf("\nSpeedup\n");
    printf("-----------------------\n");
    printf("Static Speedup  : %.2fx\n", serial_time / static_time);

    printf("Dynamic Speedup : %.2fx\n", serial_time / dynamic_time);

    free(serial_image);
    free(static_image);
    free(dynamic_image);

    stbi_image_free(image);

    return 0;
}