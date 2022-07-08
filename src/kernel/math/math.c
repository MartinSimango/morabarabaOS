#include "math.h"

float64 fabs(float64 x) { return x < 0.0 ? -x : x; }

float64 fmod(float64 x, float64 m) {
  float64 result;
  asm("1: fprem\n\t"
      "fnstsw %%ax\n\t"
      "sahf\n\t"
      "jp 1b"
      : "=t"(result)
      : "0"(x), "u"(m)
      : "ax", "cc");
  return result;
}

float64 sin(float64 x) {
  float64 result;
  asm("fsin" : "=t"(result) : "0"(x));
  return result;
}

float64 exp(float64 x) { return pow(E, x); }
float64 cos(float64 x) { return sin(x + PI / 2.0); }

// black magic
float64 pow(float64 x, float64 y) {
  float64 out;
  asm("fyl2x;"
      "fld %%st;"
      "frndint;"
      "fsub %%st,%%st(1);"
      "fxch;"
      "fchs;"
      "f2xm1;"
      "fld1;"
      "faddp;"
      "fxch;"
      "fld1;"
      "fscale;"
      "fstp %%st(1);"
      "fmulp;"
      : "=t"(out)
      : "0"(x), "u"(y)
      : "st(1)");
  return out;
}

uint64 max(uint64 a, uint64 b) { return a > b ? a : b; }
uint64 min(uint64 a, uint64 b) { return a < b ? a : b; }