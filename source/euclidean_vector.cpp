// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
// Written by Justin Geuntae Park (z5060336)
// Is an implementation of a Euclidean Vector Class Library
// as outlined by the assignment 2 specifications.
#include "comp6771/euclidean_vector.hpp"
#include <cmath>
#include <functional>
#include <list>
#include <memory>
#include <numeric>
#include <range/v3/algorithm.hpp>
#include <range/v3/functional.hpp>
#include <range/v3/range.hpp>
#include <string>
#include <vector>
namespace comp6771 {
	// Constructors
	euclidean_vector::euclidean_vector()
	: // ass2 spec requires we use double[]
	  // NOLINTNEXTLINE (modernize-avoid-c-arrays)
	   vec_{std::make_unique<double[]>(1)}
	, dimension_{1}
	, norm_result_{0.0}
	, change_{false} {}

	euclidean_vector::euclidean_vector(int dimension)
	: // ass2 spec requires we use double[]
	  // NOLINTNEXTLINE (modernize-avoid-c-arrays)
	   vec_{std::make_unique<double[]>(static_cast<std::vector<int>::size_type>(dimension))}
	, dimension_{dimension}
	, norm_result_{0.0}
	, change_{false} {}

	euclidean_vector::euclidean_vector(int dimension, double value) {
		// ass2 spec requires we use double[]
		// NOLINTNEXTLINE (modernize-avoid-c-arrays)
		vec_ = std::make_unique<double[]>(static_cast<std::vector<int>::size_type>(dimension));
		ranges::fill(vec_.get(), vec_.get() + dimension, value);
		dimension_ = dimension;
		norm_result_ = 0.0;
		change_ = false;
	}

	euclidean_vector::euclidean_vector(std::vector<double>::const_iterator beg,
	                                   std::vector<double>::const_iterator end) {
		std::vector<double> li(beg, end);
		dimension_ = static_cast<int>(li.size());
		// ass2 spec requires we use double[]
		// NOLINTNEXTLINE (modernize-avoid-c-arrays)
		vec_ = std::make_unique<double[]>(static_cast<std::vector<int>::size_type>(dimension_));
		ranges::copy(beg, end, vec_.get());
		norm_result_ = 0.0;
		change_ = false;
	}

	euclidean_vector::euclidean_vector(std::initializer_list<double> list) {
		dimension_ = static_cast<int>(list.size());
		// ass2 spec requires we use double[]
		// NOLINTNEXTLINE (modernize-avoid-c-arrays)
		vec_ = std::make_unique<double[]>(static_cast<std::vector<int>::size_type>(dimension_));
		norm_result_ = 0.0;
		change_ = false;
		ranges::copy(list.begin(), list.end(), vec_.get());
	}

	euclidean_vector::euclidean_vector(euclidean_vector const& v1) noexcept {
		dimension_ = v1.dimension_;
		// ass2 spec requires we use double[]
		// NOLINTNEXTLINE (modernize-avoid-c-arrays)
		vec_ = std::make_unique<double[]>(static_cast<std::vector<int>::size_type>(dimension_));
		norm_result_ = v1.norm_result_;
		change_ = v1.change_;
		ranges::copy(v1.vec_.get(), v1.vec_.get() + v1.dimensions(), vec_.get());
	}

	euclidean_vector::euclidean_vector(euclidean_vector&& v1) noexcept
	: vec_{std::exchange(v1.vec_, nullptr)}
	, dimension_{std::exchange(v1.dimension_, 0)}
	, norm_result_{std::exchange(v1.norm_result_, 0.0)}
	, change_{std::exchange(v1.change_, false)} {}

	// Operators
	auto euclidean_vector::operator=(euclidean_vector const& v1) noexcept -> euclidean_vector& {
		euclidean_vector copy = v1;
		std::swap(copy, *this);
		return *this;
	}

	auto euclidean_vector::clear() noexcept -> void {
		vec_ = nullptr;
		dimension_ = 0;
		norm_result_ = 0.0;
		change_ = false;
	}

	auto euclidean_vector::operator=(euclidean_vector&& v1) noexcept -> euclidean_vector& {
		ranges::swap(vec_, v1.vec_);
		ranges::swap(dimension_, v1.dimension_);
		ranges::swap(norm_result_, v1.norm_result_);
		ranges::swap(change_, v1.change_);
		v1.clear();
		return *this;
	}

	auto euclidean_vector::operator[](int index) const -> double {
		assert(index >= 0);
		assert(index < dimension_);
		return vec_[static_cast<std::vector<int>::size_type>(index)];
	}

	auto euclidean_vector::operator[](int index) -> double& {
		assert(index >= 0);
		assert(index < dimension_);
		change_ = false;
		return vec_[static_cast<std::vector<int>::size_type>(index)];
	}

	auto euclidean_vector::operator+() -> euclidean_vector {
		return *this;
	}

	auto euclidean_vector::operator-() -> euclidean_vector {
		auto ret = euclidean_vector(dimension_);
		ranges::transform(vec_.get(), vec_.get() + dimension_, ret.vec_.get(), std::negate<double>{});
		return ret;
	}

	auto euclidean_vector::operator+=(euclidean_vector const& v1) -> euclidean_vector& {
		if (v1.dimensions() != dimension_) {
			auto error = size_error(dimension_, v1.dimensions());
			throw euclidean_vector_error(error);
		}
		std::transform(vec_.get(),
		               vec_.get() + dimension_,
		               v1.vec_.get(),
		               vec_.get(),
		               std::plus<double>{});
		change_ = false;
		return *this;
	}

	auto euclidean_vector::operator-=(euclidean_vector const& v1) -> euclidean_vector& {
		if (v1.dimensions() != dimension_) {
			auto error = size_error(dimension_, v1.dimensions());
			throw euclidean_vector_error(error);
		}
		std::transform(vec_.get(),
		               vec_.get() + dimension_,
		               v1.vec_.get(),
		               vec_.get(),
		               std::minus<double>{});
		change_ = false;
		return *this;
	}

	auto euclidean_vector::operator*=(double value) -> euclidean_vector& {
		ranges::transform(vec_.get(), vec_.get() + dimension_, vec_.get(), [value](double x) {
			return x * value;
		});
		change_ = false;
		return *this;
	}

	auto euclidean_vector::operator/=(double value) -> euclidean_vector& {
		if (value == 0) {
			throw euclidean_vector_error(division_zero_error());
		}
		ranges::transform(vec_.get(), vec_.get() + dimension_, vec_.get(), [value](double x) {
			return x / value;
		});
		change_ = false;
		return *this;
	}

	euclidean_vector::operator std::vector<double>() {
		auto ret = std::vector<double>();
		ret.insert(ret.begin(), vec_.get(), vec_.get() + dimension_);
		return ret;
	}

	euclidean_vector::operator std::list<double>() {
		auto ret = std::list<double>();
		ret.insert(ret.begin(), vec_.get(), vec_.get() + dimension_);
		return ret;
	}

	// Member Functions
	auto euclidean_vector::at(int index) const -> double {
		if (index >= dimension_ || index < 0) {
			throw euclidean_vector_error(invalid_index_error(index));
		}
		return vec_[static_cast<std::vector<int>::size_type>(index)];
	}

	auto euclidean_vector::at(int index) -> double& {
		if (index >= dimension_ || index < 0) {
			throw euclidean_vector_error(invalid_index_error(index));
		}
		change_ = false;
		return vec_[static_cast<std::vector<int>::size_type>(index)];
	}

	auto euclidean_vector::dimensions() const -> int {
		return dimension_;
	}

	// Friends
	auto operator==(euclidean_vector const& v1, euclidean_vector const& v2) -> bool {
		if (v1.dimensions() != v2.dimensions()) {
			return false;
		}
		return std::equal(v1.vec_.get(), v1.vec_.get() + v1.dimensions(), v2.vec_.get());
	}

	auto operator!=(euclidean_vector const& v1, euclidean_vector const& v2) -> bool {
		if (v1.dimensions() != v2.dimensions()) {
			return true;
		}
		if (v1.dimensions() == 0 && v2.dimensions() == 0) {
			return false;
		}
		for (int i = 0; i < v1.dimensions(); ++i) {
			if (v1[i] == v2[i]) {
				return false;
			}
		}
		return true;
	}

	auto operator+(euclidean_vector const& v1, euclidean_vector const& v2) -> euclidean_vector {
		if (v1.dimensions() != v2.dimensions()) {
			auto error = size_error(v1.dimensions(), v2.dimensions());
			throw euclidean_vector_error(error);
		}
		auto ret = euclidean_vector(v1.dimensions());
		std::transform(v1.vec_.get(),
		               v1.vec_.get() + v1.dimensions(),
		               v2.vec_.get(),
		               ret.vec_.get(),
		               std::plus<double>{});
		return ret;
	}

	auto operator-(euclidean_vector const& v1, euclidean_vector const& v2) -> euclidean_vector {
		if (v1.dimensions() != v2.dimensions()) {
			auto error = size_error(v1.dimensions(), v2.dimensions());
			throw euclidean_vector_error(error);
		}
		auto ret = euclidean_vector(v1.dimensions());
		std::transform(v1.vec_.get(),
		               v1.vec_.get() + v1.dimensions(),
		               v2.vec_.get(),
		               ret.vec_.get(),
		               std::minus<double>{});
		return ret;
	}

	auto operator*(euclidean_vector const& v1, double value) -> euclidean_vector {
		auto ret = euclidean_vector(v1.dimensions());
		ranges::transform(v1.vec_.get(),
		                  v1.vec_.get() + v1.dimensions(),
		                  ret.vec_.get(),
		                  [value](double x) { return x * value; });
		return ret;
	}

	auto operator*(double value, euclidean_vector const& v1) -> euclidean_vector {
		return operator*(v1, value);
	}

	auto operator/(euclidean_vector const& v1, double value) -> euclidean_vector {
		if (value == 0) {
			throw euclidean_vector_error(division_zero_error());
		}
		auto ret = euclidean_vector(v1.dimensions());
		ranges::transform(v1.vec_.get(),
		                  v1.vec_.get() + v1.dimensions(),
		                  ret.vec_.get(),
		                  [value](double x) { return x / value; });
		return ret;
	}

	auto operator<<(std::ostream& output, euclidean_vector const& v1) -> std::ostream& {
		output << '[';
		for (int i = 0; i < v1.dimensions(); ++i) {
			if (i == 0) {
				output << v1[i];
			}
			else {
				output << ' ' << v1[i];
			}
		}
		output << ']';
		return output;
	}

	// Utility Helper Functions
	auto euclidean_vector::normalize() const -> double {
		auto value = 0.0;
		if (!change_) {
			change_ = true;
			norm_result_ = double(std::sqrt(
			   std::accumulate(vec_.get(), vec_.get() + dimension_, value, [](double x, double y) {
				   return x + y * y;
			   })));
		}
		return norm_result_;
	}

	auto euclidean_vector::dot_prod(euclidean_vector const& v1) const -> double {
		auto value = 0.0;
		return std::inner_product(vec_.get(), vec_.get() + dimension_, v1.vec_.get(), value);
	}

	// Utility Functions
	auto euclidean_norm(euclidean_vector const& v1) -> double {
		if (v1.dimensions() == 0) {
			throw euclidean_vector_error(no_norm_error());
		}
		return v1.normalize();
	}

	auto unit(euclidean_vector const& v1) -> euclidean_vector {
		if (v1.dimensions() == 0) {
			throw euclidean_vector_error(no_unit_error());
		}
		double value = euclidean_norm(v1);
		if (value == 0) {
			throw euclidean_vector_error(no_norm_no_euclidean());
		}
		auto ret_v = v1 / value;
		return ret_v;
	}

	auto dot(euclidean_vector const& v1, euclidean_vector const& v2) -> double {
		if (v1.dimensions() != v2.dimensions()) {
			auto error = size_error(v1.dimensions(), v2.dimensions());
			throw euclidean_vector_error(error);
		}
		return v1.dot_prod(v2);
	}

	// Helper
	// Used to return error messages depending on the error
	auto size_error(int const& x, int const& y) -> std::string {
		std::string error = "Dimensions of LHS() and RHS() do not match";
		error.insert(18, std::to_string(x));
		error.insert(29, std::to_string(y));
		return error;
	}

	auto division_zero_error() -> std::string {
		return "Invalid vector division by 0";
	}

	auto invalid_index_error(int const& index) -> std::string {
		std::string error = "Index  is not valid for this euclidean_vector object";
		error.insert(6, std::to_string(index));
		return error;
	}

	auto no_norm_error() -> std::string {
		return "euclidean_vector with no dimensions does not have a norm";
	}

	auto no_norm_no_euclidean() -> std::string {
		return "euclidean_vector with zero euclidean normal does not have a unit vector";
	}

	auto no_unit_error() -> std::string {
		return "euclidean_vector with no dimensions does not have a unit vector";
	}

	// Test Function (used only for testing)
	// Returns whether the vector has not been changed using true/false
	auto euclidean_vector::change_ret() const -> bool {
		return change_;
	}
} // namespace comp6771
