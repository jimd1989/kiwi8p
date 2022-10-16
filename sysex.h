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
typedef enum SysexParam {
  VCF_CUTOFF  = 40,
  VCF_RES     = 42,
  VCF_LFO_LVL = 44
} SysexParam;
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

/*
 * o1w - 20
 * o1t - 21
 * o1l - 22
 * o1e - 23
 * o1d - 24
 * o1c - 25
 * o2w - 26
 * o2t - 27
 * o2T - 28
 * o2l - 29
 * o2e - 30
 * o2d - 31
 * o2c - 32
 * dt  - 33
 * m1v - 34
 * m2v - 35
 * m2d - 36
 * m2e - 37
 * m2c - 38
 * fh  - 39
 * fL  - 40
 * fr  - 42
 * fl  - 44
 * fe  - 45
 * fk  - 46
 * fd  - 47
 * fc  - 48
 * v   - 49
 * vl  - 50
 * vc  - 51
 * vd  - 52
 * M1s - 53
 * M1c - 54
 * M1  - 55
 * M1d - 56
 * M2s - 57
 * M2c - 58
 * M2  - 59
 * M2d - 60
 * M3s - 61
 * M3  - 62
 * M3c - 63
 * M3d - 64
 * M4s - 65
 * M4  - 66
 * M4c - 67
 * M4d - 68
 * M5s - 69
 * M5  - 70
 * M5c - 71
 * M5d - 72
 * M6s - 73
 * M6  - 74
 * M6c - 75
 * M6d - 76
 * e1a - 77
 * e1d - 78
 * e1s - 79
 * e1r - 80
 * e1k - 81
 * e2a - 82
 * e2d - 83
 * e2s - 84
 * e2r - 85
 * e2k - 86
 * e3a - 87
 * e3d - 88
 * e3s - 89
 * e3r - 90
 * e3k - 91
 * l1w - 92
 * l1r - 93
 * l1d - 94
 * l1c - 95
 * l2w - 96
 * l2r - 97
 * l2d - 98
 * l2c - 99
 * l3w - 100
 * l3r - 101
 * l3d - 102
 * l3c - 103
 * c   - 104
 * p   - 105
 * s   - 106
 * V1  - 107
 * V2  - 108
 * a   - 109
 * A   - 110
 * w   - 111
 * wt  - 112
 * S   - 113
 * t   - 114
 * ad  - 116
 * sd  - 117
 * wr  - 118
 * sc  - 119
 * st  - 120
 * F   - 121
 */
