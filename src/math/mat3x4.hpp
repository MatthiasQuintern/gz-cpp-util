#pragma once

#include "concepts.hpp"
#include "../container/iterator.hpp"

namespace gz {

	// Forward declarations
	template<Number T>
	class mat3x2;
	template<Number T>
	class mat3x3;
	template<Number T>
	class mat4x2;
	template<Number T>
	class mat4x3;
	template<Number T>
	class mat4x4;
	template<Number T>
	class rvec4;
	template<Number T>
	class vec3;
	template<Number T>
	class vec4;

	/**
	 * @brief Class containing 12 numbers
	 */
 	template<Number T>
	class mat3x4 {
	    public:
		// Constructors
			/// Default constructor
			constexpr mat3x4()
				 : x1_1(0), x1_2(0), x1_3(0), x1_4(0), x2_1(0), x2_2(0), x2_3(0), x2_4(0), x3_1(0), x3_2(0), x3_3(0), x3_4(0) {}
			/// Create from scalar, all components will have value n
			template<Number N>
			constexpr mat3x4(const N n)
				 : x1_1(static_cast<T>(n)), x1_2(static_cast<T>(n)), x1_3(static_cast<T>(n)), x1_4(static_cast<T>(n)), x2_1(static_cast<T>(n)), x2_2(static_cast<T>(n)), x2_3(static_cast<T>(n)), x2_4(static_cast<T>(n)), x3_1(static_cast<T>(n)), x3_2(static_cast<T>(n)), x3_3(static_cast<T>(n)), x3_4(static_cast<T>(n)) {}
			/// Create from scalars
			template<Number N0_0, Number N0_1, Number N0_2, Number N0_3, Number N1_0, Number N1_1, Number N1_2, Number N1_3, Number N2_0, Number N2_1, Number N2_2, Number N2_3>
			constexpr mat3x4(const N0_0 x1_1, const N0_1 x1_2, const N0_2 x1_3, const N0_3 x1_4, const N1_0 x2_1, const N1_1 x2_2, const N1_2 x2_3, const N1_3 x2_4, const N2_0 x3_1, const N2_1 x3_2, const N2_2 x3_3, const N2_3 x3_4)
				 : x1_1(static_cast<T>(x1_1)), x1_2(static_cast<T>(x1_2)), x1_3(static_cast<T>(x1_3)), x1_4(static_cast<T>(x1_4)), x2_1(static_cast<T>(x2_1)), x2_2(static_cast<T>(x2_2)), x2_3(static_cast<T>(x2_3)), x2_4(static_cast<T>(x2_4)), x3_1(static_cast<T>(x3_1)), x3_2(static_cast<T>(x3_2)), x3_3(static_cast<T>(x3_3)), x3_4(static_cast<T>(x3_4)) {}
			/// Create from row vectors
			template<RowVector4 V0, RowVector4 V1, RowVector4 V2>
			constexpr mat3x4(const V0& v0, const V1& v1, const V2& v2)
				 : x1_1(static_cast<T>(v0.x)), x1_2(static_cast<T>(v0.y)), x1_3(static_cast<T>(v0.z)), x1_4(static_cast<T>(v0.w)), x2_1(static_cast<T>(v1.x)), x2_2(static_cast<T>(v1.y)), x2_3(static_cast<T>(v1.z)), x2_4(static_cast<T>(v1.w)), x3_1(static_cast<T>(v2.x)), x3_2(static_cast<T>(v2.y)), x3_3(static_cast<T>(v2.z)), x3_4(static_cast<T>(v2.w)) {}
			/// Create from column vectors
			template<ColumnVector3 V0, ColumnVector3 V1, ColumnVector3 V2, ColumnVector3 V3>
			constexpr mat3x4(const V0& v0, const V1& v1, const V2& v2, const V3& v3)
				 : x1_1(static_cast<T>(v0.x)), x1_2(static_cast<T>(v1.x)), x1_3(static_cast<T>(v2.x)), x1_4(static_cast<T>(v3.x)), x2_1(static_cast<T>(v0.y)), x2_2(static_cast<T>(v1.y)), x2_3(static_cast<T>(v2.y)), x2_4(static_cast<T>(v3.y)), x3_1(static_cast<T>(v0.z)), x3_2(static_cast<T>(v1.z)), x3_3(static_cast<T>(v2.z)), x3_4(static_cast<T>(v3.z)) {}
		// Values
			T x1_1;
			T x1_2;
			T x1_3;
			T x1_4;
			T x2_1;
			T x2_2;
			T x2_3;
			T x2_4;
			T x3_1;
			T x3_2;
			T x3_3;
			T x3_4;
		// Assignment
			/// Component-wise assignment
			template<Number N>
			constexpr void operator=(const mat3x4<N>& other);
			/// Assignment from scalar
			template<Number N>
			constexpr void operator=(const N& other);
	// Arithmetic
		// Vectorial
			/// Component-wise +
			template<Mat3x4 M>
			constexpr mat3x4<T> operator+(const M& other) const;
			/// Component-wise -
			template<Mat3x4 M>
			constexpr mat3x4<T> operator-(const M& other) const;
			/// Component-wise %
			template<Mat3x4 M>
			constexpr mat3x4<T> operator%(const M& other) const;
			/// Component-wise *
			template<Mat3x4 M>
			constexpr mat3x4<T> compWiseMult(const M& other) const;
			/// Component-wise /
			template<Mat3x4 M>
			constexpr mat3x4<T> compWiseDiv(const M& other) const;
			/// Component-wise assignment +=
			template<Mat3x4 M>
			constexpr void operator+=(const M& other);
			/// Component-wise assignment -=
			template<Mat3x4 M>
			constexpr void operator-=(const M& other);
			/// Component-wise assignment %=
			template<Mat3x4 M>
			constexpr void operator%=(const M& other);
			/// Component-wise assignment *=
			template<Mat3x4 M>
			constexpr void compWiseAssMult(const M& other);
			/// Component-wise assignment /=
			template<Mat3x4 M>
			constexpr void compWiseAssDiv(const M& other);
		// Scalar
			/// Component-wise + with scalar
			template<Number N>
			constexpr mat3x4<T> operator+(const N& other) const;
			/// Component-wise - with scalar
			template<Number N>
			constexpr mat3x4<T> operator-(const N& other) const;
			/// Component-wise % with scalar
			template<Number N>
			constexpr mat3x4<T> operator%(const N& other) const;
			/// Component-wise * with scalar
			template<Number N>
			constexpr mat3x4<T> compWiseMult(const N& other) const;
			/// Component-wise / with scalar
			template<Number N>
			constexpr mat3x4<T> compWiseDiv(const N& other) const;
			/// Component-wise assignment += from scalar
			template<Number N>
			constexpr void operator+=(const N& other);
			/// Component-wise assignment -= from scalar
			template<Number N>
			constexpr void operator-=(const N& other);
			/// Component-wise assignment %= from scalar
			template<Number N>
			constexpr void operator%=(const N& other);
			/// Component-wise assignment *= from scalar
			template<Number N>
			constexpr void compWiseAssMult(const N& other);
			/// Component-wise assignment /= from scalar
			template<Number N>
			constexpr void compWiseAssDiv(const N& other);
		// Matrix Multiplication
			/// Matrix multiplication with vec4 -> vec3
			template<ColumnVector4 C>
			constexpr vec3<T> operator*(const C& other) const;
			/// Matrix multiplication with mat4x2 -> mat3x2
			template<Mat4x2 M>
			constexpr mat3x2<T> operator*(const M& other) const;
			/// Matrix multiplication with mat4x3 -> mat3x3
			template<Mat4x3 M>
			constexpr mat3x3<T> operator*(const M& other) const;
			/// Matrix multiplication with mat4x4 -> mat3x4
			template<Mat4x4 M>
			constexpr mat3x4<T> operator*(const M& other) const;
	// Comparison
		// Vectorial
			/// Component-wise comparison == (and)
			template<Mat3x4 M>
			constexpr bool operator==(const M& other) const;
			/// Component-wise comparison < (and)
			template<Mat3x4 M>
			constexpr bool operator<(const M& other) const;
			/// Component-wise comparison > (and)
			template<Mat3x4 M>
			constexpr bool operator>(const M& other) const;
			/// Component-wise comparison != (and)
			template<Mat3x4 M>
			constexpr bool operator!=(const M& other) const;
			/// Component-wise comparison <= (and)
			template<Mat3x4 M>
			constexpr bool operator<=(const M& other) const;
			/// Component-wise comparison >= (and)
			template<Mat3x4 M>
			constexpr bool operator>=(const M& other) const;
		// Scalar
			/// Component-wise comparison == (and)
			template<Number N>
			constexpr bool operator==(const N& other) const;
			/// Component-wise comparison < (and)
			template<Number N>
			constexpr bool operator<(const N& other) const;
			/// Component-wise comparison > (and)
			template<Number N>
			constexpr bool operator>(const N& other) const;
			/// Component-wise comparison != (and)
			template<Number N>
			constexpr bool operator!=(const N& other) const;
			/// Component-wise comparison <= (and)
			template<Number N>
			constexpr bool operator<=(const N& other) const;
			/// Component-wise comparison >= (and)
			template<Number N>
			constexpr bool operator>=(const N& other) const;
	// Functional
			/// Returns the absolute value of the vector (sqrt of scalar product with itself)
			constexpr inline float abs() const;
			/// Returns the min of the components
			constexpr inline T min() const;
			/// Returns the max of the components
			constexpr inline T max() const;
			/// Scalar product (x1 * other.x1 +  x2 * other.x2 ...)
			template<Number N>
			constexpr inline T dot(const mat3x4<N>& other) const;
	// Utility
			/// Get the ith element. i starts at 0
			constexpr T operator[](std::size_t i) const;
			/// Get the element at row and col. row and col start at 0
			constexpr T at(std::size_t row, std::size_t col) const;
			/// Get the ith row as column vector. i starts at 0
			constexpr rvec4<T> row(std::size_t i) const;
			/// Get the ith column as row vector. i starts at 0
			constexpr vec3<T> column(std::size_t i) const;
			/// Return an Iterator to the first element
			constexpr Iterator<T> cbegin() const;
			/// Return an Iterator past the last element
			constexpr Iterator<T> cend() const;
			/// Return an Iterator to the first element
			constexpr Iterator<T> begin() const;
			/// Return an Iterator past the last element
			constexpr Iterator<T> end() const;
	}; // mat3x4

	using mat3x4f = mat3x4<float>;
	using mat3x4d = mat3x4<double>;
	using mat3x4i = mat3x4<int>;
	using mat3x4u = mat3x4<unsigned int>;


	static_assert(Mat3x4<mat3x4<int>>, "mat3x4<int> does not satisfy the concept Mat3x4");
} // namespace gz
