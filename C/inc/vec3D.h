#ifndef VEC3D_H
#define VEC3D_H

#define _X 0
#define _Y 1
#define _Z 2

typedef struct vec3D {
  union {
    double V[3];
    struct {
      double X;
      double Y;
      double Z;
    };
  };
} Vec3D;

Vec3D   V3D(double X, double Y, double Z);
double  V3DR(Vec3D v);
double  V3Ddot(Vec3D v1, Vec3D v2);
Vec3D   V3Dcrs(Vec3D v1, Vec3D v2);
Vec3D   V3Dadd(Vec3D v1, Vec3D v2);
Vec3D   V3Dsub(Vec3D v1, Vec3D v2);
Vec3D   V3Dmul(Vec3D v, double k);
Vec3D   V3Ddiv(Vec3D v, double k);
Vec3D   V3Dunit(Vec3D v);
Vec3D   V3Dnorm(Vec3D v1, Vec3D v2, Vec3D v3);

#endif