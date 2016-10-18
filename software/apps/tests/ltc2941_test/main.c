#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <stdbool.h>

#include "tock.h"
#include "console.h"
#include "timer.h"
#include "ltc2941.h"


void print_data (int charge) {
  char buf[64];
  sprintf(buf, "\tCharge: 0x%02x\n\n", charge);
  putstr(buf);
}

void print_status (int status) {
  char buf[64];
  sprintf(buf, "\tStatus: 0x%02x\n\n", status);
  putstr(buf);
}

int main () {
  putstr("[LTC2941] Test\n");

  int status = ltc2941_read_status_sync();
  print_status(status);

  ltc2941_reset_charge_sync();
  ltc2941_set_high_threshold_sync(0x0010);

  while (1) {
    int charge = ltc2941_get_charge_sync();
    print_data(charge);
    delay_ms(1000);
  }
}