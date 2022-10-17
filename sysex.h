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

#define UNKNOWN_FUNC 128

/* Alphabets */
#define ALPHABET_SIZE 59

static const Cmd CMDS_PURE[ALPHABET_SIZE] = {
  { 109, readInt}, /* A */
  { UNKNOWN_FUNC, readInt}, /* B */
  { 38, readInt}, /* C */
  { 94, readInt}, /* D */
  { 37, readInt}, /* E */
  { UNKNOWN_FUNC, readInt}, /* F */
  { UNKNOWN_FUNC, readInt}, /* G */
  { UNKNOWN_FUNC, readInt}, /* H */
  { UNKNOWN_FUNC, readInt}, /* I */
  { UNKNOWN_FUNC, readInt}, /* J */
  { UNKNOWN_FUNC, readInt}, /* K */
  { UNKNOWN_FUNC, readInt}, /* L */
  { UNKNOWN_FUNC, readInt}, /* M */
  { 95, readInt}, /* N */
  { UNKNOWN_FUNC, readInt}, /* O */
  { UNKNOWN_FUNC, readInt}, /* P */
  { 65, readInt}, /* Q */
  { 93, readInt}, /* R */
  { 113, readInt}, /* S */
  { 114, readInt}, /* T */
  { 66, readInt}, /* U */
  { 34, readInt}, /* V */
  { 92, readInt}, /* W */
  { 67, readInt}, /* X */
  { 36, readInt}, /* Y */
  { 68, readInt}, /* Z */
  { UNKNOWN_FUNC, readInt}, /* ignored */
  { UNKNOWN_FUNC, readInt}, /* ignored */
  { UNKNOWN_FUNC, readInt}, /* ignored */
  { UNKNOWN_FUNC, readInt}, /* ignored */
  { UNKNOWN_FUNC, readInt}, /* ignored */
  { UNKNOWN_FUNC, readInt}, /* ignored */
  { 77, readInt}, /* a */
  { 118, readInt}, /* b */
  { 25, readInt}, /* c */
  { 78, readInt}, /* d */
  { 23, readInt}, /* e */
  { 40, readInt}, /* f */
  { UNKNOWN_FUNC, readInt}, /* g */
  { UNKNOWN_FUNC, readInt}, /* h */
  { 107, readInt}, /* i */
  { UNKNOWN_FUNC, readInt}, /* j */
  { 81, readInt}, /* k */
  { 22, readInt}, /* l */
  { UNKNOWN_FUNC, readInt}, /* m */
  { UNKNOWN_FUNC, readInt}, /* n */
  { 104, readInt}, /* o */
  { 105, readInt}, /* p */
  { 53, readInt}, /* q */
  { 80, readInt}, /* r */
  { 79, readInt}, /* s */
  { 21, readInt}, /* t */
  { 54, readInt}, /* u */
  { 49, readInt}, /* v */
  { 20, readInt}, /* w */
  { 55, readInt}, /* x */
  { 24, readInt}, /* y */
  { 56, readInt}, /* z */
  { UNKNOWN_FUNC, readInt}, /* ignored */
};

static const Cmd CMDS_DOT[ALPHABET_SIZE] = {
  { 110, readInt}, /* A. */
  { UNKNOWN_FUNC, readInt}, /* B. */
  { UNKNOWN_FUNC, readInt}, /* C. */
  { 98, readInt}, /* D. */
  { UNKNOWN_FUNC, readInt}, /* E. */
  { UNKNOWN_FUNC, readInt}, /* F. */
  { UNKNOWN_FUNC, readInt}, /* G. */
  { UNKNOWN_FUNC, readInt}, /* H. */
  { UNKNOWN_FUNC, readInt}, /* I. */
  { UNKNOWN_FUNC, readInt}, /* J. */
  { UNKNOWN_FUNC, readInt}, /* K. */
  { UNKNOWN_FUNC, readInt}, /* L. */
  { UNKNOWN_FUNC, readInt}, /* M. */
  { 99, readInt}, /* N. */
  { UNKNOWN_FUNC, readInt}, /* O. */
  { UNKNOWN_FUNC, readInt}, /* P. */
  { 69, readInt}, /* Q. */
  { 97, readInt}, /* R. */
  { 119, readInt}, /* S. */
  { 116, readInt}, /* T. */
  { 70, readInt}, /* U. */
  { 35, readInt}, /* V. */
  { 96, readInt}, /* W. */
  { 71, readInt}, /* X. */
  { UNKNOWN_FUNC, readInt}, /* Y. */
  { 72, readInt}, /* Z. */
  { UNKNOWN_FUNC, readInt}, /* ignored */
  { UNKNOWN_FUNC, readInt}, /* ignored */
  { UNKNOWN_FUNC, readInt}, /* ignored */
  { UNKNOWN_FUNC, readInt}, /* ignored */
  { UNKNOWN_FUNC, readInt}, /* ignored */
  { UNKNOWN_FUNC, readInt}, /* ignored */
  { 82, readInt}, /* a. */
  { 111, readInt}, /* b. */
  { 32, readInt}, /* c. */
  { 83, readInt}, /* d. */
  { 30, readInt}, /* e. */
  { 42, readInt}, /* f. */
  { UNKNOWN_FUNC, readInt}, /* g. */
  { UNKNOWN_FUNC, readInt}, /* h. */
  { 108, readInt}, /* i. */
  { UNKNOWN_FUNC, readInt}, /* j. */
  { 86, readInt}, /* k. */
  { 29, readInt}, /* l. */
  { UNKNOWN_FUNC, readInt}, /* m. */
  { UNKNOWN_FUNC, readInt}, /* n. */
  { UNKNOWN_FUNC, readInt}, /* o. */
  { UNKNOWN_FUNC, readInt}, /* p. */
  { 57, readInt}, /* q. */
  { 85, readInt}, /* r. */
  { 84, readInt}, /* s. */
  { 27, readInt}, /* t. */
  { 58, readInt}, /* u. */
  { UNKNOWN_FUNC, readInt}, /* v. */
  { 26, readInt}, /* w. */
  { 59, readInt}, /* x. */
  { 31, readInt}, /* y. */
  { 60, readInt}, /* z. */
  { UNKNOWN_FUNC, readInt}, /* ignored */
};

static const Cmd CMDS_COLON[ALPHABET_SIZE] = {
  { 121, readInt}, /* A: */
  { UNKNOWN_FUNC, readInt}, /* B: */
  { UNKNOWN_FUNC, readInt}, /* C: */
  { 102, readInt}, /* D: */
  { UNKNOWN_FUNC, readInt}, /* E: */
  { UNKNOWN_FUNC, readInt}, /* F: */
  { UNKNOWN_FUNC, readInt}, /* G: */
  { UNKNOWN_FUNC, readInt}, /* H: */
  { UNKNOWN_FUNC, readInt}, /* I: */
  { UNKNOWN_FUNC, readInt}, /* J: */
  { UNKNOWN_FUNC, readInt}, /* K: */
  { UNKNOWN_FUNC, readInt}, /* L: */
  { UNKNOWN_FUNC, readInt}, /* M: */
  { 103, readInt}, /* N: */
  { UNKNOWN_FUNC, readInt}, /* O: */
  { UNKNOWN_FUNC, readInt}, /* P: */
  { 73, readInt}, /* Q: */
  { 101, readInt}, /* R: */
  { 120, readInt}, /* S: */
  { 117, readInt}, /* T: */
  { 74, readInt}, /* U: */
  { UNKNOWN_FUNC, readInt}, /* V: */
  { 100, readInt}, /* W: */
  { 75, readInt}, /* X: */
  { UNKNOWN_FUNC, readInt}, /* Y: */
  { 76, readInt}, /* Z: */
  { UNKNOWN_FUNC, readInt}, /* ignored */
  { UNKNOWN_FUNC, readInt}, /* ignored */
  { UNKNOWN_FUNC, readInt}, /* ignored */
  { UNKNOWN_FUNC, readInt}, /* ignored */
  { UNKNOWN_FUNC, readInt}, /* ignored */
  { UNKNOWN_FUNC, readInt}, /* ignored */
  { 87, readInt}, /* a: */
  { 112, readInt}, /* b: */
  { 51, readInt}, /* c: */
  { 88, readInt}, /* d: */
  { UNKNOWN_FUNC, readInt}, /* e: */
  { 39, readInt}, /* f: */
  { UNKNOWN_FUNC, readInt}, /* g: */
  { UNKNOWN_FUNC, readInt}, /* h: */
  { UNKNOWN_FUNC, readInt}, /* i: */
  { UNKNOWN_FUNC, readInt}, /* j: */
  { 91, readInt}, /* k: */
  { 50, readInt}, /* l: */
  { UNKNOWN_FUNC, readInt}, /* m: */
  { UNKNOWN_FUNC, readInt}, /* n: */
  { UNKNOWN_FUNC, readInt}, /* o: */
  { UNKNOWN_FUNC, readInt}, /* p: */
  { 61, readInt}, /* q: */
  { 90, readInt}, /* r: */
  { 89, readInt}, /* s: */
  { 28, readInt}, /* t: */
  { 62, readInt}, /* u: */
  { UNKNOWN_FUNC, readInt}, /* v: */
  { UNKNOWN_FUNC, readInt}, /* w: */
  { 63, readInt}, /* x: */
  { 52, readInt}, /* y: */
  { 64, readInt}, /* z: */
  { UNKNOWN_FUNC, readInt}, /* ignored */
};

static const Cmd CMDS_AT[ALPHABET_SIZE] = {
  { UNKNOWN_FUNC, readInt}, /* A@ */
  { UNKNOWN_FUNC, readInt}, /* B@ */
  { UNKNOWN_FUNC, readInt}, /* C@ */
  { UNKNOWN_FUNC, readInt}, /* D@ */
  { UNKNOWN_FUNC, readInt}, /* E@ */
  { UNKNOWN_FUNC, readInt}, /* F@ */
  { UNKNOWN_FUNC, readInt}, /* G@ */
  { UNKNOWN_FUNC, readInt}, /* H@ */
  { UNKNOWN_FUNC, readInt}, /* I@ */
  { UNKNOWN_FUNC, readInt}, /* J@ */
  { UNKNOWN_FUNC, readInt}, /* K@ */
  { UNKNOWN_FUNC, readInt}, /* L@ */
  { UNKNOWN_FUNC, readInt}, /* M@ */
  { UNKNOWN_FUNC, readInt}, /* N@ */
  { UNKNOWN_FUNC, readInt}, /* O@ */
  { UNKNOWN_FUNC, readInt}, /* P@ */
  { UNKNOWN_FUNC, readInt}, /* Q@ */
  { UNKNOWN_FUNC, readInt}, /* R@ */
  { 106, readInt}, /* S@ */
  { UNKNOWN_FUNC, readInt}, /* T@ */
  { UNKNOWN_FUNC, readInt}, /* U@ */
  { UNKNOWN_FUNC, readInt}, /* V@ */
  { UNKNOWN_FUNC, readInt}, /* W@ */
  { UNKNOWN_FUNC, readInt}, /* X@ */
  { UNKNOWN_FUNC, readInt}, /* Y@ */
  { UNKNOWN_FUNC, readInt}, /* Z@ */
  { UNKNOWN_FUNC, readInt}, /* ignored */
  { UNKNOWN_FUNC, readInt}, /* ignored */
  { UNKNOWN_FUNC, readInt}, /* ignored */
  { UNKNOWN_FUNC, readInt}, /* ignored */
  { UNKNOWN_FUNC, readInt}, /* ignored */
  { UNKNOWN_FUNC, readInt}, /* ignored */
  { UNKNOWN_FUNC, readInt}, /* a@ */
  { UNKNOWN_FUNC, readInt}, /* b@ */
  { 48, readInt}, /* c@ */
  { UNKNOWN_FUNC, readInt}, /* d@ */
  { 45, readInt}, /* e@ */
  { UNKNOWN_FUNC, readInt}, /* f@ */
  { UNKNOWN_FUNC, readInt}, /* g@ */
  { UNKNOWN_FUNC, readInt}, /* h@ */
  { UNKNOWN_FUNC, readInt}, /* i@ */
  { UNKNOWN_FUNC, readInt}, /* j@ */
  { 46, readInt}, /* k@ */
  { 44, readInt}, /* l@ */
  { UNKNOWN_FUNC, readInt}, /* m@ */
  { UNKNOWN_FUNC, readInt}, /* n@ */
  { UNKNOWN_FUNC, readInt}, /* o@ */
  { UNKNOWN_FUNC, readInt}, /* p@ */
  { UNKNOWN_FUNC, readInt}, /* q@ */
  { UNKNOWN_FUNC, readInt}, /* r@ */
  { UNKNOWN_FUNC, readInt}, /* s@ */
  { 33, readInt}, /* t@ */
  { UNKNOWN_FUNC, readInt}, /* u@ */
  { UNKNOWN_FUNC, readInt}, /* v@ */
  { UNKNOWN_FUNC, readInt}, /* w@ */
  { UNKNOWN_FUNC, readInt}, /* x@ */
  { 47, readInt}, /* y@ */
  { UNKNOWN_FUNC, readInt}, /* z@ */
  { UNKNOWN_FUNC, readInt}, /* ignored */
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
