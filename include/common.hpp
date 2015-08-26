/*
** File Name: common.hpp
** Author:    Aditya Ramesh
** Date:      08/25/2015
** Contact:   _@adityaramesh.com
*/

#ifndef Z8BD26FA9_6CF6_4010_B752_7E01F260410F
#define Z8BD26FA9_6CF6_4010_B752_7E01F260410F

#include <algorithm>
#include <chrono>
#include <cstddef>
#include <iostream>
#include <memory>
#include <blaze/Math.h>

template <class F>
static void profile(const char* name, const F f, const unsigned n = 5)
{
	using namespace std::chrono;
	using value_type = double;
	value_type s{0};

	for (auto i = 0u; i != n; ++i) {
		auto t1 = high_resolution_clock::now();
		f();
		auto t2 = high_resolution_clock::now();
		s += duration_cast<duration<value_type>>(t2 - t1).count();
	}

	s /= n;
	std::cout << "Average execution time for kernel " << name <<
		" using " << n << " measurements: " << s << "." << std::endl;
}

#endif
