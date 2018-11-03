#pragma once

#include <algorithm>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <limits>
#include <vector>

#include "span.h"
#include "../../common.h"

template<typename T>
class Matrix {
public:
	constexpr explicit Matrix() = default;

	constexpr explicit Matrix(size_t width, size_t height) : width_(width), height_(height),
	                                                         data_(width * height, T{}) {
	}

	constexpr static Matrix indentity(size_t size) {
		Matrix indentity_(size, size);
		for (auto it = indentity_.data_.begin(); it < indentity_.data_.end(); it += size + 1) {
			*it = unit<T>();
		}
		return indentity_;
	}

	constexpr size_t height() const {
		return height_;
	}

	constexpr size_t width() const {
		return width_;
	}

	constexpr Matrix& inverse() noexcept {
		return *this;
	}

	constexpr Matrix& transpose() noexcept {
		return *this;
	}

	constexpr T determinant() const {
		return {};
	}

	constexpr std::span<T> operator[](size_t index) {
		if (index >= height_) {
			return {};
		}

		auto beginRow = std::begin(data_) + (width_ * index);
		return {&*beginRow, &*(beginRow + width_)};
	};

	constexpr Matrix& operator+=(Matrix const& rhs) noexcept {
		std::transform(std::begin(data_), std::end(data_), std::cbegin(rhs.data_), std::cend(rhs.data_),
		               std::begin(data_), [](auto& lhs_value, auto& rhs_value) { return lhs_value += rhs_value; });
		return *this;
	}

	friend constexpr Matrix operator+(Matrix const& lhs, Matrix const& rhs) {
		return Matrix(lhs) += rhs;
	}

	friend constexpr Matrix operator+(Matrix const& lhs, Matrix&& rhs) noexcept {
		return std::move(rhs += lhs);
	}

	friend constexpr Matrix operator+(Matrix&& lhs, Matrix const& rhs) noexcept {
		return std::move(lhs += rhs);
	}

	friend constexpr Matrix operator+(Matrix&& lhs, Matrix&& rhs) noexcept {
		return std::move(rhs += lhs);
	}


	constexpr Matrix& operator-=(Matrix const& rhs) noexcept {
		std::transform(std::begin(data_), std::end(data_), std::cbegin(rhs.data_), std::cend(rhs.data_),
		               std::begin(data_), [](auto& lhs_value, auto& rhs_value) { return lhs_value -= rhs_value; });
		return *this;
	}

	friend constexpr Matrix operator-(Matrix const& lhs, Matrix const& rhs) {
		return Matrix(lhs) -= rhs;
	}

	friend constexpr Matrix operator-(Matrix const& lhs, Matrix&& rhs) noexcept {
		return std::move(rhs -= lhs);
	}

	friend constexpr Matrix operator-(Matrix&& lhs, Matrix const& rhs) noexcept {
		return std::move(lhs -= rhs);
	}

	friend constexpr Matrix operator-(Matrix&& lhs, Matrix&& rhs) noexcept {
		return std::move(rhs -= lhs);
	}
//
//	friend Matrix operator/(Matrix const& lhs, Matrix const& rhs);
//	friend Matrix operator/(Matrix const& lhs, Matrix&& rhs);
//	friend Matrix operator/(Matrix&& lhs, Matrix const& rhs);
//	friend Matrix operator/(Matrix&& lhs, Matrix&& rhs);
//
//	friend Matrix operator*(Matrix const& lhs, Matrix const& rhs);
//	friend Matrix operator*(Matrix const& lhs, Matrix&& rhs);
//	friend Matrix operator*(Matrix&& lhs, Matrix const& rhs);
//	friend Matrix operator*(Matrix&& lhs, Matrix&& rhs);

	constexpr Matrix& operator+=(T const& rhs) noexcept {
		std::transform(std::begin(data_), std::end(data_), std::begin(data_), [rhs](auto& value) { value += rhs; });
		return *this;
	}

	friend constexpr Matrix operator+(Matrix const& lhs, T const& rhs) noexcept {
		return Matrix(lhs) += rhs;
	}

	friend constexpr Matrix operator+(Matrix&& lhs, T const& rhs) noexcept {
		return std::move(lhs += rhs);
	}

	constexpr Matrix& operator-=(T const& rhs) noexcept {
		std::transform(std::begin(data_), std::end(data_), std::begin(data_), [rhs](auto& value) { value -= rhs; });
		return *this;
	}

	friend constexpr Matrix operator-(Matrix const& lhs, T const& rhs) noexcept {
		return Matrix(lhs) -= rhs;
	}

	friend constexpr Matrix operator-(Matrix&& lhs, T const& rhs) noexcept {
		return std::move(lhs -= rhs);
	}

	Matrix& operator/=(T const& rhs) {
		std::transform(std::begin(data_), std::end(data_), std::begin(data_), [rhs](auto& value) { value /= rhs; });
		return *this;
	}

	friend Matrix operator/(Matrix const& lhs, T const& rhs) {
		return Matrix(lhs) /= rhs;
	}

	friend Matrix operator/(Matrix&& lhs, T const& rhs) {
		return std::move(lhs /= rhs);
	}

	Matrix& operator*=(T const& rhs) {
		std::transform(std::begin(data_), std::end(data_), std::begin(data_), [rhs](auto& value) { value *= rhs; });
		return *this;
	}

	friend Matrix operator*(Matrix const& lhs, T const& rhs) {
		return Matrix(lhs) *= rhs;
	}

	friend Matrix operator*(Matrix&& lhs, T const& rhs) {
		return std::move(lhs *= rhs);
	}

	friend Matrix operator*(T const& lhs, Matrix const& rhs) {
		return Matrix(rhs) *= lhs;
	}

	friend Matrix operator*(T const& lhs, Matrix&& rhs) {
		return std::move(rhs *= lhs);
	}

	constexpr bool operator==(Matrix const& rhs) const noexcept {
		return width_ == rhs.width_ && data_ == rhs.data_; /// next for optimization you may use memcmp for simple types
	}

	constexpr bool operator!=(Matrix const& rhs) const noexcept {
		return !(operator==(rhs));
	}

	friend std::istream& operator>>(std::istream& input, Matrix& lhs) {
		input >> lhs.width_ >> lhs.height_;
		lhs.data_.resize(lhs.width_, lhs.height_);

		std::copy(std::istream_iterator<T>(input), std::istream_iterator<T>(), std::back_inserter(lhs.data_));

		return input;
	}

	friend std::ostream& operator<<(std::ostream& output, Matrix const& lhs) {
		for (auto it = std::cbegin(lhs.data_); it != std::cend(lhs.data_); it += lhs.width_) {
			std::copy(it, it + lhs.width_, std::ostream_iterator<T>(output, " "));
			output << '\n';
		}
		return output;
	}

private:
	size_t width_ = {};
	size_t height_ = {};
	std::vector<T> data_;
};