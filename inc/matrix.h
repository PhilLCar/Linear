#ifndef MATRIX_H
#define MATRIX_H

// C
#include <stdarg.h>

// CUT
#include <diagnostic.h>
#include <vec.h>
#include <str.h>
#include <array.h>

#define TYPENAME Matrix

OBJECT (int rows, int cols) INHERIT (double**)
  int      rows;
  int      cols;
END_OBJECT(2, 2);

Matrix *STATIC (From)(int rows, int cols, double values[rows][cols]);
Matrix *STATIC (I)(int size);
Matrix *STATIC (Vec)(Vec *other);
Matrix *STATIC (VecT)(Vec *other);

Vec    *CONST (Row)(int i);
Vec    *CONST (Col)(int j);
double  CONST (Det)();
String *CONST (ToString)()                         VIRTUAL (ToString);
String *CONST (ToStringFormat)(const char *format) VIRTUAL (ToStringFormat);

Matrix *_(Copy)();
Matrix *_(Cross)(Matrix *other);
Matrix *_(Mask)(Matrix *other);
Matrix *_(Add)(Matrix *other);
Matrix *_(Sub)(Matrix *other);
Matrix *_(Mul)(double k);
Matrix *_(Div)(double k);
Matrix *_(Pow)(int k);
Matrix *_(RemRow)(int j);
Matrix *_(RemCol)(int i);
Matrix *_(Rem)(int i, int j);
Matrix *_(Adj)();
Matrix *_(Inv)();
Matrix *_(T)();

#undef TYPENAME

#endif