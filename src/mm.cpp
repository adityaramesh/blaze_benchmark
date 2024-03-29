/*
** File Name:	mm.cpp
** Author:	Aditya Ramesh
** Date:	05/05/2013
** Contact:	_@adityaramesh.com
*/

#include <common.hpp>
	
using value_type = float;
using darray     = std::unique_ptr<value_type[]>;
static constexpr auto n = 1024u;

static void mm_ijk()
{
	auto a = darray{new value_type[n * n]};
	auto b = darray{new value_type[n * n]};
	auto c = darray{new value_type[n * n]};

	for (auto i = 0u; i != n; ++i) {
	for (auto j = 0u; j != n; ++j) {
	for (auto k = 0u; k != n; ++k) {
		c[n * i + j] += a[n * i + k] * b[n * k + j];
	}}}
}

static void mm_ikj()
{
	auto a = darray{new value_type[n * n]};
	auto b = darray{new value_type[n * n]};
	auto c = darray{new value_type[n * n]};

	for (auto i = 0u; i != n; ++i) {
	for (auto k = 0u; k != n; ++k) {
	for (auto j = 0u; j != n; ++j) {
		c[n * i + j] += a[n * i + k] * b[n * k + j];
	}}}
}

static void mm_jik()
{
	auto a = darray{new value_type[n * n]};
	auto b = darray{new value_type[n * n]};
	auto c = darray{new value_type[n * n]};

	for (auto j = 0u; j != n; ++j) {
	for (auto i = 0u; i != n; ++i) {
	for (auto k = 0u; k != n; ++k) {
		c[n * i + j] += a[n * i + k] * b[n * k + j];
	}}}
}

static void mm_jki()
{
	auto a = darray{new value_type[n * n]};
	auto b = darray{new value_type[n * n]};
	auto c = darray{new value_type[n * n]};

	for (auto j = 0u; j != n; ++j) {
	for (auto k = 0u; k != n; ++k) {
	for (auto i = 0u; i != n; ++i) {
		c[n * i + j] += a[n * i + k] * b[n * k + j];
	}}}
}

static void mm_kij()
{
	auto a = darray{new value_type[n * n]};
	auto b = darray{new value_type[n * n]};
	auto c = darray{new value_type[n * n]};

	for (auto k = 0u; k != n; ++k) {
	for (auto i = 0u; i != n; ++i) {
	for (auto j = 0u; j != n; ++j) {
		c[n * i + j] += a[n * i + k] * b[n * k + j];
	}}}
}

static void mm_kji()
{
	auto a = darray{new value_type[n * n]};
	auto b = darray{new value_type[n * n]};
	auto c = darray{new value_type[n * n]};

	for (auto k = 0u; k != n; ++k) {
	for (auto j = 0u; j != n; ++j) {
	for (auto i = 0u; i != n; ++i) {
		c[n * i + j] += a[n * i + k] * b[n * k + j];
	}}}
}

static void mm_u2()
{
	auto a = darray{new value_type[n * n]};
	auto b = darray{new value_type[n * n]};
	auto c = darray{new value_type[n * n]};

	for (auto i = 0u; i != n; ++i) {
	for (auto k = 0u; k != n; ++k) {
	for (auto j = 0u; j != n; j += 2) {
		c[n * i + j + 0] += a[n * i + k] * b[n * k + j + 0];
		c[n * i + j + 1] += a[n * i + k] * b[n * k + j + 1];
	}}}
}

static void mm_u4()
{
	auto a = darray{new value_type[n * n]};
	auto b = darray{new value_type[n * n]};
	auto c = darray{new value_type[n * n]};

	for (auto i = 0u; i != n; ++i) {
	for (auto k = 0u; k != n; ++k) {
	for (auto j = 0u; j != n; j += 4) {
		c[n * i + j + 0] += a[n * i + k] * b[n * k + j + 0];
		c[n * i + j + 1] += a[n * i + k] * b[n * k + j + 1];
		c[n * i + j + 2] += a[n * i + k] * b[n * k + j + 2];
		c[n * i + j + 3] += a[n * i + k] * b[n * k + j + 3];
	}}}
}

static void mm_u8()
{
	auto a = darray{new value_type[n * n]};
	auto b = darray{new value_type[n * n]};
	auto c = darray{new value_type[n * n]};

	for (auto i = 0u; i != n; ++i) {
	for (auto k = 0u; k != n; ++k) {
	for (auto j = 0u; j != n; j += 8) {
		c[n * i + j + 0] += a[n * i + k] * b[n * k + j + 0];
		c[n * i + j + 1] += a[n * i + k] * b[n * k + j + 1];
		c[n * i + j + 2] += a[n * i + k] * b[n * k + j + 2];
		c[n * i + j + 3] += a[n * i + k] * b[n * k + j + 3];
		c[n * i + j + 4] += a[n * i + k] * b[n * k + j + 4];
		c[n * i + j + 5] += a[n * i + k] * b[n * k + j + 5];
		c[n * i + j + 6] += a[n * i + k] * b[n * k + j + 6];
		c[n * i + j + 7] += a[n * i + k] * b[n * k + j + 7];
	}}}
}

static void mm_u16()
{
	auto a = darray{new value_type[n * n]};
	auto b = darray{new value_type[n * n]};
	auto c = darray{new value_type[n * n]};

	for (auto i = 0u; i != n; ++i) {
	for (auto k = 0u; k != n; ++k) {
	for (auto j = 0u; j != n; j += 16) {
		c[n * i + j + 0] += a[n * i + k] * b[n * k + j + 0];
		c[n * i + j + 1] += a[n * i + k] * b[n * k + j + 1];
		c[n * i + j + 2] += a[n * i + k] * b[n * k + j + 2];
		c[n * i + j + 3] += a[n * i + k] * b[n * k + j + 3];
		c[n * i + j + 4] += a[n * i + k] * b[n * k + j + 4];
		c[n * i + j + 5] += a[n * i + k] * b[n * k + j + 5];
		c[n * i + j + 6] += a[n * i + k] * b[n * k + j + 6];
		c[n * i + j + 7] += a[n * i + k] * b[n * k + j + 7];
		c[n * i + j + 8] += a[n * i + k] * b[n * k + j + 8];
		c[n * i + j + 9] += a[n * i + k] * b[n * k + j + 9];
		c[n * i + j + 10] += a[n * i + k] * b[n * k + j + 10];
		c[n * i + j + 11] += a[n * i + k] * b[n * k + j + 11];
		c[n * i + j + 12] += a[n * i + k] * b[n * k + j + 12];
		c[n * i + j + 13] += a[n * i + k] * b[n * k + j + 13];
		c[n * i + j + 14] += a[n * i + k] * b[n * k + j + 14];
		c[n * i + j + 15] += a[n * i + k] * b[n * k + j + 15];
	}}}
}

static void mm_t()
{
	auto a = darray{new value_type[n * n]};
	auto b = darray{new value_type[n * n]};
	auto c = darray{new value_type[n * n]};

	for (auto i = 0u; i != n; ++i) {
	for (auto j = 0u; j != n; ++j) {
	for (auto k = 0u; k != n; ++k) {
		c[n * i + j] += a[n * i + k] * b[n * j + k];
	}}}
}

static void mm_tile2()
{
	auto a = darray{new value_type[n * n]};
	auto b = darray{new value_type[n * n]};
	auto c = darray{new value_type[n * n]};
	static constexpr auto m = 2u;

	for (auto i = 0u; i != n; i += m) {
	for (auto k = 0u; k != n; k += m) {
	for (auto j = 0u; j != n; j += m) {
		for (auto i2 = i; i2 != i + m; ++i2) {
		for (auto k2 = k; k2 != k + m; ++k2) {
		for (auto j2 = j; j2 != j + m; ++j2) {
			c[n * i2 + j2] += a[n * i2 + k2] * b[n * k2 + j2];
		}}}
	}}}
}

static void mm_tile4()
{
	auto a = darray{new value_type[n * n]};
	auto b = darray{new value_type[n * n]};
	auto c = darray{new value_type[n * n]};
	static constexpr auto m = 4u;

	for (auto i = 0u; i != n; i += m) {
	for (auto k = 0u; k != n; k += m) {
	for (auto j = 0u; j != n; j += m) {
		for (auto i2 = i; i2 != i + m; ++i2) {
		for (auto k2 = k; k2 != k + m; ++k2) {
		for (auto j2 = j; j2 != j + m; ++j2) {
			c[n * i2 + j2] += a[n * i2 + k2] * b[n * k2 + j2];
		}}}
	}}}
}

static void mm_tile8()
{
	auto a = darray{new value_type[n * n]};
	auto b = darray{new value_type[n * n]};
	auto c = darray{new value_type[n * n]};
	static constexpr auto m = 8u;

	for (auto i = 0u; i != n; i += m) {
	for (auto k = 0u; k != n; k += m) {
	for (auto j = 0u; j != n; j += m) {
		for (auto i2 = i; i2 != i + m; ++i2) {
		for (auto k2 = k; k2 != k + m; ++k2) {
		for (auto j2 = j; j2 != j + m; ++j2) {
			c[n * i2 + j2] += a[n * i2 + k2] * b[n * k2 + j2];
		}}}
	}}}
}

static void mm_tile16()
{
	auto a = darray{new value_type[n * n]};
	auto b = darray{new value_type[n * n]};
	auto c = darray{new value_type[n * n]};
	static constexpr auto m = 16u;

	for (auto i = 0u; i != n; i += m) {
	for (auto k = 0u; k != n; k += m) {
	for (auto j = 0u; j != n; j += m) {
		for (auto i2 = i; i2 != i + m; ++i2) {
		for (auto k2 = k; k2 != k + m; ++k2) {
		for (auto j2 = j; j2 != j + m; ++j2) {
			c[n * i2 + j2] += a[n * i2 + k2] * b[n * k2 + j2];
		}}}
	}}}
}

static void mm_tile32()
{
	auto a = darray{new value_type[n * n]};
	auto b = darray{new value_type[n * n]};
	auto c = darray{new value_type[n * n]};
	static constexpr auto m = 32u;

	for (auto i = 0u; i != n / m; ++i) {
	for (auto k = 0u; k != n / m; ++k) {
	for (auto j = 0u; j != n / m; ++j) {
		for (auto i2 = i; i2 != i + m; ++i2) {
		for (auto k2 = k; k2 != k + m; ++k2) {
		for (auto j2 = j; j2 != j + m; ++j2) {
			c[n * i2 + j2] += a[n * i2 + k2] * b[n * k2 + j2];
		}}}
	}}}
}

static void mm_tile64()
{
	auto a = darray{new value_type[n * n]};
	auto b = darray{new value_type[n * n]};
	auto c = darray{new value_type[n * n]};
	static constexpr auto m = 64u;

	for (auto i = 0u; i != n / m; ++i) {
	for (auto k = 0u; k != n / m; ++k) {
	for (auto j = 0u; j != n / m; ++j) {
		for (auto i2 = i; i2 != i + m; ++i2) {
		for (auto k2 = k; k2 != k + m; ++k2) {
		for (auto j2 = j; j2 != j + m; ++j2) {
			c[n * i2 + j2] += a[n * i2 + k2] * b[n * k2 + j2];
		}}}
	}}}
}

static void mm_super_1()
{
	/*
	** Optimizations performed:
	** 1. Loop transposition: <i,j,k> -> <i,k,j>.
	** 2. Separate tiling on each of the loop indices.
	** 3. Unrolling of the innermost loop.
	** 4. Reordering to exploit instruction-level parallelism.
	*/
	auto a = darray{new value_type[n * n]};
	auto b = darray{new value_type[n * n]};
	auto c = darray{new value_type[n * n]};

	static constexpr auto m1 = 1u;
	static constexpr auto m2 = 4u;
	static constexpr auto m3 = 8u;

	for (auto i = 0u; i != n; i += m1) {
	for (auto k = 0u; k != n; k += m3) {
	for (auto j = 0u; j != n; j += m2) {
		//for (auto i2 = i; i2 != i + m1; ++i2) {
		//for (auto k2 = k; k2 != k + m2; ++k2) {
		//for (auto j2 = j; j2 != j + m3; ++j2) {
			c[n * i + (j + 0)] += a[n * i + k] * b[n * k + j + 0]
			              + a[n * i + (k + 1)] * b[n * (k + 1) + j + 0]
			              + a[n * i + (k + 2)] * b[n * (k + 2) + j + 0]
			              + a[n * i + (k + 3)] * b[n * (k + 3) + j + 0]
			              + a[n * i + (k + 4)] * b[n * (k + 4) + j + 0]
			              + a[n * i + (k + 5)] * b[n * (k + 5) + j + 0]
			              + a[n * i + (k + 6)] * b[n * (k + 6) + j + 0]
			              + a[n * i + (k + 7)] * b[n * (k + 7) + j + 0];

			c[n * i + (j + 1)] += a[n * i + k] * b[n * k + j + 1]
			              + a[n * i + (k + 1)] * b[n * (k + 1) + j + 1]
			              + a[n * i + (k + 2)] * b[n * (k + 2) + j + 1]
			              + a[n * i + (k + 3)] * b[n * (k + 3) + j + 1]
			              + a[n * i + (k + 4)] * b[n * (k + 4) + j + 1]
			              + a[n * i + (k + 5)] * b[n * (k + 5) + j + 1]
			              + a[n * i + (k + 6)] * b[n * (k + 6) + j + 1]
			              + a[n * i + (k + 7)] * b[n * (k + 7) + j + 1];

			c[n * i + (j + 2)] += a[n * i + k] * b[n * k + j + 2]
			              + a[n * i + (k + 1)] * b[n * (k + 1) + j + 2]
			              + a[n * i + (k + 2)] * b[n * (k + 2) + j + 2]
			              + a[n * i + (k + 3)] * b[n * (k + 3) + j + 2]
			              + a[n * i + (k + 4)] * b[n * (k + 4) + j + 2]
			              + a[n * i + (k + 5)] * b[n * (k + 5) + j + 2]
			              + a[n * i + (k + 6)] * b[n * (k + 6) + j + 2]
			              + a[n * i + (k + 7)] * b[n * (k + 7) + j + 2];

			c[n * i + (j + 3)] += a[n * i + k] * b[n * k + j + 3]
			              + a[n * i + (k + 1)] * b[n * (k + 1) + j + 3]
			              + a[n * i + (k + 2)] * b[n * (k + 2) + j + 3]
			              + a[n * i + (k + 3)] * b[n * (k + 3) + j + 3]
			              + a[n * i + (k + 4)] * b[n * (k + 4) + j + 3]
			              + a[n * i + (k + 5)] * b[n * (k + 5) + j + 3]
			              + a[n * i + (k + 6)] * b[n * (k + 6) + j + 3]
			              + a[n * i + (k + 7)] * b[n * (k + 7) + j + 3];

			//c[n * i + (j + 4)] += a[n * i + k] * b[n * k + j + 4]
			//              + a[n * i + (k + 1)] * b[n * (k + 1) + j + 4]
			//              + a[n * i + (k + 2)] * b[n * (k + 2) + j + 4]
			//              + a[n * i + (k + 3)] * b[n * (k + 3) + j + 4]
			//              + a[n * i + (k + 4)] * b[n * (k + 4) + j + 4]
			//              + a[n * i + (k + 5)] * b[n * (k + 5) + j + 4]
			//              + a[n * i + (k + 6)] * b[n * (k + 6) + j + 4]
			//              + a[n * i + (k + 7)] * b[n * (k + 7) + j + 4];

			//c[n * i + (j + 5)] += a[n * i + k] * b[n * k + j + 5]
			//              + a[n * i + (k + 1)] * b[n * (k + 1) + j + 5]
			//              + a[n * i + (k + 2)] * b[n * (k + 2) + j + 5]
			//              + a[n * i + (k + 3)] * b[n * (k + 3) + j + 5]
			//              + a[n * i + (k + 4)] * b[n * (k + 4) + j + 5]
			//              + a[n * i + (k + 5)] * b[n * (k + 5) + j + 5]
			//              + a[n * i + (k + 6)] * b[n * (k + 6) + j + 5]
			//              + a[n * i + (k + 7)] * b[n * (k + 7) + j + 5];

			//c[n * i + (j + 6)] += a[n * i + k] * b[n * k + j + 6]
			//              + a[n * i + (k + 1)] * b[n * (k + 1) + j + 6]
			//              + a[n * i + (k + 2)] * b[n * (k + 2) + j + 6]
			//              + a[n * i + (k + 3)] * b[n * (k + 3) + j + 6]
			//              + a[n * i + (k + 4)] * b[n * (k + 4) + j + 6]
			//              + a[n * i + (k + 5)] * b[n * (k + 5) + j + 6]
			//              + a[n * i + (k + 6)] * b[n * (k + 6) + j + 6]
			//              + a[n * i + (k + 7)] * b[n * (k + 7) + j + 6];

			//c[n * i + (j + 7)] += a[n * i + k] * b[n * k + j + 7]
			//              + a[n * i + (k + 1)] * b[n * (k + 1) + j + 7]
			//              + a[n * i + (k + 2)] * b[n * (k + 2) + j + 7]
			//              + a[n * i + (k + 3)] * b[n * (k + 3) + j + 7]
			//              + a[n * i + (k + 4)] * b[n * (k + 4) + j + 7]
			//              + a[n * i + (k + 5)] * b[n * (k + 5) + j + 7]
			//              + a[n * i + (k + 6)] * b[n * (k + 6) + j + 7]
			//              + a[n * i + (k + 7)] * b[n * (k + 7) + j + 7];
		//}}}
	}}}
}

static void mm_super_2()
{
	auto a = darray{new value_type[n * n]};
	auto b = darray{new value_type[n * n]};
	auto c = darray{new value_type[n * n]};

	static constexpr auto m1 = 1u;
	static constexpr auto m2 = 4u;
	static constexpr auto m3 = 8u;
	static constexpr auto r1 = n % m1;
	static constexpr auto r2 = n % m2;
	static constexpr auto r3 = n % m3;

	// Main Loop
	for (auto i = 0u; i < n; i += m1) {
	for (auto k = 0u; k < n; k += m3) {
	for (auto j = 0u; j < n; j += m2) {
		for (auto i2 = i; i2 < std::min(i + m1, n); ++i2) {
		for (auto k2 = k; k2 < std::min(k + m3, n); ++k2) {
		for (auto j2 = j; j2 < std::min(j + m2, n); ++j2) {
			c[n * i2 + j2] += a[n * i2 + k2] * b[n * k2 + j2];
		}}}
	}}}
}

int main()
{
	// Tests index order.
	//profile("mm_ijk", mm_ijk, 1);
	//profile("mm_ikj", mm_ikj, 1);
	//profile("mm_jik", mm_jik, 1);
	//profile("mm_jki", mm_jki, 1);
	//profile("mm_kij", mm_kij, 1);
	//profile("mm_kji", mm_kji, 1);
	
	// Tests unrolling.
	//profile("mm_ikj", mm_ikj, 1);
	//profile("mm_u2", mm_u2, 1);
	//profile("mm_u4", mm_u4, 1);
	//profile("mm_u8", mm_u8, 1);
	//profile("mm_u16", mm_u16, 1);

	// Tests transpose.
	//profile("mm_ikj", mm_ikj, 1);
	//profile("mm_t", mm_t, 1);

	// Tests hierarchial unrolling.
	//profile("mm_u4", mm_u4, 1);
	//profile("mm_tile2", mm_tile2, 1);
	//profile("mm_tile4", mm_tile4, 1);
	//profile("mm_tile16", mm_tile16, 1);
	//profile("mm_tile32", mm_tile32, 1);
	//profile("mm_tile64", mm_tile64, 1);

	// Tests a combination of optimizations.
	profile("mm_super_1", mm_super_1);
	profile("mm_super_2", mm_super_2);
}
