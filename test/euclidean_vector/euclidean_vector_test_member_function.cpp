#include "comp6771/euclidean_vector.hpp"
#include <catch2/catch.hpp>
#include <fmt/format.h>
#include <fmt/ostream.h>
// Written by Justin Geuntae Park (z5060336)
// The following program tests for ONLY member functions
// using the implementation found in euclidean_vector.cpp
// All operations start with the empty vector if possible then
// tests for exception cases if applicable. Finally vectors of increasing
// size is used. To determine the contents of the vector
// the at() and dimensions() are used.

TEST_CASE("Testing at [double(&) at(int) const]") {
	SECTION("Testing for empty vector") {
		auto const a1 = comp6771::euclidean_vector(0);
		CHECK_THROWS(a1.at(-1));
		CHECK_THROWS(a1.at(0));
		CHECK_THROWS(a1.at(13));
	}

	SECTION("Testing for exception of 3 dimension vector") {
		auto const a1 = comp6771::euclidean_vector(3);
		CHECK_THROWS(a1.at(-3));
		CHECK_THROWS(a1.at(13));
	}

	SECTION("Testing Default Vector") {
		auto const a1 = comp6771::euclidean_vector();
		CHECK(a1.at(0) == 0.0);
	}

	SECTION("Testing a vector of length 3 with same magnitudes") {
		auto const a1 = comp6771::euclidean_vector(3, 3.0);
		CHECK(a1.at(0) == 3.0);
		CHECK(a1.at(1) == 3.0);
		CHECK(a1.at(2) == 3.0);
	}

	SECTION("Testing a vector of length 3 but with different magnitudes") {
		auto a1 = comp6771::euclidean_vector(3, 3.0);
		a1[0] = -1.3;
		a1[2] = 4.5;
		CHECK(a1.at(0) == -1.3);
		CHECK(a1.at(1) == 3.0);
		CHECK(a1.at(2) == 4.5);
	}

	SECTION("Checking at to assign a value for a particular dimension") {
		auto a1 = comp6771::euclidean_vector(3, 3.0);
		a1.at(0) = -1.3;
		a1.at(1) = 4.5;
		CHECK(a1.at(0) == -1.3);
		CHECK(a1.at(1) == 4.5);
		CHECK(a1.at(2) == 3.0);
	}
}

TEST_CASE("Testing Dimension [int dimensions()]") {
	SECTION("Testing Empty Vector") {
		auto const a1 = comp6771::euclidean_vector(0);
		CHECK(a1.dimensions() == 0);
	}

	SECTION("Testing Default Vector") {
		auto const a1 = comp6771::euclidean_vector();
		CHECK(a1.dimensions() == 1);
	}

	SECTION("Testing vector of length 2") {
		auto const a1 = comp6771::euclidean_vector(2);
		CHECK(a1.dimensions() == 2);
	}

	SECTION("Testing vector of length 3") {
		auto const a1 = comp6771::euclidean_vector(3);
		CHECK(a1.dimensions() == 3);
	}
}