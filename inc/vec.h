#ifndef VEC_H
#define VEC_H

// lmath
#include <math.h>

// CUT
#include <diagnostic.h>
#include <oop.h>
#include <exception.h>
#include <str.h>

#define TYPENAME Vec

OBJECT(int dimension) INHERIT (double*)
  int     dimension;
END_OBJECT(3);

Vec *STATIC (From)(int dimension, double values[dimension]);

Vec   *_(Copy)();
double _(Size)();
double _(Dot)(Vec *other);
Vec   *_(Add)(Vec *other);
Vec   *_(Sub)(Vec *other);
Vec   *_(Mul)(double k);
Vec   *_(Div)(double k);
Vec   *_(Unit)();

String *CONST (ToString)() VIRTUAL(ToString);


#undef TYPENAME

#endif