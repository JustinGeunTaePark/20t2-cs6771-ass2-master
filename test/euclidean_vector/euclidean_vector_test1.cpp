#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <fmt/format.h>
#include <fmt/ostream.h>

TEST_CASE("basic test") {
	auto const a1 = comp6771::euclidean_vector(3, 3.0);
	auto const a2 = comp6771::euclidean_vector(3, 3.0);
	auto const a3 = comp6771::euclidean_vector(3, 3.0);
	auto const a4 = a1 + a2 + a3;
	double test{a1[0]};
	CHECK(test == 3.0);
	CHECK(a1[0] == 3.0);
	CHECK(a4[0] == 9.0);
	CHECK(a4[1] == 9.0);
	CHECK(a4[2] == 9.0);
	// CHECK(fmt::format("{}", a1 + a2 + a3) == "[9 9 9]");
}

TEST_CASE("Testing Constructor [euclidean_vector(std::vector<double>::const_iterator, "
          "std::vector<double>::const_iterator)]") {
	SECTION("Testing constructor for a vector<double> list of size 4") {
		auto v = std::vector<double>{5.0, 6.5, 7.91};
		auto c = comp6771::euclidean_vector(v.begin(), v.end());
		CHECK(c.dimensions() == 3);
		CHECK(c[0] == 5.0);
		CHECK(c[1] == 6.5);
		CHECK(c[2] == 7.91);
		v[0] = -12.3;
		v[1] = -2.2;
		CHECK(c.dimensions() == 3);
		CHECK(c[0] == 5.0);
		CHECK(c[1] == 6.5);
		CHECK(c[2] == 7.91);
		CHECK(c.dimensions() == 3);
		CHECK(v[0] == -12.3);
		CHECK(v[1] == -2.2);
		CHECK(v[2] == 7.91);
		v.clear();
		CHECK(c.dimensions() == 3);
		CHECK(c[0] == 5.0);
		CHECK(c[1] == 6.5);
		CHECK(c[2] == 7.91);
	}
}