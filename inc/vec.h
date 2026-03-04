#ifndef VEC_H
#define VEC_H

// lmath
#include <math.h>

// CUT
#include <diagnostic.h>
#include <oop.h>
#include <exception.h>
#include <str.h>

#include "linear.export.h"

#define PUBLIC LINEAR_EXPORT
#define TYPENAME Vec

OBJECT(int dimension) INHERIT (double*)
  int     dimension;
END_OBJECT(3);

PUBLIC Vec *STATIC (From)(int dimension, double values[dimension]);

PUBLIC Vec   *_(Copy)();
PUBLIC double _(Size)();
PUBLIC double _(Dot)(Vec *other);
PUBLIC Vec   *_(Add)(Vec *other);
PUBLIC Vec   *_(Sub)(Vec *other);
PUBLIC Vec   *_(Mul)(double k);
PUBLIC Vec   *_(Div)(double k);
PUBLIC Vec   *_(Unit)();

PUBLIC String *CONST (ToString)() VIRTUAL(ToString);

#undef TYPENAME
#undef PUBLIC

#endif