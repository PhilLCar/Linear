#ifndef VEC3_H
#define VEC3_H

// CUT
#include <diagnostic.h>
#include <vec.h>

#include "linear.export.h"

#define PUBLIC LINEAR_EXPORT
#define TYPENAME Vec3

OBJECT(double x, double y, double z) INHERIT (Vec)
END_OBJECT(0, 0, 0);

PUBLIC double *_(X)();
PUBLIC double *_(Y)();
PUBLIC double *_(Z)();

PUBLIC Vec3 *STATIC (Vec)(Vec *other);
PUBLIC Vec3 *STATIC (Normal)(Vec3 *p1, Vec3 *p2, Vec3 *p3);

PUBLIC Vec3 *_(Cross)(Vec3 *other);

#undef TYPENAME
#undef PUBLIC

#endif