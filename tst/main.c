#include <diagnostic.h>
#include <matrix.h>
#include <print.h>
#include <vec3.h>

int main() {
  CHECK_MEMORY

  double vals[5][5] = {
    { 0, 1, 0, 0, 1 },
    { 0, 0, 0, 0, 1 },
    { 0, 1, 0, 0, 0 },
    { 1, 0, 0, 0, 0 },
    { 1, 0, 0, 0, 0 }
  };

  Matrix *test = Matrix_From(5, 5, vals);
  
  print("%O\n", test);
  print("%[%.1f]Of\n", test);

  print("----------\n");

  Vec3 *t = NEW (Vec3) (1, 2, 3);

  print("%Of\n", t);

  CHECK_MEMORY

  STOP_WATCHING

  return 0;
}