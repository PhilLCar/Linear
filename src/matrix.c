#include <matrix.h>

#define TYPENAME Matrix

Matrix *_(Construct)(int rows, int cols)
{
  if (this) {
    this->rows   = rows;
    this->cols   = cols;
    this->values = malloc(rows * sizeof(double*));

    for (int i = 0; i < rows; i++) {
      this->values[i] = malloc(cols * sizeof(double));
    }
  }

  return this;
}

void _(Destruct)()
{
  if (this->values) {
    for (int i = 0; i < this->rows; i++) free(this->values[i]);
    free(this->values);
    this->values = NULL;
  }
}

Matrix *STATIC (Fill)(int rows, int cols, double values[cols][rows])
{
  Matrix *out = NEW (Matrix)(rows, cols);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      // For display it's intuitive to write a matrix row by row, but once processed
      // it's nice to have m[i][j], to follow mathematical notation, hence the flip
      out->values[i][j] = values[j][i];
    }
  }

  return out;
}

Matrix *STATIC (Vec)(Vec *other)
{
  Matrix *out = NEW (Matrix) (other->dimension, 1);

  if (out) {
    for (int i = 0; i < other->dimension; i++) {
      out->values[i][0] = other->values[i];
    }
  }

  return out;
}

Matrix *STATIC (VecT)(Vec *other)
{
  Matrix *out = NEW (Matrix) (1, other->dimension);

  if (out) {
    for (int j = 0; j < other->dimension; j++) {
      out->values[0][j] = other->values[j];
    }
  }

  return out;
}

Array *_(Row)(int i) {
  Array *row = NEW (Array) (sizeof(double*));

  Array_Resize(row, this->cols);

  double **base = row->base;

  for (int j = 0; j < this->cols; j++) {
    base[j] = &this->values[i][j];
  }

  return row;
}

Array *_(Col)(int j) {
  Array *col = NEW (Array) (sizeof(double*));

  Array_Resize(col, this->rows);

  double **base = col->base;

  for (int i = 0; i < this->rows; i++) {
    base[i] = &this->values[i][j];
  }

  return col;
}

Matrix *_(Copy)() {
  Matrix *out = NEW (Matrix) (this->rows, this->cols);

  if (out) {
    for (int i = 0; i < this->rows; i++) {
      for (int j = 0; j < this->cols; j++) {
        out->values[i][j] = this->values[i][j];
      }
    }
  }

  return out;
}

Matrix *_(Cross)(Matrix *other) {
  if (this->cols != other->rows) {
    THROW (NEW (Exception)("Cannot multiply a (%dx%d) matrix with a (%dx%d)", this->rows, this->cols, other->rows, other->cols));
  }

  Matrix *out = NEW (Matrix) (this->rows, other->cols);

  if (out) {
    for (int i = 0; i < out->rows; i++) {
      for (int j = 0; j < out->cols; j++) {
        out->values[i][j] = 0;

        for (int k = 0; k < this->cols; k++) {
          out->values[i][j] += this->values[i][k] * other->values[k][j];
        }
      }
    }
  }
  
  DELETE (this);
  DELETE (other);

  return out;
}

Matrix *_(Add)(Matrix *other) {
  if (this->rows != other->rows || this->cols != other->cols) {
    THROW (NEW (Exception)("Cannot add a (%dx%d) matrix with a (%dx%d)", this->rows, this->cols, other->rows, other->cols));
  }

  for (int i = 0; i < this->rows; i++) {
    for (int j = 0; j < this->cols; j++) {
      this->values[i][j] += other->values[i][j];
    }
  }
  
  DELETE (other);
  
  return this;
}

Matrix *_(Sub)(Matrix *other) {
  if (this->rows != other->rows || this->cols != other->cols) {
    THROW (NEW (Exception)("Cannot substract a (%dx%d) matrix with a (%dx%d)", this->rows, this->cols, other->rows, other->cols));
  }

  for (int i = 0; i < this->rows; i++) {
    for (int j = 0; j < this->cols; j++) {
      this->values[i][j] -= other->values[i][j];
    }
  }
  
  DELETE (other);
  
  return this;
}

Matrix *_(Mul)(double k) {
  for (int i = 0; i < this->rows; i++) {
    for (int j = 0; j < this->cols; j++) {
      this->values[i][j] *= k;
    }
  }
  
  return this;
}

Matrix *_(Div)(double k) {
  for (int i = 0; i < this->rows; i++) {
    for (int j = 0; j < this->cols; j++) {
      this->values[i][j] /= k;
    }
  }
  
  return this;
}

double _(Sn)(int sigma[], int depth, int *parity) {
  double det;

  if (depth > 1) {
    det = 0;

    for (int i = 0; ; i++) {
      int swap;
      int with = depth % 2 ? 0 : i;

      det += Matrix_Sn(this, sigma, depth - 1, parity);

      if (i == depth - 1) break;

      *parity          = -*parity;
      swap             = sigma[depth - 1];
      sigma[depth - 1] = sigma[with];
      sigma[with]      = swap;
    }
  } else {
    det = *parity;

    for (int i = 0; i < this->rows; i++) {
      det *= this->values[i][sigma[i]];
    }
  }

  return det;
}

double _(Det)() {
  int sigma[this->rows];
  int parity = 1;

  for (int i = 0; i < this->rows; i++) {
    sigma[i] = i;
  }

  return Matrix_Sn(this, sigma, this->rows, &parity);
}

Matrix *_(Min)(int i, int j) {
  Matrix *out = NEW (Matrix)(this->rows - 1, this->cols - 1);

  for (int ii = 0, mi = 0; ii < out->rows; ii++) {
    if (ii == i) mi = 1;
    for (int jj = 0, mj = 0; jj < out->cols; jj++) {
      if (jj == j) mj = 1;
      out->values[ii][jj] = this->values[ii + mi][jj + mj];
    }
  }
  
  DELETE (this);

  return out;
}

Matrix *_(Adj)() {
  Matrix *out = NEW (Matrix) (this->rows, this->cols);

  for (int i = 0; i < out->rows; i++) {
    for (int j = 0; j < out->cols; j++) {
      Matrix *min  = Matrix_Min(Matrix_Copy(this), i, j);
      int     sign = (i + j) % 2 ? -1 : 1;

      out->values[i][j] = sign * Matrix_Det(min);

      DELETE(min);
    }
  }

  DELETE (this);

  return Matrix_T(out);
}

Matrix *_(I)() {
  // For cross platform
  Matrix *out = Matrix_Div(Matrix_Adj(Matrix_Copy(this)), Matrix_Det(this));
  
  DELETE (this);

  return out;
}

Matrix *_(T)() {
  Matrix *out = NEW (Matrix) (this->cols, this->rows);

  for (int i = 0; i < out->rows; i++) {
    for (int j = 0; j < out->cols; j++) {
      out->values[i][j] = this->values[j][i];
    }
  }
  
  DELETE (this);

  return out;
}

String *_(ToString)() {
  String *mx = NEW (String) ("");

  String_Cat(mx, "[ ");

  for (int j = 0; j < this->cols; j++) {
    String_Cat(mx, "[ ");

    for (int i = 0; i < this->rows; i++) {
      String_Concat(mx, String_Format( i == this->rows - 1 ? "%g " : "%g, ", this->values[i][j]));
    }

    String_Cat(mx, j == this->cols - 1 ? "] " : "], ");
  }

  String_Cat(mx, "]");
  
  return mx;
}

#undef TYPEANME