#include <diagnostic.h>
#include <matrix.h>
#include <print.h>

int main() {
  CHECK_MEMORY

  Matrix *a = Matrix_Fill(3, 2, (double[3][2]){{ 1, 2 }, { 4, 5 }, { 7, 8 }});
  Matrix *b = Matrix_Fill(2, 3, (double[2][3]){{ 1, 2, 3 }, { 4, 5, 6 }});

  print("%O\n", a);
  print("%O\n", b);

  Matrix *matrix = Matrix_Cross(b, a);

  print("%g\n", Matrix_Det(matrix));

  print("%Of\n", matrix);

  STOP_WATCHING

  return 0;
}