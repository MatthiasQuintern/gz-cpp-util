#pragma once

#include "concepts.hpp"
#include "../container/iterator.hpp"

namespace gz {

	// Forward declarations
	template<Number T>
	class mat4x2;
	template<Number T>
	class mat4x3;
	template<Number T>
	class mat4x4;
	template<Number T>
	class rvec2;
	template<Number T>
	class rvec3;
	template<Number T>
	class vec4;

	/**
	 * @brief Class containing 4 numbers
	 */
 	template<Number T>
	class rvec4 {
	    public:
			/// just to satisfy concept RowVector
			using isRowVector = T;
		// Constructors
			/// Default constructor
			constexpr rvec4()
				 : x(0), y(0), z(0), w(0) {}
			/// Create from scalar, all components will have value n
			template<Number N>
			constexpr rvec4(const N n)
				 : x(static_cast<T>(n)), y(static_cast<T>(n)), z(static_cast<T>(n)), w(static_cast<T>(n)) {}
			/// Create from n n n n 
			template<Number N1, Number N2, Number N3, Number N4>
			constexpr rvec4(N1 n1, N2 n2, N3 n3, N4 n4)
				 : x(static_cast<T>(n1)), y(static_cast<T>(n2)), z(static_cast<T>(n3)), w(static_cast<T>(n4)) {}
			/// Create from n n vec2 
			template<Number N1, Number N2, Vector4 V1>
			constexpr rvec4(N1 n1, N2 n2, const V1& v1)
				 : x(static_cast<T>(n1)), y(static_cast<T>(n2)), z(static_cast<T>(v1.x)), w(static_cast<T>(v1.y)) {}
			/// Create from n vec2 n 
			template<Number N1, Vector4 V1, Number N2>
			constexpr rvec4(N1 n1, const V1& v1, N2 n2)
				 : x(static_cast<T>(n1)), y(static_cast<T>(v1.x)), z(static_cast<T>(v1.y)), w(static_cast<T>(n2)) {}
			/// Create from n vec3 
			template<Number N1, Vector4 V1>
			constexpr rvec4(N1 n1, const V1& v1)
				 : x(static_cast<T>(n1)), y(static_cast<T>(v1.x)), z(static_cast<T>(v1.y)), w(static_cast<T>(v1.z)) {}
			/// Create from vec2 n n 
			template<Vector4 V1, Number N1, Number N2>
			constexpr rvec4(const V1& v1, N1 n1, N2 n2)
				 : x(static_cast<T>(v1.x)), y(static_cast<T>(v1.y)), z(static_cast<T>(n1)), w(static_cast<T>(n2)) {}
			/// Create from vec2 vec2 
			template<Vector4 V1, Vector4 V2>
			constexpr rvec4(const V1& v1, const V2& v2)
				 : x(static_cast<T>(v1.x)), y(static_cast<T>(v1.y)), z(static_cast<T>(v2.x)), w(static_cast<T>(v2.y)) {}
			/// Create from vec3 n 
			template<Vector4 V1, Number N1>
			constexpr rvec4(const V1& v1, N1 n1)
				 : x(static_cast<T>(v1.x)), y(static_cast<T>(v1.y)), z(static_cast<T>(v1.z)), w(static_cast<T>(n1)) {}
			/// Create from vec4 
			template<Vector4 V1>
			constexpr rvec4(const V1& v1)
				 : x(static_cast<T>(v1.x)), y(static_cast<T>(v1.y)), z(static_cast<T>(v1.z)), w(static_cast<T>(v1.w)) {}
		// Values
			T x;
			T y;
			T z;
			T w;
		// Assignment
			/// Component-wise assignment
			template<Number N>
			constexpr void operator=(const rvec4<N>& other);
			/// Assignment from scalar
			template<Number N>
			constexpr void operator=(const N& other);
	// Arithmetic
		// Vectorial
			/// Component-wise +
			template<RowVector4 R>
			constexpr rvec4<T> operator+(const R& other) const;
			/// Component-wise -
			template<RowVector4 R>
			constexpr rvec4<T> operator-(const R& other) const;
			/// Component-wise %
			template<RowVector4 R>
			constexpr rvec4<T> operator%(const R& other) const;
			/// Component-wise *
			template<RowVector4 R>
			constexpr rvec4<T> compWiseMult(const R& other) const;
			/// Component-wise /
			template<RowVector4 R>
			constexpr rvec4<T> compWiseDiv(const R& other) const;
			/// Component-wise assignment +=
			template<RowVector4 R>
			constexpr void operator+=(const R& other);
			/// Component-wise assignment -=
			template<RowVector4 R>
			constexpr void operator-=(const R& other);
			/// Component-wise assignment %=
			template<RowVector4 R>
			constexpr void operator%=(const R& other);
			/// Component-wise assignment *=
			template<RowVector4 R>
			constexpr void compWiseAssMult(const R& other);
			/// Component-wise assignment /=
			template<RowVector4 R>
			constexpr void compWiseAssDiv(const R& other);
		// Scalar
			/// Component-wise + with scalar
			template<Number N>
			constexpr rvec4<T> operator+(const N& other) const;
			/// Component-wise - with scalar
			template<Number N>
			constexpr rvec4<T> operator-(const N& other) const;
			/// Component-wise % with scalar
			template<Number N>
			constexpr rvec4<T> operator%(const N& other) const;
			/// Component-wise * with scalar
			template<Number N>
			constexpr rvec4<T> compWiseMult(const N& other) const;
			/// Component-wise / with scalar
			template<Number N>
			constexpr rvec4<T> compWiseDiv(const N& other) const;
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
			/// Matrix multiplication with mat4x2 -> rvec2
			template<Mat4x2 M>
			constexpr rvec2<T> operator*(const M& other) const;
			/// Matrix multiplication with mat4x3 -> rvec3
			template<Mat4x3 M>
			constexpr rvec3<T> operator*(const M& other) const;
			/// Matrix multiplication with mat4x4 -> rvec4
			template<Mat4x4 M>
			constexpr rvec4<T> operator*(const M& other) const;
	// Comparison
		// Vectorial
			/// Component-wise comparison == (and)
			template<RowVector4 R>
			constexpr bool operator==(const R& other) const;
			/// Component-wise comparison < (and)
			template<RowVector4 R>
			constexpr bool operator<(const R& other) const;
			/// Component-wise comparison > (and)
			template<RowVector4 R>
			constexpr bool operator>(const R& other) const;
			/// Component-wise comparison != (and)
			template<RowVector4 R>
			constexpr bool operator!=(const R& other) const;
			/// Component-wise comparison <= (and)
			template<RowVector4 R>
			constexpr bool operator<=(const R& other) const;
			/// Component-wise comparison >= (and)
			template<RowVector4 R>
			constexpr bool operator>=(const R& other) const;
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
			constexpr inline T dot(const rvec4<N>& other) const;
	// Utility
			/// Get the ith element. i starts at 0
			constexpr T operator[](std::size_t i) const;
			/// Return an Iterator to the first element
			constexpr Iterator<T> cbegin() const;
			/// Return an Iterator past the last element
			constexpr Iterator<T> cend() const;
			/// Return an Iterator to the first element
			constexpr Iterator<T> begin() const;
			/// Return an Iterator past the last element
			constexpr Iterator<T> end() const;
	}; // rvec4

	using rvec4f = rvec4<float>;
	using rvec4d = rvec4<double>;
	using rvec4i = rvec4<int>;
	using rvec4u = rvec4<unsigned int>;


	static_assert(RowVector4<rvec4<int>>, "rvec4<int> does not satisfy the concept RowVector4");
} // namespace gz
