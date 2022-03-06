#include <matrix.h>
#include <stdlib.h>
#include <stdio.h>

Matrix MX(int rows, int cols) {
  Matrix out;
  out.rows = rows;
  out.cols = cols;
  out.M = malloc(rows * sizeof(double*));
  for (int i = 0; i < rows; i++) {
    out.M[i] = malloc(cols * sizeof(double));
  }
  return out;
}

Matrix MXD(Matrix m) {
  Matrix out;
  out.rows = m.rows;
  out.cols = m.cols;
  out.M = malloc(m.rows * sizeof(double*));
  for (int i = 0; i < m.rows; i++) {
    out.M[i] = malloc(m.cols * sizeof(double));
    for (int j = 0; j < m.cols; j++) {
      out.M[i][j] = m.M[i][j];
    }
  }
  return out;
}

Matrix MXV3D(Vec3D v) {
  Matrix out = MX(3, 1);
  out.M[0][0] = v.X;
  out.M[1][0] = v.Y;
  out.M[2][0] = v.Z;
  return out;
}

Matrix MXV3DT(Vec3D v) {
  Matrix out = MX(1, 3);
  out.M[0][0] = v.X;
  out.M[0][1] = v.Y;
  out.M[0][2] = v.Z;
  return out;
}

double **MXrow(Matrix m, int i) {
  double **row = malloc(m.cols * sizeof(double*));
  for (int j = 0; j < m.cols; j++) {
    row[j] = &m.M[i][j];
  }
  return row;
}

double **MXcol(Matrix m, int j) {
  double **col = malloc(m.rows * sizeof(double*));
  for (int i = 0; i < m.rows; i++) {
    col[i] = &m.M[i][j];
  }
  return col;
}

Matrix MXcrs(Matrix m1, Matrix m2) {
  Matrix out = MX(m1.rows, m2.cols);
  for (int i = 0; i < out.rows; i++) {
    for (int j = 0; j < out.cols; j++) {
      out.M[i][j] = 0;
      for (int k = 0; k < m1.cols; k++) {
        out.M[i][j] += m1.M[i][k] * m2.M[k][j];
      }
    }
  }
  MXfree(m1);
  MXfree(m2);
  return out;
}

Matrix MXadd(Matrix m1, Matrix m2) {
  Matrix out = MX(m1.rows, m1.cols);
  for (int i = 0; i < out.rows; i++) {
    for (int j = 0; j < out.cols; j++) {
      out.M[i][j] = m1.M[i][j] + m2.M[i][j];
    }
  }
  MXfree(m1);
  MXfree(m2);
  return out;
}

Matrix MXsub(Matrix m1, Matrix m2) {
  Matrix out = MX(m1.rows, m1.cols);
  for (int i = 0; i < out.rows; i++) {
    for (int j = 0; j < out.cols; j++) {
      out.M[i][j] = m1.M[i][j] - m2.M[i][j];
    }
  }
  MXfree(m1);
  MXfree(m2);
  return out;
}

Matrix MXmul(Matrix m, double k) {
  Matrix out = MX(m.rows, m.cols);
  for (int i = 0; i < out.rows; i++) {
    for (int j = 0; j < out.cols; j++) {
      out.M[i][j] = m.M[i][j] * k;
    }
  }
  MXfree(m);
  return out;
}

Matrix MXdiv(Matrix m, double k) {
  Matrix out = MX(m.rows, m.cols);
  for (int i = 0; i < out.rows; i++) {
    for (int j = 0; j < out.cols; j++) {
      out.M[i][j] = m.M[i][j] / k;
    }
  }
  MXfree(m);
  return out;
}

double MXSn(Matrix *m, int *sigma, int depth, int *parity) {
  double det;
  if (depth > 1) {
    det = 0;
    for (int i = 0; ; i++) {
      int swap;
      int with = depth % 2 ? 0 : i;
      det += MXSn(m, sigma, depth - 1, parity);
      if (i == depth - 1) break;
      *parity = -*parity;
      swap             = sigma[depth - 1];
      sigma[depth - 1] = sigma[with];
      sigma[with]      = swap;
    }
  } else {
    det = *parity;
    for (int i = 0; i < m->rows; i++) {
      det *= m->M[i][sigma[i]];
    }
  }
  return det;
}

double MXdet(Matrix m) {
  int    *sigma  = malloc(m.rows * sizeof(int));
  int     parity = 1;
  double  det;
  for (int i = 0; i < m.rows; i++) {
    sigma[i] = i;
  }
  det = MXSn(&m, sigma, m.rows, &parity);
  free(sigma);
  MXfree(m);
  return det;
}

Matrix MXmin(Matrix m, int i, int j) {
  Matrix out = MX(m.rows - 1, m.cols - 1);
  for (int ii = 0, mi = 0; ii < out.rows; ii++) {
    if (ii == i) mi = 1;
    for (int jj = 0, mj = 0; jj < out.cols; jj++) {
      if (jj == j) mj = 1;
      out.M[ii][jj] = m.M[ii + mi][jj + mj];
    }
  }
  MXfree(m);
  return out;
}

Matrix MXadj(Matrix m) {
  Matrix out = MX(m.rows, m.cols);
  int sign;
  for (int i = 0; i < out.rows; i++) {
    for (int j = 0; j < out.cols; j++) {
      sign = (i + j) % 2 ? -1 : 1;
      out.M[i][j] = sign * MXdet(MXmin(MXD(m), i, j));
    }
  }
  out = MXT(out);
  MXfree(m);
  return out;
}

Matrix MXI(Matrix m) {
  // For cross platform
  Matrix out = MXdiv(MXadj(MXD(m)), MXdet(MXD(m)));
  MXfree(m);
  return out;
}

Matrix MXT(Matrix m) {
  Matrix out = MX(m.cols, m.rows);
  for (int i = 0; i < out.rows; i++) {
    for (int j = 0; j < out.cols; j++) {
      out.M[i][j] = m.M[j][i];
    }
  }
  MXfree(m);
  return out;
}

void MXfree(Matrix m) {
  for (int i = 0; i < m.rows; i++) free(m.M[i]);
  free(m.M);
}

Matrix *MXnew(int rows, int cols) {
  Matrix *out = malloc(sizeof(Matrix));
  *out = MX(rows, cols);
  return out;
}

void MXdel(Matrix **m) {
  MXfree(**m);
  free(*m);
  *m = NULL;
}

void MXprint(Matrix m) {
  for (int i = 0; i < m.rows; i++) {
    printf("[ ");
    for (int j = 0; j < m.cols; j++) {
      printf("%5.2f ", m.M[i][j]);
    }
    printf("]\n");
  }
  MXfree(m);
}