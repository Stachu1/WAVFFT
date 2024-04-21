#ifndef WAV_H
#define WAV_H

typedef struct header_t {
    char chunk_id[4];
    int chunk_size;
    char format[4];
    char subchunk1_id[4];
    int subchunk1_size;
    short audio_format;
    short num_channels;
    int sample_rate;
    int byte_rate;
    short block_align;
    short bits_per_sample;
    char subchunk2_id[4];
    int subchunk2_size;
} header_t;

void read_wav_interval(FILE *file, header_t *wav_header, float start_sec, float end_sec, short **samples, int *num_samples);
void wav_read(FILE *file, unsigned long offset, int count, short *samples);
void wav_test(const char *filename);

#endif