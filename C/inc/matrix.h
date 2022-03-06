#ifndef MATRIX_H
#define MATRIX_H

#include <vec3D.h>

typedef struct matrix {
  double **M;
  int      rows;
  int      cols;
} Matrix;

Matrix   MX(int rows, int cols);
Matrix   MXD(Matrix m);
Matrix   MXV3D(Vec3D v);
Matrix   MXV3DT(Vec3D v);
double **MXrow(Matrix m, int i);
double **MXcol(Matrix m, int j);
Matrix   MXcrs(Matrix m1, Matrix m2);
Matrix   MXadd(Matrix m1, Matrix m2);
Matrix   MXsub(Matrix m1, Matrix m2);
Matrix   MXmul(Matrix m, double k);
Matrix   MXdiv(Matrix m, double k);
double   MXdet(Matrix m);
Matrix   MXmin(Matrix m, int i, int j);
Matrix   MXadj(Matrix m);
Matrix   MXI(Matrix m);
Matrix   MXT(Matrix m);
void     MXfree(Matrix m);
Matrix  *MXnew(int rows, int cols);
void     MXdel(Matrix **m);
void     MXprint(Matrix m);

#endif