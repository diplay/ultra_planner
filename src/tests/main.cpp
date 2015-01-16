
#include "helpers.h"
#include "test_sort.h"
#include <core/UMatrix.h>
#include <string>
#include <functional>
#include <random>

using namespace std;
using namespace UltraCore;

template<typename M>
void random_fill(M & matrix)
{
	auto gen = std::bind(uniform_real_distribution<float>(0, 20.0), default_random_engine());

	for(int r = 0; r < matrix.rows(); ++r)
		for(int c = 0; c < matrix.columns(); ++c)
			matrix.at(r, c) = gen();
}

void test_matrix()
{
	UMatrix<float, 4, 4> m1, m2;
	random_fill(m1);
	random_fill(m2);

	auto correct_res = mult(m1, m2);
	auto res = mult_strassen(m1, m2);

	assert_test(correct_res == res, "Matrix multiplication");
}

void test_bitset();
void test_search();
void test_puzzle_core();
void test_complex_vector();
void test_complex_hashmap();
void test_cached_file();
void test_merge();

int main()
{
	test_bitset();
	test_merge();
	test_cached_file();
	test_complex_vector();
	test_complex_hashmap();
	

	//test_matrix();

	//test_sorting();

	test_puzzle_core();

	test_search();

	return 0;
}
