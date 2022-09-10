#include "vec4.hpp"

#include "mat4x2.hpp"
#include "mat4x3.hpp"
#include "mat4x4.hpp"
#include "rvec2.hpp"
#include "rvec3.hpp"
#include "rvec4.hpp"

#include <cmath>
#include <algorithm>
#include <cstdint>

namespace gz {

	//
	// CLASS vec4
	//
	template<Number T>
	template<Number N>
	constexpr void vec4<T>::operator=(const vec4<N>& other) {
			x = static_cast<T>(other.x);
			y = static_cast<T>(other.y);
			z = static_cast<T>(other.z);
			w = static_cast<T>(other.w);

	}
	template<Number T>
	template<Number N>
	constexpr void vec4<T>::operator=(const N& other) {
			x = static_cast<T>(other);
			y = static_cast<T>(other);
			z = static_cast<T>(other);
			w = static_cast<T>(other);

	}
	template<Number T>
	template<ColumnVector4 C>
	constexpr vec4<T> vec4<T>::operator+(const C& other) const {
		return vec4<T>(x + static_cast<T>(other.x), y + static_cast<T>(other.y), z + static_cast<T>(other.z), w + static_cast<T>(other.w));
	}
	template<Number T>
	template<ColumnVector4 C>
	constexpr vec4<T> vec4<T>::operator-(const C& other) const {
		return vec4<T>(x - static_cast<T>(other.x), y - static_cast<T>(other.y), z - static_cast<T>(other.z), w - static_cast<T>(other.w));
	}
	template<Number T>
	template<ColumnVector4 C>
	constexpr vec4<T> vec4<T>::operator%(const C& other) const {
		return vec4<T>(x % static_cast<T>(other.x), y % static_cast<T>(other.y), z % static_cast<T>(other.z), w % static_cast<T>(other.w));
	}
	template<Number T>
	template<ColumnVector4 C>
	constexpr vec4<T> vec4<T>::compWiseMult(const C& other) const {
		return vec4<T>(x * static_cast<T>(other.x), y * static_cast<T>(other.y), z * static_cast<T>(other.z), w * static_cast<T>(other.w));
	}
	template<Number T>
	template<ColumnVector4 C>
	constexpr vec4<T> vec4<T>::compWiseDiv(const C& other) const {
		return vec4<T>(x / static_cast<T>(other.x), y / static_cast<T>(other.y), z / static_cast<T>(other.z), w / static_cast<T>(other.w));
	}
	template<Number T>
	template<ColumnVector4 C>
	constexpr void vec4<T>::operator+=(const C& other) {
			x += static_cast<T>(other.x);
			y += static_cast<T>(other.y);
			z += static_cast<T>(other.z);
			w += static_cast<T>(other.w);
	}
	template<Number T>
	template<ColumnVector4 C>
	constexpr void vec4<T>::operator-=(const C& other) {
			x -= static_cast<T>(other.x);
			y -= static_cast<T>(other.y);
			z -= static_cast<T>(other.z);
			w -= static_cast<T>(other.w);
	}
	template<Number T>
	template<ColumnVector4 C>
	constexpr void vec4<T>::operator%=(const C& other) {
			x %= static_cast<T>(other.x);
			y %= static_cast<T>(other.y);
			z %= static_cast<T>(other.z);
			w %= static_cast<T>(other.w);
	}
	template<Number T>
	template<ColumnVector4 C>
	constexpr void vec4<T>::compWiseAssMult(const C& other) {
			x *= static_cast<T>(other.x);
			y *= static_cast<T>(other.y);
			z *= static_cast<T>(other.z);
			w *= static_cast<T>(other.w);
	}
	template<Number T>
	template<ColumnVector4 C>
	constexpr void vec4<T>::compWiseAssDiv(const C& other) {
			x /= static_cast<T>(other.x);
			y /= static_cast<T>(other.y);
			z /= static_cast<T>(other.z);
			w /= static_cast<T>(other.w);
	}
	template<Number T>
	template<Number N>
	constexpr vec4<T> vec4<T>::operator+(const N& other) const {
		return vec4<T>(x + static_cast<T>(other), y + static_cast<T>(other), z + static_cast<T>(other), w + static_cast<T>(other));
	}
	template<Number T>
	template<Number N>
	constexpr vec4<T> vec4<T>::operator-(const N& other) const {
		return vec4<T>(x - static_cast<T>(other), y - static_cast<T>(other), z - static_cast<T>(other), w - static_cast<T>(other));
	}
	template<Number T>
	template<Number N>
	constexpr vec4<T> vec4<T>::operator%(const N& other) const {
		return vec4<T>(x % static_cast<T>(other), y % static_cast<T>(other), z % static_cast<T>(other), w % static_cast<T>(other));
	}
	template<Number T>
	template<Number N>
	constexpr vec4<T> vec4<T>::compWiseMult(const N& other) const {
		return vec4<T>(x * static_cast<T>(other), y * static_cast<T>(other), z * static_cast<T>(other), w * static_cast<T>(other));
	}
	template<Number T>
	template<Number N>
	constexpr vec4<T> vec4<T>::compWiseDiv(const N& other) const {
		return vec4<T>(x / static_cast<T>(other), y / static_cast<T>(other), z / static_cast<T>(other), w / static_cast<T>(other));
	}
	template<Number T>
	template<Number N>
	constexpr void vec4<T>::operator+=(const N& other) {
			x += static_cast<T>(other);
			y += static_cast<T>(other);
			z += static_cast<T>(other);
			w += static_cast<T>(other);
	}
	template<Number T>
	template<Number N>
	constexpr void vec4<T>::operator-=(const N& other) {
			x -= static_cast<T>(other);
			y -= static_cast<T>(other);
			z -= static_cast<T>(other);
			w -= static_cast<T>(other);
	}
	template<Number T>
	template<Number N>
	constexpr void vec4<T>::operator%=(const N& other) {
			x %= static_cast<T>(other);
			y %= static_cast<T>(other);
			z %= static_cast<T>(other);
			w %= static_cast<T>(other);
	}
	template<Number T>
	template<Number N>
	constexpr void vec4<T>::compWiseAssMult(const N& other) {
			x *= static_cast<T>(other);
			y *= static_cast<T>(other);
			z *= static_cast<T>(other);
			w *= static_cast<T>(other);
	}
	template<Number T>
	template<Number N>
	constexpr void vec4<T>::compWiseAssDiv(const N& other) {
			x /= static_cast<T>(other);
			y /= static_cast<T>(other);
			z /= static_cast<T>(other);
			w /= static_cast<T>(other);
	}
	template<Number T>
	template<RowVector2 R>
	constexpr mat4x2<T> vec4<T>::operator*(const R& other) const {
		mat4x2<T> new_;
		new_.x1_1 = x * other.x;
		new_.x1_2 = x * other.y;
		new_.x2_1 = y * other.x;
		new_.x2_2 = y * other.y;
		new_.x3_1 = z * other.x;
		new_.x3_2 = z * other.y;
		new_.x4_1 = w * other.x;
		new_.x4_2 = w * other.y;
		return new_;
	}
	template<Number T>
	template<RowVector3 R>
	constexpr mat4x3<T> vec4<T>::operator*(const R& other) const {
		mat4x3<T> new_;
		new_.x1_1 = x * other.x;
		new_.x1_2 = x * other.y;
		new_.x1_3 = x * other.z;
		new_.x2_1 = y * other.x;
		new_.x2_2 = y * other.y;
		new_.x2_3 = y * other.z;
		new_.x3_1 = z * other.x;
		new_.x3_2 = z * other.y;
		new_.x3_3 = z * other.z;
		new_.x4_1 = w * other.x;
		new_.x4_2 = w * other.y;
		new_.x4_3 = w * other.z;
		return new_;
	}
	template<Number T>
	template<RowVector4 R>
	constexpr mat4x4<T> vec4<T>::operator*(const R& other) const {
		mat4x4<T> new_;
		new_.x1_1 = x * other.x;
		new_.x1_2 = x * other.y;
		new_.x1_3 = x * other.z;
		new_.x1_4 = x * other.w;
		new_.x2_1 = y * other.x;
		new_.x2_2 = y * other.y;
		new_.x2_3 = y * other.z;
		new_.x2_4 = y * other.w;
		new_.x3_1 = z * other.x;
		new_.x3_2 = z * other.y;
		new_.x3_3 = z * other.z;
		new_.x3_4 = z * other.w;
		new_.x4_1 = w * other.x;
		new_.x4_2 = w * other.y;
		new_.x4_3 = w * other.z;
		new_.x4_4 = w * other.w;
		return new_;
	}
	template<Number T>
	template<ColumnVector4 C>
	constexpr bool vec4<T>::operator==(const C& other) const {
		return x == other.x and y == other.y and z == other.z and w == other.w;
	}
	template<Number T>
	template<ColumnVector4 C>
	constexpr bool vec4<T>::operator<(const C& other) const {
		return x < other.x and y < other.y and z < other.z and w < other.w;
	}
	template<Number T>
	template<ColumnVector4 C>
	constexpr bool vec4<T>::operator>(const C& other) const {
		return x > other.x and y > other.y and z > other.z and w > other.w;
	}
	template<Number T>
	template<ColumnVector4 C>
	constexpr bool vec4<T>::operator!=(const C& other) const {
		return x == other.x and y == other.y and z == other.z and w == other.w;
	}
	template<Number T>
	template<ColumnVector4 C>
	constexpr bool vec4<T>::operator<=(const C& other) const {
		return x > other.x and y > other.y and z > other.z and w > other.w;
	}
	template<Number T>
	template<ColumnVector4 C>
	constexpr bool vec4<T>::operator>=(const C& other) const {
		return x < other.x and y < other.y and z < other.z and w < other.w;
	}
	template<Number T>
	template<Number N>
	constexpr bool vec4<T>::operator==(const N& other) const {
		return x == other and y == other and z == other and w == other;
	}
	template<Number T>
	template<Number N>
	constexpr bool vec4<T>::operator<(const N& other) const {
		return x < other and y < other and z < other and w < other;
	}
	template<Number T>
	template<Number N>
	constexpr bool vec4<T>::operator>(const N& other) const {
		return x > other and y > other and z > other and w > other;
	}
	template<Number T>
	template<Number N>
	constexpr bool vec4<T>::operator!=(const N& other) const {
		return x == other and y == other and z == other and w == other;
	}
	template<Number T>
	template<Number N>
	constexpr bool vec4<T>::operator<=(const N& other) const {
		return x > other and y > other and z > other and w > other;
	}
	template<Number T>
	template<Number N>
	constexpr bool vec4<T>::operator>=(const N& other) const {
		return x < other and y < other and z < other and w < other;
	}
	template<Number T>
	constexpr inline float vec4<T>::abs() const {
		return std::sqrt(static_cast<float>(x * x) + static_cast<float>(y * y) + static_cast<float>(z * z) + static_cast<float>(w * w));
	}
	template<Number T>
	constexpr inline T vec4<T>::min() const {
		return *std::min_element(cbegin(), cend());
	}
	template<Number T>
	constexpr inline T vec4<T>::max() const {
		return *std::max_element(cbegin(), cend());
	}
	template<Number T>
	template<Number N>
	constexpr inline T vec4<T>::dot(const vec4<N>& other) const {
		return x * static_cast<T>(other.x) + y * static_cast<T>(other.y) + z * static_cast<T>(other.z) + w * static_cast<T>(other.w);
	}
	template<Number T>
	constexpr T vec4<T>::operator[](std::size_t i) const {
		return *(&x + sizeof(T) * i);
	}
	template<Number T>
	constexpr Iterator<T> vec4<T>::cbegin() const {
		return Iterator(const_cast<T*>(&x));
	}
	template<Number T>
	constexpr Iterator<T> vec4<T>::cend() const {
		return Iterator(const_cast<T*>(&w + sizeof(T)));
	}
	template<Number T>
	constexpr Iterator<T> vec4<T>::begin() const {
		return Iterator(const_cast<T*>(&x));
	}
	template<Number T>
	constexpr Iterator<T> vec4<T>::end() const {
		return Iterator(const_cast<T*>(&w + sizeof(T)));
	}


} // namespace gz

#include "vec4.tpp"