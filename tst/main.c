#include <diagnostic.h>
#include <matrix.h>
#include <print.h>
#include <vec3.h>

int main() {
  CHECK_MEMORY

  double test[5][5] = {
    { 0, 1, 0, 0, 1 },
    { 0, 0, 0, 0, 1 },
    { 0, 1, 0, 0, 0 },
    { 1, 0, 0, 0, 0 },
    { 1, 0, 0, 0, 0 }
  };

  int startn = 0;
  int endn   = 2;

  Matrix *ajd = Matrix_Fill(5, 5, test);
  Matrix *pow = Matrix_Copy(ajd);

  for (int i = 0; i < 5; i++) {
    print("%O\n", pow);
    print("%s\n", "==========");

    pow = Matrix_Cross(Matrix_Copy(ajd), pow);
  }

  print("%Of\n", pow);
    print("%s\n", "==========");

  print("%Of\n", Matrix_Pow(ajd, 6));


  Vec3 *t = NEW (Vec3) (1, 2, 3);

  print("%Of\n", t);

  STOP_WATCHING

  return 0;
}