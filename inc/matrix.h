#ifndef MATRIX_H
#define MATRIX_H

// C
#include <stdarg.h>

// CUT
#include <diagnostic.h>
#include <vec.h>
#include <str.h>
#include <array.h>

#include "linear.export.h"

#define PUBLIC LINEAR_EXPORT
#define TYPENAME Matrix

OBJECT (int rows, int cols) INHERIT (double**)
  int      rows;
  int      cols;
END_OBJECT(2, 2);

PUBLIC Matrix *STATIC (From)(int rows, int cols, double values[rows][cols]);
PUBLIC Matrix *STATIC (I)(int size);
PUBLIC Matrix *STATIC (Vec)(Vec *other);
PUBLIC Matrix *STATIC (VecT)(Vec *other);

PUBLIC Vec    *CONST (Row)(int i);
PUBLIC Vec    *CONST (Col)(int j);
PUBLIC double  CONST (Det)();
PUBLIC String *CONST (ToString)()                         VIRTUAL (ToString);
PUBLIC String *CONST (ToStringFormat)(const char *format) VIRTUAL (ToStringFormat);

PUBLIC Matrix *_(Copy)();
PUBLIC Matrix *_(Cross)(Matrix *other);
PUBLIC Matrix *_(Mask)(Matrix *other);
PUBLIC Matrix *_(Add)(Matrix *other);
PUBLIC Matrix *_(Sub)(Matrix *other);
PUBLIC Matrix *_(Mul)(double k);
PUBLIC Matrix *_(Div)(double k);
PUBLIC Matrix *_(Pow)(int k);
PUBLIC Matrix *_(RemRow)(int j);
PUBLIC Matrix *_(RemCol)(int i);
PUBLIC Matrix *_(Rem)(int i, int j);
PUBLIC Matrix *_(Adj)();
PUBLIC Matrix *_(Inv)();
PUBLIC Matrix *_(T)();

#undef TYPENAME
#undef PUBLIC

#endif