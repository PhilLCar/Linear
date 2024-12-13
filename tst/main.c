#include <diagnostic.h>
#include <matrix.h>
#include <print.h>

int main() {
  CHECK_MEMORY

  Matrix *matrix = Matrix_Fill(3, 3, (double[3][3]){{ 1, 2, 3 }, { 3, 4, 5 }, { 6, 7, 8 }});

  print("%Of\n", matrix);

  STOP_WATCHING

  return 0;
}