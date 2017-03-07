// FIXED POINT MATHS
// Long Le <longle2718@gmail.com>
// University of Illinois
//

#ifndef __RIDGETRACKER_H__
#define __RIDGETRACKER_H__

#include <stdbool.h>
#include "dynArray.h"

// The extern vars
extern bool ridgeTracker_isReady;
extern Array ridgeTracker_out;

void ridgeTracker_init(void);
void ridgeTracker_update(kiss_fft_scalar* spec, kiss_fft_scalar* snrOut);
void ridgeTracker_destroy(void);
void ridgeTracker_reset(void);

#endif
