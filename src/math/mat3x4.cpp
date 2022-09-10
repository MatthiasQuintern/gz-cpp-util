#include "mat3x4.hpp"

#include "mat3x2.hpp"
#include "mat3x3.hpp"
#include "mat4x2.hpp"
#include "mat4x3.hpp"
#include "mat4x4.hpp"
#include "rvec4.hpp"
#include "vec3.hpp"
#include "vec4.hpp"

#include <cmath>
#include <algorithm>
#include <cstdint>

namespace gz {

	//
	// CLASS mat3x4
	//
	template<Number T>
	template<Number N>
	constexpr void mat3x4<T>::operator=(const mat3x4<N>& other) {
			x1_1 = static_cast<T>(other.x1_1);
			x1_2 = static_cast<T>(other.x1_2);
			x1_3 = static_cast<T>(other.x1_3);
			x1_4 = static_cast<T>(other.x1_4);
			x2_1 = static_cast<T>(other.x2_1);
			x2_2 = static_cast<T>(other.x2_2);
			x2_3 = static_cast<T>(other.x2_3);
			x2_4 = static_cast<T>(other.x2_4);
			x3_1 = static_cast<T>(other.x3_1);
			x3_2 = static_cast<T>(other.x3_2);
			x3_3 = static_cast<T>(other.x3_3);
			x3_4 = static_cast<T>(other.x3_4);

	}
	template<Number T>
	template<Number N>
	constexpr void mat3x4<T>::operator=(const N& other) {
			x1_1 = static_cast<T>(other);
			x1_2 = static_cast<T>(other);
			x1_3 = static_cast<T>(other);
			x1_4 = static_cast<T>(other);
			x2_1 = static_cast<T>(other);
			x2_2 = static_cast<T>(other);
			x2_3 = static_cast<T>(other);
			x2_4 = static_cast<T>(other);
			x3_1 = static_cast<T>(other);
			x3_2 = static_cast<T>(other);
			x3_3 = static_cast<T>(other);
			x3_4 = static_cast<T>(other);

	}
	template<Number T>
	template<Mat3x4 M>
	constexpr mat3x4<T> mat3x4<T>::operator+(const M& other) const {
		return mat3x4<T>(x1_1 + static_cast<T>(other.x1_1), x1_2 + static_cast<T>(other.x1_2), x1_3 + static_cast<T>(other.x1_3), x1_4 + static_cast<T>(other.x1_4), x2_1 + static_cast<T>(other.x2_1), x2_2 + static_cast<T>(other.x2_2), x2_3 + static_cast<T>(other.x2_3), x2_4 + static_cast<T>(other.x2_4), x3_1 + static_cast<T>(other.x3_1), x3_2 + static_cast<T>(other.x3_2), x3_3 + static_cast<T>(other.x3_3), x3_4 + static_cast<T>(other.x3_4));
	}
	template<Number T>
	template<Mat3x4 M>
	constexpr mat3x4<T> mat3x4<T>::operator-(const M& other) const {
		return mat3x4<T>(x1_1 - static_cast<T>(other.x1_1), x1_2 - static_cast<T>(other.x1_2), x1_3 - static_cast<T>(other.x1_3), x1_4 - static_cast<T>(other.x1_4), x2_1 - static_cast<T>(other.x2_1), x2_2 - static_cast<T>(other.x2_2), x2_3 - static_cast<T>(other.x2_3), x2_4 - static_cast<T>(other.x2_4), x3_1 - static_cast<T>(other.x3_1), x3_2 - static_cast<T>(other.x3_2), x3_3 - static_cast<T>(other.x3_3), x3_4 - static_cast<T>(other.x3_4));
	}
	template<Number T>
	template<Mat3x4 M>
	constexpr mat3x4<T> mat3x4<T>::operator%(const M& other) const {
		return mat3x4<T>(x1_1 % static_cast<T>(other.x1_1), x1_2 % static_cast<T>(other.x1_2), x1_3 % static_cast<T>(other.x1_3), x1_4 % static_cast<T>(other.x1_4), x2_1 % static_cast<T>(other.x2_1), x2_2 % static_cast<T>(other.x2_2), x2_3 % static_cast<T>(other.x2_3), x2_4 % static_cast<T>(other.x2_4), x3_1 % static_cast<T>(other.x3_1), x3_2 % static_cast<T>(other.x3_2), x3_3 % static_cast<T>(other.x3_3), x3_4 % static_cast<T>(other.x3_4));
	}
	template<Number T>
	template<Mat3x4 M>
	constexpr mat3x4<T> mat3x4<T>::compWiseMult(const M& other) const {
		return mat3x4<T>(x1_1 * static_cast<T>(other.x1_1), x1_2 * static_cast<T>(other.x1_2), x1_3 * static_cast<T>(other.x1_3), x1_4 * static_cast<T>(other.x1_4), x2_1 * static_cast<T>(other.x2_1), x2_2 * static_cast<T>(other.x2_2), x2_3 * static_cast<T>(other.x2_3), x2_4 * static_cast<T>(other.x2_4), x3_1 * static_cast<T>(other.x3_1), x3_2 * static_cast<T>(other.x3_2), x3_3 * static_cast<T>(other.x3_3), x3_4 * static_cast<T>(other.x3_4));
	}
	template<Number T>
	template<Mat3x4 M>
	constexpr mat3x4<T> mat3x4<T>::compWiseDiv(const M& other) const {
		return mat3x4<T>(x1_1 / static_cast<T>(other.x1_1), x1_2 / static_cast<T>(other.x1_2), x1_3 / static_cast<T>(other.x1_3), x1_4 / static_cast<T>(other.x1_4), x2_1 / static_cast<T>(other.x2_1), x2_2 / static_cast<T>(other.x2_2), x2_3 / static_cast<T>(other.x2_3), x2_4 / static_cast<T>(other.x2_4), x3_1 / static_cast<T>(other.x3_1), x3_2 / static_cast<T>(other.x3_2), x3_3 / static_cast<T>(other.x3_3), x3_4 / static_cast<T>(other.x3_4));
	}
	template<Number T>
	template<Mat3x4 M>
	constexpr void mat3x4<T>::operator+=(const M& other) {
			x1_1 += static_cast<T>(other.x1_1);
			x1_2 += static_cast<T>(other.x1_2);
			x1_3 += static_cast<T>(other.x1_3);
			x1_4 += static_cast<T>(other.x1_4);
			x2_1 += static_cast<T>(other.x2_1);
			x2_2 += static_cast<T>(other.x2_2);
			x2_3 += static_cast<T>(other.x2_3);
			x2_4 += static_cast<T>(other.x2_4);
			x3_1 += static_cast<T>(other.x3_1);
			x3_2 += static_cast<T>(other.x3_2);
			x3_3 += static_cast<T>(other.x3_3);
			x3_4 += static_cast<T>(other.x3_4);
	}
	template<Number T>
	template<Mat3x4 M>
	constexpr void mat3x4<T>::operator-=(const M& other) {
			x1_1 -= static_cast<T>(other.x1_1);
			x1_2 -= static_cast<T>(other.x1_2);
			x1_3 -= static_cast<T>(other.x1_3);
			x1_4 -= static_cast<T>(other.x1_4);
			x2_1 -= static_cast<T>(other.x2_1);
			x2_2 -= static_cast<T>(other.x2_2);
			x2_3 -= static_cast<T>(other.x2_3);
			x2_4 -= static_cast<T>(other.x2_4);
			x3_1 -= static_cast<T>(other.x3_1);
			x3_2 -= static_cast<T>(other.x3_2);
			x3_3 -= static_cast<T>(other.x3_3);
			x3_4 -= static_cast<T>(other.x3_4);
	}
	template<Number T>
	template<Mat3x4 M>
	constexpr void mat3x4<T>::operator%=(const M& other) {
			x1_1 %= static_cast<T>(other.x1_1);
			x1_2 %= static_cast<T>(other.x1_2);
			x1_3 %= static_cast<T>(other.x1_3);
			x1_4 %= static_cast<T>(other.x1_4);
			x2_1 %= static_cast<T>(other.x2_1);
			x2_2 %= static_cast<T>(other.x2_2);
			x2_3 %= static_cast<T>(other.x2_3);
			x2_4 %= static_cast<T>(other.x2_4);
			x3_1 %= static_cast<T>(other.x3_1);
			x3_2 %= static_cast<T>(other.x3_2);
			x3_3 %= static_cast<T>(other.x3_3);
			x3_4 %= static_cast<T>(other.x3_4);
	}
	template<Number T>
	template<Mat3x4 M>
	constexpr void mat3x4<T>::compWiseAssMult(const M& other) {
			x1_1 *= static_cast<T>(other.x1_1);
			x1_2 *= static_cast<T>(other.x1_2);
			x1_3 *= static_cast<T>(other.x1_3);
			x1_4 *= static_cast<T>(other.x1_4);
			x2_1 *= static_cast<T>(other.x2_1);
			x2_2 *= static_cast<T>(other.x2_2);
			x2_3 *= static_cast<T>(other.x2_3);
			x2_4 *= static_cast<T>(other.x2_4);
			x3_1 *= static_cast<T>(other.x3_1);
			x3_2 *= static_cast<T>(other.x3_2);
			x3_3 *= static_cast<T>(other.x3_3);
			x3_4 *= static_cast<T>(other.x3_4);
	}
	template<Number T>
	template<Mat3x4 M>
	constexpr void mat3x4<T>::compWiseAssDiv(const M& other) {
			x1_1 /= static_cast<T>(other.x1_1);
			x1_2 /= static_cast<T>(other.x1_2);
			x1_3 /= static_cast<T>(other.x1_3);
			x1_4 /= static_cast<T>(other.x1_4);
			x2_1 /= static_cast<T>(other.x2_1);
			x2_2 /= static_cast<T>(other.x2_2);
			x2_3 /= static_cast<T>(other.x2_3);
			x2_4 /= static_cast<T>(other.x2_4);
			x3_1 /= static_cast<T>(other.x3_1);
			x3_2 /= static_cast<T>(other.x3_2);
			x3_3 /= static_cast<T>(other.x3_3);
			x3_4 /= static_cast<T>(other.x3_4);
	}
	template<Number T>
	template<Number N>
	constexpr mat3x4<T> mat3x4<T>::operator+(const N& other) const {
		return mat3x4<T>(x1_1 + static_cast<T>(other), x1_2 + static_cast<T>(other), x1_3 + static_cast<T>(other), x1_4 + static_cast<T>(other), x2_1 + static_cast<T>(other), x2_2 + static_cast<T>(other), x2_3 + static_cast<T>(other), x2_4 + static_cast<T>(other), x3_1 + static_cast<T>(other), x3_2 + static_cast<T>(other), x3_3 + static_cast<T>(other), x3_4 + static_cast<T>(other));
	}
	template<Number T>
	template<Number N>
	constexpr mat3x4<T> mat3x4<T>::operator-(const N& other) const {
		return mat3x4<T>(x1_1 - static_cast<T>(other), x1_2 - static_cast<T>(other), x1_3 - static_cast<T>(other), x1_4 - static_cast<T>(other), x2_1 - static_cast<T>(other), x2_2 - static_cast<T>(other), x2_3 - static_cast<T>(other), x2_4 - static_cast<T>(other), x3_1 - static_cast<T>(other), x3_2 - static_cast<T>(other), x3_3 - static_cast<T>(other), x3_4 - static_cast<T>(other));
	}
	template<Number T>
	template<Number N>
	constexpr mat3x4<T> mat3x4<T>::operator%(const N& other) const {
		return mat3x4<T>(x1_1 % static_cast<T>(other), x1_2 % static_cast<T>(other), x1_3 % static_cast<T>(other), x1_4 % static_cast<T>(other), x2_1 % static_cast<T>(other), x2_2 % static_cast<T>(other), x2_3 % static_cast<T>(other), x2_4 % static_cast<T>(other), x3_1 % static_cast<T>(other), x3_2 % static_cast<T>(other), x3_3 % static_cast<T>(other), x3_4 % static_cast<T>(other));
	}
	template<Number T>
	template<Number N>
	constexpr mat3x4<T> mat3x4<T>::compWiseMult(const N& other) const {
		return mat3x4<T>(x1_1 * static_cast<T>(other), x1_2 * static_cast<T>(other), x1_3 * static_cast<T>(other), x1_4 * static_cast<T>(other), x2_1 * static_cast<T>(other), x2_2 * static_cast<T>(other), x2_3 * static_cast<T>(other), x2_4 * static_cast<T>(other), x3_1 * static_cast<T>(other), x3_2 * static_cast<T>(other), x3_3 * static_cast<T>(other), x3_4 * static_cast<T>(other));
	}
	template<Number T>
	template<Number N>
	constexpr mat3x4<T> mat3x4<T>::compWiseDiv(const N& other) const {
		return mat3x4<T>(x1_1 / static_cast<T>(other), x1_2 / static_cast<T>(other), x1_3 / static_cast<T>(other), x1_4 / static_cast<T>(other), x2_1 / static_cast<T>(other), x2_2 / static_cast<T>(other), x2_3 / static_cast<T>(other), x2_4 / static_cast<T>(other), x3_1 / static_cast<T>(other), x3_2 / static_cast<T>(other), x3_3 / static_cast<T>(other), x3_4 / static_cast<T>(other));
	}
	template<Number T>
	template<Number N>
	constexpr void mat3x4<T>::operator+=(const N& other) {
			x1_1 += static_cast<T>(other);
			x1_2 += static_cast<T>(other);
			x1_3 += static_cast<T>(other);
			x1_4 += static_cast<T>(other);
			x2_1 += static_cast<T>(other);
			x2_2 += static_cast<T>(other);
			x2_3 += static_cast<T>(other);
			x2_4 += static_cast<T>(other);
			x3_1 += static_cast<T>(other);
			x3_2 += static_cast<T>(other);
			x3_3 += static_cast<T>(other);
			x3_4 += static_cast<T>(other);
	}
	template<Number T>
	template<Number N>
	constexpr void mat3x4<T>::operator-=(const N& other) {
			x1_1 -= static_cast<T>(other);
			x1_2 -= static_cast<T>(other);
			x1_3 -= static_cast<T>(other);
			x1_4 -= static_cast<T>(other);
			x2_1 -= static_cast<T>(other);
			x2_2 -= static_cast<T>(other);
			x2_3 -= static_cast<T>(other);
			x2_4 -= static_cast<T>(other);
			x3_1 -= static_cast<T>(other);
			x3_2 -= static_cast<T>(other);
			x3_3 -= static_cast<T>(other);
			x3_4 -= static_cast<T>(other);
	}
	template<Number T>
	template<Number N>
	constexpr void mat3x4<T>::operator%=(const N& other) {
			x1_1 %= static_cast<T>(other);
			x1_2 %= static_cast<T>(other);
			x1_3 %= static_cast<T>(other);
			x1_4 %= static_cast<T>(other);
			x2_1 %= static_cast<T>(other);
			x2_2 %= static_cast<T>(other);
			x2_3 %= static_cast<T>(other);
			x2_4 %= static_cast<T>(other);
			x3_1 %= static_cast<T>(other);
			x3_2 %= static_cast<T>(other);
			x3_3 %= static_cast<T>(other);
			x3_4 %= static_cast<T>(other);
	}
	template<Number T>
	template<Number N>
	constexpr void mat3x4<T>::compWiseAssMult(const N& other) {
			x1_1 *= static_cast<T>(other);
			x1_2 *= static_cast<T>(other);
			x1_3 *= static_cast<T>(other);
			x1_4 *= static_cast<T>(other);
			x2_1 *= static_cast<T>(other);
			x2_2 *= static_cast<T>(other);
			x2_3 *= static_cast<T>(other);
			x2_4 *= static_cast<T>(other);
			x3_1 *= static_cast<T>(other);
			x3_2 *= static_cast<T>(other);
			x3_3 *= static_cast<T>(other);
			x3_4 *= static_cast<T>(other);
	}
	template<Number T>
	template<Number N>
	constexpr void mat3x4<T>::compWiseAssDiv(const N& other) {
			x1_1 /= static_cast<T>(other);
			x1_2 /= static_cast<T>(other);
			x1_3 /= static_cast<T>(other);
			x1_4 /= static_cast<T>(other);
			x2_1 /= static_cast<T>(other);
			x2_2 /= static_cast<T>(other);
			x2_3 /= static_cast<T>(other);
			x2_4 /= static_cast<T>(other);
			x3_1 /= static_cast<T>(other);
			x3_2 /= static_cast<T>(other);
			x3_3 /= static_cast<T>(other);
			x3_4 /= static_cast<T>(other);
	}
	template<Number T>
	template<ColumnVector4 C>
	constexpr vec3<T> mat3x4<T>::operator*(const C& other) const {
		vec3<T> new_;
		new_.x = x1_1 * other.x + x1_2 * other.y + x1_3 * other.z + x1_4 * other.w;
		new_.y = x2_1 * other.x + x2_2 * other.y + x2_3 * other.z + x2_4 * other.w;
		new_.z = x3_1 * other.x + x3_2 * other.y + x3_3 * other.z + x3_4 * other.w;
		return new_;
	}
	template<Number T>
	template<Mat4x2 M>
	constexpr mat3x2<T> mat3x4<T>::operator*(const M& other) const {
		mat3x2<T> new_;
		new_.x1_1 = x1_1 * other.x1_1 + x1_2 * other.x2_1 + x1_3 * other.x3_1 + x1_4 * other.x4_1;
		new_.x1_2 = x1_1 * other.x1_2 + x1_2 * other.x2_2 + x1_3 * other.x3_2 + x1_4 * other.x4_2;
		new_.x2_1 = x2_1 * other.x1_1 + x2_2 * other.x2_1 + x2_3 * other.x3_1 + x2_4 * other.x4_1;
		new_.x2_2 = x2_1 * other.x1_2 + x2_2 * other.x2_2 + x2_3 * other.x3_2 + x2_4 * other.x4_2;
		new_.x3_1 = x3_1 * other.x1_1 + x3_2 * other.x2_1 + x3_3 * other.x3_1 + x3_4 * other.x4_1;
		new_.x3_2 = x3_1 * other.x1_2 + x3_2 * other.x2_2 + x3_3 * other.x3_2 + x3_4 * other.x4_2;
		return new_;
	}
	template<Number T>
	template<Mat4x3 M>
	constexpr mat3x3<T> mat3x4<T>::operator*(const M& other) const {
		mat3x3<T> new_;
		new_.x1_1 = x1_1 * other.x1_1 + x1_2 * other.x2_1 + x1_3 * other.x3_1 + x1_4 * other.x4_1;
		new_.x1_2 = x1_1 * other.x1_2 + x1_2 * other.x2_2 + x1_3 * other.x3_2 + x1_4 * other.x4_2;
		new_.x1_3 = x1_1 * other.x1_3 + x1_2 * other.x2_3 + x1_3 * other.x3_3 + x1_4 * other.x4_3;
		new_.x2_1 = x2_1 * other.x1_1 + x2_2 * other.x2_1 + x2_3 * other.x3_1 + x2_4 * other.x4_1;
		new_.x2_2 = x2_1 * other.x1_2 + x2_2 * other.x2_2 + x2_3 * other.x3_2 + x2_4 * other.x4_2;
		new_.x2_3 = x2_1 * other.x1_3 + x2_2 * other.x2_3 + x2_3 * other.x3_3 + x2_4 * other.x4_3;
		new_.x3_1 = x3_1 * other.x1_1 + x3_2 * other.x2_1 + x3_3 * other.x3_1 + x3_4 * other.x4_1;
		new_.x3_2 = x3_1 * other.x1_2 + x3_2 * other.x2_2 + x3_3 * other.x3_2 + x3_4 * other.x4_2;
		new_.x3_3 = x3_1 * other.x1_3 + x3_2 * other.x2_3 + x3_3 * other.x3_3 + x3_4 * other.x4_3;
		return new_;
	}
	template<Number T>
	template<Mat4x4 M>
	constexpr mat3x4<T> mat3x4<T>::operator*(const M& other) const {
		mat3x4<T> new_;
		new_.x1_1 = x1_1 * other.x1_1 + x1_2 * other.x2_1 + x1_3 * other.x3_1 + x1_4 * other.x4_1;
		new_.x1_2 = x1_1 * other.x1_2 + x1_2 * other.x2_2 + x1_3 * other.x3_2 + x1_4 * other.x4_2;
		new_.x1_3 = x1_1 * other.x1_3 + x1_2 * other.x2_3 + x1_3 * other.x3_3 + x1_4 * other.x4_3;
		new_.x1_4 = x1_1 * other.x1_4 + x1_2 * other.x2_4 + x1_3 * other.x3_4 + x1_4 * other.x4_4;
		new_.x2_1 = x2_1 * other.x1_1 + x2_2 * other.x2_1 + x2_3 * other.x3_1 + x2_4 * other.x4_1;
		new_.x2_2 = x2_1 * other.x1_2 + x2_2 * other.x2_2 + x2_3 * other.x3_2 + x2_4 * other.x4_2;
		new_.x2_3 = x2_1 * other.x1_3 + x2_2 * other.x2_3 + x2_3 * other.x3_3 + x2_4 * other.x4_3;
		new_.x2_4 = x2_1 * other.x1_4 + x2_2 * other.x2_4 + x2_3 * other.x3_4 + x2_4 * other.x4_4;
		new_.x3_1 = x3_1 * other.x1_1 + x3_2 * other.x2_1 + x3_3 * other.x3_1 + x3_4 * other.x4_1;
		new_.x3_2 = x3_1 * other.x1_2 + x3_2 * other.x2_2 + x3_3 * other.x3_2 + x3_4 * other.x4_2;
		new_.x3_3 = x3_1 * other.x1_3 + x3_2 * other.x2_3 + x3_3 * other.x3_3 + x3_4 * other.x4_3;
		new_.x3_4 = x3_1 * other.x1_4 + x3_2 * other.x2_4 + x3_3 * other.x3_4 + x3_4 * other.x4_4;
		return new_;
	}
	template<Number T>
	template<Mat3x4 M>
	constexpr bool mat3x4<T>::operator==(const M& other) const {
		return x1_1 == other.x1_1 and x1_2 == other.x1_2 and x1_3 == other.x1_3 and x1_4 == other.x1_4 and x2_1 == other.x2_1 and x2_2 == other.x2_2 and x2_3 == other.x2_3 and x2_4 == other.x2_4 and x3_1 == other.x3_1 and x3_2 == other.x3_2 and x3_3 == other.x3_3 and x3_4 == other.x3_4;
	}
	template<Number T>
	template<Mat3x4 M>
	constexpr bool mat3x4<T>::operator<(const M& other) const {
		return x1_1 < other.x1_1 and x1_2 < other.x1_2 and x1_3 < other.x1_3 and x1_4 < other.x1_4 and x2_1 < other.x2_1 and x2_2 < other.x2_2 and x2_3 < other.x2_3 and x2_4 < other.x2_4 and x3_1 < other.x3_1 and x3_2 < other.x3_2 and x3_3 < other.x3_3 and x3_4 < other.x3_4;
	}
	template<Number T>
	template<Mat3x4 M>
	constexpr bool mat3x4<T>::operator>(const M& other) const {
		return x1_1 > other.x1_1 and x1_2 > other.x1_2 and x1_3 > other.x1_3 and x1_4 > other.x1_4 and x2_1 > other.x2_1 and x2_2 > other.x2_2 and x2_3 > other.x2_3 and x2_4 > other.x2_4 and x3_1 > other.x3_1 and x3_2 > other.x3_2 and x3_3 > other.x3_3 and x3_4 > other.x3_4;
	}
	template<Number T>
	template<Mat3x4 M>
	constexpr bool mat3x4<T>::operator!=(const M& other) const {
		return x1_1 == other.x1_1 and x1_2 == other.x1_2 and x1_3 == other.x1_3 and x1_4 == other.x1_4 and x2_1 == other.x2_1 and x2_2 == other.x2_2 and x2_3 == other.x2_3 and x2_4 == other.x2_4 and x3_1 == other.x3_1 and x3_2 == other.x3_2 and x3_3 == other.x3_3 and x3_4 == other.x3_4;
	}
	template<Number T>
	template<Mat3x4 M>
	constexpr bool mat3x4<T>::operator<=(const M& other) const {
		return x1_1 > other.x1_1 and x1_2 > other.x1_2 and x1_3 > other.x1_3 and x1_4 > other.x1_4 and x2_1 > other.x2_1 and x2_2 > other.x2_2 and x2_3 > other.x2_3 and x2_4 > other.x2_4 and x3_1 > other.x3_1 and x3_2 > other.x3_2 and x3_3 > other.x3_3 and x3_4 > other.x3_4;
	}
	template<Number T>
	template<Mat3x4 M>
	constexpr bool mat3x4<T>::operator>=(const M& other) const {
		return x1_1 < other.x1_1 and x1_2 < other.x1_2 and x1_3 < other.x1_3 and x1_4 < other.x1_4 and x2_1 < other.x2_1 and x2_2 < other.x2_2 and x2_3 < other.x2_3 and x2_4 < other.x2_4 and x3_1 < other.x3_1 and x3_2 < other.x3_2 and x3_3 < other.x3_3 and x3_4 < other.x3_4;
	}
	template<Number T>
	template<Number N>
	constexpr bool mat3x4<T>::operator==(const N& other) const {
		return x1_1 == other and x1_2 == other and x1_3 == other and x1_4 == other and x2_1 == other and x2_2 == other and x2_3 == other and x2_4 == other and x3_1 == other and x3_2 == other and x3_3 == other and x3_4 == other;
	}
	template<Number T>
	template<Number N>
	constexpr bool mat3x4<T>::operator<(const N& other) const {
		return x1_1 < other and x1_2 < other and x1_3 < other and x1_4 < other and x2_1 < other and x2_2 < other and x2_3 < other and x2_4 < other and x3_1 < other and x3_2 < other and x3_3 < other and x3_4 < other;
	}
	template<Number T>
	template<Number N>
	constexpr bool mat3x4<T>::operator>(const N& other) const {
		return x1_1 > other and x1_2 > other and x1_3 > other and x1_4 > other and x2_1 > other and x2_2 > other and x2_3 > other and x2_4 > other and x3_1 > other and x3_2 > other and x3_3 > other and x3_4 > other;
	}
	template<Number T>
	template<Number N>
	constexpr bool mat3x4<T>::operator!=(const N& other) const {
		return x1_1 == other and x1_2 == other and x1_3 == other and x1_4 == other and x2_1 == other and x2_2 == other and x2_3 == other and x2_4 == other and x3_1 == other and x3_2 == other and x3_3 == other and x3_4 == other;
	}
	template<Number T>
	template<Number N>
	constexpr bool mat3x4<T>::operator<=(const N& other) const {
		return x1_1 > other and x1_2 > other and x1_3 > other and x1_4 > other and x2_1 > other and x2_2 > other and x2_3 > other and x2_4 > other and x3_1 > other and x3_2 > other and x3_3 > other and x3_4 > other;
	}
	template<Number T>
	template<Number N>
	constexpr bool mat3x4<T>::operator>=(const N& other) const {
		return x1_1 < other and x1_2 < other and x1_3 < other and x1_4 < other and x2_1 < other and x2_2 < other and x2_3 < other and x2_4 < other and x3_1 < other and x3_2 < other and x3_3 < other and x3_4 < other;
	}
	template<Number T>
	constexpr inline float mat3x4<T>::abs() const {
		return std::sqrt(static_cast<float>(x1_1 * x1_1) + static_cast<float>(x1_2 * x1_2) + static_cast<float>(x1_3 * x1_3) + static_cast<float>(x1_4 * x1_4) + static_cast<float>(x2_1 * x2_1) + static_cast<float>(x2_2 * x2_2) + static_cast<float>(x2_3 * x2_3) + static_cast<float>(x2_4 * x2_4) + static_cast<float>(x3_1 * x3_1) + static_cast<float>(x3_2 * x3_2) + static_cast<float>(x3_3 * x3_3) + static_cast<float>(x3_4 * x3_4));
	}
	template<Number T>
	constexpr inline T mat3x4<T>::min() const {
		return *std::min_element(cbegin(), cend());
	}
	template<Number T>
	constexpr inline T mat3x4<T>::max() const {
		return *std::max_element(cbegin(), cend());
	}
	template<Number T>
	template<Number N>
	constexpr inline T mat3x4<T>::dot(const mat3x4<N>& other) const {
		return x1_1 * static_cast<T>(other.x1_1) + x1_2 * static_cast<T>(other.x1_2) + x1_3 * static_cast<T>(other.x1_3) + x1_4 * static_cast<T>(other.x1_4) + x2_1 * static_cast<T>(other.x2_1) + x2_2 * static_cast<T>(other.x2_2) + x2_3 * static_cast<T>(other.x2_3) + x2_4 * static_cast<T>(other.x2_4) + x3_1 * static_cast<T>(other.x3_1) + x3_2 * static_cast<T>(other.x3_2) + x3_3 * static_cast<T>(other.x3_3) + x3_4 * static_cast<T>(other.x3_4);
	}
	template<Number T>
	constexpr T mat3x4<T>::operator[](std::size_t i) const {
		return *(&x1_1 + sizeof(T) * i);
	}
	template<Number T>
	constexpr T mat3x4<T>::at(std::size_t row, std::size_t col) const {
		return *(&x1_1 + (row * 3 + col * 4) * sizeof(T));
	}
	template<Number T>
	constexpr rvec4<T> mat3x4<T>::row(std::size_t i) const {
		return rvec4<T>(*(&x1_1 + (3 * 0 + i) * sizeof(T)), *(&x1_1 + (3 * 1 + i) * sizeof(T)), *(&x1_1 + (3 * 2 + i) * sizeof(T)), *(&x1_1 + (3 * 3 + i) * sizeof(T)));
	}
	template<Number T>
	constexpr vec3<T> mat3x4<T>::column(std::size_t i) const {
		return vec3<T>(*(&x1_1 + (4 * 0 + i) * sizeof(T)), *(&x1_1 + (4 * 1 + i) * sizeof(T)), *(&x1_1 + (4 * 2 + i) * sizeof(T)));
	}
	template<Number T>
	constexpr Iterator<T> mat3x4<T>::cbegin() const {
		return Iterator(const_cast<T*>(&x1_1));
	}
	template<Number T>
	constexpr Iterator<T> mat3x4<T>::cend() const {
		return Iterator(const_cast<T*>(&x3_4 + sizeof(T)));
	}
	template<Number T>
	constexpr Iterator<T> mat3x4<T>::begin() const {
		return Iterator(const_cast<T*>(&x1_1));
	}
	template<Number T>
	constexpr Iterator<T> mat3x4<T>::end() const {
		return Iterator(const_cast<T*>(&x3_4 + sizeof(T)));
	}


} // namespace gz

#include "mat3x4.tpp"