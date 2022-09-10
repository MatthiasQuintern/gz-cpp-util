#include "mat4x3.hpp"

#include "mat3x2.hpp"
#include "mat3x3.hpp"
#include "mat3x4.hpp"
#include "mat4x2.hpp"
#include "mat4x4.hpp"
#include "rvec3.hpp"
#include "vec3.hpp"
#include "vec4.hpp"

#include <cmath>
#include <algorithm>
#include <cstdint>

namespace gz {

	//
	// CLASS mat4x3
	//
	template<Number T>
	template<Number N>
	constexpr void mat4x3<T>::operator=(const mat4x3<N>& other) {
			x1_1 = static_cast<T>(other.x1_1);
			x1_2 = static_cast<T>(other.x1_2);
			x1_3 = static_cast<T>(other.x1_3);
			x2_1 = static_cast<T>(other.x2_1);
			x2_2 = static_cast<T>(other.x2_2);
			x2_3 = static_cast<T>(other.x2_3);
			x3_1 = static_cast<T>(other.x3_1);
			x3_2 = static_cast<T>(other.x3_2);
			x3_3 = static_cast<T>(other.x3_3);
			x4_1 = static_cast<T>(other.x4_1);
			x4_2 = static_cast<T>(other.x4_2);
			x4_3 = static_cast<T>(other.x4_3);

	}
	template<Number T>
	template<Number N>
	constexpr void mat4x3<T>::operator=(const N& other) {
			x1_1 = static_cast<T>(other);
			x1_2 = static_cast<T>(other);
			x1_3 = static_cast<T>(other);
			x2_1 = static_cast<T>(other);
			x2_2 = static_cast<T>(other);
			x2_3 = static_cast<T>(other);
			x3_1 = static_cast<T>(other);
			x3_2 = static_cast<T>(other);
			x3_3 = static_cast<T>(other);
			x4_1 = static_cast<T>(other);
			x4_2 = static_cast<T>(other);
			x4_3 = static_cast<T>(other);

	}
	template<Number T>
	template<Mat4x3 M>
	constexpr mat4x3<T> mat4x3<T>::operator+(const M& other) const {
		return mat4x3<T>(x1_1 + static_cast<T>(other.x1_1), x1_2 + static_cast<T>(other.x1_2), x1_3 + static_cast<T>(other.x1_3), x2_1 + static_cast<T>(other.x2_1), x2_2 + static_cast<T>(other.x2_2), x2_3 + static_cast<T>(other.x2_3), x3_1 + static_cast<T>(other.x3_1), x3_2 + static_cast<T>(other.x3_2), x3_3 + static_cast<T>(other.x3_3), x4_1 + static_cast<T>(other.x4_1), x4_2 + static_cast<T>(other.x4_2), x4_3 + static_cast<T>(other.x4_3));
	}
	template<Number T>
	template<Mat4x3 M>
	constexpr mat4x3<T> mat4x3<T>::operator-(const M& other) const {
		return mat4x3<T>(x1_1 - static_cast<T>(other.x1_1), x1_2 - static_cast<T>(other.x1_2), x1_3 - static_cast<T>(other.x1_3), x2_1 - static_cast<T>(other.x2_1), x2_2 - static_cast<T>(other.x2_2), x2_3 - static_cast<T>(other.x2_3), x3_1 - static_cast<T>(other.x3_1), x3_2 - static_cast<T>(other.x3_2), x3_3 - static_cast<T>(other.x3_3), x4_1 - static_cast<T>(other.x4_1), x4_2 - static_cast<T>(other.x4_2), x4_3 - static_cast<T>(other.x4_3));
	}
	template<Number T>
	template<Mat4x3 M>
	constexpr mat4x3<T> mat4x3<T>::operator%(const M& other) const {
		return mat4x3<T>(x1_1 % static_cast<T>(other.x1_1), x1_2 % static_cast<T>(other.x1_2), x1_3 % static_cast<T>(other.x1_3), x2_1 % static_cast<T>(other.x2_1), x2_2 % static_cast<T>(other.x2_2), x2_3 % static_cast<T>(other.x2_3), x3_1 % static_cast<T>(other.x3_1), x3_2 % static_cast<T>(other.x3_2), x3_3 % static_cast<T>(other.x3_3), x4_1 % static_cast<T>(other.x4_1), x4_2 % static_cast<T>(other.x4_2), x4_3 % static_cast<T>(other.x4_3));
	}
	template<Number T>
	template<Mat4x3 M>
	constexpr mat4x3<T> mat4x3<T>::compWiseMult(const M& other) const {
		return mat4x3<T>(x1_1 * static_cast<T>(other.x1_1), x1_2 * static_cast<T>(other.x1_2), x1_3 * static_cast<T>(other.x1_3), x2_1 * static_cast<T>(other.x2_1), x2_2 * static_cast<T>(other.x2_2), x2_3 * static_cast<T>(other.x2_3), x3_1 * static_cast<T>(other.x3_1), x3_2 * static_cast<T>(other.x3_2), x3_3 * static_cast<T>(other.x3_3), x4_1 * static_cast<T>(other.x4_1), x4_2 * static_cast<T>(other.x4_2), x4_3 * static_cast<T>(other.x4_3));
	}
	template<Number T>
	template<Mat4x3 M>
	constexpr mat4x3<T> mat4x3<T>::compWiseDiv(const M& other) const {
		return mat4x3<T>(x1_1 / static_cast<T>(other.x1_1), x1_2 / static_cast<T>(other.x1_2), x1_3 / static_cast<T>(other.x1_3), x2_1 / static_cast<T>(other.x2_1), x2_2 / static_cast<T>(other.x2_2), x2_3 / static_cast<T>(other.x2_3), x3_1 / static_cast<T>(other.x3_1), x3_2 / static_cast<T>(other.x3_2), x3_3 / static_cast<T>(other.x3_3), x4_1 / static_cast<T>(other.x4_1), x4_2 / static_cast<T>(other.x4_2), x4_3 / static_cast<T>(other.x4_3));
	}
	template<Number T>
	template<Mat4x3 M>
	constexpr void mat4x3<T>::operator+=(const M& other) {
			x1_1 += static_cast<T>(other.x1_1);
			x1_2 += static_cast<T>(other.x1_2);
			x1_3 += static_cast<T>(other.x1_3);
			x2_1 += static_cast<T>(other.x2_1);
			x2_2 += static_cast<T>(other.x2_2);
			x2_3 += static_cast<T>(other.x2_3);
			x3_1 += static_cast<T>(other.x3_1);
			x3_2 += static_cast<T>(other.x3_2);
			x3_3 += static_cast<T>(other.x3_3);
			x4_1 += static_cast<T>(other.x4_1);
			x4_2 += static_cast<T>(other.x4_2);
			x4_3 += static_cast<T>(other.x4_3);
	}
	template<Number T>
	template<Mat4x3 M>
	constexpr void mat4x3<T>::operator-=(const M& other) {
			x1_1 -= static_cast<T>(other.x1_1);
			x1_2 -= static_cast<T>(other.x1_2);
			x1_3 -= static_cast<T>(other.x1_3);
			x2_1 -= static_cast<T>(other.x2_1);
			x2_2 -= static_cast<T>(other.x2_2);
			x2_3 -= static_cast<T>(other.x2_3);
			x3_1 -= static_cast<T>(other.x3_1);
			x3_2 -= static_cast<T>(other.x3_2);
			x3_3 -= static_cast<T>(other.x3_3);
			x4_1 -= static_cast<T>(other.x4_1);
			x4_2 -= static_cast<T>(other.x4_2);
			x4_3 -= static_cast<T>(other.x4_3);
	}
	template<Number T>
	template<Mat4x3 M>
	constexpr void mat4x3<T>::operator%=(const M& other) {
			x1_1 %= static_cast<T>(other.x1_1);
			x1_2 %= static_cast<T>(other.x1_2);
			x1_3 %= static_cast<T>(other.x1_3);
			x2_1 %= static_cast<T>(other.x2_1);
			x2_2 %= static_cast<T>(other.x2_2);
			x2_3 %= static_cast<T>(other.x2_3);
			x3_1 %= static_cast<T>(other.x3_1);
			x3_2 %= static_cast<T>(other.x3_2);
			x3_3 %= static_cast<T>(other.x3_3);
			x4_1 %= static_cast<T>(other.x4_1);
			x4_2 %= static_cast<T>(other.x4_2);
			x4_3 %= static_cast<T>(other.x4_3);
	}
	template<Number T>
	template<Mat4x3 M>
	constexpr void mat4x3<T>::compWiseAssMult(const M& other) {
			x1_1 *= static_cast<T>(other.x1_1);
			x1_2 *= static_cast<T>(other.x1_2);
			x1_3 *= static_cast<T>(other.x1_3);
			x2_1 *= static_cast<T>(other.x2_1);
			x2_2 *= static_cast<T>(other.x2_2);
			x2_3 *= static_cast<T>(other.x2_3);
			x3_1 *= static_cast<T>(other.x3_1);
			x3_2 *= static_cast<T>(other.x3_2);
			x3_3 *= static_cast<T>(other.x3_3);
			x4_1 *= static_cast<T>(other.x4_1);
			x4_2 *= static_cast<T>(other.x4_2);
			x4_3 *= static_cast<T>(other.x4_3);
	}
	template<Number T>
	template<Mat4x3 M>
	constexpr void mat4x3<T>::compWiseAssDiv(const M& other) {
			x1_1 /= static_cast<T>(other.x1_1);
			x1_2 /= static_cast<T>(other.x1_2);
			x1_3 /= static_cast<T>(other.x1_3);
			x2_1 /= static_cast<T>(other.x2_1);
			x2_2 /= static_cast<T>(other.x2_2);
			x2_3 /= static_cast<T>(other.x2_3);
			x3_1 /= static_cast<T>(other.x3_1);
			x3_2 /= static_cast<T>(other.x3_2);
			x3_3 /= static_cast<T>(other.x3_3);
			x4_1 /= static_cast<T>(other.x4_1);
			x4_2 /= static_cast<T>(other.x4_2);
			x4_3 /= static_cast<T>(other.x4_3);
	}
	template<Number T>
	template<Number N>
	constexpr mat4x3<T> mat4x3<T>::operator+(const N& other) const {
		return mat4x3<T>(x1_1 + static_cast<T>(other), x1_2 + static_cast<T>(other), x1_3 + static_cast<T>(other), x2_1 + static_cast<T>(other), x2_2 + static_cast<T>(other), x2_3 + static_cast<T>(other), x3_1 + static_cast<T>(other), x3_2 + static_cast<T>(other), x3_3 + static_cast<T>(other), x4_1 + static_cast<T>(other), x4_2 + static_cast<T>(other), x4_3 + static_cast<T>(other));
	}
	template<Number T>
	template<Number N>
	constexpr mat4x3<T> mat4x3<T>::operator-(const N& other) const {
		return mat4x3<T>(x1_1 - static_cast<T>(other), x1_2 - static_cast<T>(other), x1_3 - static_cast<T>(other), x2_1 - static_cast<T>(other), x2_2 - static_cast<T>(other), x2_3 - static_cast<T>(other), x3_1 - static_cast<T>(other), x3_2 - static_cast<T>(other), x3_3 - static_cast<T>(other), x4_1 - static_cast<T>(other), x4_2 - static_cast<T>(other), x4_3 - static_cast<T>(other));
	}
	template<Number T>
	template<Number N>
	constexpr mat4x3<T> mat4x3<T>::operator%(const N& other) const {
		return mat4x3<T>(x1_1 % static_cast<T>(other), x1_2 % static_cast<T>(other), x1_3 % static_cast<T>(other), x2_1 % static_cast<T>(other), x2_2 % static_cast<T>(other), x2_3 % static_cast<T>(other), x3_1 % static_cast<T>(other), x3_2 % static_cast<T>(other), x3_3 % static_cast<T>(other), x4_1 % static_cast<T>(other), x4_2 % static_cast<T>(other), x4_3 % static_cast<T>(other));
	}
	template<Number T>
	template<Number N>
	constexpr mat4x3<T> mat4x3<T>::compWiseMult(const N& other) const {
		return mat4x3<T>(x1_1 * static_cast<T>(other), x1_2 * static_cast<T>(other), x1_3 * static_cast<T>(other), x2_1 * static_cast<T>(other), x2_2 * static_cast<T>(other), x2_3 * static_cast<T>(other), x3_1 * static_cast<T>(other), x3_2 * static_cast<T>(other), x3_3 * static_cast<T>(other), x4_1 * static_cast<T>(other), x4_2 * static_cast<T>(other), x4_3 * static_cast<T>(other));
	}
	template<Number T>
	template<Number N>
	constexpr mat4x3<T> mat4x3<T>::compWiseDiv(const N& other) const {
		return mat4x3<T>(x1_1 / static_cast<T>(other), x1_2 / static_cast<T>(other), x1_3 / static_cast<T>(other), x2_1 / static_cast<T>(other), x2_2 / static_cast<T>(other), x2_3 / static_cast<T>(other), x3_1 / static_cast<T>(other), x3_2 / static_cast<T>(other), x3_3 / static_cast<T>(other), x4_1 / static_cast<T>(other), x4_2 / static_cast<T>(other), x4_3 / static_cast<T>(other));
	}
	template<Number T>
	template<Number N>
	constexpr void mat4x3<T>::operator+=(const N& other) {
			x1_1 += static_cast<T>(other);
			x1_2 += static_cast<T>(other);
			x1_3 += static_cast<T>(other);
			x2_1 += static_cast<T>(other);
			x2_2 += static_cast<T>(other);
			x2_3 += static_cast<T>(other);
			x3_1 += static_cast<T>(other);
			x3_2 += static_cast<T>(other);
			x3_3 += static_cast<T>(other);
			x4_1 += static_cast<T>(other);
			x4_2 += static_cast<T>(other);
			x4_3 += static_cast<T>(other);
	}
	template<Number T>
	template<Number N>
	constexpr void mat4x3<T>::operator-=(const N& other) {
			x1_1 -= static_cast<T>(other);
			x1_2 -= static_cast<T>(other);
			x1_3 -= static_cast<T>(other);
			x2_1 -= static_cast<T>(other);
			x2_2 -= static_cast<T>(other);
			x2_3 -= static_cast<T>(other);
			x3_1 -= static_cast<T>(other);
			x3_2 -= static_cast<T>(other);
			x3_3 -= static_cast<T>(other);
			x4_1 -= static_cast<T>(other);
			x4_2 -= static_cast<T>(other);
			x4_3 -= static_cast<T>(other);
	}
	template<Number T>
	template<Number N>
	constexpr void mat4x3<T>::operator%=(const N& other) {
			x1_1 %= static_cast<T>(other);
			x1_2 %= static_cast<T>(other);
			x1_3 %= static_cast<T>(other);
			x2_1 %= static_cast<T>(other);
			x2_2 %= static_cast<T>(other);
			x2_3 %= static_cast<T>(other);
			x3_1 %= static_cast<T>(other);
			x3_2 %= static_cast<T>(other);
			x3_3 %= static_cast<T>(other);
			x4_1 %= static_cast<T>(other);
			x4_2 %= static_cast<T>(other);
			x4_3 %= static_cast<T>(other);
	}
	template<Number T>
	template<Number N>
	constexpr void mat4x3<T>::compWiseAssMult(const N& other) {
			x1_1 *= static_cast<T>(other);
			x1_2 *= static_cast<T>(other);
			x1_3 *= static_cast<T>(other);
			x2_1 *= static_cast<T>(other);
			x2_2 *= static_cast<T>(other);
			x2_3 *= static_cast<T>(other);
			x3_1 *= static_cast<T>(other);
			x3_2 *= static_cast<T>(other);
			x3_3 *= static_cast<T>(other);
			x4_1 *= static_cast<T>(other);
			x4_2 *= static_cast<T>(other);
			x4_3 *= static_cast<T>(other);
	}
	template<Number T>
	template<Number N>
	constexpr void mat4x3<T>::compWiseAssDiv(const N& other) {
			x1_1 /= static_cast<T>(other);
			x1_2 /= static_cast<T>(other);
			x1_3 /= static_cast<T>(other);
			x2_1 /= static_cast<T>(other);
			x2_2 /= static_cast<T>(other);
			x2_3 /= static_cast<T>(other);
			x3_1 /= static_cast<T>(other);
			x3_2 /= static_cast<T>(other);
			x3_3 /= static_cast<T>(other);
			x4_1 /= static_cast<T>(other);
			x4_2 /= static_cast<T>(other);
			x4_3 /= static_cast<T>(other);
	}
	template<Number T>
	template<ColumnVector3 C>
	constexpr vec4<T> mat4x3<T>::operator*(const C& other) const {
		vec4<T> new_;
		new_.x = x1_1 * other.x + x1_2 * other.y + x1_3 * other.z;
		new_.y = x2_1 * other.x + x2_2 * other.y + x2_3 * other.z;
		new_.z = x3_1 * other.x + x3_2 * other.y + x3_3 * other.z;
		new_.w = x4_1 * other.x + x4_2 * other.y + x4_3 * other.z;
		return new_;
	}
	template<Number T>
	template<Mat3x2 M>
	constexpr mat4x2<T> mat4x3<T>::operator*(const M& other) const {
		mat4x2<T> new_;
		new_.x1_1 = x1_1 * other.x1_1 + x1_2 * other.x2_1 + x1_3 * other.x3_1;
		new_.x1_2 = x1_1 * other.x1_2 + x1_2 * other.x2_2 + x1_3 * other.x3_2;
		new_.x2_1 = x2_1 * other.x1_1 + x2_2 * other.x2_1 + x2_3 * other.x3_1;
		new_.x2_2 = x2_1 * other.x1_2 + x2_2 * other.x2_2 + x2_3 * other.x3_2;
		new_.x3_1 = x3_1 * other.x1_1 + x3_2 * other.x2_1 + x3_3 * other.x3_1;
		new_.x3_2 = x3_1 * other.x1_2 + x3_2 * other.x2_2 + x3_3 * other.x3_2;
		new_.x4_1 = x4_1 * other.x1_1 + x4_2 * other.x2_1 + x4_3 * other.x3_1;
		new_.x4_2 = x4_1 * other.x1_2 + x4_2 * other.x2_2 + x4_3 * other.x3_2;
		return new_;
	}
	template<Number T>
	template<Mat3x3 M>
	constexpr mat4x3<T> mat4x3<T>::operator*(const M& other) const {
		mat4x3<T> new_;
		new_.x1_1 = x1_1 * other.x1_1 + x1_2 * other.x2_1 + x1_3 * other.x3_1;
		new_.x1_2 = x1_1 * other.x1_2 + x1_2 * other.x2_2 + x1_3 * other.x3_2;
		new_.x1_3 = x1_1 * other.x1_3 + x1_2 * other.x2_3 + x1_3 * other.x3_3;
		new_.x2_1 = x2_1 * other.x1_1 + x2_2 * other.x2_1 + x2_3 * other.x3_1;
		new_.x2_2 = x2_1 * other.x1_2 + x2_2 * other.x2_2 + x2_3 * other.x3_2;
		new_.x2_3 = x2_1 * other.x1_3 + x2_2 * other.x2_3 + x2_3 * other.x3_3;
		new_.x3_1 = x3_1 * other.x1_1 + x3_2 * other.x2_1 + x3_3 * other.x3_1;
		new_.x3_2 = x3_1 * other.x1_2 + x3_2 * other.x2_2 + x3_3 * other.x3_2;
		new_.x3_3 = x3_1 * other.x1_3 + x3_2 * other.x2_3 + x3_3 * other.x3_3;
		new_.x4_1 = x4_1 * other.x1_1 + x4_2 * other.x2_1 + x4_3 * other.x3_1;
		new_.x4_2 = x4_1 * other.x1_2 + x4_2 * other.x2_2 + x4_3 * other.x3_2;
		new_.x4_3 = x4_1 * other.x1_3 + x4_2 * other.x2_3 + x4_3 * other.x3_3;
		return new_;
	}
	template<Number T>
	template<Mat3x4 M>
	constexpr mat4x4<T> mat4x3<T>::operator*(const M& other) const {
		mat4x4<T> new_;
		new_.x1_1 = x1_1 * other.x1_1 + x1_2 * other.x2_1 + x1_3 * other.x3_1;
		new_.x1_2 = x1_1 * other.x1_2 + x1_2 * other.x2_2 + x1_3 * other.x3_2;
		new_.x1_3 = x1_1 * other.x1_3 + x1_2 * other.x2_3 + x1_3 * other.x3_3;
		new_.x1_4 = x1_1 * other.x1_4 + x1_2 * other.x2_4 + x1_3 * other.x3_4;
		new_.x2_1 = x2_1 * other.x1_1 + x2_2 * other.x2_1 + x2_3 * other.x3_1;
		new_.x2_2 = x2_1 * other.x1_2 + x2_2 * other.x2_2 + x2_3 * other.x3_2;
		new_.x2_3 = x2_1 * other.x1_3 + x2_2 * other.x2_3 + x2_3 * other.x3_3;
		new_.x2_4 = x2_1 * other.x1_4 + x2_2 * other.x2_4 + x2_3 * other.x3_4;
		new_.x3_1 = x3_1 * other.x1_1 + x3_2 * other.x2_1 + x3_3 * other.x3_1;
		new_.x3_2 = x3_1 * other.x1_2 + x3_2 * other.x2_2 + x3_3 * other.x3_2;
		new_.x3_3 = x3_1 * other.x1_3 + x3_2 * other.x2_3 + x3_3 * other.x3_3;
		new_.x3_4 = x3_1 * other.x1_4 + x3_2 * other.x2_4 + x3_3 * other.x3_4;
		new_.x4_1 = x4_1 * other.x1_1 + x4_2 * other.x2_1 + x4_3 * other.x3_1;
		new_.x4_2 = x4_1 * other.x1_2 + x4_2 * other.x2_2 + x4_3 * other.x3_2;
		new_.x4_3 = x4_1 * other.x1_3 + x4_2 * other.x2_3 + x4_3 * other.x3_3;
		new_.x4_4 = x4_1 * other.x1_4 + x4_2 * other.x2_4 + x4_3 * other.x3_4;
		return new_;
	}
	template<Number T>
	template<Mat4x3 M>
	constexpr bool mat4x3<T>::operator==(const M& other) const {
		return x1_1 == other.x1_1 and x1_2 == other.x1_2 and x1_3 == other.x1_3 and x2_1 == other.x2_1 and x2_2 == other.x2_2 and x2_3 == other.x2_3 and x3_1 == other.x3_1 and x3_2 == other.x3_2 and x3_3 == other.x3_3 and x4_1 == other.x4_1 and x4_2 == other.x4_2 and x4_3 == other.x4_3;
	}
	template<Number T>
	template<Mat4x3 M>
	constexpr bool mat4x3<T>::operator<(const M& other) const {
		return x1_1 < other.x1_1 and x1_2 < other.x1_2 and x1_3 < other.x1_3 and x2_1 < other.x2_1 and x2_2 < other.x2_2 and x2_3 < other.x2_3 and x3_1 < other.x3_1 and x3_2 < other.x3_2 and x3_3 < other.x3_3 and x4_1 < other.x4_1 and x4_2 < other.x4_2 and x4_3 < other.x4_3;
	}
	template<Number T>
	template<Mat4x3 M>
	constexpr bool mat4x3<T>::operator>(const M& other) const {
		return x1_1 > other.x1_1 and x1_2 > other.x1_2 and x1_3 > other.x1_3 and x2_1 > other.x2_1 and x2_2 > other.x2_2 and x2_3 > other.x2_3 and x3_1 > other.x3_1 and x3_2 > other.x3_2 and x3_3 > other.x3_3 and x4_1 > other.x4_1 and x4_2 > other.x4_2 and x4_3 > other.x4_3;
	}
	template<Number T>
	template<Mat4x3 M>
	constexpr bool mat4x3<T>::operator!=(const M& other) const {
		return x1_1 == other.x1_1 and x1_2 == other.x1_2 and x1_3 == other.x1_3 and x2_1 == other.x2_1 and x2_2 == other.x2_2 and x2_3 == other.x2_3 and x3_1 == other.x3_1 and x3_2 == other.x3_2 and x3_3 == other.x3_3 and x4_1 == other.x4_1 and x4_2 == other.x4_2 and x4_3 == other.x4_3;
	}
	template<Number T>
	template<Mat4x3 M>
	constexpr bool mat4x3<T>::operator<=(const M& other) const {
		return x1_1 > other.x1_1 and x1_2 > other.x1_2 and x1_3 > other.x1_3 and x2_1 > other.x2_1 and x2_2 > other.x2_2 and x2_3 > other.x2_3 and x3_1 > other.x3_1 and x3_2 > other.x3_2 and x3_3 > other.x3_3 and x4_1 > other.x4_1 and x4_2 > other.x4_2 and x4_3 > other.x4_3;
	}
	template<Number T>
	template<Mat4x3 M>
	constexpr bool mat4x3<T>::operator>=(const M& other) const {
		return x1_1 < other.x1_1 and x1_2 < other.x1_2 and x1_3 < other.x1_3 and x2_1 < other.x2_1 and x2_2 < other.x2_2 and x2_3 < other.x2_3 and x3_1 < other.x3_1 and x3_2 < other.x3_2 and x3_3 < other.x3_3 and x4_1 < other.x4_1 and x4_2 < other.x4_2 and x4_3 < other.x4_3;
	}
	template<Number T>
	template<Number N>
	constexpr bool mat4x3<T>::operator==(const N& other) const {
		return x1_1 == other and x1_2 == other and x1_3 == other and x2_1 == other and x2_2 == other and x2_3 == other and x3_1 == other and x3_2 == other and x3_3 == other and x4_1 == other and x4_2 == other and x4_3 == other;
	}
	template<Number T>
	template<Number N>
	constexpr bool mat4x3<T>::operator<(const N& other) const {
		return x1_1 < other and x1_2 < other and x1_3 < other and x2_1 < other and x2_2 < other and x2_3 < other and x3_1 < other and x3_2 < other and x3_3 < other and x4_1 < other and x4_2 < other and x4_3 < other;
	}
	template<Number T>
	template<Number N>
	constexpr bool mat4x3<T>::operator>(const N& other) const {
		return x1_1 > other and x1_2 > other and x1_3 > other and x2_1 > other and x2_2 > other and x2_3 > other and x3_1 > other and x3_2 > other and x3_3 > other and x4_1 > other and x4_2 > other and x4_3 > other;
	}
	template<Number T>
	template<Number N>
	constexpr bool mat4x3<T>::operator!=(const N& other) const {
		return x1_1 == other and x1_2 == other and x1_3 == other and x2_1 == other and x2_2 == other and x2_3 == other and x3_1 == other and x3_2 == other and x3_3 == other and x4_1 == other and x4_2 == other and x4_3 == other;
	}
	template<Number T>
	template<Number N>
	constexpr bool mat4x3<T>::operator<=(const N& other) const {
		return x1_1 > other and x1_2 > other and x1_3 > other and x2_1 > other and x2_2 > other and x2_3 > other and x3_1 > other and x3_2 > other and x3_3 > other and x4_1 > other and x4_2 > other and x4_3 > other;
	}
	template<Number T>
	template<Number N>
	constexpr bool mat4x3<T>::operator>=(const N& other) const {
		return x1_1 < other and x1_2 < other and x1_3 < other and x2_1 < other and x2_2 < other and x2_3 < other and x3_1 < other and x3_2 < other and x3_3 < other and x4_1 < other and x4_2 < other and x4_3 < other;
	}
	template<Number T>
	constexpr inline float mat4x3<T>::abs() const {
		return std::sqrt(static_cast<float>(x1_1 * x1_1) + static_cast<float>(x1_2 * x1_2) + static_cast<float>(x1_3 * x1_3) + static_cast<float>(x2_1 * x2_1) + static_cast<float>(x2_2 * x2_2) + static_cast<float>(x2_3 * x2_3) + static_cast<float>(x3_1 * x3_1) + static_cast<float>(x3_2 * x3_2) + static_cast<float>(x3_3 * x3_3) + static_cast<float>(x4_1 * x4_1) + static_cast<float>(x4_2 * x4_2) + static_cast<float>(x4_3 * x4_3));
	}
	template<Number T>
	constexpr inline T mat4x3<T>::min() const {
		return *std::min_element(cbegin(), cend());
	}
	template<Number T>
	constexpr inline T mat4x3<T>::max() const {
		return *std::max_element(cbegin(), cend());
	}
	template<Number T>
	template<Number N>
	constexpr inline T mat4x3<T>::dot(const mat4x3<N>& other) const {
		return x1_1 * static_cast<T>(other.x1_1) + x1_2 * static_cast<T>(other.x1_2) + x1_3 * static_cast<T>(other.x1_3) + x2_1 * static_cast<T>(other.x2_1) + x2_2 * static_cast<T>(other.x2_2) + x2_3 * static_cast<T>(other.x2_3) + x3_1 * static_cast<T>(other.x3_1) + x3_2 * static_cast<T>(other.x3_2) + x3_3 * static_cast<T>(other.x3_3) + x4_1 * static_cast<T>(other.x4_1) + x4_2 * static_cast<T>(other.x4_2) + x4_3 * static_cast<T>(other.x4_3);
	}
	template<Number T>
	constexpr T mat4x3<T>::operator[](std::size_t i) const {
		return *(&x1_1 + sizeof(T) * i);
	}
	template<Number T>
	constexpr T mat4x3<T>::at(std::size_t row, std::size_t col) const {
		return *(&x1_1 + (row * 4 + col * 3) * sizeof(T));
	}
	template<Number T>
	constexpr rvec3<T> mat4x3<T>::row(std::size_t i) const {
		return rvec3<T>(*(&x1_1 + (4 * 0 + i) * sizeof(T)), *(&x1_1 + (4 * 1 + i) * sizeof(T)), *(&x1_1 + (4 * 2 + i) * sizeof(T)));
	}
	template<Number T>
	constexpr vec4<T> mat4x3<T>::column(std::size_t i) const {
		return vec4<T>(*(&x1_1 + (3 * 0 + i) * sizeof(T)), *(&x1_1 + (3 * 1 + i) * sizeof(T)), *(&x1_1 + (3 * 2 + i) * sizeof(T)), *(&x1_1 + (3 * 3 + i) * sizeof(T)));
	}
	template<Number T>
	constexpr Iterator<T> mat4x3<T>::cbegin() const {
		return Iterator(const_cast<T*>(&x1_1));
	}
	template<Number T>
	constexpr Iterator<T> mat4x3<T>::cend() const {
		return Iterator(const_cast<T*>(&x4_3 + sizeof(T)));
	}
	template<Number T>
	constexpr Iterator<T> mat4x3<T>::begin() const {
		return Iterator(const_cast<T*>(&x1_1));
	}
	template<Number T>
	constexpr Iterator<T> mat4x3<T>::end() const {
		return Iterator(const_cast<T*>(&x4_3 + sizeof(T)));
	}


} // namespace gz

#include "mat4x3.tpp"