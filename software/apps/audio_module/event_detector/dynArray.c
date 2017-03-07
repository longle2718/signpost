#include <stdio.h>
#include <stdlib.h>
#include "dynArray.h"
#include "_kiss_fft_guts.h"

void initArray(Array *a, size_t initialSize) {
    a->maxSize = initialSize;
    a->used = 0;

    a->size = a->maxSize;
    printf("Init array size = %zu\n",a->size);
    a->SNR = malloc(a->size * sizeof(kiss_fft_scalar));
    a->FI = malloc(a->size * sizeof(size_t));
    a->TI = malloc(a->size * sizeof(size_t));
}

void insertArray(Array *a, kiss_fft_scalar snr, size_t fi, size_t ti) {
    // a->used is the number of used entries, because a->array[a->used++] updates a->used only *after* the array has been accessed.
    // Therefore a->used can go up to a->size 
    if (a->size > 0 && a->used == a->size) {
        a->maxSize *= 2;
        printf("Doubled array max size to %zu\n",a->maxSize);
    }
    if (a->size < a->maxSize) {
        a->size = a->maxSize;
        // with NULL ptr, realloc == malloc
        a->SNR = realloc(a->SNR, a->size * sizeof(kiss_fft_scalar));
        a->FI = realloc(a->FI, a->size * sizeof(size_t));
        a->TI = realloc(a->TI, a->size * sizeof(size_t));
    }
    a->SNR[a->used] = snr;
    a->FI[a->used] = fi;
    a->TI[a->used] = ti;
    a->used++;
}

void freeArray(Array *a) {
    free(a->SNR);
    free(a->FI);
    free(a->TI);
    a->SNR = NULL;
    a->FI = NULL;
    a->TI = NULL;
    a->used = a->size = 0;
}
size_t getMaxDurArray(Array a){
    if (a.used == 0)
        return 0;

    size_t minTI = a.TI[0];
    size_t maxTI = a.TI[a.used-1];
    return maxTI-minTI;
}

kiss_fft_scalar getAvgSNRArray(Array a){
    if (a.used == 0)
        return 0;

    SAMPPROD sum = 0;
    for (size_t k=0; k < a.used; k++){
        sum += a.SNR[k];
    }
    return (kiss_fft_scalar)(sum/a.used);
}
