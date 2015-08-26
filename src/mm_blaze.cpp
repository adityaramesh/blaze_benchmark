/*
** File Name:	eigen_mm.cpp
** Author:	Aditya Ramesh
** Date:	05/05/2013
** Contact:	_@adityaramesh.com
*/

#include <common.hpp>

static void mm_blaze()
{
	using namespace blaze;
	using matrix = DynamicMatrix<float>;

	matrix a(1024, 1024);
	matrix b(1024, 1024);
	matrix c(1024, 1024);
	c = a * b;
}

int main() { profile("blaze_mm", blaze_mm); }
