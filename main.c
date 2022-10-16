#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "sysex.h"

static void editParam(const SysexParam p, uint16_t v) {
  sysexMsg[SYSEX_PARAM_IX] = p;
  sysexMsg[SYSEX_VAL_UPPER_IX] = v >> 7;
  sysexMsg[SYSEX_VAL_LOWER_IX] = v & 127;
  fwrite(sysexMsg, SYSEX_MSG_SIZE, 1, stdout);
  fflush(stdout);
  return;
}

int main(void) {
  char buf[4096] = {0};
  uint16_t n = 0;
  while (1) {
    fgets(buf, 4096, stdin);
    n = atoi(buf);
    editParam(VCF_CUTOFF, n);
  }
  return 0;
}
