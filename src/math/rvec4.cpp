#include "rvec4.hpp"

#include "mat4x2.hpp"
#include "mat4x3.hpp"
#include "mat4x4.hpp"
#include "rvec2.hpp"
#include "rvec3.hpp"
#include "vec4.hpp"

#include <cmath>
#include <algorithm>
#include <cstdint>

namespace gz {

	//
	// CLASS rvec4
	//
	template<Number T>
	template<Number N>
	constexpr void rvec4<T>::operator=(const rvec4<N>& other) {
			x = static_cast<T>(other.x);
			y = static_cast<T>(other.y);
			z = static_cast<T>(other.z);
			w = static_cast<T>(other.w);

	}
	template<Number T>
	template<Number N>
	constexpr void rvec4<T>::operator=(const N& other) {
			x = static_cast<T>(other);
			y = static_cast<T>(other);
			z = static_cast<T>(other);
			w = static_cast<T>(other);

	}
	template<Number T>
	template<RowVector4 R>
	constexpr rvec4<T> rvec4<T>::operator+(const R& other) const {
		return rvec4<T>(x + static_cast<T>(other.x), y + static_cast<T>(other.y), z + static_cast<T>(other.z), w + static_cast<T>(other.w));
	}
	template<Number T>
	template<RowVector4 R>
	constexpr rvec4<T> rvec4<T>::operator-(const R& other) const {
		return rvec4<T>(x - static_cast<T>(other.x), y - static_cast<T>(other.y), z - static_cast<T>(other.z), w - static_cast<T>(other.w));
	}
	template<Number T>
	template<RowVector4 R>
	constexpr rvec4<T> rvec4<T>::operator%(const R& other) const {
		return rvec4<T>(x % static_cast<T>(other.x), y % static_cast<T>(other.y), z % static_cast<T>(other.z), w % static_cast<T>(other.w));
	}
	template<Number T>
	template<RowVector4 R>
	constexpr rvec4<T> rvec4<T>::compWiseMult(const R& other) const {
		return rvec4<T>(x * static_cast<T>(other.x), y * static_cast<T>(other.y), z * static_cast<T>(other.z), w * static_cast<T>(other.w));
	}
	template<Number T>
	template<RowVector4 R>
	constexpr rvec4<T> rvec4<T>::compWiseDiv(const R& other) const {
		return rvec4<T>(x / static_cast<T>(other.x), y / static_cast<T>(other.y), z / static_cast<T>(other.z), w / static_cast<T>(other.w));
	}
	template<Number T>
	template<RowVector4 R>
	constexpr void rvec4<T>::operator+=(const R& other) {
			x += static_cast<T>(other.x);
			y += static_cast<T>(other.y);
			z += static_cast<T>(other.z);
			w += static_cast<T>(other.w);
	}
	template<Number T>
	template<RowVector4 R>
	constexpr void rvec4<T>::operator-=(const R& other) {
			x -= static_cast<T>(other.x);
			y -= static_cast<T>(other.y);
			z -= static_cast<T>(other.z);
			w -= static_cast<T>(other.w);
	}
	template<Number T>
	template<RowVector4 R>
	constexpr void rvec4<T>::operator%=(const R& other) {
			x %= static_cast<T>(other.x);
			y %= static_cast<T>(other.y);
			z %= static_cast<T>(other.z);
			w %= static_cast<T>(other.w);
	}
	template<Number T>
	template<RowVector4 R>
	constexpr void rvec4<T>::compWiseAssMult(const R& other) {
			x *= static_cast<T>(other.x);
			y *= static_cast<T>(other.y);
			z *= static_cast<T>(other.z);
			w *= static_cast<T>(other.w);
	}
	template<Number T>
	template<RowVector4 R>
	constexpr void rvec4<T>::compWiseAssDiv(const R& other) {
			x /= static_cast<T>(other.x);
			y /= static_cast<T>(other.y);
			z /= static_cast<T>(other.z);
			w /= static_cast<T>(other.w);
	}
	template<Number T>
	template<Number N>
	constexpr rvec4<T> rvec4<T>::operator+(const N& other) const {
		return rvec4<T>(x + static_cast<T>(other), y + static_cast<T>(other), z + static_cast<T>(other), w + static_cast<T>(other));
	}
	template<Number T>
	template<Number N>
	constexpr rvec4<T> rvec4<T>::operator-(const N& other) const {
		return rvec4<T>(x - static_cast<T>(other), y - static_cast<T>(other), z - static_cast<T>(other), w - static_cast<T>(other));
	}
	template<Number T>
	template<Number N>
	constexpr rvec4<T> rvec4<T>::operator%(const N& other) const {
		return rvec4<T>(x % static_cast<T>(other), y % static_cast<T>(other), z % static_cast<T>(other), w % static_cast<T>(other));
	}
	template<Number T>
	template<Number N>
	constexpr rvec4<T> rvec4<T>::compWiseMult(const N& other) const {
		return rvec4<T>(x * static_cast<T>(other), y * static_cast<T>(other), z * static_cast<T>(other), w * static_cast<T>(other));
	}
	template<Number T>
	template<Number N>
	constexpr rvec4<T> rvec4<T>::compWiseDiv(const N& other) const {
		return rvec4<T>(x / static_cast<T>(other), y / static_cast<T>(other), z / static_cast<T>(other), w / static_cast<T>(other));
	}
	template<Number T>
	template<Number N>
	constexpr void rvec4<T>::operator+=(const N& other) {
			x += static_cast<T>(other);
			y += static_cast<T>(other);
			z += static_cast<T>(other);
			w += static_cast<T>(other);
	}
	template<Number T>
	template<Number N>
	constexpr void rvec4<T>::operator-=(const N& other) {
			x -= static_cast<T>(other);
			y -= static_cast<T>(other);
			z -= static_cast<T>(other);
			w -= static_cast<T>(other);
	}
	template<Number T>
	template<Number N>
	constexpr void rvec4<T>::operator%=(const N& other) {
			x %= static_cast<T>(other);
			y %= static_cast<T>(other);
			z %= static_cast<T>(other);
			w %= static_cast<T>(other);
	}
	template<Number T>
	template<Number N>
	constexpr void rvec4<T>::compWiseAssMult(const N& other) {
			x *= static_cast<T>(other);
			y *= static_cast<T>(other);
			z *= static_cast<T>(other);
			w *= static_cast<T>(other);
	}
	template<Number T>
	template<Number N>
	constexpr void rvec4<T>::compWiseAssDiv(const N& other) {
			x /= static_cast<T>(other);
			y /= static_cast<T>(other);
			z /= static_cast<T>(other);
			w /= static_cast<T>(other);
	}
	template<Number T>
	template<Mat4x2 M>
	constexpr rvec2<T> rvec4<T>::operator*(const M& other) const {
		rvec2<T> new_;
		new_.x = x * other.x1_1 + y * other.x2_1 + z * other.x3_1 + w * other.x4_1;
		new_.y = x * other.x1_2 + y * other.x2_2 + z * other.x3_2 + w * other.x4_2;
		return new_;
	}
	template<Number T>
	template<Mat4x3 M>
	constexpr rvec3<T> rvec4<T>::operator*(const M& other) const {
		rvec3<T> new_;
		new_.x = x * other.x1_1 + y * other.x2_1 + z * other.x3_1 + w * other.x4_1;
		new_.y = x * other.x1_2 + y * other.x2_2 + z * other.x3_2 + w * other.x4_2;
		new_.z = x * other.x1_3 + y * other.x2_3 + z * other.x3_3 + w * other.x4_3;
		return new_;
	}
	template<Number T>
	template<Mat4x4 M>
	constexpr rvec4<T> rvec4<T>::operator*(const M& other) const {
		rvec4<T> new_;
		new_.x = x * other.x1_1 + y * other.x2_1 + z * other.x3_1 + w * other.x4_1;
		new_.y = x * other.x1_2 + y * other.x2_2 + z * other.x3_2 + w * other.x4_2;
		new_.z = x * other.x1_3 + y * other.x2_3 + z * other.x3_3 + w * other.x4_3;
		new_.w = x * other.x1_4 + y * other.x2_4 + z * other.x3_4 + w * other.x4_4;
		return new_;
	}
	template<Number T>
	template<RowVector4 R>
	constexpr bool rvec4<T>::operator==(const R& other) const {
		return x == other.x and y == other.y and z == other.z and w == other.w;
	}
	template<Number T>
	template<RowVector4 R>
	constexpr bool rvec4<T>::operator<(const R& other) const {
		return x < other.x and y < other.y and z < other.z and w < other.w;
	}
	template<Number T>
	template<RowVector4 R>
	constexpr bool rvec4<T>::operator>(const R& other) const {
		return x > other.x and y > other.y and z > other.z and w > other.w;
	}
	template<Number T>
	template<RowVector4 R>
	constexpr bool rvec4<T>::operator!=(const R& other) const {
		return x == other.x and y == other.y and z == other.z and w == other.w;
	}
	template<Number T>
	template<RowVector4 R>
	constexpr bool rvec4<T>::operator<=(const R& other) const {
		return x > other.x and y > other.y and z > other.z and w > other.w;
	}
	template<Number T>
	template<RowVector4 R>
	constexpr bool rvec4<T>::operator>=(const R& other) const {
		return x < other.x and y < other.y and z < other.z and w < other.w;
	}
	template<Number T>
	template<Number N>
	constexpr bool rvec4<T>::operator==(const N& other) const {
		return x == other and y == other and z == other and w == other;
	}
	template<Number T>
	template<Number N>
	constexpr bool rvec4<T>::operator<(const N& other) const {
		return x < other and y < other and z < other and w < other;
	}
	template<Number T>
	template<Number N>
	constexpr bool rvec4<T>::operator>(const N& other) const {
		return x > other and y > other and z > other and w > other;
	}
	template<Number T>
	template<Number N>
	constexpr bool rvec4<T>::operator!=(const N& other) const {
		return x == other and y == other and z == other and w == other;
	}
	template<Number T>
	template<Number N>
	constexpr bool rvec4<T>::operator<=(const N& other) const {
		return x > other and y > other and z > other and w > other;
	}
	template<Number T>
	template<Number N>
	constexpr bool rvec4<T>::operator>=(const N& other) const {
		return x < other and y < other and z < other and w < other;
	}
	template<Number T>
	constexpr inline float rvec4<T>::abs() const {
		return std::sqrt(static_cast<float>(x * x) + static_cast<float>(y * y) + static_cast<float>(z * z) + static_cast<float>(w * w));
	}
	template<Number T>
	constexpr inline T rvec4<T>::min() const {
		return *std::min_element(cbegin(), cend());
	}
	template<Number T>
	constexpr inline T rvec4<T>::max() const {
		return *std::max_element(cbegin(), cend());
	}
	template<Number T>
	template<Number N>
	constexpr inline T rvec4<T>::dot(const rvec4<N>& other) const {
		return x * static_cast<T>(other.x) + y * static_cast<T>(other.y) + z * static_cast<T>(other.z) + w * static_cast<T>(other.w);
	}
	template<Number T>
	constexpr T rvec4<T>::operator[](std::size_t i) const {
		return *(&x + sizeof(T) * i);
	}
	template<Number T>
	constexpr Iterator<T> rvec4<T>::cbegin() const {
		return Iterator(const_cast<T*>(&x));
	}
	template<Number T>
	constexpr Iterator<T> rvec4<T>::cend() const {
		return Iterator(const_cast<T*>(&w + sizeof(T)));
	}
	template<Number T>
	constexpr Iterator<T> rvec4<T>::begin() const {
		return Iterator(const_cast<T*>(&x));
	}
	template<Number T>
	constexpr Iterator<T> rvec4<T>::end() const {
		return Iterator(const_cast<T*>(&w + sizeof(T)));
	}


} // namespace gz

#include "rvec4.tpp"