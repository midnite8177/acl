#pragma once

////////////////////////////////////////////////////////////////////////////////
// The MIT License (MIT)
//
// Copyright (c) 2017 Nicholas Frechette & Animation Compression Library contributors
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

#include "acl/core/error.h"
#include "acl/math/scalar_32.h"

#include <cstdint>

namespace acl
{
	inline uint32_t pack_scalar_unsigned(float input, uint8_t num_bits)
	{
		ACL_ASSERT(num_bits < 31, "Attempting to pack on too many bits");
		ACL_ASSERT(input >= 0.0f && input <= 1.0f, "Expected normalized unsigned input value: %f", input);
		const uint32_t max_value = (1 << num_bits) - 1;
		return static_cast<uint32_t>(symmetric_round(input * safe_to_float(max_value)));
	}

	inline float unpack_scalar_unsigned(uint32_t input, uint8_t num_bits)
	{
		ACL_ASSERT(num_bits < 31, "Attempting to unpack from too many bits");
		const uint32_t max_value = (1 << num_bits) - 1;
		ACL_ASSERT(input <= max_value, "Input value too large: %ull", input);
		return safe_to_float(input) / safe_to_float(max_value);
	}

	inline uint32_t pack_scalar_signed(float input, uint8_t num_bits)
	{
		return pack_scalar_unsigned((input * 0.5f) + 0.5f, num_bits);
	}

	inline float unpack_scalar_signed(uint32_t input, uint8_t num_bits)
	{
		return (unpack_scalar_unsigned(input, num_bits) * 2.0f) - 1.0f;
	}
}
