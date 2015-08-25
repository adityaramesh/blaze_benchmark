/*
** File Name:	eigen_mm.cpp
** Author:	Aditya Ramesh
** Date:	05/05/2013
** Contact:	_@adityaramesh.com
*/

#include <chrono>
#include <cstddef>
#include <iostream>
#include <Eigen/Dense>
#include <blaze/Math.h>

static void eigen_mm()
{
	using namespace Eigen;
	using matrix = Matrix<float, Dynamic, Dynamic>;

	matrix a(1024, 1024);
	matrix b(1024, 1024);
	matrix c(1024, 1024);
	c.noalias() = a * b;
}

static void blaze_mm()
{
	using namespace blaze;
	using matrix = DynamicMatrix<float>;

	matrix a(1024, 1024);
	matrix b(1024, 1024);
	matrix c(1024, 1024);
	c = a * b;
}

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

int main()
{
	profile("eigen_mm", eigen_mm);
	profile("blaze_mm", eigen_mm);
}
