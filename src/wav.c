#include <stdlib.h>
#include <stdio.h>
#include "wav.h"


void read_wav_interval(FILE *file, header_t *header, float start_sec, float end_sec, short **samples, int *num_samples) {
    int start_byte = (int)(start_sec * header->byte_rate);
    int end_byte = (int)(end_sec * header->byte_rate);
    int bytes_to_read = end_byte - start_byte;

    printf("Byte start: %lu\n", sizeof(header_t) + start_byte);
    *samples = (short *)malloc(bytes_to_read);
    if (*samples == NULL) {
        printf("Memory allocation error\n");
        fclose(file);
        exit(1);
    }

    fseek(file, start_byte, SEEK_SET);
    fread(*samples, bytes_to_read, 1, file);
    *num_samples = bytes_to_read / (header->bits_per_sample / 8);
}


void wav_read(FILE *file, unsigned long offset, int count, short *samples) {
    fseek(file, offset, SEEK_SET);
    fread(samples, sizeof(short), count, file);
}


void wav_test(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Cannot open WAV file\n");
        exit(1);
    }
    header_t header;

    fread(&header, sizeof(header_t), 1, file);
    printf("\nFormat: %.4s\n", header.format);
    printf("Audio Format: %d\n", header.audio_format);
    printf("Number of Channels: %d\n", header.num_channels);
    printf("Sample Rate: %d\n", header.sample_rate);
    printf("Byte Rate: %d\n", header.byte_rate);
    printf("Block Align: %d\n", header.block_align);
    printf("Bits per Sample: %d\n\n", header.bits_per_sample);
    fclose(file);
}