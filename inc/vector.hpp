/* Author: Philippe Caron
 * Date: 04 Mar 2022
 * Description: C++17 FloatType _Vectors.
 */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <matrix.hpp>
#include <math.h>
#include <type_traits>

namespace linear {
  template <int DIM, typename FloatType>
  using Mx = Matrix<DIM, 1, FloatType>;


  template <int DIM, typename FloatType>
  class _Vector : public Mx<DIM, FloatType> {
    public:
    // Initializer constructor
    template <typename ...FloatTypes>
    inline constexpr _Vector(const FloatTypes... values) {
      int i = 0;
      ((Mx<DIM, FloatType>::data[i++] = values), ...);
    }

    // Copy constructors
    inline _Vector(Mx<DIM, FloatType>&& other) : Mx<DIM, FloatType>(other) {}
    inline _Vector(const _Vector& other) : Mx<DIM, FloatType>(other) {}
    inline _Vector(const _Vector&& other) : Mx<DIM, FloatType>(other) {}
    //inline _Vector(_Vector& other) : Mx<DIM, FloatType>(static_cast<const _Vector>(other)) {}

    inline _Vector& operator =(const _Vector& other) {
      for (int i = 0; i < DIM; i++) Mx<DIM, FloatType>::data[i] = other.data[i];
      return *this;
    }
    inline _Vector& operator =(const FloatType array[DIM]) {
      for (int i = 0; i < DIM; i++) Mx<DIM, FloatType>::data[i] = array[i];
      return *this;
    }
    // scalar product
    inline FloatType operator *(const _Vector& other) {
      FloatType s = 0;
      for (int i = 0; i < DIM; i++) s += Mx<DIM, FloatType>::data[i] * other.data[i];
      return s;
    }

    template <int N>
    inline _Vector<N, FloatType> operator *(const Matrix<DIM, N, FloatType>& matrix) {
      return _Vector<N, FloatType>((this->T() * matrix).T());
    }

    inline FloatType operator [](const int index) {
      return Mx<DIM, FloatType>::data[index];
    }

    inline FloatType length() {
      FloatType s = 0;
      for (int i = 0; i < DIM; i++) s += Mx<DIM, FloatType>::data[i] * Mx<DIM, FloatType>::data[i];
      return sqrt(s);
    }
    inline _Vector unit() {
      return _Vector(*this / length());
    }
  };

  template <int M, int N, typename FloatType>
  inline _Vector<M, FloatType> operator *(Matrix<M, N, FloatType> matrix, _Vector<N, FloatType>& vector) {
    return _Vector(matrix * (Mx<N, FloatType>)vector);
  }

  template <int DIM, typename FloatType = double>
  class Vector : public _Vector<DIM, FloatType> {
    public:
    // Constructors
    template <typename ...FloatTypes,
      std::enable_if_t<(std::is_floating_point_v<FloatTypes> && ...), int> = 0
    >
    constexpr Vector(const FloatTypes... values) : _Vector<DIM, FloatType>(values...) {}
    inline Vector(const _Vector<DIM, FloatType>& other) : _Vector<DIM, FloatType>(other) {}
  };

  //Specializations
  /////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <typename FloatType>
  class Vector<2, FloatType> : public _Vector<2, FloatType> {
    public:
    // Constructors
    template <typename ...FloatTypes>
    inline constexpr Vector(const FloatTypes... values) : _Vector<2, FloatType>(values...) {}
    inline _Vector<2, FloatType>& operator =(Vector &other) { return _Vector<2, FloatType>::operator =(other); }

    FloatType& x = Mx<2, FloatType>::data[0];
    FloatType& y = Mx<2, FloatType>::data[1];
  };
  template <typename FloatType>
  class Vector<3, FloatType> : public _Vector<3, FloatType> {
    public:
    // Constructors
    template <typename ...FloatTypes>
    inline constexpr Vector(const FloatTypes... values) : _Vector<3, FloatType>(values...) {}
    inline _Vector<3, FloatType>& operator =(Vector &other) { return _Vector<3, FloatType>::operator =(other); }

    //cross product
    inline Vector operator ^(_Vector<3, FloatType>& other) {
      Vector V;
      V.x = y * other[2] - z * other[1];
      V.y = z * other[0] - x * other[2];
      V.z = x * other[1] - y * other[0];
      return V;
    }
    inline Vector normal(const _Vector<3, FloatType>& other) {
      return (*this ^ other).unit();
    }
    
    FloatType& x = Mx<3, FloatType>::data[0];
    FloatType& y = Mx<3, FloatType>::data[1];
    FloatType& z = Mx<3, FloatType>::data[2];
  };
  template <typename FloatType>
  class Vector<4, FloatType> : public _Vector<4, FloatType> {
    public:
    // Constructors
    template <typename ...FloatTypes>
    inline constexpr Vector(const FloatTypes... values) : _Vector<4, FloatType>(values...) {}
    inline _Vector<4, FloatType>& operator =(Vector &other) { return _Vector<4, FloatType>::operator =(other); }

    FloatType& x = Mx<4, FloatType>::data[0];
    FloatType& y = Mx<4, FloatType>::data[1];
    FloatType& z = Mx<4, FloatType>::data[2];
    FloatType& t = Mx<4, FloatType>::data[3];
  };

  template <typename ...FloatTypes>
  Vector(const FloatTypes...) -> Vector<sizeof...(FloatTypes), std::common_type_t<FloatTypes...>>;
}

#endif