////////////////////////////////////////////////////////////////////////////////
// The MIT License (MIT)
//
// Copyright (c) 2018 Nicholas Frechette & Animation Compression Library contributors
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
////////////////////////////////////////////////////////////////////////////////

#include <catch.hpp>

#include <acl/core/interpolation_utils.h>
#include <acl/math/scalar_32.h>

using namespace acl;

TEST_CASE("interpolation utils", "[core][utils]")
{
	uint32_t key0;
	uint32_t key1;
	float alpha;
	find_linear_interpolation_samples(31, 1.0f, 0.0f, SampleRoundingPolicy::None, key0, key1, alpha);

	REQUIRE(key0 == 0);
	REQUIRE(key1 == 1);
	REQUIRE(scalar_near_equal(alpha, 0.0f, 1.0e-8f));

	find_linear_interpolation_samples(31, 1.0f, 1.0f / 30.0f, SampleRoundingPolicy::None, key0, key1, alpha);

	REQUIRE(key0 == 1);
	REQUIRE(key1 == 2);
	REQUIRE(scalar_near_equal(alpha, 0.0f, 1.0e-8f));

	find_linear_interpolation_samples(31, 1.0f, 2.5f / 30.0f, SampleRoundingPolicy::None, key0, key1, alpha);

	REQUIRE(key0 == 2);
	REQUIRE(key1 == 3);
	REQUIRE(scalar_near_equal(alpha, 0.5f, 1.0e-8f));

	find_linear_interpolation_samples(31, 1.0f, 1.0f, SampleRoundingPolicy::None, key0, key1, alpha);

	REQUIRE(key0 == 30);
	REQUIRE(key1 == 30);
	REQUIRE(scalar_near_equal(alpha, 0.0f, 1.0e-8f));

	find_linear_interpolation_samples(31, 1.0f, 2.5f / 30.0f, SampleRoundingPolicy::Floor, key0, key1, alpha);

	REQUIRE(key0 == 2);
	REQUIRE(key1 == 3);
	REQUIRE(scalar_near_equal(alpha, 0.0f, 1.0e-8f));

	find_linear_interpolation_samples(31, 1.0f, 2.5f / 30.0f, SampleRoundingPolicy::Ceil, key0, key1, alpha);

	REQUIRE(key0 == 2);
	REQUIRE(key1 == 3);
	REQUIRE(scalar_near_equal(alpha, 1.0f, 1.0e-8f));

	find_linear_interpolation_samples(31, 1.0f, 2.4f / 30.0f, SampleRoundingPolicy::Nearest, key0, key1, alpha);

	REQUIRE(key0 == 2);
	REQUIRE(key1 == 3);
	REQUIRE(scalar_near_equal(alpha, 0.0f, 1.0e-8f));

	find_linear_interpolation_samples(31, 1.0f, 2.6f / 30.0f, SampleRoundingPolicy::Nearest, key0, key1, alpha);

	REQUIRE(key0 == 2);
	REQUIRE(key1 == 3);
	REQUIRE(scalar_near_equal(alpha, 1.0f, 1.0e-8f));
}
