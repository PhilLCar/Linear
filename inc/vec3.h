#ifndef VEC3_H
#define VEC3_H

// CUT
#include <diagnostic.h>
#include <vec.h>

#define TYPENAME Vec3

OBJECT(double x, double y, double z) INHERIT (Vec)
END_OBJECT(0, 0, 0);

double *_(X)();
double *_(Y)();
double *_(Z)();

Vec3 *STATIC (Vec)(Vec *other);
Vec3 *STATIC (Normal)(Vec3 *p1, Vec3 *p2, Vec3 *p3);

Vec3 *_(Cross)(Vec3 *other);


#undef TYPENAME

#endif