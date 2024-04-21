#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <complex.h>
#include <time.h>
#include "wav.h"
#include "fft.h"


uint32_t millis() {
  struct timespec t ;
  clock_gettime(CLOCK_MONOTONIC_RAW, &t) ;
  return t.tv_sec * 1000 + ( t.tv_nsec + 500000 ) / 1000000 ;
}

int main() {
    const char *filename = "f.wav";

    wav_test(filename);
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Cannot open WAV file\n");
        exit(1);
    }

    header_t header;
    fread(&header, sizeof(header_t), 1, file);

    fseek(file, 0L, SEEK_END);
    long int file_size = ftell(file);
    fseek(file, 0L, SEEK_SET);
    int file_duration_ms = 1e3 * file_size / header.byte_rate;

    printf("Duration: %.2fs\n", file_duration_ms / 1000.0f);

    // Wait for 3s
    for (int i = 3; i > 0; i--) {
        printf("%ds\n", i);
        uint32_t t_s = millis();
        while(millis() - t_s < 1000);
    }

    const int N = 32;
    complex double fft_values[N];
    for (int i = 0; i < N; i++) { fft_values[i] = 0; }

    uint32_t t_print, t_start = millis();
    for (int i = 0; i < file_duration_ms * 0.1; i++) {
        short sound_v[N];
        wav_read(file, header.sample_rate / 100 * i + 0xF0, N, sound_v);
        complex double x[N];
        for (int j = 0; j < N; j++) { x[j] = (complex double)sound_v[j]; }

        fft(x, N);

        for (int j = 0; j < N; j++) {
            fft_values[j] = fft_values[j] - 0.05*(fft_values[j] + x[j]);
        }

        if (i % 10 == 0) {
            t_print = millis();
            fft_display(fft_values, N, header.sample_rate, 10);
            printf("%.2fs\n", (millis() - t_start) * 0.001);
            while (millis() - t_print < 100);
        }
    }

    fclose(file);
    return 0;
}