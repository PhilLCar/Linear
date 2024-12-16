#include <matrix.h>

#define TYPENAME Matrix

Matrix *_(Construct)(int rows, int cols)
{
  if (this) {
    this->rows   = rows;
    this->cols   = cols;
    this->base = malloc(rows * sizeof(double*));

    for (int i = 0; i < rows; i++) {
      this->base[i] = malloc(cols * sizeof(double));
    }
  }

  return this;
}

void _(Destruct)()
{
  if (this->base) {
    for (int i = 0; i < this->rows; i++) free(this->base[i]);
    free(this->base);
    this->base = NULL;
  }
}

Matrix *STATIC (Fill)(int rows, int cols, double base[rows][cols])
{
  Matrix *out = NEW (Matrix)(rows, cols);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      out->base[i][j] = base[i][j];
    }
  }

  return out;
}

Matrix *STATIC (I)(int size)
{
  Matrix *out = NEW (Matrix)(size, size);

  for (int i = 0; i < out->rows; i++) {
    for (int j = 0; j < out->cols; j++) {
      out->base[i][j] = i == j;
    }
  }

  return out;
}

Matrix *STATIC (Vec)(Vec *other)
{
  Matrix *out = NEW (Matrix) (other->dimension, 1);

  if (out) {
    for (int i = 0; i < out->rows; i++) {
      out->base[i][0] = other->base[i];
    }
  }

  DELETE (other);

  return out;
}

Matrix *STATIC (VecT)(Vec *other)
{
  Matrix *out = NEW (Matrix) (1, other->dimension);

  if (out) {
    for (int j = 0; j < out->cols; j++) {
      out->base[0][j] = other->base[j];
    }
  }

  DELETE (other);

  return out;
}

Vec *CONST (Row)(int i) {
  Vec *out = NEW (Vec)(this->cols);

  for (int j = 0; j < this->cols; j++) {
    out->base[j] = this->base[i][j];
  }

  return out;
}

Vec *CONST (Col)(int j) {
  Vec *out = NEW (Vec)(this->rows);

  for (int i = 0; i < this->rows; i++) {
    out->base[i] = this->base[i][j];
  }

  return out;
}

double CONST (sn)(int sigma[], int depth, int *parity) {
  double det;

  if (depth > 1) {
    det = 0;

    for (int i = 0; ; i++) {
      int swap;
      int with = depth % 2 ? 0 : i;

      det += Matrix_sn(this, sigma, depth - 1, parity);

      if (i == depth - 1) break;

      *parity          = -*parity;
      swap             = sigma[depth - 1];
      sigma[depth - 1] = sigma[with];
      sigma[with]      = swap;
    }
  } else {
    det = *parity;

    for (int i = 0; i < this->rows; i++) {
      det *= this->base[i][sigma[i]];
    }
  }

  return det;
}

double CONST (Det)() {
  int sigma[this->rows];
  int parity = 1;

  for (int i = 0; i < this->rows; i++) {
    sigma[i] = i;
  }

  return Matrix_sn(this, sigma, this->rows, &parity);
}

String *CONST (ToString)() {
  String *mx = NEW (String) ("");

  String_Cat(mx, "[");

  for (int i = 0; i < this->rows; i++) {
    String_Cat(mx, "[ ");

    for (int j = 0; j < this->cols; j++) {
      String_Concat(mx, String_Format(j == this->cols - 1 ? "%g " : "%g, ", this->base[i][j]));
    }

    String_Cat(mx, i == this->rows - 1 ? "]" : "], ");
  }

  String_Cat(mx, "]");
  
  return mx;
}

String *CONST (ToStringFormat)(const char *format) {
  String *mx = NEW (String) ("");

  String *fmt1 = String_Format("%s ",  format);
  String *fmt2 = String_Format("%s, ", format);

  for (int i = 0; i < this->rows; i++) {
    String_Cat(mx, "[ ");

    for (int j = 0; j < this->cols; j++) {
      String_Concat(mx, String_Format(j == this->cols - 1 ? fmt1->base : fmt2->base, this->base[i][j]));
    }

    String_Cat(mx, i == this->rows - 1 ? "]" : "]\n");
  }

  DELETE (fmt1);
  DELETE (fmt2);
  
  return mx;
}

Matrix *_(Copy)() {
  Matrix *out = NEW (Matrix) (this->rows, this->cols);

  if (out) {
    for (int i = 0; i < this->rows; i++) {
      for (int j = 0; j < this->cols; j++) {
        out->base[i][j] = this->base[i][j];
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
        out->base[i][j] = 0;

        for (int k = 0; k < this->cols; k++) {
          out->base[i][j] += this->base[i][k] * other->base[k][j];
        }
      }
    }
  }
  
  DELETE (this);
  DELETE (other);

  return out;
}

Matrix *_(Mask)(Matrix *other) {
  if (this->rows != other->rows || this->cols != other->cols) {
    THROW (NEW (Exception)("Cannot mask a (%dx%d) matrix with a (%dx%d)", this->rows, this->cols, other->rows, other->cols));
  }

  for (int i = 0; i < this->rows; i++) {
    for (int j = 0; j < this->cols; j++) {
      this->base[i][j] *= other->base[i][j];
    }
  }
  
  DELETE (other);
  
  return this;
}

Matrix *_(Add)(Matrix *other) {
  if (this->rows != other->rows || this->cols != other->cols) {
    THROW (NEW (Exception)("Cannot add a (%dx%d) matrix with a (%dx%d)", this->rows, this->cols, other->rows, other->cols));
  }

  for (int i = 0; i < this->rows; i++) {
    for (int j = 0; j < this->cols; j++) {
      this->base[i][j] += other->base[i][j];
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
      this->base[i][j] -= other->base[i][j];
    }
  }
  
  DELETE (other);
  
  return this;
}

Matrix *_(Mul)(double k) {
  for (int i = 0; i < this->rows; i++) {
    for (int j = 0; j < this->cols; j++) {
      this->base[i][j] *= k;
    }
  }
  
  return this;
}

Matrix *_(Div)(double k) {
  for (int i = 0; i < this->rows; i++) {
    for (int j = 0; j < this->cols; j++) {
      this->base[i][j] /= k;
    }
  }
  
  return this;
}

Matrix *_(Pow)(int k) {
  if (this->cols != this->rows) {
    THROW (NEW (Exception)("Raising a matrix to any power requires it to be square!"));
  }

  Matrix *out = Matrix_I(this->rows);

  if (k) {
    if (k < 0) {
      this = Matrix_Inv(this);
      k    = -k;
    }

    for (int i = 0; i < k; i++) {
      out = Matrix_Cross(Matrix_Copy(this), out);
    }
  }

  DELETE (this);
  
  return out;
}

Matrix *_(RemRow)(int i) {
  Matrix *out = NEW (Matrix)(this->rows - 1, this->cols);

  for (int ii = 0, mi = 0; ii < out->rows; ii++) {
    if (ii == i) ++mi;

    for (int j = 0; j < out->cols; j++) {
      out->base[ii][j] = this->base[ii + mi][j];
    }
  }
  
  DELETE (this);

  return out;
}

Matrix *_(RemCol)(int j) {
  Matrix *out = NEW (Matrix)(this->rows, this->cols - 1);

  for (int i = 0; i < out->rows; i++) {
    for (int jj = 0, mj = 0; jj < out->cols; jj++) {
      if (jj == j) ++mj;

      out->base[i][jj] = this->base[i][jj + mj];
    }
  }
  
  DELETE (this);

  return out;
}

Matrix *_(Rem)(int i, int j) {
  Matrix *out = NEW (Matrix)(this->rows - 1, this->cols - 1);

  for (int ii = 0, mi = 0; ii < out->rows; ii++) {
    if (ii == i) ++mi;

    for (int jj = 0, mj = 0; jj < out->cols; jj++) {
      if (jj == j) ++mj;

      out->base[ii][jj] = this->base[ii + mi][jj + mj];
    }
  }
  
  DELETE (this);

  return out;
}

Matrix *_(Adj)() {
  Matrix *out = NEW (Matrix) (this->rows, this->cols);

  for (int i = 0; i < out->rows; i++) {
    for (int j = 0; j < out->cols; j++) {
      Matrix *rem  = Matrix_Rem(Matrix_Copy(this), i, j);
      int     sign = (i + j) % 2 ? -1 : 1;

      out->base[i][j] = sign * Matrix_Det(rem);

      DELETE(rem);
    }
  }

  DELETE (this);

  return Matrix_T(out);
}

Matrix *_(Inv)() {
  // For cross platform
  Matrix *out = Matrix_Div(Matrix_Adj(Matrix_Copy(this)), Matrix_Det(this));
  
  DELETE (this);

  return out;
}

Matrix *_(T)() {
  Matrix *out = NEW (Matrix) (this->cols, this->rows);

  for (int i = 0; i < out->rows; i++) {
    for (int j = 0; j < out->cols; j++) {
      out->base[i][j] = this->base[j][i];
    }
  }
  
  DELETE (this);

  return out;
}

#undef TYPEANME