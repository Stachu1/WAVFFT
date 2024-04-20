#include <stdlib.h>
#include <stdio.h>
#include "wav.h"


void read_wav_header(const char *filename, header_t *wav_header) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Cannot open WAV file\n");
        exit(1);
    }
    fread(wav_header, sizeof(header_t), 1, file);
    fclose(file);
}

void read_wav_interval(const char *filename, header_t *wav_header, float start_sec, float end_sec, short **samples, int *num_samples) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Cannot open WAV file\n");
        exit(1);
    }

    int start_byte = (int)(start_sec * wav_header->byte_rate);
    int end_byte = (int)(end_sec * wav_header->byte_rate);
    int bytes_to_read = end_byte - start_byte;

    *samples = (short *)malloc(bytes_to_read);
    if (*samples == NULL) {
        printf("Memory allocation error\n");
        fclose(file);
        exit(1);
    }

    fseek(file, sizeof(header_t) + start_byte, SEEK_SET);

    fread(*samples, bytes_to_read, 1, file);
    *num_samples = bytes_to_read / (wav_header->bits_per_sample / 8);

    fclose(file);
}

// Thest the other two functions
void wav_test(const char *filename) {
    header_t wav_header;
    short *samples = NULL;
    int num_samples = 0;

    printf("\n\n\n");
    read_wav_header(filename, &wav_header);
    printf("Audio Format: %d\n", wav_header.audio_format);
    printf("Number of Channels: %d\n", wav_header.num_channels);
    printf("Sample Rate: %d\n", wav_header.sample_rate);
    printf("Byte Rate: %d\n", wav_header.byte_rate);
    printf("Block Align: %d\n", wav_header.block_align);
    printf("Bits per Sample: %d\n", wav_header.bits_per_sample);

    read_wav_interval(filename, &wav_header, 10.0f, 11.0f, &samples, &num_samples);

    for (int i = 0; i < 10; i++) {
        printf("%d ", samples[i]);
    }
    printf("\n");
    free(samples);
}