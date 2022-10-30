/* Author: Philippe Caron
 * Date: 04 Mar 2022
 * Description: C++17 FloatType Matrices.
 * Standard: https://en.wikipedia.org/wiki/Matrix_(mathematics)
 */

#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <string>

// (!) This is a C++17 implementation

// Linear Algebra
namespace linear {
  template <typename FloatType, int N>
  using Row = const FloatType (&)[N];

  template <int M, int N, typename FloatType = double>
  class Matrix {
    template <int, int, typename> friend class Matrix;
  public:
    // Initializer constructor
    // https://stackoverflow.com/questions/15810171/is-there-a-way-to-pass-nested-initializer-lists-in-c11-to-construct-a-2d-matri
    template <typename RowType, int ...n>
    inline constexpr Matrix(Row<RowType, n>... rows) {
      auto pos = &data[0];
      ((pos = std::copy(rows, rows + n, pos)), ...);
    }

    // Default constructor
    inline Matrix() {
      for (int i = 0; i < M * N; i++) data[i] = 0;
    }

    // Copy constructor
    inline Matrix(const Matrix& other) {
      for (int i = 0; i < M * N; i++) data[i] = other.data[i];
    }
    inline Matrix(const Matrix&& other) {
    for (int i = 0; i < M * N; i++) data[i] = other.data[i];
    }

  public:
    inline static Matrix I() {
      Matrix A;
      for (int i = 0; i < M * N; i+= N + 1) A.data[i] = 1;
      return A;
    }

    inline Matrix<N, M, FloatType> T() {
      Matrix<N, M, FloatType> A;
      for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
          A.data[i * M + j] = data[j * N + i];
        }
      }
      return A;
    }
    inline Matrix<N, M, FloatType> inv() {
      return adj() / det();
    }
    inline Matrix<M - 1, N - 1, FloatType> min(int i, int j) {
      Matrix<M - 1, N - 1, FloatType> A;
      for (int ii = 0, mi = 0; ii < M - 1; ii++) {
        if (ii == i) mi = 1;
        for (int jj = 0, mj = 0; jj < N - 1; jj++) {
          if (jj == j) mj = 1;
          A.data[ii * (N - 1) + jj] = data[(ii + mi) * N + jj + mj];
        }
      }
      return A;
    }
    inline Matrix<N, M, FloatType> adj() {
      Matrix A;
      int    sign;
      for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
          sign = (i + j) % 2 ? -1 : 1;
          A.data[i * N + j] = sign * min(i, j).det();
        }
      }
      return A.T();
    }
    private:
    inline double Sn(int sigma[], int depth, int& parity) {
      double det;
      if (depth > 1) {
        det = 0;
        for (int i = 0; ; i++) {
          int swap;
          int with = depth % 2 ? 0 : i;
          det += Sn(sigma, depth - 1, parity);
          if (i == depth - 1) break;
          parity = -parity;
          swap             = sigma[depth - 1];
          sigma[depth - 1] = sigma[with];
          sigma[with]      = swap;
        }
      } else {
        det = parity;
        for (int i = 0; i < M; i++) {
          det *= data[i * N + sigma[i]];
        }
      }
      return det;
    }
    public:
    inline FloatType det() {
      int     sigma[M];
      int     parity = 1;

      for (int i = 0; i < M; i++) {
        sigma[i] = i;
      }
      return Sn(sigma, M, parity);
    }
    int m() { return M; }
    int n() { return N; }

    inline Matrix& operator =(const Matrix& other) {
      for (int i = 0; i < M * N; i++) data[i] = other.data[i];
      return *this;
    }
    inline Matrix& operator =(const FloatType array[M * N]) {
      for (int i = 0; i < M * N; i++) data[i] = array[i];
      return *this;
    }
    Matrix operator +(const Matrix& other) {
      Matrix A = *this;
      for (int i = 0; i < M * N; i++) A.data[i] += other.data[i];
      return A;
    }
    inline Matrix& operator +=(const Matrix& other) {
      for (int i = 0; i < M * N; i++) data[i] += other.data[i];
      return *this;
    }
    inline Matrix operator +(const FloatType scalar) {
      Matrix A = *this;
      for (int i = 0; i < M * N; i++) A.data[i] += scalar;
      return A;
    }
    inline Matrix& operator +=(const FloatType scalar) {
      for (int i = 0; i < M * N; i++) data[i] += scalar;
      return *this;
    }
    inline Matrix operator -(const Matrix& other) {
      Matrix A = *this;
      for (int i = 0; i < M * N; i++) A.data[i] -= other.data[i];
      return A;
    }
    inline Matrix& operator -=(const Matrix& other) {
      for (int i = 0; i < M * N; i++) data[i] -= other.data[i];
      return *this;
    }
    inline Matrix operator -(const FloatType scalar) {
      Matrix A = *this;
      for (int i = 0; i < M * N; i++) A.data[i] -= scalar;
      return A;
    }
    inline Matrix& operator -=(const FloatType scalar) {
      for (int i = 0; i < M * N; i++) data[i] -= scalar;
      return *this;
    }
    template <int n>
    inline Matrix<M, n, FloatType> operator *(const Matrix<N, n, FloatType>& other) {
      Matrix<M, n, FloatType> A;
      for (int i = 0; i < M; i++) {
        for (int j = 0; j < n; j++) {
          A.data[i * n + j]= 0;
          for (int k = 0; k < N; k++) {
            A.data[i * n + j] += data[i * N + k] * other.data[k * n + j];
          }
        }
      }
      return A;
    }
    inline Matrix& operator *=(const Matrix& other) {
      return *this * this * other;
    }
    inline Matrix operator *(const FloatType scalar) {
      Matrix A = *this;
      for (int i = 0; i < M * N; i++) A.data[i] *= scalar;
      return A;
    }
    inline Matrix& operator *=(const FloatType scalar) {
      for (int i = 0; i < M * N; i++) data[i] *= scalar;
      return *this;
    }
    template <int n>
    Matrix<M, M, FloatType> operator /(const Matrix<n, M, FloatType>& other) {
      return *this * other.inv();
    }
    template <int n>
    Matrix<M, M, FloatType> operator /=(const Matrix<n, M, FloatType>& other) {
      return *this *= other.inv();
    }
    inline Matrix operator /(const FloatType scalar) {
      Matrix A = *this;
      for (int i = 0; i < M * N; i++) A.data[i] /= scalar;
      return A;
    }
    inline Matrix& operator /=(const FloatType scalar) {
      for (int i = 0; i < M * N; i++) data[i] /= scalar;
      return *this;
    }
    inline Matrix operator ^(unsigned int integer) {
      Matrix A = I();
      for (int i = 0; i < integer; i++) {
        A *= A;
      }
      return A;
    }
    inline FloatType* operator [](const int row) {
      return &data[N * row];
    }

    inline operator std::string () const {
      std::string tmp = "";

      for (int i = 0; i < M; i++) {
        tmp += "[ ";
        for (int j = 0; j < N; j++) {
          tmp += std::to_string(data[i * N + j]) + " ";
        }
        tmp += "]\n";
      }

      return tmp;
    }

  protected:
    FloatType data[M * N];
  };

  template <int M, int N, typename FloatType = double>
  inline Matrix<M, N, FloatType> operator +(const FloatType scalar, const Matrix<M, N, FloatType> &other) { return other + scalar; }
  template <int M, int N, typename FloatType = double>
  inline Matrix<M, N, FloatType> operator -(const FloatType scalar, const Matrix<M, N, FloatType> &other) { return other - scalar; }
  template <int M, int N, typename FloatType = double>
  inline Matrix<M, N, FloatType> operator *(const FloatType scalar, const Matrix<M, N, FloatType> &other) { return other * scalar; }
  template <int M, int N, typename FloatType = double>
  inline Matrix<M, N, FloatType> operator /(const FloatType scalar, const Matrix<M, N, FloatType> &other) { return other / scalar; }

  // https://stackoverflow.com/questions/63211172/automatic-size-deduction-for-two-dimensional-array
  template <typename... RowType, int N>
  Matrix(Row<RowType, N>...) -> Matrix<sizeof...(RowType), N, std::common_type_t<RowType...>>;
}

#endif