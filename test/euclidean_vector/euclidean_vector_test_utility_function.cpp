#include "comp6771/euclidean_vector.hpp"
#include <catch2/catch.hpp>
#include <fmt/format.h>
#include <fmt/ostream.h>
// Written by Justin Geuntae Park (z5060336)
// The following program tests for ONLY utility operations
// using the implementation found in euclidean_vector.cpp
// All utility operations start with the empty vector if possible then
// tests for exception cases if applicable. Finally vectors of increasing
// size is used. To determine the contents of the vector
// the output stream, []operator and dimensions() are used, unfortunately it is impossible
// to not use other functions but the test tries to limit it to only these
// two.

TEST_CASE("Testing euclidean normal [auto euclidean_norm(euclidean_vector const& v) -> double]") {
	SECTION("Testing for empty vector") {
		auto const a1 = comp6771::euclidean_vector(0);
		CHECK_THROWS(comp6771::euclidean_norm(a1));
	}

	SECTION("Testing for default vector") {
		auto const a1 = comp6771::euclidean_vector();
		double value = comp6771::euclidean_norm(a1);
		CHECK(value == 0.0);
	}

	SECTION("Testing for a vector with 3 dimensions all positive magnitudes") {
		auto const a1 = comp6771::euclidean_vector(3, 3.0);
		double value = comp6771::euclidean_norm(a1);
		CHECK(value == Approx(5.1961524227));
	}

	SECTION("Testing for a vector with 3 dimensions all negative magnitudes") {
		auto const a1 = comp6771::euclidean_vector(3, -3.0);
		double value = comp6771::euclidean_norm(a1);
		CHECK(value == Approx(5.1961524227));
	}

	SECTION("Testing for a vector with 3 dimensions with different magnitudes") {
		auto a1 = comp6771::euclidean_vector(3, 3.0);
		a1[0] = 3.2;
		a1[1] = -9.7;
		a1[2] = 1.2;
		double value = comp6771::euclidean_norm(a1);
		CHECK(value == Approx(10.2844542879));
	}
}

TEST_CASE("Testing unit euclidean_vector [auto unit(euclidean_vector const& v) -> "
          "euclidean_vector;]") {
	SECTION("Testing for empty vector") {
		auto const a1 = comp6771::euclidean_vector(0);
		CHECK_THROWS(comp6771::unit(a1));
	}
	SECTION("Testing unit vector for a vector that has 0 norm") {
		auto const a1 = comp6771::euclidean_vector(3);
		CHECK_THROWS(comp6771::unit(a1));
	}
	SECTION("Testing for a vector that has the same value for each dimension") {
		auto const a1 = comp6771::euclidean_vector(3, 3.0);
		auto const a2 = comp6771::unit(a1);
		CHECK(a2[0] == Approx(0.57735));
		CHECK(a2[1] == Approx(0.57735));
		CHECK(a2[2] == Approx(0.57735));
	}

	SECTION("Testing for a vector that has a different value for each dimension") {
		auto a1 = comp6771::euclidean_vector(3, 3.0);
		a1[0] = -12.3;
		a1[1] = 1.23;
		a1[2] = 3.35;
		auto const a2 = comp6771::unit(a1);
		CHECK(a2[0] == Approx(-0.9604));
		CHECK(a2[1] == Approx(0.09604));
		CHECK(a2[2] == Approx(0.26157));
	}
}

TEST_CASE("Testing dot product of euclidean_vector [auto dot(euclidean_vector const& x, "
          "euclidean_vector const& y) -> double]") {
	SECTION("Testing for one empty vector and one 3 dimension vector") {
		auto const a1 = comp6771::euclidean_vector(0);
		auto const a2 = comp6771::euclidean_vector(3);
		CHECK_THROWS(double{comp6771::dot(a1, a2)});
	}

	SECTION("Testing for 5 dimension vector and one 3 dimension vector") {
		auto const a1 = comp6771::euclidean_vector(5);
		auto const a2 = comp6771::euclidean_vector(3);
		CHECK_THROWS(double{comp6771::dot(a1, a2)});
	}

	SECTION("Testing for a vector that is the same") {
		auto const a1 = comp6771::euclidean_vector(3, 3.0);
		auto c = double{comp6771::dot(a1, a1)};
		CHECK(c == 27.0);
	}

	SECTION("Testing for a vector that is different") {
		auto a1 = comp6771::euclidean_vector(3, 3.0);
		auto a2 = comp6771::euclidean_vector(3, 10.0);
		auto c = double{comp6771::dot(a1, a2)};
		CHECK(c == 90.0);
	}

	SECTION("Testing for a vector that has all magnitudes different") {
		auto a1 = comp6771::euclidean_vector(3, 3.0);
		a1[0] = -1.34;
		a1[2] = 12.32;
		auto a2 = comp6771::euclidean_vector(3, 10.0);
		a2[0] = -21.22;
		a2[1] = 1.23;
		auto c = double{comp6771::dot(a1, a2)};
		CHECK(c == Approx(155.3248));
	}
}

TEST_CASE("Testing cache functionality") {
	SECTION("Testing norm of vector but does not need to be recalculated") {
		auto const a1 = comp6771::euclidean_vector(3, 3.0);
		CHECK(a1.change_ret() == false);
		double value = comp6771::euclidean_norm(a1);
		CHECK(value == Approx(5.1961524227));
		CHECK(a1.change_ret() == true);

		double value1 = comp6771::euclidean_norm(a1);
		CHECK(value1 == Approx(5.1961524227));
		CHECK(a1.change_ret() == true);
	}

	SECTION("Testing to see if change state copies over when using copy construtor for false") {
		auto a = comp6771::euclidean_vector{1.0, 4.5, 1.34};
		CHECK(a.change_ret() == false);
		auto a_copy = comp6771::euclidean_vector(a);
		CHECK(a_copy.change_ret() == false);
	}

	SECTION("Testing to see if change state copies over when using copy construtor for true") {
		auto a = comp6771::euclidean_vector{1.0, 4.5, 1.34};
		CHECK(a.change_ret() == false);
		auto value = comp6771::euclidean_norm(a);
		CHECK(value == Approx(4.8005832979));
		CHECK(a.change_ret() == true);

		auto a_copy = comp6771::euclidean_vector(a);
		CHECK(a_copy.change_ret() == true);
		value = comp6771::euclidean_norm(a_copy);
		CHECK(value == Approx(4.8005832979));
	}

	SECTION("Testing to see if change state moves over when using move construtor for false") {
		auto a = comp6771::euclidean_vector{1.0, 4.5, 1.34};
		CHECK(a.change_ret() == false);
		auto a_copy = comp6771::euclidean_vector(std::move(a));
		CHECK(a_copy.change_ret() == false);
	}

	SECTION("Testing to see if change state moves over when using move construtor for true") {
		auto a = comp6771::euclidean_vector{1.0, 4.5, 1.34};
		CHECK(a.change_ret() == false);
		auto value = comp6771::euclidean_norm(a);
		CHECK(value == Approx(4.8005832979));
		CHECK(a.change_ret() == true);

		auto a_copy = comp6771::euclidean_vector(std::move(a));
		CHECK(a_copy.change_ret() == true);
		value = comp6771::euclidean_norm(a_copy);
		CHECK(value == Approx(4.8005832979));
	}

	SECTION("Testing to see when using at() it changes the state of vector") {
		auto a = comp6771::euclidean_vector{2.0, 4.0, 6.0};
		CHECK(a.change_ret() == false);
		auto value = comp6771::euclidean_norm(a);
		CHECK(value == Approx(7.4833));
		CHECK(a.change_ret() == true);
		a.at(0) = 3.0;
		CHECK(a.change_ret() == false);
	}

	SECTION("Testing norm of vector but does not need to be recalculated using friends") {
		auto const a1 = comp6771::euclidean_vector(3, 3.0);
		CHECK(a1.change_ret() == false);
		double value = comp6771::euclidean_norm(a1);
		CHECK(value == Approx(5.1961524227));
		CHECK(a1.change_ret() == true);

		double value1 = comp6771::euclidean_norm(a1);
		CHECK(value1 == Approx(5.1961524227));
		CHECK(a1.change_ret() == true);
	}
}

TEST_CASE("Test cache functionality for friend operations") {
	SECTION("Testing norm of vector but does not need to be recalculated using additon false") {
		auto const a1 = comp6771::euclidean_vector(3, 3.0);
		CHECK(a1.change_ret() == false);
		auto const a2 = comp6771::euclidean_vector(3, 3.0);
		auto const a3 = a1 + a2;
		CHECK(a1.change_ret() == false);
	}

	SECTION("Testing norm of vector but does not need to be recalculated using subtraction false") {
		auto const a1 = comp6771::euclidean_vector(3, 3.0);
		CHECK(a1.change_ret() == false);
		auto const a2 = comp6771::euclidean_vector(3, 3.0);
		auto const a3 = a1 - a2;
		CHECK(a1.change_ret() == false);
	}

	SECTION("Testing norm of vector but does not need to be recalculated using multiplication "
	        "false") {
		auto const a1 = comp6771::euclidean_vector(3, 3.0);
		CHECK(a1.change_ret() == false);
		auto const val = 2.0;
		auto const a3 = a1 * val;
		CHECK(a1.change_ret() == false);
	}

	SECTION("Testing norm of vector but does not need to be recalculated using division false") {
		auto const a1 = comp6771::euclidean_vector(3, 3.0);
		CHECK(a1.change_ret() == false);
		auto const val = 2.0;
		auto const a3 = a1 / val;
		CHECK(a1.change_ret() == false);
	}

	SECTION("Testing norm of vector does not need to be recalculated using additon true") {
		auto const a1 = comp6771::euclidean_vector(3, 3.0);
		CHECK(a1.change_ret() == false);
		double value = comp6771::euclidean_norm(a1);
		CHECK(value == Approx(5.1961524227));
		CHECK(a1.change_ret() == true);
		auto const a2 = comp6771::euclidean_vector(3, 3.0);
		auto const a3 = a1 + a2;
		CHECK(a1.change_ret() == true);
		CHECK(a2.change_ret() == false);
		CHECK(a3.change_ret() == false);
	}

	SECTION("Testing norm of vector but does not need to be recalculated using subtraction true") {
		auto const a1 = comp6771::euclidean_vector(3, 3.0);
		CHECK(a1.change_ret() == false);
		auto value = comp6771::euclidean_norm(a1);
		CHECK(value == Approx(5.1961524227));
		CHECK(a1.change_ret() == true);

		auto const a2 = comp6771::euclidean_vector(3, 3.0);
		auto const a3 = a1 - a2;
		CHECK(a1.change_ret() == true);
		CHECK(a2.change_ret() == false);
		CHECK(a3.change_ret() == false);
	}

	SECTION("Testing norm of vector but does not need to be recalculated using multiplication "
	        "true") {
		auto const a1 = comp6771::euclidean_vector(3, 3.0);
		CHECK(a1.change_ret() == false);
		auto value = comp6771::euclidean_norm(a1);
		CHECK(value == Approx(5.1961524227));
		CHECK(a1.change_ret() == true);
		auto const val = 2.0;
		auto const a3 = a1 * val;
		CHECK(a1.change_ret() == true);
	}

	SECTION("Testing norm of vector but does not need to be recalculated using division true") {
		auto const a1 = comp6771::euclidean_vector(3, 3.0);
		CHECK(a1.change_ret() == false);
		auto value = comp6771::euclidean_norm(a1);
		CHECK(value == Approx(5.1961524227));
		CHECK(a1.change_ret() == true);
		auto const val = 2.0;
		auto const a3 = a1 / val;
		CHECK(a1.change_ret() == true);
	}
}

TEST_CASE("Test cache functionality for operation functions") {
	SECTION("Testing recalculation for compound addition") {
		auto b = std::vector<double>{1.24, 4.32, 2.3};
		auto a = comp6771::euclidean_vector(b.begin(), b.end());
		auto a1 = comp6771::euclidean_vector(3, 1.0);
		CHECK(a.change_ret() == false);
		auto value = comp6771::euclidean_norm(a);
		CHECK(value == Approx(5.0487622));
		CHECK(a.change_ret() == true);
		a += a1;
		CHECK(a.change_ret() == false);
		value = comp6771::euclidean_norm(a);
		CHECK(value == Approx(6.649060084));
		CHECK(a.change_ret() == true);
	}

	SECTION("Testing recalculation for compound subtraction") {
		auto b = std::vector<double>{1.24, 4.32, 2.3};
		auto a = comp6771::euclidean_vector(b.begin(), b.end());
		auto a1 = comp6771::euclidean_vector(3, 1.0);
		CHECK(a.change_ret() == false);
		auto value = comp6771::euclidean_norm(a);
		CHECK(value == Approx(5.0487622));
		CHECK(a.change_ret() == true);
		a -= a1;
		CHECK(a.change_ret() == false);
		value = comp6771::euclidean_norm(a);
		CHECK(value == Approx(3.573513677));
		CHECK(a.change_ret() == true);
	}

	SECTION("Testing recalculation for compound multiplication") {
		auto b = std::vector<double>{1.24, 4.32, 2.3};
		auto a = comp6771::euclidean_vector(b.begin(), b.end());
		CHECK(a.change_ret() == false);
		auto value = comp6771::euclidean_norm(a);
		CHECK(value == Approx(5.0487622));
		CHECK(a.change_ret() == true);
		a *= 1;
		CHECK(a.change_ret() == false);
		value = comp6771::euclidean_norm(a);
		CHECK(value == Approx(5.0487622));
		CHECK(a.change_ret() == true);
	}

	SECTION("Testing recalculation for compound division") {
		auto b = std::vector<double>{1.24, 4.32, 2.3};
		auto a = comp6771::euclidean_vector(b.begin(), b.end());
		CHECK(a.change_ret() == false);
		auto value = comp6771::euclidean_norm(a);
		CHECK(value == Approx(5.0487622));
		CHECK(a.change_ret() == true);
		a /= 1;
		CHECK(a.change_ret() == false);
		value = comp6771::euclidean_norm(a);
		CHECK(value == Approx(5.0487622));
		CHECK(a.change_ret() == true);
	}
}