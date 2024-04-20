#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <complex.h>
#include "fft.h"


void fft(complex double *x, int n) {
    if (n <= 1) return;

    // Divide
    complex double even[n/2], odd[n/2];
    for (int i = 0; i < n/2; i++) {
        even[i] = x[i*2];
        odd[i] = x[i*2 + 1];
    }

    // Conquer
    fft(even, n/2);
    fft(odd, n/2);

    // Combine
    for (int k = 0; k < n/2; k++) {
        complex double t = cexp(-2 * I * M_PI * k / n) * odd[k];
        x[k] = even[k] + t;
        x[k +n/2] = even[k] - t;
    }
}

void fft_print(complex double *x, int n, double sample_rate) {
    for(int i = 0; i < n/2+1; i++) {
        printf("Frequency: %f Hz   Amplitude = %f\n", i * sample_rate / n, cabs(x[i]) * 2 / n);
    }
}

void fft_display(complex double *x, int n, double sample_rate, double scale) {
    printf("--------------------------------\n");
    for(int i = 0; i < n/2+1; i++) {
        printf("|");
        int a = (int)(cabs(x[i]) * 2 / n * scale);
        for (int j = 0; j < a; j++) {
            printf("#");
        }
        printf("\n");
    }
    printf("--------------------------------\n");
}