#include <ctype.h>
#include <err.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sysex.h"

#define BUF_SIZE 4906

static char * eatSpace(char *);
static void   parseCmd(char *);
static void   runCmd(char, char, char *);
static void   editParam(uint8_t, uint16_t);

/* input transformers */
uint16_t readInt(char *s) {
  return (uint16_t)atoi(s);
}

uint16_t selectWave(char *s) {
  uint8_t w = *s == 's' ? 0 :
              *s == 'p' ? 1 :
              *s == 'q' ? 2 :
              *s == 'n' ? 3 : INVALID;
  uint8_t x = 0;
  uint8_t r = INVALID;
  s++;
  if      (*s == 'y') { x = 1; s++; }
  else if (*s == 'Y') { x = 2; s++; }
  else if (*s == 'x') { x = 3; s++; }
  r = atoi(s);
  r = r == 16 ? 0 :
      r == 8  ? 1 :
      r == 4  ? 2 :
      r == 2  ? 3 : INVALID;
  return (w != INVALID && r != INVALID) ? 
    (r & 3) | ((w & 3) << 2) | ((x & 3) << 4) : INVALID;
}

uint16_t coarseTune(char *s) {
  return 24 + atoi(s);
}

uint16_t fineTune(char *s) {
  return 63 + atoi(s);
}

uint16_t dcoControl(char *s) {
  int8_t e  = 0;
  int8_t ei = 0;
  int8_t l  = 0;
  int8_t li = 0;
  while(*s != '\0') {
    if (*s == 'e') {
      s++;
      if (*s == '-') { ei = 1; s++; }
      e = ((uint8_t)*s - 49) & 3;
      s++;
    }
    else if (*s == 'l') {
      s++;
      if (*s == '-') { li = 1; s++; }
      l = ((uint8_t)*s - 49) & 3;
      s++;
    }
    else { return INVALID; }
  }
  return e | (l << 2) | (ei << 4) | (li << 5);
}

/* core functions */
static char* eatSpace(char *s) {
  while (isspace(*s)) {
    s++;
  }
  return s;
}

static void parseCmd(char *s) {
  char l = ' ';
  char m = ' ';
  s = eatSpace(s);
  l = *s;
  s++;
  if (*s == '.' || *s == ':' || *s == '@') {
    m = *s;
    s++;
  }
  s = eatSpace(s); 
  runCmd(l, m, s);
}

static void runCmd(char l, char m, char *arg) {
  uint8_t n = ((uint8_t)l - 65);
  if (n >= ALPHABET_SIZE) {
    warnx("%s", "bad input");
    return;
  }
  Cmd cmd = m == ' ' ? CMDS_PURE[n]  :
            m == '.' ? CMDS_DOT[n]   :
            m == ':' ? CMDS_COLON[n] :
            m == '@' ? CMDS_AT[n]    : CMDS_PURE[ALPHABET_SIZE - 1];
  uint16_t v = cmd.f(arg);
  editParam(cmd.n, v);
}

static void editParam(uint8_t p, uint16_t v) {
  if (p == INVALID || v == INVALID) {
    warnx("%s", "bad input");
    return;
  }
  sysexMsg[SYSEX_PARAM_IX] = p;
  sysexMsg[SYSEX_VAL_UPPER_IX] = (v >> 7) & 4095;
  sysexMsg[SYSEX_VAL_LOWER_IX] = v & 127;
  fwrite(sysexMsg, SYSEX_MSG_SIZE, 1, stdout);
  fflush(stdout);
}

int main(void) {
  char *t = NULL;
  char buf[BUF_SIZE] = {0};
  while (1) {
    fgets(buf, BUF_SIZE, stdin);
    t = strtok(buf, ";\n");
    while (t != NULL) {
      parseCmd(t);
      t = strtok(NULL, ";\n");
    }
  }
  return 0;
}
