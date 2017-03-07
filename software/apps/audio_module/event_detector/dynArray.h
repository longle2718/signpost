#ifndef __DYNARRAY_H__
#define __DYNARRAY_H__

#include "kiss_fft.h"

typedef struct {
    kiss_fft_scalar *SNR; // log SNR
    size_t *FI; // frequency index
    size_t *TI; // time index
    size_t size;
    size_t used;
    size_t maxSize;
} Array;

void initArray(Array *a, size_t initialSize);
void insertArray(Array *a, kiss_fft_scalar snr, size_t fi, size_t ti);
void freeArray(Array *a);

size_t getMaxDurArray(Array a);
kiss_fft_scalar getAvgSNRArray(Array a);
#endif
