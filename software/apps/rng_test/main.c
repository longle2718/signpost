#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <stdbool.h>

#include "tock.h"
#include "console.h"
#include "timer.h"
#include "rng.h"
#include "app_watchdog.h"

unsigned char randbuf[256];

int main () {
  printf("hello\n");

  while(1) {
    delay_ms(500);
    rng_sync(randbuf, 256, 4);
    char buf[256];
    sprintf(buf, "Random number: 0x%x\n", randbuf[0]);
    putstr(buf);
  }
}
