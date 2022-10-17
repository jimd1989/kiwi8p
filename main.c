#include <err.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "sysex.h"

#define BUF_SIZE 4906

static void runCmd(char, char, char *);
static void editParam(uint8_t, uint16_t);

/* input transformers */
uint16_t readInt(char *s) {
  return (uint16_t)atoi(s);
}

/* core functions */
static void runCmd(char l, char m, char *arg) {
  uint8_t n = ((uint8_t)l - 65) & ALPHABET_SIZE;
  Cmd cmd = m == ' ' ? CMDS_PURE[n]  :
            m == '.' ? CMDS_DOT[n]   :
            m == ':' ? CMDS_COLON[n] :
            m == '@' ? CMDS_AT[n]    : CMDS_PURE[ALPHABET_SIZE - 1];
  uint16_t v = cmd.f(arg);
  editParam(cmd.n, v);
}

static void editParam(uint8_t p, uint16_t v) {
  if (p == UNKNOWN_FUNC) {
    warnx("%s", "got unknown input");
    return;
  }
  sysexMsg[SYSEX_PARAM_IX] = p;
  sysexMsg[SYSEX_VAL_UPPER_IX] = (v >> 7) & 4095;
  sysexMsg[SYSEX_VAL_LOWER_IX] = v & 127;
  fwrite(sysexMsg, SYSEX_MSG_SIZE, 1, stdout);
  fflush(stdout);
}

int main(void) {
  char buf[BUF_SIZE] = {0};
  uint16_t n = 0;
  while (1) {
    fgets(buf, BUF_SIZE, stdin);
    /* split semicolons */
    /* split letter:modifier:arg */
  }
  return 0;
}
