#include <vec3D.h>
#include <math.h>

Vec3D V3D(double X, double Y, double Z) {
  Vec3D vector;
  vector.X = X;
  vector.Y = Y;
  vector.Z = Z;
  return vector;
}

double V3DR(Vec3D v) {
  return sqrt(v.X*v.X + v.Y*v.Y + v.Z*v.Z);
}

double V3Ddot(Vec3D v1, Vec3D v2) {
  return v1.X*v2.X + v1.Y*v2.Y + v1.Z*v2.Z;
}

Vec3D V3Dcrs(Vec3D v1, Vec3D v2) {
  Vec3D out;
  out.X = v1.Y*v2.Z - v1.Z*v2.Y;
  out.Y = v1.Z*v2.X - v1.X*v2.Z;
  out.Z = v1.X*v2.Y - v1.Y*v2.X;
  return out;
}

Vec3D V3Dadd(Vec3D v1, Vec3D v2) {
  Vec3D out;
  out.X = v1.X + v2.X;
  out.Y = v1.Y + v2.Y;
  out.Z = v1.Z + v2.Z;
  return out;
}

Vec3D V3Dsub(Vec3D v1, Vec3D v2) {
  Vec3D out;
  out.X = v1.X - v2.X;
  out.Y = v1.Y - v2.Y;
  out.Z = v1.Z - v2.Z;
  return out;
}

Vec3D V3Dmul(Vec3D v, double k) {
  Vec3D out;
  out.X = v.X * k;
  out.Y = v.Y * k;
  out.Z = v.Z * k;
  return out;
}

Vec3D V3Ddiv(Vec3D v, double k) {
  Vec3D out;
  out.X = v.X / k;
  out.Y = v.Y / k;
  out.Z = v.Z / k;
  return out;
}

Vec3D V3Dunit(Vec3D v) {
  return V3Ddiv(v, V3DR(v));
}

Vec3D V3Dnorm(Vec3D v1, Vec3D v2, Vec3D v3) {
  return V3Dunit(V3Dcrs(V3Dsub(v2, v1), V3Dsub(v3, v1)));
}