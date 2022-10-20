#pragma once

#include <stdint.h>

/* Sysex message format */
#define SYSEX_START 240
#define MANUFACTURER_ID_1 0
#define MANUFACTURER_ID_2 33
#define MANUFACTURER_ID_3 22
#define FAMILY_ID 96
#define JX8P_ID 4
/* Device id here (set by parameter 611; locked to 1 for now) */
#define DEVICE_ID 0
/* Command id here */
#define SYSEX_EDIT_PARAM 14
/* Data here */
#define VOICE_NUM 1
#define SYSEX_FOOTER 247
/* Full cmd */
#define SYSEX_MSG_SIZE 13
#define SYSEX_PARAM_IX 9
#define SYSEX_VAL_UPPER_IX 10
#define SYSEX_VAL_LOWER_IX 11

static uint8_t sysexMsg[SYSEX_MSG_SIZE] = {
  SYSEX_START,
  MANUFACTURER_ID_1, MANUFACTURER_ID_2, MANUFACTURER_ID_3,
  FAMILY_ID,
  JX8P_ID,
  DEVICE_ID,
  SYSEX_EDIT_PARAM,
  VOICE_NUM,
  0,    /* Insert parameter here */
  0, 0, /* Insert two bytes of values here */
  SYSEX_FOOTER
};

/* Command type */
typedef uint16_t (*Transformer)(char *s);

typedef struct Cmd {
  uint8_t       n;
  Transformer   f;
} Cmd;

/* Transformer declarations */
uint16_t readInt(char *);
uint16_t selectWave(char *);
uint16_t coarseTune(char *);
uint16_t fineTune(char *);
uint16_t envLfoControl(char *);
uint16_t vcaControl(char *);
uint16_t matrixSource(char *);
uint16_t matrixControl(char*);
uint16_t matrixDestination(char *);
uint16_t selectLfoWave(char *);

#define INVALID 128

/* Alphabets */
#define ALPHABET_SIZE 59

static const Cmd CMDS_PURE[ALPHABET_SIZE] = {
  { 109, readInt}, /* A */
  { INVALID, readInt}, /* B */
  { 38, envLfoControl}, /* C */
  { 94, readInt}, /* D */
  { 37, readInt}, /* E */
  { INVALID, readInt}, /* F */
  { INVALID, readInt}, /* G */
  { INVALID, readInt}, /* H */
  { INVALID, readInt}, /* I */
  { INVALID, readInt}, /* J */
  { INVALID, readInt}, /* K */
  { INVALID, readInt}, /* L */
  { INVALID, readInt}, /* M */
  { 95, readInt}, /* N */
  { INVALID, readInt}, /* O */
  { INVALID, readInt}, /* P */
  { 65, matrixSource}, /* Q */
  { 93, readInt}, /* R */
  { 113, readInt}, /* S */
  { 114, readInt}, /* T */
  { 66, matrixControl}, /* U */
  { 34, readInt}, /* V */
  { 92, selectLfoWave}, /* W */
  { 67, readInt}, /* X */
  { 36, readInt}, /* Y */
  { 68, matrixDestination}, /* Z */
  { INVALID, readInt}, /* ignored */
  { INVALID, readInt}, /* ignored */
  { INVALID, readInt}, /* ignored */
  { INVALID, readInt}, /* ignored */
  { INVALID, readInt}, /* ignored */
  { INVALID, readInt}, /* ignored */
  { 77, readInt}, /* a */
  { 118, readInt}, /* b */
  { 25, envLfoControl}, /* c */
  { 78, readInt}, /* d */
  { 23, readInt}, /* e */
  { 40, readInt}, /* f */
  { INVALID, readInt}, /* g */
  { INVALID, readInt}, /* h */
  { 107, readInt}, /* i */
  { INVALID, readInt}, /* j */
  { 81, readInt}, /* k */
  { 22, readInt}, /* l */
  { INVALID, readInt}, /* m */
  { INVALID, readInt}, /* n */
  { 104, readInt}, /* o */
  { 105, readInt}, /* p */
  { 53, matrixSource}, /* q */
  { 80, readInt}, /* r */
  { 79, readInt}, /* s */
  { 21, coarseTune}, /* t */
  { 54, matrixControl}, /* u */
  { 49, readInt}, /* v */
  { 20, selectWave}, /* w */
  { 55, readInt}, /* x */
  { 24, readInt}, /* y */
  { 56, matrixDestination}, /* z */
  { INVALID, readInt}, /* ignored */
};

static const Cmd CMDS_DOT[ALPHABET_SIZE] = {
  { 110, readInt}, /* A. */
  { INVALID, readInt}, /* B. */
  { INVALID, readInt}, /* C. */
  { 98, readInt}, /* D. */
  { INVALID, readInt}, /* E. */
  { INVALID, readInt}, /* F. */
  { INVALID, readInt}, /* G. */
  { INVALID, readInt}, /* H. */
  { INVALID, readInt}, /* I. */
  { INVALID, readInt}, /* J. */
  { INVALID, readInt}, /* K. */
  { INVALID, readInt}, /* L. */
  { INVALID, readInt}, /* M. */
  { 99, readInt}, /* N. */
  { INVALID, readInt}, /* O. */
  { INVALID, readInt}, /* P. */
  { 69, matrixSource}, /* Q. */
  { 97, readInt}, /* R. */
  { 119, readInt}, /* S. */
  { 116, readInt}, /* T. */
  { 70, matrixControl}, /* U. */
  { 35, readInt}, /* V. */
  { 96, selectLfoWave}, /* W. */
  { 71, readInt}, /* X. */
  { INVALID, readInt}, /* Y. */
  { 72, matrixDestination}, /* Z. */
  { INVALID, readInt}, /* ignored */
  { INVALID, readInt}, /* ignored */
  { INVALID, readInt}, /* ignored */
  { INVALID, readInt}, /* ignored */
  { INVALID, readInt}, /* ignored */
  { INVALID, readInt}, /* ignored */
  { 82, readInt}, /* a. */
  { 111, readInt}, /* b. */
  { 32, envLfoControl}, /* c. */
  { 83, readInt}, /* d. */
  { 30, readInt}, /* e. */
  { 42, readInt}, /* f. */
  { INVALID, readInt}, /* g. */
  { INVALID, readInt}, /* h. */
  { 108, readInt}, /* i. */
  { INVALID, readInt}, /* j. */
  { 86, readInt}, /* k. */
  { 29, readInt}, /* l. */
  { INVALID, readInt}, /* m. */
  { INVALID, readInt}, /* n. */
  { INVALID, readInt}, /* o. */
  { INVALID, readInt}, /* p. */
  { 57, matrixSource}, /* q. */
  { 85, readInt}, /* r. */
  { 84, readInt}, /* s. */
  { 27, coarseTune}, /* t. */
  { 58, matrixControl}, /* u. */
  { INVALID, readInt}, /* v. */
  { 26, selectWave}, /* w. */
  { 59, readInt}, /* x. */
  { 31, readInt}, /* y. */
  { 60, matrixDestination}, /* z. */
  { INVALID, readInt}, /* ignored */
};

static const Cmd CMDS_COLON[ALPHABET_SIZE] = {
  { 121, readInt}, /* A: */
  { INVALID, readInt}, /* B: */
  { INVALID, readInt}, /* C: */
  { 102, readInt}, /* D: */
  { INVALID, readInt}, /* E: */
  { INVALID, readInt}, /* F: */
  { INVALID, readInt}, /* G: */
  { INVALID, readInt}, /* H: */
  { INVALID, readInt}, /* I: */
  { INVALID, readInt}, /* J: */
  { INVALID, readInt}, /* K: */
  { INVALID, readInt}, /* L: */
  { INVALID, readInt}, /* M: */
  { 103, readInt}, /* N: */
  { INVALID, readInt}, /* O: */
  { INVALID, readInt}, /* P: */
  { 73, matrixSource}, /* Q: */
  { 101, readInt}, /* R: */
  { 120, readInt}, /* S: */
  { 117, readInt}, /* T: */
  { 74, matrixControl}, /* U: */
  { INVALID, readInt}, /* V: */
  { 100, selectLfoWave}, /* W: */
  { 75, readInt}, /* X: */
  { INVALID, readInt}, /* Y: */
  { 76, matrixDestination}, /* Z: */
  { INVALID, readInt}, /* ignored */
  { INVALID, readInt}, /* ignored */
  { INVALID, readInt}, /* ignored */
  { INVALID, readInt}, /* ignored */
  { INVALID, readInt}, /* ignored */
  { INVALID, readInt}, /* ignored */
  { 87, readInt}, /* a: */
  { 112, readInt}, /* b: */
  { 51, vcaControl}, /* c: */
  { 88, readInt}, /* d: */
  { INVALID, readInt}, /* e: */
  { 39, readInt}, /* f: */
  { INVALID, readInt}, /* g: */
  { INVALID, readInt}, /* h: */
  { INVALID, readInt}, /* i: */
  { INVALID, readInt}, /* j: */
  { 91, readInt}, /* k: */
  { 50, readInt}, /* l: */
  { INVALID, readInt}, /* m: */
  { INVALID, readInt}, /* n: */
  { INVALID, readInt}, /* o: */
  { INVALID, readInt}, /* p: */
  { 61, matrixSource}, /* q: */
  { 90, readInt}, /* r: */
  { 89, readInt}, /* s: */
  { 28, fineTune}, /* t: */
  { 62, matrixControl}, /* u: */
  { INVALID, readInt}, /* v: */
  { INVALID, readInt}, /* w: */
  { 63, readInt}, /* x: */
  { 52, readInt}, /* y: */
  { 64, matrixDestination}, /* z: */
  { INVALID, readInt}, /* ignored */
};

static const Cmd CMDS_AT[ALPHABET_SIZE] = {
  { INVALID, readInt}, /* A@ */
  { INVALID, readInt}, /* B@ */
  { INVALID, readInt}, /* C@ */
  { INVALID, readInt}, /* D@ */
  { INVALID, readInt}, /* E@ */
  { INVALID, readInt}, /* F@ */
  { INVALID, readInt}, /* G@ */
  { INVALID, readInt}, /* H@ */
  { INVALID, readInt}, /* I@ */
  { INVALID, readInt}, /* J@ */
  { INVALID, readInt}, /* K@ */
  { INVALID, readInt}, /* L@ */
  { INVALID, readInt}, /* M@ */
  { INVALID, readInt}, /* N@ */
  { INVALID, readInt}, /* O@ */
  { INVALID, readInt}, /* P@ */
  { INVALID, readInt}, /* Q@ */
  { INVALID, readInt}, /* R@ */
  { 106, readInt}, /* S@ */
  { INVALID, readInt}, /* T@ */
  { INVALID, readInt}, /* U@ */
  { INVALID, readInt}, /* V@ */
  { INVALID, readInt}, /* W@ */
  { INVALID, readInt}, /* X@ */
  { INVALID, readInt}, /* Y@ */
  { INVALID, readInt}, /* Z@ */
  { INVALID, readInt}, /* ignored */
  { INVALID, readInt}, /* ignored */
  { INVALID, readInt}, /* ignored */
  { INVALID, readInt}, /* ignored */
  { INVALID, readInt}, /* ignored */
  { INVALID, readInt}, /* ignored */
  { INVALID, readInt}, /* a@ */
  { INVALID, readInt}, /* b@ */
  { 48, envLfoControl}, /* c@ */
  { INVALID, readInt}, /* d@ */
  { 45, readInt}, /* e@ */
  { INVALID, readInt}, /* f@ */
  { INVALID, readInt}, /* g@ */
  { INVALID, readInt}, /* h@ */
  { INVALID, readInt}, /* i@ */
  { INVALID, readInt}, /* j@ */
  { 46, readInt}, /* k@ */
  { 44, readInt}, /* l@ */
  { INVALID, readInt}, /* m@ */
  { INVALID, readInt}, /* n@ */
  { INVALID, readInt}, /* o@ */
  { INVALID, readInt}, /* p@ */
  { INVALID, readInt}, /* q@ */
  { INVALID, readInt}, /* r@ */
  { INVALID, readInt}, /* s@ */
  { 33, readInt}, /* t@ */
  { INVALID, readInt}, /* u@ */
  { INVALID, readInt}, /* v@ */
  { INVALID, readInt}, /* w@ */
  { INVALID, readInt}, /* x@ */
  { 47, readInt}, /* y@ */
  { INVALID, readInt}, /* z@ */
  { INVALID, readInt}, /* ignored */
};

/*
 * o1w - 20 - w
 * o1t - 21 - t
 * o1l - 22 - l
 * o1e - 23 - e
 * o1d - 24 - y
 * o1c - 25 - c
 * o2w - 26 - w.
 * o2t - 27 - t.
 * o2T - 28 - t:
 * o2l - 29 - l.
 * o2e - 30 - e.
 * o2d - 31 - y.
 * o2c - 32 - c.
 * dt  - 33 - t@
 * m1v - 34 - V
 * m2v - 35 - V.
 * m2d - 36 - Y
 * m2e - 37 - E
 * m2c - 38 - C
 * fh  - 39 - f:
 * fL  - 40 - f
 * fr  - 42 - f.
 * fl  - 44 - l@
 * fe  - 45 - e@
 * fk  - 46 - k@
 * fd  - 47 - y@
 * fc  - 48 - c@
 * v   - 49 - v
 * vl  - 50 - l: 
 * vc  - 51 - c:
 * vd  - 52 - y:
 * M1s - 53 - q
 * M1c - 54 - u
 * M1  - 55 - x
 * M1d - 56 - z
 * M2s - 57 - q.
 * M2c - 58 - u.
 * M2  - 59 - x.
 * M2d - 60 - z.
 * M3s - 61 - q:
 * M3  - 62 - u:
 * M3c - 63 - x:
 * M3d - 64 - z:
 * M4s - 65 - Q
 * M4  - 66 - U
 * M4c - 67 - X
 * M4d - 68 - Z
 * M5s - 69 - Q.
 * M5  - 70 - U.
 * M5c - 71 - X.
 * M5d - 72 - Z.
 * M6s - 73 - Q:
 * M6  - 74 - U:
 * M6c - 75 - X:
 * M6d - 76 - Z:
 * e1a - 77 - a
 * e1d - 78 - d
 * e1s - 79 - s
 * e1r - 80 - r
 * e1k - 81 - k
 * e2a - 82 - a.
 * e2d - 83 - d.
 * e2s - 84 - s.
 * e2r - 85 - r.
 * e2k - 86 - k.
 * e3a - 87 - a:
 * e3d - 88 - d:
 * e3s - 89 - s:
 * e3r - 90 - r:
 * e3k - 91 - k:
 * l1w - 92 - W
 * l1r - 93 - R
 * l1d - 94 - D
 * l1c - 95 - N
 * l2w - 96 - W.
 * l2r - 97 - R.
 * l2d - 98 - D.
 * l2c - 99 - N.
 * l3w - 100 - W:
 * l3r - 101 - R:
 * l3d - 102 - D:
 * l3c - 103 - N:
 * c   - 104 - o
 * p   - 105 - p
 * s   - 106 - S@
 * V1  - 107 - i
 * V2  - 108 - i.
 * a   - 109 - A
 * A   - 110 - A.
 * w   - 111 - b.
 * wt  - 112 - b:
 * S   - 113 - S
 * t   - 114 - T
 * ad  - 116 - T.
 * sd  - 117 - T:
 * wr  - 118 - b
 * sc  - 119 - S.
 * st  - 120 - S:
 * F   - 121 - A:
 */
