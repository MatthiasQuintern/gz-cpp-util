#include "mat2x2.hpp"

#include "mat2x3.hpp"
#include "mat2x4.hpp"
#include "rvec2.hpp"
#include "vec2.hpp"

#include <cmath>
#include <algorithm>
#include <cstdint>

namespace gz {

	//
	// CLASS mat2x2
	//
	template<Number T>
	template<Number N>
	constexpr void mat2x2<T>::operator=(const mat2x2<N>& other) {
			x1_1 = static_cast<T>(other.x1_1);
			x1_2 = static_cast<T>(other.x1_2);
			x2_1 = static_cast<T>(other.x2_1);
			x2_2 = static_cast<T>(other.x2_2);

	}
	template<Number T>
	template<Number N>
	constexpr void mat2x2<T>::operator=(const N& other) {
			x1_1 = static_cast<T>(other);
			x1_2 = static_cast<T>(other);
			x2_1 = static_cast<T>(other);
			x2_2 = static_cast<T>(other);

	}
	template<Number T>
	template<Mat2x2 M>
	constexpr mat2x2<T> mat2x2<T>::operator+(const M& other) const {
		return mat2x2<T>(x1_1 + static_cast<T>(other.x1_1), x1_2 + static_cast<T>(other.x1_2), x2_1 + static_cast<T>(other.x2_1), x2_2 + static_cast<T>(other.x2_2));
	}
	template<Number T>
	template<Mat2x2 M>
	constexpr mat2x2<T> mat2x2<T>::operator-(const M& other) const {
		return mat2x2<T>(x1_1 - static_cast<T>(other.x1_1), x1_2 - static_cast<T>(other.x1_2), x2_1 - static_cast<T>(other.x2_1), x2_2 - static_cast<T>(other.x2_2));
	}
	template<Number T>
	template<Mat2x2 M>
	constexpr mat2x2<T> mat2x2<T>::operator%(const M& other) const {
		return mat2x2<T>(x1_1 % static_cast<T>(other.x1_1), x1_2 % static_cast<T>(other.x1_2), x2_1 % static_cast<T>(other.x2_1), x2_2 % static_cast<T>(other.x2_2));
	}
	template<Number T>
	template<Mat2x2 M>
	constexpr mat2x2<T> mat2x2<T>::compWiseMult(const M& other) const {
		return mat2x2<T>(x1_1 * static_cast<T>(other.x1_1), x1_2 * static_cast<T>(other.x1_2), x2_1 * static_cast<T>(other.x2_1), x2_2 * static_cast<T>(other.x2_2));
	}
	template<Number T>
	template<Mat2x2 M>
	constexpr mat2x2<T> mat2x2<T>::compWiseDiv(const M& other) const {
		return mat2x2<T>(x1_1 / static_cast<T>(other.x1_1), x1_2 / static_cast<T>(other.x1_2), x2_1 / static_cast<T>(other.x2_1), x2_2 / static_cast<T>(other.x2_2));
	}
	template<Number T>
	template<Mat2x2 M>
	constexpr void mat2x2<T>::operator+=(const M& other) {
			x1_1 += static_cast<T>(other.x1_1);
			x1_2 += static_cast<T>(other.x1_2);
			x2_1 += static_cast<T>(other.x2_1);
			x2_2 += static_cast<T>(other.x2_2);
	}
	template<Number T>
	template<Mat2x2 M>
	constexpr void mat2x2<T>::operator-=(const M& other) {
			x1_1 -= static_cast<T>(other.x1_1);
			x1_2 -= static_cast<T>(other.x1_2);
			x2_1 -= static_cast<T>(other.x2_1);
			x2_2 -= static_cast<T>(other.x2_2);
	}
	template<Number T>
	template<Mat2x2 M>
	constexpr void mat2x2<T>::operator%=(const M& other) {
			x1_1 %= static_cast<T>(other.x1_1);
			x1_2 %= static_cast<T>(other.x1_2);
			x2_1 %= static_cast<T>(other.x2_1);
			x2_2 %= static_cast<T>(other.x2_2);
	}
	template<Number T>
	template<Mat2x2 M>
	constexpr void mat2x2<T>::compWiseAssMult(const M& other) {
			x1_1 *= static_cast<T>(other.x1_1);
			x1_2 *= static_cast<T>(other.x1_2);
			x2_1 *= static_cast<T>(other.x2_1);
			x2_2 *= static_cast<T>(other.x2_2);
	}
	template<Number T>
	template<Mat2x2 M>
	constexpr void mat2x2<T>::compWiseAssDiv(const M& other) {
			x1_1 /= static_cast<T>(other.x1_1);
			x1_2 /= static_cast<T>(other.x1_2);
			x2_1 /= static_cast<T>(other.x2_1);
			x2_2 /= static_cast<T>(other.x2_2);
	}
	template<Number T>
	template<Number N>
	constexpr mat2x2<T> mat2x2<T>::operator+(const N& other) const {
		return mat2x2<T>(x1_1 + static_cast<T>(other), x1_2 + static_cast<T>(other), x2_1 + static_cast<T>(other), x2_2 + static_cast<T>(other));
	}
	template<Number T>
	template<Number N>
	constexpr mat2x2<T> mat2x2<T>::operator-(const N& other) const {
		return mat2x2<T>(x1_1 - static_cast<T>(other), x1_2 - static_cast<T>(other), x2_1 - static_cast<T>(other), x2_2 - static_cast<T>(other));
	}
	template<Number T>
	template<Number N>
	constexpr mat2x2<T> mat2x2<T>::operator%(const N& other) const {
		return mat2x2<T>(x1_1 % static_cast<T>(other), x1_2 % static_cast<T>(other), x2_1 % static_cast<T>(other), x2_2 % static_cast<T>(other));
	}
	template<Number T>
	template<Number N>
	constexpr mat2x2<T> mat2x2<T>::compWiseMult(const N& other) const {
		return mat2x2<T>(x1_1 * static_cast<T>(other), x1_2 * static_cast<T>(other), x2_1 * static_cast<T>(other), x2_2 * static_cast<T>(other));
	}
	template<Number T>
	template<Number N>
	constexpr mat2x2<T> mat2x2<T>::compWiseDiv(const N& other) const {
		return mat2x2<T>(x1_1 / static_cast<T>(other), x1_2 / static_cast<T>(other), x2_1 / static_cast<T>(other), x2_2 / static_cast<T>(other));
	}
	template<Number T>
	template<Number N>
	constexpr void mat2x2<T>::operator+=(const N& other) {
			x1_1 += static_cast<T>(other);
			x1_2 += static_cast<T>(other);
			x2_1 += static_cast<T>(other);
			x2_2 += static_cast<T>(other);
	}
	template<Number T>
	template<Number N>
	constexpr void mat2x2<T>::operator-=(const N& other) {
			x1_1 -= static_cast<T>(other);
			x1_2 -= static_cast<T>(other);
			x2_1 -= static_cast<T>(other);
			x2_2 -= static_cast<T>(other);
	}
	template<Number T>
	template<Number N>
	constexpr void mat2x2<T>::operator%=(const N& other) {
			x1_1 %= static_cast<T>(other);
			x1_2 %= static_cast<T>(other);
			x2_1 %= static_cast<T>(other);
			x2_2 %= static_cast<T>(other);
	}
	template<Number T>
	template<Number N>
	constexpr void mat2x2<T>::compWiseAssMult(const N& other) {
			x1_1 *= static_cast<T>(other);
			x1_2 *= static_cast<T>(other);
			x2_1 *= static_cast<T>(other);
			x2_2 *= static_cast<T>(other);
	}
	template<Number T>
	template<Number N>
	constexpr void mat2x2<T>::compWiseAssDiv(const N& other) {
			x1_1 /= static_cast<T>(other);
			x1_2 /= static_cast<T>(other);
			x2_1 /= static_cast<T>(other);
			x2_2 /= static_cast<T>(other);
	}
	template<Number T>
	template<ColumnVector2 C>
	constexpr vec2<T> mat2x2<T>::operator*(const C& other) const {
		vec2<T> new_;
		new_.x = x1_1 * other.x + x1_2 * other.y;
		new_.y = x2_1 * other.x + x2_2 * other.y;
		return new_;
	}
	template<Number T>
	template<Mat2x2 M>
	constexpr mat2x2<T> mat2x2<T>::operator*(const M& other) const {
		mat2x2<T> new_;
		new_.x1_1 = x1_1 * other.x1_1 + x1_2 * other.x2_1;
		new_.x1_2 = x1_1 * other.x1_2 + x1_2 * other.x2_2;
		new_.x2_1 = x2_1 * other.x1_1 + x2_2 * other.x2_1;
		new_.x2_2 = x2_1 * other.x1_2 + x2_2 * other.x2_2;
		return new_;
	}
	template<Number T>
	template<Mat2x3 M>
	constexpr mat2x3<T> mat2x2<T>::operator*(const M& other) const {
		mat2x3<T> new_;
		new_.x1_1 = x1_1 * other.x1_1 + x1_2 * other.x2_1;
		new_.x1_2 = x1_1 * other.x1_2 + x1_2 * other.x2_2;
		new_.x1_3 = x1_1 * other.x1_3 + x1_2 * other.x2_3;
		new_.x2_1 = x2_1 * other.x1_1 + x2_2 * other.x2_1;
		new_.x2_2 = x2_1 * other.x1_2 + x2_2 * other.x2_2;
		new_.x2_3 = x2_1 * other.x1_3 + x2_2 * other.x2_3;
		return new_;
	}
	template<Number T>
	template<Mat2x4 M>
	constexpr mat2x4<T> mat2x2<T>::operator*(const M& other) const {
		mat2x4<T> new_;
		new_.x1_1 = x1_1 * other.x1_1 + x1_2 * other.x2_1;
		new_.x1_2 = x1_1 * other.x1_2 + x1_2 * other.x2_2;
		new_.x1_3 = x1_1 * other.x1_3 + x1_2 * other.x2_3;
		new_.x1_4 = x1_1 * other.x1_4 + x1_2 * other.x2_4;
		new_.x2_1 = x2_1 * other.x1_1 + x2_2 * other.x2_1;
		new_.x2_2 = x2_1 * other.x1_2 + x2_2 * other.x2_2;
		new_.x2_3 = x2_1 * other.x1_3 + x2_2 * other.x2_3;
		new_.x2_4 = x2_1 * other.x1_4 + x2_2 * other.x2_4;
		return new_;
	}
	template<Number T>
	template<Mat2x2 M>
	constexpr bool mat2x2<T>::operator==(const M& other) const {
		return x1_1 == other.x1_1 and x1_2 == other.x1_2 and x2_1 == other.x2_1 and x2_2 == other.x2_2;
	}
	template<Number T>
	template<Mat2x2 M>
	constexpr bool mat2x2<T>::operator<(const M& other) const {
		return x1_1 < other.x1_1 and x1_2 < other.x1_2 and x2_1 < other.x2_1 and x2_2 < other.x2_2;
	}
	template<Number T>
	template<Mat2x2 M>
	constexpr bool mat2x2<T>::operator>(const M& other) const {
		return x1_1 > other.x1_1 and x1_2 > other.x1_2 and x2_1 > other.x2_1 and x2_2 > other.x2_2;
	}
	template<Number T>
	template<Mat2x2 M>
	constexpr bool mat2x2<T>::operator!=(const M& other) const {
		return x1_1 == other.x1_1 and x1_2 == other.x1_2 and x2_1 == other.x2_1 and x2_2 == other.x2_2;
	}
	template<Number T>
	template<Mat2x2 M>
	constexpr bool mat2x2<T>::operator<=(const M& other) const {
		return x1_1 > other.x1_1 and x1_2 > other.x1_2 and x2_1 > other.x2_1 and x2_2 > other.x2_2;
	}
	template<Number T>
	template<Mat2x2 M>
	constexpr bool mat2x2<T>::operator>=(const M& other) const {
		return x1_1 < other.x1_1 and x1_2 < other.x1_2 and x2_1 < other.x2_1 and x2_2 < other.x2_2;
	}
	template<Number T>
	template<Number N>
	constexpr bool mat2x2<T>::operator==(const N& other) const {
		return x1_1 == other and x1_2 == other and x2_1 == other and x2_2 == other;
	}
	template<Number T>
	template<Number N>
	constexpr bool mat2x2<T>::operator<(const N& other) const {
		return x1_1 < other and x1_2 < other and x2_1 < other and x2_2 < other;
	}
	template<Number T>
	template<Number N>
	constexpr bool mat2x2<T>::operator>(const N& other) const {
		return x1_1 > other and x1_2 > other and x2_1 > other and x2_2 > other;
	}
	template<Number T>
	template<Number N>
	constexpr bool mat2x2<T>::operator!=(const N& other) const {
		return x1_1 == other and x1_2 == other and x2_1 == other and x2_2 == other;
	}
	template<Number T>
	template<Number N>
	constexpr bool mat2x2<T>::operator<=(const N& other) const {
		return x1_1 > other and x1_2 > other and x2_1 > other and x2_2 > other;
	}
	template<Number T>
	template<Number N>
	constexpr bool mat2x2<T>::operator>=(const N& other) const {
		return x1_1 < other and x1_2 < other and x2_1 < other and x2_2 < other;
	}
	template<Number T>
	constexpr inline float mat2x2<T>::abs() const {
		return std::sqrt(static_cast<float>(x1_1 * x1_1) + static_cast<float>(x1_2 * x1_2) + static_cast<float>(x2_1 * x2_1) + static_cast<float>(x2_2 * x2_2));
	}
	template<Number T>
	constexpr inline T mat2x2<T>::min() const {
		return *std::min_element(cbegin(), cend());
	}
	template<Number T>
	constexpr inline T mat2x2<T>::max() const {
		return *std::max_element(cbegin(), cend());
	}
	template<Number T>
	template<Number N>
	constexpr inline T mat2x2<T>::dot(const mat2x2<N>& other) const {
		return x1_1 * static_cast<T>(other.x1_1) + x1_2 * static_cast<T>(other.x1_2) + x2_1 * static_cast<T>(other.x2_1) + x2_2 * static_cast<T>(other.x2_2);
	}
	template<Number T>
	constexpr T mat2x2<T>::operator[](std::size_t i) const {
		return *(&x1_1 + sizeof(T) * i);
	}
	template<Number T>
	constexpr T mat2x2<T>::at(std::size_t row, std::size_t col) const {
		return *(&x1_1 + (row * 2 + col * 2) * sizeof(T));
	}
	template<Number T>
	constexpr rvec2<T> mat2x2<T>::row(std::size_t i) const {
		return rvec2<T>(*(&x1_1 + (2 * 0 + i) * sizeof(T)), *(&x1_1 + (2 * 1 + i) * sizeof(T)));
	}
	template<Number T>
	constexpr vec2<T> mat2x2<T>::column(std::size_t i) const {
		return vec2<T>(*(&x1_1 + (2 * 0 + i) * sizeof(T)), *(&x1_1 + (2 * 1 + i) * sizeof(T)));
	}
	template<Number T>
	constexpr Iterator<T> mat2x2<T>::cbegin() const {
		return Iterator(const_cast<T*>(&x1_1));
	}
	template<Number T>
	constexpr Iterator<T> mat2x2<T>::cend() const {
		return Iterator(const_cast<T*>(&x2_2 + sizeof(T)));
	}
	template<Number T>
	constexpr Iterator<T> mat2x2<T>::begin() const {
		return Iterator(const_cast<T*>(&x1_1));
	}
	template<Number T>
	constexpr Iterator<T> mat2x2<T>::end() const {
		return Iterator(const_cast<T*>(&x2_2 + sizeof(T)));
	}


} // namespace gz

#include "mat2x2.tpp"