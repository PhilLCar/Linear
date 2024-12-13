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

OBJECT (int rows, int cols) NOBASE
  double **values;
  int      rows;
  int      cols;
END_OBJECT(2, 2);

Matrix *STATIC (Fill)(int rows, int cols, double values[cols][rows]);
Matrix *STATIC (Vec)(Vec *other);
Matrix *STATIC (VecT)(Vec *other);

Array *_(Row)(int i);
Array *_(Col)(int j);

Matrix *_(Copy)();
Matrix *_(Cross)(Matrix *other);
Matrix *_(Add)(Matrix *other);
Matrix *_(Sub)(Matrix *other);
Matrix *_(Mul)(double k);
Matrix *_(Div)(double k);
double  _(Det)();
Matrix *_(Min)(int i, int j);
Matrix *_(Adj)();
Matrix *_(I)();
Matrix *_(T)();
String *_(ToString)() VIRTUAL (ToString);

#undef TYPENAME

#endif