#include <vec.h>

#define TYPENAME Vec

Vec *_(Construct)(int dimension)
{
  if (this) {
    this->base    = malloc(dimension * sizeof(double));
    this->dimension = dimension;
  }

  return this;
}

void _(Destruct)()
{
  if (this->base) {
    free(this->base);
    this->base = NULL;
  }
}

Vec *STATIC (From)(int dimension, double base[dimension])
{
  Vec *vec = NEW (Vec) (dimension);

  for (int i = 0; i < vec->dimension; i++) {
    vec->base[i] = base[i];
  }

  return vec;
}

Vec *_(Copy)()
{
  Vec *vec = NEW (Vec) (this->dimension);

  for (int i = 0; i < this->dimension; i++) vec->base[i] = this->base[i];

  return vec;
}

double _(Size)() {
  double tot = 0;

  for (int i = 0; i < this->dimension; i++) {
    double v = this->base[i];

    tot += v * v;
  }

  return sqrt(tot);
}

double _(Dot)(Vec *other) {
  double  tot = 0;
  double *v1  = this->base;
  double *v2  = other->base;

  if (this->dimension != other->dimension) {
    THROW (NEW (Exception) ("Cannot multiply vectors of size %d and %d", this->dimension, other->dimension));
  }

  for (int i = 0; i < this->dimension; i++) {
    tot += v1[i] * v2[i];
  }

  DELETE (other);
  DELETE (this);

  return tot;
}

Vec *_(Add)(Vec *other) {
  double *v1  = this->base;
  double *v2  = other->base;

  if (this->dimension != other->dimension) {
    THROW (NEW (Exception) ("Cannot multiply vectors of size %d and %d", this->dimension, other->dimension));
  }

  for (int i = 0; i < this->dimension; i++) {
    v1[i] += v2[i];
  }

  DELETE (other);

  return this;
}

Vec *_(Sub)(Vec *other) {
  double *v1  = this->base;
  double *v2  = other->base;

  if (this->dimension != other->dimension) {
    THROW (NEW (Exception) ("Cannot multiply vectors of size %d and %d", this->dimension, other->dimension));
  }

  for (int i = 0; i < this->dimension; i++) {
    v1[i] -= v2[i];
  }

  DELETE (other);

  return this;
}

Vec *_(Mul)(double k) {
  double *v1  = this->base;

  for (int i = 0; i < this->dimension; i++) {
    v1[i] *= k;
  }

  return this;
}

Vec *_(Div)(double k) {
  double *v1  = this->base;

  for (int i = 0; i < this->dimension; i++) {
    v1[i] /= k;
  }

  return this;
}

Vec *_(Unit)() {
  return Vec_Div(this, Vec_Size(this));
}

String *CONST (ToString)() {
  String *result = NEW (String)("[");

  for (int i = 0; i < this->dimension; i++) {
    String_Concat(result, String_Format(i == this->dimension - 1 ? " %g " : " %g,", this->base[i]));
  }

  String_Cat(result, "]");

  return result;
}

#undef TYPENAME