#ifndef FFT_H
#define FFT_H

#include <complex.h>

void fft(complex double *x, int n);
void fft_print(complex double *x, int n, double sample_rate);
void fft_display(complex double *x, int n, double sample_rate, double scale);

#endif