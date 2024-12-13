#include <diagnostic.h>
#include <matrix.h>
#include <print.h>

int main() {
  CHECK_MEMORY

  Matrix *matrix = Matrix_Fill(3, 3, 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0);

  print("%Of", matrix);

  STOP_WATCHING

  return 0;
}