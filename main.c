#include <ctype.h>
#include <err.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "sysex.h"

#define BUF_SIZE 4906

#define INCREMENT(S) if (*S == '\0') { return INVALID; } else { S++; }

static char * eatSpace(char *);
static void   parseCmd(char *);
static void   runCmd(char, char, char *);
static void   setClock(uint16_t);
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
  INCREMENT(s)
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

uint16_t envLfoControl(char *s) {
  int8_t e  = 0;
  int8_t ei = 0;
  int8_t l  = 0;
  int8_t li = 0;
  while(*s != '\0') {
    if (*s == 'e') {
      INCREMENT(s)
      if (*s == '-') { ei = 1; s++; }
      e = ((uint8_t)*s - 49) & 3;
      s++;
    }
    else if (*s == 'l') {
      INCREMENT(s)
      if (*s == '-') { li = 1; s++; }
      l = ((uint8_t)*s - 49) & 3;
      s++;
    }
    else { return INVALID; }
  }
  return e | (l << 2) | (ei << 4) | (li << 5);
}

uint16_t vcaControl(char *s) {
  int8_t e  = 0;
  int8_t l  = 0;
  int8_t li = 0;
  while(*s != '\0') {
    if (*s == 'e') {
      INCREMENT(s)
      e = ((uint8_t)*s - 48) & 3;
      s++;
    }
    else if (*s == 'l') {
      INCREMENT(s)
      if (*s == '-') { li = 1; s++; }
      l = ((uint8_t)*s - 49) & 3;
      s++;
    }
    else { return INVALID; }
  }
  return e | (l << 3) | (li << 6);
}

uint16_t matrixSource(char *s) {
  uint8_t l = 8;
  if (*s == 'b') {
    s++;
    return *s == 'u'  ? 1  :
           *s == 'd'  ? 2  :
           *s == 'w'  ? 32 :
           *s == '\0' ? 3  : INVALID;
  } else if (*s == 'l') {
    INCREMENT(s)
    l += ((uint8_t)*s - 49) * 2;
    s++;
    return l + (*s == 'u'); 
  } else if (*s == 'e') {
    INCREMENT(s)
    return 14 + ((uint8_t)*s - 49);
  } else if (*s == 'c') {
    INCREMENT(s)
    return 17 + ((uint8_t)*s - 49);
  } else if (*s == 's') {
    INCREMENT(s)
    return 26 + ((uint8_t)*s - 49);
  }
  return *s == 'o' ? 0  :
         *s == 'w' ? 4  :
         *s == 'd' ? 5  :
         *s == 'v' ? 6  :
         *s == 'n' ? 7  :
         *s == 'a' ? 25 : INVALID;
}

uint16_t matrixControl(char *s) {
  uint8_t i = 0;
  if (*s == '-') { i = 1 ; s++; }
  if (*s == 'b') {
    s++;
    return *s == 'u'  ? 2 + i :
           *s == 'd'  ? 4 + i :
           *s == '\0' ? 6 + i : INVALID;
  } else if (*s == 'c') {
    INCREMENT(s)
    return 14 + (((uint8_t)*s - 49) * 2) + i;
  } else if (*s == 's') {
    INCREMENT(s)
    return 30 + ((uint8_t)*s - 49);
  }
  return *s == 'o' ? 0 + i  :
         *s == 'w' ? 8 + i  :
         *s == 'd' ? 10 + i :
         *s == 'a' ? 12 + i : INVALID;
}

uint16_t matrixDestination(char *s) {
  if (*s == 'p') {
    s++;
    return *s == '1'  ? 1 :
           *s == '2'  ? 2 :
           *s == '\0' ? 3 : INVALID;
  } else if (*s == 'w') {
    INCREMENT(s)
    return 4 + (((uint8_t)*s - 49) * 2);
  } else if (*s == 'r') {
    INCREMENT(s)
    return 5 + (((uint8_t)*s - 49) * 2);
  } else if (*s == 'm') {
    INCREMENT(s)
    return 9 + ((uint8_t)*s - 49);
  } else if (*s == 'f') {
    s++;
    return *s == '.'  ? 12 :
           *s == ':'  ? 13 :
           *s == '\0' ? 11 : INVALID;
  } else if (*s == 'l') {
    INCREMENT(s)
    return 16 + ((uint8_t)*s - 49);
  } else if (*s == 'e') {
    INCREMENT(s)
    return 19 + ((uint8_t)*s - 49);
  }
  return *s == 'o' ? 0  :
         *s == 'd' ? 8  :
         *s == 'v' ? 14 :
         *s == 'P' ? 15 : INVALID;
}

uint16_t selectLfoWave(char *s) {
  return *s == 'i' ? 0 :
         *s == 't' ? 1 :
         *s == 'q' ? 2 :
         *s == 's' ? 3 :
         *s == 'S' ? 4 :
         *s == 'r' ? 5 : INVALID;
}

uint16_t lfoControl(char *s) {
  uint8_t f = 0;
  float d = 0.0f;
  uint8_t l = INVALID;
  if (*s == '+') { f = 1; s++; }
  d = atof(s);
  l = d == 0.0f   ? 0  :
      d == 2.0f   ? 1  :
      d == 1.5f   ? 2  :
      d == 1.0f   ? 3  :
      d == 1.25f  ? 4  :
      d == 1.2f   ? 5  :
      d == 1.45f  ? 6  :
      d == 1.4f   ? 7  :
      d == 1.85f  ? 8  :
      d == 1.43f  ? 9  :
      d == 1.8f   ? 10 :
      d == 1.83f  ? 11 :
      d == 1.16f  ? 12 :
      d == 1.163f ? 13 :
      d == 1.32f  ? 14 :
      d == 1.323f ? 15 :
      d == 1.64f  ? 16 : INVALID;
  return l != INVALID ? f | (l << 1) : l;
}

uint16_t voiceMode1(char *s) {
  uint8_t r = 0;
  uint8_t l = 0;
  uint8_t p = 0;
  while (*s != '\0') {
    if      (*s == 's') { p = 0 ; s++;    }
    else if (*s == 'd') { p = 1 ; s++;    }
    else if (*s == 't') { p = 2 ; s++;    }
    else if (*s == 'u') { p = 4 ; s++;    }
    else if (*s == 'S') { p = 5 ; s++;    }
    else if (*s == 'r') { r = 1 ; s++;    }
    else if (*s == 'l') { l = 1 ; s++;    }
    else                { return INVALID; }
  }
  return p | (r << 3) | (l << 4);
}

uint16_t voiceMode2(char *s) {
  return *s == 'o' ? 0 :
         *s == 'n' ? 1 :
         *s == 'h' ? 2 :
         *s == 'l' ? 3 :
         *s == 'q' ? 4 :
         *s == 'i' ? 5 : INVALID;
}

uint16_t arpControl(char *s) {
  uint8_t o = (uint8_t)*s - 49;
  uint8_t p = INVALID;
  INCREMENT(s)
  p = *s == 'u' ? 0 :
      *s == 'd' ? 1 :
      *s == 'b' ? 2 :
      *s == 'r' ? 3 :
      *s == 'p' ? 4 : INVALID;
  return (o & 3) | (p << 3);
}

uint16_t afterTouchWheelControl(char *s) {
  uint8_t n = 0;
  while (*s != '\0') {
    if      (*s == 'l') { n |= 1; s++; }
    else if (*s == 'f') { n |= 2; s++; }
    else if (*s == 'v') { n |= 4; s++; }
    else                { return INVALID; }
  }
  return n;
}

uint16_t midiControl(char *s) {
  uint8_t n = 0;
  while (*s != '\0') {
    if      (*s == 'a') { n |= 1; s++; }
    else if (*s == 's') { n |= 2; s++; }
    else if (*s == 'h') { n |= 8; s++; }
    else                { return INVALID; }
  }
  return n;
}

uint16_t clockDivide(char *s) {
  float f = atof(s);
  return f == 1.2f   ? 0  :
         f == 1.4f   ? 1  :
         f == 1.8f   ? 2  :
         f == 1.85f  ? 3  :
         f == 1.89f  ? 4  :
         f == 1.83f  ? 5  :
         f == 1.16f  ? 6  :
         f == 1.165f ? 7  :
         f == 1.169f ? 8  :
         f == 1.163f ? 9  :
         f == 1.32f  ? 10 :
         f == 1.323f ? 11 :
         f == 1.64f  ? 12 : INVALID;
}

uint16_t seqControl(char *s) {
  uint8_t n = 0;
  while (*s != '\0') {
    if      (*s == 'o') { n |= 1; s++; }
    else if (*s == 'k') { n |= 2; s++; }
    else if (*s == 't') { n |= 4; s++; }
    else if (*s == 'r') { n |= 8; s++; }
    else if (*s == 'c') { n |= 16; s++; }
    else                { return INVALID; }
  }
  return n;
}

uint16_t seqTranspose(char *s) {
  return 12 + atoi(s);
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
  if (cmd.n == CLOCK) {
    setClock(v);
  } else { 
    editParam(cmd.n, v); 
  }
}

static void setClock(uint16_t v) {
  v = (((v & 240) << 4) | v) & 3855;
  sysexMsg[SYSEX_PARAM_IX] = CLOCK;
  sysexMsg[SYSEX_VAL_UPPER_IX] = v >> 8;
  sysexMsg[SYSEX_VAL_LOWER_IX] = v & 15;
  fwrite(sysexMsg, SYSEX_MSG_SIZE, 1, stdout);
  fflush(stdout);
}

static void editParam(uint8_t p, uint16_t v) {
  if (v == NOOP) {
    return;
  }
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
      usleep(20000);
      t = strtok(NULL, ";\n");
    }
  }
  return 0;
}
