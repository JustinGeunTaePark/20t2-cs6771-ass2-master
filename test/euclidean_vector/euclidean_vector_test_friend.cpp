#include "comp6771/euclidean_vector.hpp"
#include <catch2/catch.hpp>
#include <fmt/format.h>
#include <fmt/ostream.h>
// Written by Justin Geuntae Park (z5060336)
// The following program tests for ONLY friend operations
// using the implementation found in euclidean_vector.cpp
// All operations start with the empty vector if possible then
// tests for exception cases if applicable. Finally vectors of increasing
// size is used. To determine the contents of the vector
// the output stream, []operator and dimensions() are used, unfortunately it is impossible
// to not use other functions but the test tries to limit it to only these
// two.

TEST_CASE("Testing Equal [bool operator==(euclidean_vector const&, euclidean_vector const&)]") {
	SECTION("Testing two empty vectors") {
		auto const a1 = comp6771::euclidean_vector(0);
		auto const a2 = comp6771::euclidean_vector(0);
		CHECK((a1 == a2) == true);
	}

	SECTION("Testing a empty vector and a 3 dimensional vector") {
		auto const a1 = comp6771::euclidean_vector(0);
		auto const a2 = comp6771::euclidean_vector(3);
		CHECK((a1 == a2) == false);
	}

	SECTION("Testing two default vectors") {
		auto const a1 = comp6771::euclidean_vector();
		auto const a2 = comp6771::euclidean_vector();
		CHECK((a1 == a2) == true);
	}

	SECTION("Testing two multiple dimension vectors that are actually equal") {
		auto const a1 = comp6771::euclidean_vector(4, 3.4);
		auto const a2 = comp6771::euclidean_vector(4, 3.4);
		CHECK((a1 == a2) == true);
	}

	SECTION("Testing two vectors that have different dimensions") {
		auto const a1 = comp6771::euclidean_vector(4, 3.4);
		auto const a2 = comp6771::euclidean_vector(2, 3.4);
		CHECK((a1 == a2) == false);
	}

	SECTION("Testing two vectors that have same dimensions but different magnitudes") {
		auto a1 = comp6771::euclidean_vector(4, 3.4);
		a1[0] = 1.2;
		a1[3] = 9.7;
		auto const a2 = comp6771::euclidean_vector(4, 3.4);
		CHECK((a1 == a2) == false);
	}
}

TEST_CASE("Testing Not Equal [bool operator!=(euclidean_vector const&, euclidean_vector const&)]") {
	SECTION("Testing two empty vectors") {
		auto const a1 = comp6771::euclidean_vector(0);
		auto const a2 = comp6771::euclidean_vector(0);
		CHECK((a1 != a2) == false);
	}

	SECTION("Testing a empty vector and a 3 dimensional vector") {
		auto const a1 = comp6771::euclidean_vector(0);
		auto const a2 = comp6771::euclidean_vector(3);
		CHECK((a1 != a2) == true);
	}

	SECTION("Testing two default vectors") {
		auto const a1 = comp6771::euclidean_vector();
		auto const a2 = comp6771::euclidean_vector();
		CHECK((a1 != a2) == false);
	}

	SECTION("Testing two multiple dimension vectors that are actually equal") {
		auto const a1 = comp6771::euclidean_vector(4, 3.4);
		auto const a2 = comp6771::euclidean_vector(4, 3.4);
		CHECK((a1 != a2) == false);
	}

	SECTION("Testing two vectors that have different dimensions") {
		auto const a1 = comp6771::euclidean_vector(4, 3.4);
		auto const a2 = comp6771::euclidean_vector(2, 3.4);
		CHECK((a1 != a2) == true);
	}

	SECTION("Testing two vectors that have same dimensions and one same magnitude") {
		auto a1 = comp6771::euclidean_vector(4, 3.4);
		a1[0] = 1.2;
		a1[3] = 9.7;
		auto const a2 = comp6771::euclidean_vector(4, 3.4);
		CHECK((a1 != a2) == false);
	}

	SECTION("Testing two vectors that have same dimensions and all different magnitude") {
		auto a1 = comp6771::euclidean_vector(4, 3.4);
		a1[0] = 1.2;
		a1[1] = -2.3;
		a1[2] = 10.4;
		a1[3] = 9.7;
		auto const a2 = comp6771::euclidean_vector(4, 3.4);
		CHECK((a1 != a2) == true);
	}
}

TEST_CASE("Testing for addition [euclidean_vector operator+(euclidean_vector const&, "
          "euclidean_vector const&)]") {
	SECTION("Testing for two empty vectors") {
		auto const a1 = comp6771::euclidean_vector(0);
		auto const a2 = comp6771::euclidean_vector(0);
		auto const a3 = a1 + a2;
		CHECK(a3.dimensions() == 0);
		CHECK(fmt::format("{}", a3) == "[]");
	}

	SECTION("Testing for one empty vector and 3 dimension vector") {
		auto const a1 = comp6771::euclidean_vector(0);
		auto const a2 = comp6771::euclidean_vector(3);
		CHECK_THROWS(a1 + a2, "Dimensions of LHS(0) and RHS(3) do not match");
	}

	SECTION("Testing for 3 and 5 dimensional vectors") {
		auto const a1 = comp6771::euclidean_vector(3);
		auto const a2 = comp6771::euclidean_vector(5);
		CHECK_THROWS(a1 + a2, "Dimensions of LHS(3) and RHS(5) do not match");
	}

	SECTION("Testing for 3,0 and 5 dimensional vectors") {
		auto const a1 = comp6771::euclidean_vector(3);
		auto const a2 = comp6771::euclidean_vector(0);
		auto const a3 = comp6771::euclidean_vector(5);
		CHECK_THROWS(a1 + a2 + a3, "Dimensions of LHS(3) and RHS(0) do not match");
	}

	SECTION("Testing two default vectors") {
		auto const a1 = comp6771::euclidean_vector();
		auto const a2 = comp6771::euclidean_vector();
		REQUIRE(a1.dimensions() == a2.dimensions());
		auto const a3 = a1 + a2;
		CHECK(a3[0] == 0.0);
	}

	SECTION("Testing for two vectors with multiple dimensions and are both positive") {
		auto const a1 = comp6771::euclidean_vector(3, 3.0);
		auto const a2 = comp6771::euclidean_vector(3, 3.0);
		REQUIRE(a1.dimensions() == a2.dimensions());
		auto const a3 = a1 + a2;
		CHECK(a3[0] == 6.0);
		CHECK(a3[1] == 6.0);
		CHECK(a3[2] == 6.0);
	}

	SECTION("Testing for two vectors with one negative and one positive") {
		auto const a1 = comp6771::euclidean_vector(3, 6.7);
		auto const a2 = comp6771::euclidean_vector(3, -4.7);
		REQUIRE(a1.dimensions() == a2.dimensions());
		auto const a3 = a1 + a2;
		CHECK(a3[0] == 2.0);
		CHECK(a3[1] == 2.0);
		CHECK(a3[2] == 2.0);
	}

	SECTION("Testing for two vectors with one negative and one positive that results in a negative "
	        "value") {
		auto const a1 = comp6771::euclidean_vector(3, 6.7);
		auto const a2 = comp6771::euclidean_vector(3, -10.7);
		REQUIRE(a1.dimensions() == a2.dimensions());
		auto const a3 = a1 + a2;
		CHECK(a3[0] == Approx(-4.0));
		CHECK(a3[1] == Approx(-4.0));
		CHECK(a3[2] == Approx(-4.0));
	}

	SECTION("Testing for addition of multiple vectors") {
		auto const a1 = comp6771::euclidean_vector(3, 6.7);
		auto const a2 = comp6771::euclidean_vector(3, -10.7);
		auto const a3 = comp6771::euclidean_vector(3, 14.8);
		REQUIRE(a1.dimensions() == a2.dimensions());
		REQUIRE(a2.dimensions() == a3.dimensions());
		auto const a4 = a1 + a2 + a3;
		CHECK(a4[0] == 10.8);
		CHECK(a4[1] == 10.8);
		CHECK(a4[2] == 10.8);
	}

	SECTION("Test for two same vectors") {
		auto const a2 = comp6771::euclidean_vector(3, 10);
		auto const a3 = a2 + a2;
		CHECK(a3[0] == 20);
		CHECK(a3[1] == 20);
		CHECK(a3[2] == 20);
	}
}

TEST_CASE("Testing for subtraction [euclidean_vector operator-(euclidean_vector const&, "
          "euclidean_vector const&)]") {
	SECTION("Testing for two empty vectors") {
		auto const a1 = comp6771::euclidean_vector(0);
		auto const a2 = comp6771::euclidean_vector(0);
		auto const a3 = a1 - a2;
		CHECK(a3.dimensions() == 0);
		CHECK(fmt::format("{}", a3) == "[]");
	}

	SECTION("Testing for one empty vector and 3 dimension vector") {
		auto const a1 = comp6771::euclidean_vector(0);
		auto const a2 = comp6771::euclidean_vector(3);
		CHECK_THROWS(a1 - a2, "Dimensions of LHS(0) and RHS(3) do not match");
	}

	SECTION("Testing for 3 and 5 dimensional vectors") {
		auto const a1 = comp6771::euclidean_vector(5);
		auto const a2 = comp6771::euclidean_vector(3);
		CHECK_THROWS(a1 - a2, "Dimensions of LHS(5) and RHS(3) do not match");
	}

	SECTION("Testing for 3,0 and 5 dimensional vectors") {
		auto const a1 = comp6771::euclidean_vector(3);
		auto const a2 = comp6771::euclidean_vector(0);
		auto const a3 = comp6771::euclidean_vector(5);
		CHECK_THROWS(a1 - a2 - a3, "Dimensions of LHS(3) and RHS(0) do not match");
	}

	SECTION("Testing two default vectors") {
		auto const a1 = comp6771::euclidean_vector();
		auto const a2 = comp6771::euclidean_vector();
		REQUIRE(a1.dimensions() == a2.dimensions());
		auto const a3 = a1 - a2;
		CHECK(a3[0] == 0.0);
	}

	SECTION("Testing for two vectors with multiple dimensions and are both positive") {
		auto const a1 = comp6771::euclidean_vector(3, 3.0);
		auto const a2 = comp6771::euclidean_vector(3, 3.0);
		REQUIRE(a1.dimensions() == a2.dimensions());
		auto const a3 = a1 - a2;
		CHECK(a3[0] == 0.0);
		CHECK(a3[1] == 0.0);
		CHECK(a3[2] == 0.0);
	}

	SECTION("Testing for two vectors with one negative and one positive") {
		auto const a1 = comp6771::euclidean_vector(3, 6.7);
		auto const a2 = comp6771::euclidean_vector(3, -4.3);
		REQUIRE(a1.dimensions() == a2.dimensions());
		auto const a3 = a1 - a2;
		CHECK(a3[0] == 11.0);
		CHECK(a3[1] == 11.0);
		CHECK(a3[2] == 11.0);
	}

	SECTION("Testing for two vectors with one negative and one positive that results in a negative "
	        "value") {
		auto const a1 = comp6771::euclidean_vector(3, -6.7);
		auto const a2 = comp6771::euclidean_vector(3, -1.7);
		REQUIRE(a1.dimensions() == a2.dimensions());
		auto const a3 = a1 - a2;
		CHECK(a3[0] == -5.0);
		CHECK(a3[1] == -5.0);
		CHECK(a3[2] == -5.0);
	}

	SECTION("Testing for subtraction of multiple vectors") {
		auto const a1 = comp6771::euclidean_vector(3, 6.7);
		auto const a2 = comp6771::euclidean_vector(3, -10.7);
		auto const a3 = comp6771::euclidean_vector(3, 14.8);
		REQUIRE(a1.dimensions() == a2.dimensions());
		REQUIRE(a2.dimensions() == a3.dimensions());
		auto const a4 = a1 - a2 - a3;
		CHECK(a4[0] == Approx(2.6));
		CHECK(a4[1] == Approx(2.6));
		CHECK(a4[2] == Approx(2.6));
	}
}

TEST_CASE("Testing for multiplication [euclidean_vector operator*(euclidean_vector const&, "
          "double)]") {
	SECTION("Testing for a empty vector") {
		auto const a1 = comp6771::euclidean_vector(0);
		auto const a2 = a1 * -1.3;
		auto const a3 = comp6771::euclidean_vector(0);
		CHECK(a2.dimensions() == 0);
		CHECK(a2 == a3);
	}

	SECTION("Testing for default vector") {
		auto const a1 = comp6771::euclidean_vector();
		auto const a2 = a1 * 3.0;
		CHECK(a2[0] == 0.0);
	}

	SECTION("Testing a vector with a positive double") {
		auto const a1 = comp6771::euclidean_vector(3, 3.0);
		auto const a2 = a1 * 5.6;
		CHECK(a2[0] == Approx(16.8));
		CHECK(a2[1] == Approx(16.8));
		CHECK(a2[2] == Approx(16.8));
	}

	SECTION("Testing a vector with a negative double") {
		auto const a1 = comp6771::euclidean_vector(3, 6.7);
		auto const a2 = a1 * -2.1;
		CHECK(a2[0] == -14.07);
		CHECK(a2[1] == -14.07);
		CHECK(a2[2] == -14.07);
	}

	SECTION("Testing a negative vector with a negative double") {
		auto const a1 = comp6771::euclidean_vector(3, -9.0);
		auto const a2 = a1 * -3.0;
		CHECK(a2[0] == 27.0);
		CHECK(a2[1] == 27.0);
		CHECK(a2[2] == 27.0);
	}

	SECTION("Testing multiplication of a vector and double but in opposite position") {
		auto const a1 = comp6771::euclidean_vector(3, -9.0);
		auto const a2 = 3.0 * a1;
		CHECK(a2[0] == -27.0);
		CHECK(a2[1] == -27.0);
		CHECK(a2[2] == -27.0);

		auto const a3 = -3.0 * a1;
		CHECK(a3[0] == 27.0);
		CHECK(a3[1] == 27.0);
		CHECK(a3[2] == 27.0);
	}

	SECTION("Testing multiplication of a vector and double but in opposite position") {
		auto const a1 = comp6771::euclidean_vector(3, 1.0);
		double c = 3.0;
		auto const a2 = c * a1;
		CHECK(a2[0] == 3.0);
		CHECK(a2[1] == 3.0);
		CHECK(a2[2] == 3.0);
	}
}

TEST_CASE("Testing for division [euclidean_vector operator/(euclidean_vector const&, double)]") {
	SECTION("Testing for empty vector") {
		auto const a1 = comp6771::euclidean_vector(0);
		auto const a2 = a1 / -24.5;
		auto const a3 = comp6771::euclidean_vector(0);
		CHECK(a2.dimensions() == 0);
		CHECK(a2 == a3);
	}

	SECTION("Testing division by 0 of empty vector") {
		auto const a1 = comp6771::euclidean_vector(0);
		CHECK_THROWS(a1 / 0);
	}

	SECTION("Testing division by 0 of a 3 dimension vector") {
		auto const a1 = comp6771::euclidean_vector(3);
		CHECK_THROWS(a1 / 0);
	}

	SECTION("Testing for default vector") {
		auto const a1 = comp6771::euclidean_vector();
		auto const a2 = a1 / 3.0;
		CHECK(a2[0] == 0.0);
	}

	SECTION("Testing for division of a positive vector with a positive double") {
		auto const a1 = comp6771::euclidean_vector(4, 12.0);
		auto const a2 = a1 / 3.0;
		CHECK(a2[0] == 4.0);
		CHECK(a2[1] == 4.0);
		CHECK(a2[2] == 4.0);
		CHECK(a2[3] == 4.0);
	}

	SECTION("Testing for division of a positive vector with a negative double") {
		auto const a1 = comp6771::euclidean_vector(4, 4.0);
		double const value = -4;
		auto const a2 = a1 / value;
		CHECK(a2[0] == -1.0);
		CHECK(a2[1] == -1.0);
		CHECK(a2[2] == -1.0);
		CHECK(a2[3] == -1.0);
	}

	SECTION("Testing for division of a negative vector with a negative double") {
		auto const a1 = comp6771::euclidean_vector(3, -4.0);
		auto const a2 = a1 / -2.5;
		CHECK(a2[0] == 1.6);
		CHECK(a2[1] == 1.6);
		CHECK(a2[2] == 1.6);
	}
}

TEST_CASE("Testing for output stream [std::ostream& operator<<(std::ostream&, euclidean_vector "
          "const&)]") {
	SECTION("Testing for empty vector") {
		auto const a1 = comp6771::euclidean_vector(0);
		CHECK(fmt::format("{}", a1) == "[]");
	}
	SECTION("Testing for default vector") {
		auto const a1 = comp6771::euclidean_vector();
		CHECK(fmt::format("{}", a1) == "[0]");
	}

	SECTION("Testing for a vector with same values") {
		auto const a1 = comp6771::euclidean_vector(4, 2.3);
		CHECK(fmt::format("{}", a1) == "[2.3 2.3 2.3 2.3]");
	}

	SECTION("Testing for a vector with different values") {
		auto a1 = comp6771::euclidean_vector(4, 2.3);
		a1[0] = -3.2;
		a1[2] = -1.34;
		a1[3] = 45.2;
		CHECK(fmt::format("{}", a1) == "[-3.2 2.3 -1.34 45.2]");
	}

	SECTION("Testing for a vector with friend operations") {
		auto const a1 = comp6771::euclidean_vector(3, 3.0);
		auto const a2 = comp6771::euclidean_vector(3, -3.0);
		auto const a3 = comp6771::euclidean_vector(3, 3.0);
		CHECK(fmt::format("{}", a1 + a2 + a3) == "[3 3 3]");
		CHECK(fmt::format("{}", a1 - a2 - a3) == "[3 3 3]");
		CHECK(fmt::format("{}", a1 * 2) == "[6 6 6]");
		CHECK(fmt::format("{}", a2 / 3) == "[-1 -1 -1]");
	}
}