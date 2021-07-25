#include "comp6771/euclidean_vector.hpp"
#include <catch2/catch.hpp>
#include <fmt/format.h>
#include <fmt/ostream.h>
// Written by Justin Geuntae Park (z5060336)
// The following program tests for ONLY constructors
// using the implementation found in euclidean_vector.cpp
// All constructors start with the empty vector if possible
// then increase in size. To determine the contents of the vector
// the output stream, []operator and dimensions() are used, unfortunately it is impossible
// to not use other functions but the test tries to limit it to only these
// two.

TEST_CASE("Testing Default Constructor [euclidean_vector()]") {
	auto const a1 = comp6771::euclidean_vector();
	CHECK(a1.dimensions() == 1);
	CHECK(a1[0] == 0.0);
}

TEST_CASE("Testing Single Argument Constructor [explict euclidean_vector(int)]") {
	SECTION("Testing empty vector") {
		auto const a1 = comp6771::euclidean_vector(0);
		CHECK(a1.dimensions() == 0);
		CHECK(fmt::format("{}", a1) == "[]");
	}

	SECTION("Testing for one dimension, should be the same as default constructor") {
		auto const a1 = comp6771::euclidean_vector(1);
		CHECK(a1.dimensions() == 1);
		CHECK(a1[0] == 0.0);
	}

	SECTION("Testing for 4 dimension") {
		auto const a1 = comp6771::euclidean_vector(4);
		CHECK(a1.dimensions() == 4);
		CHECK(a1[0] == 0.0);
		CHECK(a1[1] == 0.0);
		CHECK(a1[2] == 0.0);
		CHECK(a1[3] == 0.0);
	}
}

TEST_CASE("Testing Constructor [euclidean_vector(int, double)]") {
	SECTION("Testing for one dimension, with a negative double") {
		auto const a1 = comp6771::euclidean_vector(1, -3.2);
		CHECK(a1.dimensions() == 1);
		CHECK(a1[0] == -3.2);
	}

	SECTION("Testing for multiple dimension, using a different method negative double") {
		auto x = int{3};
		auto y = double{-1.23};
		auto const a1 = comp6771::euclidean_vector(x, y);
		CHECK(a1.dimensions() == 3);
		CHECK(a1[0] == -1.23);
		CHECK(a1[1] == -1.23);
		CHECK(a1[2] == -1.23);
	}

	SECTION("Testing for 6 dimensions, with a double") {
		auto const a1 = comp6771::euclidean_vector(6, 13.34);
		CHECK(a1.dimensions() == 6);
		CHECK(a1[0] == 13.34);
		CHECK(a1[1] == 13.34);
		CHECK(a1[2] == 13.34);
		CHECK(a1[3] == 13.34);
		CHECK(a1[4] == 13.34);
		CHECK(a1[5] == 13.34);
	}

	SECTION("Testing for multiple dimensions, using a different method double") {
		auto x = int{3};
		auto y = double{3.24};
		auto const a1 = comp6771::euclidean_vector(x, y);
		CHECK(a1.dimensions() == 3);
		CHECK(a1[0] == 3.24);
		CHECK(a1[1] == 3.24);
		CHECK(a1[2] == 3.24);
	}
}

TEST_CASE("Testing Constructor [euclidean_vector(std::vector<double>::const_iterator, "
          "std::vector<double>::const_iterator)]") {
	SECTION("Testing constructor for a empty vector") {
		auto const v = std::vector<double>{};
		auto c = comp6771::euclidean_vector(v.begin(), v.end());
		CHECK(c.dimensions() == 0);
		CHECK(fmt::format("{}", c) == "[]");
	}

	SECTION("Testing constructor for a vector<double> list of size 1") {
		auto const v = std::vector<double>{-1.2};
		auto c = comp6771::euclidean_vector(v.begin(), v.end());
		CHECK(c.dimensions() == 1);
		CHECK(c[0] == -1.2);
	}

	SECTION("Testing constructor for a vector<double> list of size 4") {
		auto const v = std::vector<double>{5.0, 6.5, 7.91};
		auto c = comp6771::euclidean_vector(v.begin(), v.end());
		CHECK(c.dimensions() == 3);
		CHECK(c[0] == 5.0);
		CHECK(c[1] == 6.5);
		CHECK(c[2] == 7.91);
	}
}

TEST_CASE("Testing Constructor [euclidean_vector(std::initializer_list<double>)]") {
	SECTION("Testing for a empty list") {
		// When list is empty, it initalizes to {0}
		auto const b = comp6771::euclidean_vector{};
		CHECK(b.dimensions() == 1);
		CHECK(fmt::format("{}", b) == "[0]");
	}

	SECTION("Testing for a list with size 1") {
		auto const b = comp6771::euclidean_vector{-1.34};
		CHECK(b.dimensions() == 1);
		CHECK(b[0] == -1.34);
	}

	SECTION("Testing for a list with size 3") {
		auto const b = comp6771::euclidean_vector{1.0, 2.0, 3.0};
		CHECK(b.dimensions() == 3);
		CHECK(b[0] == 1.0);
		CHECK(b[1] == 2.0);
		CHECK(b[2] == 3.0);
	}

	SECTION("Testing for a list with size 5") {
		auto const b = comp6771::euclidean_vector{1.0, -2.33, 3.0, 91.3, -10000.3};
		CHECK(b.dimensions() == 5);
		CHECK(b[0] == 1.0);
		CHECK(b[1] == -2.33);
		CHECK(b[2] == 3.0);
		CHECK(b[3] == 91.3);
		CHECK(b[4] == -10000.3);
	}
}

TEST_CASE("Testing Copy Constructor [euclidean_vector(euclidean_vector const&)]") {
	SECTION("Testing copy for a empty vector") {
		auto const a = comp6771::euclidean_vector(0);
		auto a_copy = comp6771::euclidean_vector(a);
		CHECK(a_copy.dimensions() == 0);
		CHECK(fmt::format("{}", a_copy) == "[]");
		CHECK(a.dimensions() == 0);
		CHECK(fmt::format("{}", a) == "[]");
	}

	SECTION("Testing copy for a default vector") {
		auto const a = comp6771::euclidean_vector();
		auto a_copy = comp6771::euclidean_vector(a);
		CHECK(a_copy.dimensions() == 1);
		CHECK(a_copy[0] == 0);
		CHECK(a.dimensions() == 1);
		CHECK(a[0] == 0);
	}

	SECTION("Testing copy for a single argument constructor of size 4") {
		auto const a = comp6771::euclidean_vector(4);
		auto a_copy = comp6771::euclidean_vector(a);
		CHECK(a_copy.dimensions() == 4);
		CHECK(a_copy[0] == 0);
		CHECK(a_copy[1] == 0);
		CHECK(a_copy[2] == 0);
		CHECK(a_copy[3] == 0);
		CHECK(a.dimensions() == 4);
		CHECK(a[0] == 0);
		CHECK(a[1] == 0);
		CHECK(a[2] == 0);
		CHECK(a[3] == 0);
	}

	SECTION("Testing copy for the same vector that is empty") {
		auto a = comp6771::euclidean_vector(0);
		a = comp6771::euclidean_vector(a);
		CHECK(a.dimensions() == 0);
		CHECK(fmt::format("{}", a) == "[]");
	}

	SECTION("Testing copy for the same vector") {
		auto a = comp6771::euclidean_vector{4, 1};
		a = comp6771::euclidean_vector(a);
		CHECK(a.dimensions() == 2);
		CHECK(a[0] == 4);
		CHECK(a[1] == 1);
	}
}

TEST_CASE("Testing Move Constructor [euclidean_vector(euclidean_vector const&)]") {
	SECTION("Testing move for a empty vector") {
		auto a = comp6771::euclidean_vector(0);
		auto a_move = comp6771::euclidean_vector(std::move(a));
		CHECK(a_move.dimensions() == 0);
		CHECK(fmt::format("{}", a_move) == "[]");
		CHECK(fmt::format("{}", a) == "[]");
	}

	SECTION("Testing move for a default vector") {
		auto a = comp6771::euclidean_vector();
		auto a_move = comp6771::euclidean_vector(std::move(a));
		CHECK(a_move.dimensions() == 1);
		CHECK(a_move[0] == 0);
		CHECK(fmt::format("{}", a) == "[]");
	}

	SECTION("Testing move for a single argument constructor of size 4") {
		auto a = comp6771::euclidean_vector(4);
		auto a_move = comp6771::euclidean_vector(std::move(a));
		CHECK(a_move.dimensions() == 4);
		CHECK(a_move[0] == 0);
		CHECK(a_move[1] == 0);
		CHECK(a_move[2] == 0);
		CHECK(a_move[3] == 0);
		CHECK(fmt::format("{}", a) == "[]");
	}

	SECTION("Testing move for the same vector that is empty") {
		auto a = comp6771::euclidean_vector(0);
		a = comp6771::euclidean_vector(std::move(a));
		CHECK(a.dimensions() == 0);
		CHECK(fmt::format("{}", a) == "[]");
	}

	SECTION("Testing move for the same vector") {
		auto a = comp6771::euclidean_vector{4, 1};
		a = comp6771::euclidean_vector(std::move(a));
		CHECK(a.dimensions() == 2);
		CHECK(a[0] == 4);
		CHECK(a[1] == 1);
	}
}