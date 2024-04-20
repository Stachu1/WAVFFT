#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <complex.h>
#include <time.h>
#include "wav.h"
#include "fft.h"


int main() {
    wav_test("data.wav");

    int N = 8;
    double sample_rate = 8;
    complex double x[N];

    for(int i = 0; i < N; i++) {
        x[i] = sin(2 * M_PI * i / N);
    }

    // Perform FFT
    fft(x, N);
    fft_display(x, N, sample_rate, 2);

    return 0;

}