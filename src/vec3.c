#include <vec3.h>

#define TYPENAME Vec3

Vec3 *_(Construct)(double x, double y, double z)
{
  if (Vec_Construct(BASE(0), 3)) {
    BASE(0)->base[0] = x;
    BASE(0)->base[1] = y;
    BASE(0)->base[2] = z;
  }

  return this;
}

void _(Destruct)()
{
  Vec_Destruct(BASE(0));
}

double *_(X)() 
{
  return &BASE(0)->base[0];
}

double *_(Y)() 
{
  return &BASE(0)->base[1];
}

double *_(Z)() 
{
  return &BASE(0)->base[2];
}

Vec3 *STATIC (Vec)(Vec *other)
{
  if (other->dimension != 3) {
    THROW (NEW (Exception) ("Cannot convert a vector of %d dimension to a Vec3!", other->dimension));
  }

  return (Vec3*)other;
}


Vec3 *STATIC (Normal)(Vec3 *p1, Vec3 *p2, Vec3 *p3)
{
  Vec *p1c = Vec_Copy((Vec*)p1);

  return (Vec3*)Vec_Unit((Vec*)Vec3_Cross((Vec3*)Vec_Sub((Vec*)p2, (Vec*)p1), (Vec3*)Vec_Sub((Vec*)p3, p1c)));
}

Vec3 *_(Cross)(Vec3 *other) {
  double *v1 = this->base.base;
  double *v2 = other->base.base;

  Vec3 *result = NEW (Vec3)(
    v1[1] * v2[2] - v1[2] * v2[1],
    v1[2] * v2[0] - v1[0] * v2[2],
    v1[0] * v2[1] - v1[1] * v2[0]
  );

  DELETE (this);
  DELETE (other);

  return result;
}

#undef TYPENAME