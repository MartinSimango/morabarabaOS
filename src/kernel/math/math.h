#ifndef MATH_H
#define MATH_H

#include "types.h"

#define E 2.71828
#define PI 3.14159265358979323846264338327950

float64 fmod(float64 x, float64 m);
float64 fabs(float64 x);
float64 sin(float64 x);
float64 cos(float64 x);
float64 pow(float64 x, float64 y);
float64 exp(float64 x);

uint64 max(uint64 a, uint64 b);
uint64 min(uint64 a, uint64 b);

#endif
