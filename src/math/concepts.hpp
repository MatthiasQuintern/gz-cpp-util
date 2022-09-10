#pragma once

#include <concepts>

// Number
template<typename T>
concept Number = std::integral<T> or std::floating_point<T>;

// VectorX
template<typename T>
concept Vector2 = requires(T t) {
	requires Number<decltype(t.x)>;
	requires Number<decltype(t.y)>;
} and requires(T t) { sizeof(t.x) == (sizeof(T) * 2); };

template<typename T>
concept Vector3 = requires(T t) {
	requires Number<decltype(t.x)>;
	requires Number<decltype(t.y)>;
	requires Number<decltype(t.z)>;
} and requires(T t) { sizeof(t.x) == (sizeof(T) * 3); };

template<typename T>
concept Vector4 = requires(T t) {
	requires Number<decltype(t.x)>;
	requires Number<decltype(t.y)>;
	requires Number<decltype(t.z)>;
	requires Number<decltype(t.w)>;
} and requires(T t) { sizeof(t.x) == (sizeof(T) * 4); };

// RowVectorX
template<typename T>
concept RowVector2 = Vector2<T> and Number<typename T::isRowVector>;

template<typename T>
concept RowVector3 = Vector3<T> and Number<typename T::isRowVector>;

template<typename T>
concept RowVector4 = Vector4<T> and Number<typename T::isRowVector>;

// ColumnVectorX
template<typename T>
concept ColumnVector2 = Vector2<T> and Number<typename T::isColumnVector>;

template<typename T>
concept ColumnVector3 = Vector3<T> and Number<typename T::isColumnVector>;

template<typename T>
concept ColumnVector4 = Vector4<T> and Number<typename T::isColumnVector>;

// Matrices
template<typename T>
concept Mat2x2 = requires(T t) {
	requires Number<decltype(t.x1_1)>;
	requires Number<decltype(t.x1_2)>;
	requires Number<decltype(t.x2_1)>;
	requires Number<decltype(t.x2_2)>;
};
template<typename T>
concept Mat2x3 = requires(T t) {
	requires Number<decltype(t.x1_1)>;
	requires Number<decltype(t.x1_2)>;
	requires Number<decltype(t.x1_3)>;
	requires Number<decltype(t.x2_1)>;
	requires Number<decltype(t.x2_2)>;
	requires Number<decltype(t.x2_3)>;
};
template<typename T>
concept Mat2x4 = requires(T t) {
	requires Number<decltype(t.x1_1)>;
	requires Number<decltype(t.x1_2)>;
	requires Number<decltype(t.x1_3)>;
	requires Number<decltype(t.x1_4)>;
	requires Number<decltype(t.x2_1)>;
	requires Number<decltype(t.x2_2)>;
	requires Number<decltype(t.x2_3)>;
	requires Number<decltype(t.x2_4)>;
};
template<typename T>
concept Mat3x2 = requires(T t) {
	requires Number<decltype(t.x1_1)>;
	requires Number<decltype(t.x1_2)>;
	requires Number<decltype(t.x2_1)>;
	requires Number<decltype(t.x2_2)>;
	requires Number<decltype(t.x3_1)>;
	requires Number<decltype(t.x3_2)>;
};
template<typename T>
concept Mat3x3 = requires(T t) {
	requires Number<decltype(t.x1_1)>;
	requires Number<decltype(t.x1_2)>;
	requires Number<decltype(t.x1_3)>;
	requires Number<decltype(t.x2_1)>;
	requires Number<decltype(t.x2_2)>;
	requires Number<decltype(t.x2_3)>;
	requires Number<decltype(t.x3_1)>;
	requires Number<decltype(t.x3_2)>;
	requires Number<decltype(t.x3_3)>;
};
template<typename T>
concept Mat3x4 = requires(T t) {
	requires Number<decltype(t.x1_1)>;
	requires Number<decltype(t.x1_2)>;
	requires Number<decltype(t.x1_3)>;
	requires Number<decltype(t.x1_4)>;
	requires Number<decltype(t.x2_1)>;
	requires Number<decltype(t.x2_2)>;
	requires Number<decltype(t.x2_3)>;
	requires Number<decltype(t.x2_4)>;
	requires Number<decltype(t.x3_1)>;
	requires Number<decltype(t.x3_2)>;
	requires Number<decltype(t.x3_3)>;
	requires Number<decltype(t.x3_4)>;
};
template<typename T>
concept Mat4x2 = requires(T t) {
	requires Number<decltype(t.x1_1)>;
	requires Number<decltype(t.x1_2)>;
	requires Number<decltype(t.x2_1)>;
	requires Number<decltype(t.x2_2)>;
	requires Number<decltype(t.x3_1)>;
	requires Number<decltype(t.x3_2)>;
	requires Number<decltype(t.x4_1)>;
	requires Number<decltype(t.x4_2)>;
};
template<typename T>
concept Mat4x3 = requires(T t) {
	requires Number<decltype(t.x1_1)>;
	requires Number<decltype(t.x1_2)>;
	requires Number<decltype(t.x1_3)>;
	requires Number<decltype(t.x2_1)>;
	requires Number<decltype(t.x2_2)>;
	requires Number<decltype(t.x2_3)>;
	requires Number<decltype(t.x3_1)>;
	requires Number<decltype(t.x3_2)>;
	requires Number<decltype(t.x3_3)>;
	requires Number<decltype(t.x4_1)>;
	requires Number<decltype(t.x4_2)>;
	requires Number<decltype(t.x4_3)>;
};
template<typename T>
concept Mat4x4 = requires(T t) {
	requires Number<decltype(t.x1_1)>;
	requires Number<decltype(t.x1_2)>;
	requires Number<decltype(t.x1_3)>;
	requires Number<decltype(t.x1_4)>;
	requires Number<decltype(t.x2_1)>;
	requires Number<decltype(t.x2_2)>;
	requires Number<decltype(t.x2_3)>;
	requires Number<decltype(t.x2_4)>;
	requires Number<decltype(t.x3_1)>;
	requires Number<decltype(t.x3_2)>;
	requires Number<decltype(t.x3_3)>;
	requires Number<decltype(t.x3_4)>;
	requires Number<decltype(t.x4_1)>;
	requires Number<decltype(t.x4_2)>;
	requires Number<decltype(t.x4_3)>;
	requires Number<decltype(t.x4_4)>;
};
