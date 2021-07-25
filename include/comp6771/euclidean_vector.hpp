#ifndef COMP6771_EUCLIDEAN_VECTOR_HPP
#define COMP6771_EUCLIDEAN_VECTOR_HPP

#include <compare>
#include <functional>
#include <list>
#include <memory>
#include <ostream>
#include <range/v3/algorithm.hpp>
#include <range/v3/iterator.hpp>
#include <span>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

namespace comp6771 {
	class euclidean_vector_error : public std::runtime_error {
	public:
		explicit euclidean_vector_error(std::string const& what) noexcept
		: std::runtime_error(what) {}
	};

	class euclidean_vector {
	public:
		// constructors
		euclidean_vector();
		explicit euclidean_vector(int);
		euclidean_vector(int, double);
		euclidean_vector(std::vector<double>::const_iterator, std::vector<double>::const_iterator);
		euclidean_vector(std::initializer_list<double>);
		euclidean_vector(euclidean_vector const&) noexcept;
		euclidean_vector(euclidean_vector&&) noexcept;
		// destructor
		~euclidean_vector() = default;
		// operator
		auto operator=(euclidean_vector const&) noexcept -> euclidean_vector&;
		auto clear() noexcept -> void;
		auto operator=(euclidean_vector&&) noexcept -> euclidean_vector&;
		auto operator[](int index) const -> double;
		auto operator[](int index) -> double&;
		auto operator+() -> euclidean_vector;
		auto operator-() -> euclidean_vector;
		auto operator+=(euclidean_vector const&) -> euclidean_vector&;
		auto operator-=(euclidean_vector const&) -> euclidean_vector&;
		auto operator*=(double) -> euclidean_vector&;
		auto operator/=(double) -> euclidean_vector&;
		explicit operator std::vector<double>();
		explicit operator std::list<double>();
		// Member Functions
		[[nodiscard]] auto at(int) const -> double;
		[[nodiscard]] auto at(int) -> double&;
		[[nodiscard]] auto dimensions() const -> int;

		// Friends
		friend auto operator==(euclidean_vector const&, euclidean_vector const&) -> bool;
		friend auto operator!=(euclidean_vector const&, euclidean_vector const&) -> bool;
		friend auto operator+(euclidean_vector const&, euclidean_vector const&) -> euclidean_vector;
		friend auto operator-(euclidean_vector const&, euclidean_vector const&) -> euclidean_vector;
		friend auto operator*(euclidean_vector const&, double) -> euclidean_vector;
		friend auto operator*(double, euclidean_vector const&) -> euclidean_vector;
		friend auto operator/(euclidean_vector const&, double) -> euclidean_vector;
		friend auto operator<<(std::ostream&, euclidean_vector const&) -> std::ostream&;

		// Utility Helper Function
		[[nodiscard]] auto normalize() const -> double;
		[[nodiscard]] auto dot_prod(euclidean_vector const& v1) const -> double;

		// Test Function (used only for testing)
		auto change_ret() const -> bool;

	private:
		// ass2 spec requires we use double[]
		// NOLINTNEXTLINE (modernize-avoid-c-arrays)
		std::unique_ptr<double[]> vec_;
		int dimension_;
		double mutable norm_result_;
		bool mutable change_;
	};

	// Utility Function
	auto euclidean_norm(euclidean_vector const&) -> double;
	auto unit(euclidean_vector const&) -> euclidean_vector;
	auto dot(euclidean_vector const&, euclidean_vector const&) -> double;

	// Helper
	auto size_error(int const& x, int const& y) -> std::string;
	auto division_zero_error() -> std::string;
	auto invalid_index_error(int const& index) -> std::string;
	auto no_norm_error() -> std::string;
	auto no_norm_no_euclidean() -> std::string;
	auto no_unit_error() -> std::string;
} // namespace comp6771
#endif // COMP6771_EUCLIDEAN_VECTOR_HPP
