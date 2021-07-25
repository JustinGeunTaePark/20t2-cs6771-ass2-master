#include "comp6771/euclidean_vector.hpp"
#include <catch2/catch.hpp>
#include <fmt/format.h>
#include <fmt/ostream.h>
// Written by Justin Geuntae Park (z5060336)
// The following program tests for ONLY operations
// using the implementation found in euclidean_vector.cpp
// All operations start with the empty vector if possible then
// tests for exception cases if applicable. Finally vectors of increasing
// size is used. To determine the contents of the vector
// the output stream, []operator and dimensions() are used, unfortunately it is impossible
// to not use other functions but the test tries to limit it to only these
// two.
TEST_CASE("Testing copy assignment [euclidean_vector& operator=(euclidean_vector const&)]") {
	SECTION("Testing for empty vectors") {
		auto a = comp6771::euclidean_vector(0);
		auto b = comp6771::euclidean_vector(0);
		a = b;
		CHECK(a.dimensions() == 0);
		CHECK(fmt::format("{}", a) == "[]");
		CHECK(b.dimensions() == 0);
		CHECK(fmt::format("{}", b) == "[]");
	}

	SECTION("Testing for default vectors") {
		auto a = comp6771::euclidean_vector();
		auto b = comp6771::euclidean_vector();
		a = b;
		CHECK(a.dimensions() == 1);
		CHECK(a[0] == 0);

		CHECK(b.dimensions() == 1);
		CHECK(b[0] == 0);
	}

	SECTION("Testing for vectors of two different sizes") {
		auto a = comp6771::euclidean_vector(7);
		auto b = comp6771::euclidean_vector(3);
		b[0] = -2.3;
		b[2] = 1000;
		a = b;
		CHECK(a.dimensions() == 3);
		CHECK(a[0] == -2.3);
		CHECK(a[1] == 0);
		CHECK(a[2] == 1000);

		CHECK(b.dimensions() == 3);
		CHECK(b[0] == -2.3);
		CHECK(b[1] == 0);
		CHECK(b[2] == 1000);
	}

	SECTION("Testing for vectors of two different sizes using a different constructor") {
		auto a = comp6771::euclidean_vector{1.2, -2.3, 5.3};
		auto b_vec = std::vector<double>{1.3, 3.3};
		auto b = comp6771::euclidean_vector(b_vec.begin(), b_vec.end());
		a = b;
		CHECK(a.dimensions() == 2);
		CHECK(a[0] == 1.3);
		CHECK(a[1] == 3.3);

		CHECK(b.dimensions() == 2);
		CHECK(b[0] == 1.3);
		CHECK(b[1] == 3.3);
	}
}

TEST_CASE("Testing move assignment [euclidean_vector& operator=(euclidean_vector&&)]") {
	SECTION("Testing for empty vectors") {
		auto a = comp6771::euclidean_vector(0);
		auto b = comp6771::euclidean_vector(0);
		a = std::move(b);
		CHECK(a.dimensions() == 0);
		CHECK(fmt::format("{}", a) == "[]");
		CHECK(fmt::format("{}", b) == "[]");
	}

	SECTION("Testing for default vectors") {
		auto a = comp6771::euclidean_vector();
		auto b = comp6771::euclidean_vector();
		a = std::move(b);
		CHECK(a.dimensions() == 1);
		CHECK(a[0] == 0);
		CHECK(fmt::format("{}", b) == "[]");
	}

	SECTION("Testing for vectors that have different sizes") {
		auto a = comp6771::euclidean_vector{1.2, -2.3, 5.3};
		auto b_vec = std::vector<double>{1.3, 3.3};
		auto b = comp6771::euclidean_vector(b_vec.begin(), b_vec.end());
		a = std::move(b);
		CHECK(a.dimensions() == 2);
		CHECK(a[0] == 1.3);
		CHECK(a[1] == 3.3);
		CHECK(fmt::format("{}", b) == "[]");
	}
}

TEST_CASE("Testing subscript operator [operator[]]") {
	SECTION("Testing for first value") {
		auto const a1 = comp6771::euclidean_vector(3, 3.0);
		CHECK(a1[0] == 3.0);
	}

	SECTION("Testing for middle value") {
		auto const a1 = comp6771::euclidean_vector(3, 2.3);
		CHECK(a1[1] == 2.3);
	}

	SECTION("Testing for end value") {
		auto const a1 = comp6771::euclidean_vector(3, -6.7);
		CHECK(a1[2] == -6.7);
	}

	SECTION("Testing [] operators for a double intializer") {
		auto const a1 = comp6771::euclidean_vector(3, 5.6);
		double a{a1[0]};
		CHECK(a == 5.6);
	}

	SECTION("Testing [] operators for a negative double intializer") {
		auto const a1 = comp6771::euclidean_vector(3, -9.0);
		double a{a1[2]};
		CHECK(a == -9.0);
	}

	SECTION("Testing for changing values of a vector") {
		auto a1 = comp6771::euclidean_vector(4, 14.0);
		a1[0] = 10.0;
		a1[1] = -43.0;
		a1[2] = 0.0;
		CHECK(a1[0] == 10.0);
		CHECK(a1[1] == -43.0);
		CHECK(a1[2] == 0.0);
		CHECK(a1[3] == 14.0);
	}
}

TEST_CASE("Testing unary plus [euclidean_vector operator+()]") {
	SECTION("Testing unary plus for empty vector") {
		auto v1 = comp6771::euclidean_vector(0);
		auto const v2 = +v1;
		CHECK(fmt::format("{}", v1) == "[]");
		CHECK(fmt::format("{}", v2) == "[]");
	}

	SECTION("Testing unary plus for a default vector") {
		auto v1 = comp6771::euclidean_vector();
		auto const v2 = +v1;
		CHECK(v2.dimensions() == 1);
		CHECK(v2[0] == 0);
		CHECK(v1.dimensions() == 1);
		CHECK(v1[0] == 0);
	}

	SECTION("Testing unary plus for multi dimension vector") {
		auto v1 = comp6771::euclidean_vector{-1.2, 4.22, 21.3};
		auto v2 = +v1;
		CHECK(v2[0] == -1.2);
		CHECK(v2[1] == 4.22);
		CHECK(v2[2] == 21.3);
	}
}

TEST_CASE("Testing negation [euclidean_vector operator-()]") {
	SECTION("Testing negation for a empty vector") {
		auto actual = comp6771::euclidean_vector(0);
		auto const expected = comp6771::euclidean_vector(0);
		CHECK(expected == -actual);
	}

	SECTION("Testing negation for a default vector") {
		auto actual = comp6771::euclidean_vector();
		auto const expected = comp6771::euclidean_vector();
		CHECK(expected == -actual);
	}

	SECTION("Testing negation for a vector with dimension 2") {
		auto actual = comp6771::euclidean_vector{-6, 1};
		auto const expected = comp6771::euclidean_vector{6, -1};
		CHECK(expected == -actual);
	}

	SECTION("Testing negation for a vector with dimension 4") {
		auto actual = comp6771::euclidean_vector{-6, 1.12, 6.51, -93.2};
		auto const expected = comp6771::euclidean_vector{6, -1.12, -6.51, 93.2};
		CHECK(expected == -actual);
	}

	SECTION("Testing double negation for a vector with dimension 4") {
		auto actual = comp6771::euclidean_vector{-6, 1.12, 6.51, -93.2};
		auto const expected = comp6771::euclidean_vector{-6, 1.12, 6.51, -93.2};
		CHECK(expected == -(-actual));
	}
}

TEST_CASE("Testing compound addition [euclidean_vector& operator+=(euclidean_vector const&)]") {
	auto a1 = comp6771::euclidean_vector(4, 3.54);
	auto a_neg = comp6771::euclidean_vector(4, -3.54);
	SECTION("Testing for compound addition for two empty vectors") {
		auto a2 = comp6771::euclidean_vector(0);
		auto const a3 = comp6771::euclidean_vector(0);
		REQUIRE(a2.dimensions() == a3.dimensions());
		a2 += a3;
		CHECK(a2.dimensions() == 0);
		CHECK(fmt::format("{}", a2) == "[]");
	}

	SECTION("Testing for compound addition of two different dimensions") {
		auto a2 = comp6771::euclidean_vector(3);
		auto const a3 = comp6771::euclidean_vector(5);
		CHECK_THROWS(a2 += a3, "Dimensions of LHS(3) and RHS(5) do not match");
	}

	SECTION("Testing for compound addition of empty and 2 dimension vector") {
		auto a2 = comp6771::euclidean_vector(2);
		auto const a3 = comp6771::euclidean_vector(0);
		CHECK_THROWS(a2 += a3, "Dimensions of LHS(2) and RHS(0) do not match");
	}

	SECTION("Testing for compound addition of two positive vectors") {
		auto const a2 = comp6771::euclidean_vector(4, 2.46);
		a1 += a2;
		REQUIRE(a1.dimensions() == a2.dimensions());
		CHECK(a1[0] == 6.0);
		CHECK(a1[1] == 6.0);
		CHECK(a1[2] == 6.0);
		CHECK(a1[3] == 6.0);
	}

	SECTION("Testing for compound addition of two vectors, one negative and one positive vector") {
		auto const a2 = comp6771::euclidean_vector(4, -1.54);
		a1 += a2;
		REQUIRE(a1.dimensions() == a2.dimensions());
		CHECK(a1[0] == 2.0);
		CHECK(a1[1] == 2.0);
		CHECK(a1[2] == 2.0);
		CHECK(a1[3] == 2.0);
	}

	SECTION("Testing for compound addition of two vectors, that results in a negative magnitude") {
		auto const a2 = comp6771::euclidean_vector(4, -6.78);
		a1 += a2;
		REQUIRE(a1.dimensions() == a2.dimensions());
		CHECK(a1[0] == -3.24);
		CHECK(a1[1] == -3.24);
		CHECK(a1[2] == -3.24);
		CHECK(a1[3] == -3.24);
	}

	SECTION("Testing for compound addition of two negative vectors") {
		auto const a2 = comp6771::euclidean_vector(4, -6.78);
		a_neg += a2;
		REQUIRE(a1.dimensions() == a2.dimensions());
		CHECK(a_neg[0] == -10.32);
		CHECK(a_neg[1] == -10.32);
		CHECK(a_neg[2] == -10.32);
		CHECK(a_neg[3] == -10.32);
	}

	SECTION("Testing compound addition of the same vector that is empty") {
		auto a2_vector = std::vector<double>{};
		auto a2 = comp6771::euclidean_vector(a2_vector.begin(), a2_vector.end());
		a2 += a2;
		CHECK(fmt::format("{}", a2) == "[]");
	}

	SECTION("Testing compound addition of the same vector") {
		auto a2_vector = std::vector<double>{-1.2, 2.3, 3.4};
		auto a2 = comp6771::euclidean_vector(a2_vector.begin(), a2_vector.end());
		a2 += a2;
		CHECK(a2[0] == -2.4);
		CHECK(a2[1] == 4.6);
		CHECK(a2[2] == 6.8);
	}
}

TEST_CASE("Testing compound subtraction [euclidean_vector& operator-=(euclidean_vector const&)]") {
	auto a1 = comp6771::euclidean_vector(4, 3.54);
	auto a_neg = comp6771::euclidean_vector(4, -3.54);
	SECTION("Testing for compound subtraction for two empty vectors") {
		auto a2 = comp6771::euclidean_vector(0);
		auto const a3 = comp6771::euclidean_vector(0);
		REQUIRE(a2.dimensions() == a3.dimensions());
		a2 -= a3;
		CHECK(a2.dimensions() == 0);
	}

	SECTION("Testing for compound subtraction of two different dimensions") {
		auto a2 = comp6771::euclidean_vector(3);
		auto const a3 = comp6771::euclidean_vector(5);
		CHECK_THROWS(a2 -= a3, "Dimensions of LHS(3) and RHS(5) do not match");
	}

	SECTION("Testing for compound subtraction of empty and 2 dimension vector") {
		auto a2 = comp6771::euclidean_vector(2);
		auto const a3 = comp6771::euclidean_vector(0);
		CHECK_THROWS(a2 -= a3, "Dimensions of LHS(2) and RHS(0) do not match");
	}

	SECTION("Testing for compound subtraction of two positive vectors") {
		auto const a2 = comp6771::euclidean_vector(4, 2.46);
		a1 -= a2;
		REQUIRE(a1.dimensions() == a2.dimensions());
		CHECK(a1[0] == 1.08);
		CHECK(a1[1] == 1.08);
		CHECK(a1[2] == 1.08);
		CHECK(a1[3] == 1.08);
	}

	SECTION("Testing for compound subtraction of two vectors, one negative and one positive "
	        "vector") {
		auto const a2 = comp6771::euclidean_vector(4, -1.54);
		a1 -= a2;
		REQUIRE(a1.dimensions() == a2.dimensions());
		CHECK(a1[0] == 5.08);
		CHECK(a1[1] == 5.08);
		CHECK(a1[2] == 5.08);
		CHECK(a1[3] == 5.08);
	}

	SECTION("Testing for compound subtraction of two vectors, that results in a negative "
	        "magnitude") {
		auto const a2 = comp6771::euclidean_vector(4, 6.48);
		a1 -= a2;
		REQUIRE(a1.dimensions() == a2.dimensions());
		CHECK(a1[0] == Approx(-2.94));
		CHECK(a1[1] == Approx(-2.94));
		CHECK(a1[2] == Approx(-2.94));
		CHECK(a1[3] == Approx(-2.94));
	}

	SECTION("Testing for compound subtraction of two negative vectors") {
		auto const a2 = comp6771::euclidean_vector(4, -6.78);
		a_neg -= a2;
		REQUIRE(a1.dimensions() == a2.dimensions());
		CHECK(a_neg[0] == 3.24);
		CHECK(a_neg[1] == 3.24);
		CHECK(a_neg[2] == 3.24);
		CHECK(a_neg[3] == 3.24);
	}
}

TEST_CASE("Testing compound multiplication [euclidean_vector& operator*=(double)]") {
	auto a1 = comp6771::euclidean_vector(4, 2.12);
	auto a_neg = comp6771::euclidean_vector(4, -2.12);
	SECTION("Testing for compound multiplication for empty vector") {
		auto a2 = comp6771::euclidean_vector(0);
		a2 *= 1.42;
		CHECK(a2.dimensions() == 0);
	}

	SECTION("Testing for compound multiplication of a positive double") {
		a1 *= 3.0;
		CHECK(a1[0] == 6.36);
		CHECK(a1[1] == 6.36);
		CHECK(a1[2] == 6.36);
		CHECK(a1[3] == 6.36);
	}

	SECTION("Testing for compound multiplication of zero") {
		a1 *= 0.0;
		CHECK(a1[0] == 0.0);
		CHECK(a1[1] == 0.0);
		CHECK(a1[2] == 0.0);
		CHECK(a1[3] == 0.0);
	}

	SECTION("Testing for compound multiplication of a negative double") {
		a1 *= -3.14;
		CHECK(a1[0] == Approx(-6.6568));
		CHECK(a1[1] == Approx(-6.6568));
		CHECK(a1[2] == Approx(-6.6568));
		CHECK(a1[3] == Approx(-6.6568));
	}

	SECTION("Testing for compound multiplication of a negative double with a negative vector") {
		a_neg *= -3.14;
		CHECK(a_neg[0] == Approx(6.6568));
		CHECK(a_neg[1] == Approx(6.6568));
		CHECK(a_neg[2] == Approx(6.6568));
		CHECK(a_neg[3] == Approx(6.6568));
	}
}

TEST_CASE("Testing compound division [euclidean_vector& operator/=(double)]") {
	auto a1 = comp6771::euclidean_vector(4, 1.12);
	auto a_neg = comp6771::euclidean_vector(4, -1.12);

	SECTION("Testing for compound division a 3 dimensions") {
		auto a2 = comp6771::euclidean_vector(3);
		CHECK_THROWS(a2 /= 0, "Invalid vector division by 0");
	}

	SECTION("Testing for compound division of empty vector") {
		auto a2 = comp6771::euclidean_vector(0);
		CHECK_THROWS(a2 /= 0, "Invalid vector division by 0");
	}

	SECTION("Testing for compound division for empty vector") {
		auto a2 = comp6771::euclidean_vector(0);
		a2 /= 1.42;
		CHECK(a2.dimensions() == 0);
	}

	SECTION("Testing for compound division of a positive double") {
		a1 /= 3.1;
		CHECK(a1[0] == Approx(0.3612903226));
		CHECK(a1[1] == Approx(0.3612903226));
		CHECK(a1[2] == Approx(0.3612903226));
		CHECK(a1[3] == Approx(0.3612903226));
	}

	SECTION("Testing for compound division of a negative double") {
		a1 /= -3.1;
		CHECK(a1[0] == Approx(-0.3612903226));
		CHECK(a1[1] == Approx(-0.3612903226));
		CHECK(a1[2] == Approx(-0.3612903226));
		CHECK(a1[3] == Approx(-0.3612903226));
	}

	SECTION("Testing for compound division of a negative double with a negative vector") {
		a_neg /= -0.14;
		CHECK(a_neg[0] == 8.0);
		CHECK(a_neg[1] == 8.0);
		CHECK(a_neg[2] == 8.0);
		CHECK(a_neg[3] == 8.0);
	}
}

TEST_CASE("Testing Vector Type Conversion [explicit operator std::vector<double>()]") {
	SECTION("Testing Vector Conversion for a empty vector") {
		auto a = comp6771::euclidean_vector(0);
		auto const vf = static_cast<std::vector<double>>(a);
		CHECK(vf.empty() == true);
	}

	SECTION("Testing Vector Type Conversion for a vector of magnitude 3") {
		auto a = comp6771::euclidean_vector{0.0, 1.0, 2.0};
		auto const vf = static_cast<std::vector<double>>(a);
		CHECK(vf[0] == 0.0);
		CHECK(vf[1] == 1.0);
		CHECK(vf[2] == 2.0);
	}
}

TEST_CASE("Testing List Type Conversion [explicit operator std::list<double>()]") {
	SECTION("Testing List Conversion for a empty vector") {
		auto a = comp6771::euclidean_vector(0);
		auto const vf = static_cast<std::list<double>>(a);
		CHECK(vf.empty() == true);
	}

	SECTION("Testing Vector Type Conversion for a vector of magnitude 3") {
		auto a = comp6771::euclidean_vector{0.0, 1.0, 2.0};
		auto const lf = static_cast<std::list<double>>(a);
		CHECK(lf.size() == 3);
	}
}