#ifndef VEC_H
#define VEC_H

// lmath
#include <math.h>

// CUT
#include <diagnostic.h>
#include <oop.h>
#include <exception.h>

#define TYPENAME Vec

OBJECT(int dimension) NOBASE
  double *values;
  int     dimension;
END_OBJECT(3);

Vec *STATIC (Fill)(int dimension, double values[dimension]);

Vec   *_(Copy)();
double _(Size)();
double _(Dot)(Vec *other);
Vec   *_(Add)(Vec *other);
Vec   *_(Sub)(Vec *other);
Vec   *_(Mul)(double k);
Vec   *_(Div)(double k);
Vec   *_(Unit)();


#undef TYPENAME

#endif