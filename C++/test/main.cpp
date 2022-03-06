#include <matrix.hpp>
#include <vector.hpp>

#include <iostream>

using namespace linear;

int main() {
  Matrix m1 = {{ 1., 2. }, { 4., 5. }, { 7., 8. }};
  Matrix m2 = {{ 4., 3., 2. }, {2., 5., 3.}};
  Vector v1 = { 1., 2., 4. };
  Vector v2 = { 3., 3., 1.};

  std::cout << "Matrix tests:\n";
  std::cout << "=============\n\n";
  std::cout << "The first matrix (M1):\n";
  std::cout << (std::string)m1;
  std::cout << std::endl;

  std::cout << "The second matrix (M2):\n";
  std::cout << (std::string)m2;
  std::cout << std::endl;

  std::cout << "A 3x3 identity matrix:\n";
  std::cout << (std::string)Matrix<3, 3>::I();
  std::cout << std::endl;

  std::cout << "The first matrix transposed (M1.T):\n";
  std::cout << (std::string)m1.T();
  std::cout << std::endl;

  std::cout << "The first matrix's determinant (det M1): ";
  std::cout << m1.det() << std::endl;
  std::cout << std::endl;

  std::cout << "The first matrix inverted (M1^-1):\n";
  std::cout << (std::string)(m1.inv());
  std::cout << std::endl;

  std::cout << "M1 * M2:\n";
  std::cout << (std::string)(m1 * m2);
  std::cout << std::endl;

  std::cout << "M2 * M1:\n";
  std::cout << (std::string)(m2 * m1);
  std::cout << std::endl;


  std::cout << "Vector tests:\n";
  std::cout << "=============\n\n";
  std::cout << "The first vecctor (V1):\n";
  std::cout << (std::string)v1;
  std::cout << std::endl;

  std::cout << "The second vector (V2):\n";
  std::cout << (std::string)v2;
  std::cout << std::endl;

  std::cout << "The first vector's length: ";
  std::cout << v1.length() << std::endl;
  std::cout << std::endl;

  std::cout << "The second vector's unit:\n";
  std::cout << (std::string)v2.unit() << std::endl;
  std::cout << std::endl;


  std::cout << "The dot product (V1 * V2): ";
  std::cout << v1 * v2 << std::endl;
  std::cout << std::endl;

  std::cout << "The cross product (V1 ^ V2):\n";
  std::cout << (std::string)(v1 ^ v2);
  std::cout << std::endl;


  std::cout << "Mix tests:\n";
  std::cout << "=============\n\n";

  std::cout << "V1 * M1:\n";
  std::cout << (std::string)(v1 * m1);
  std::cout << std::endl;

  std::cout << "M2 * v1:\n";
  std::cout << (std::string)(m2 * v1);
  std::cout << std::endl;

  Vector v3 = v1 = v2;

  std::cout << (std::string)v3;
  return 0;
}