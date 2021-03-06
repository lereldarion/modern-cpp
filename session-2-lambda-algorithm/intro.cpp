#include "benchmark.h"
#include <iostream>
#include <vector>

/* Exemple: test if a vector<int> contains a 0.
 */
bool has_zero (const std::vector<int> & vec);

int main () {
	// initializer_list syntax for containers (session 3)
	auto with_zero = std::vector<int>{0, 1, 2, 3, 4};
	auto no_zero = std::vector<int>{1, 2, 3, 4, 5};

	std::cout << std::boolalpha;
	std::cout << "with_zero: " << has_zero (with_zero) << "\n";
	std::cout << "no_zero: " << has_zero (no_zero) << "\n";

	// Small benchmark
	benchmark_predicate_on_non_zero_random_vector (has_zero);
	return 0;
}

#ifdef MANUAL
// C++03 index version
bool has_zero (const std::vector<int> & vec) {
	for (std::size_t i = 0; i < vec.size (); ++i)
		if (vec[i] == 0)
			return true;
	return false;
}
// -Wall : signed vs unsigned comparison
#endif

#ifdef ITERATOR
// C++03 iterator version
bool has_zero (const std::vector<int> & vec) {
	for (std::vector<int>::const_iterator it = vec.begin (); it != vec.end (); ++it)
		if (*it == 0)
			return true;
	return false;
}
#endif

#ifdef AUTO_ITERATOR
// C++11 auto iterator version
bool has_zero (const std::vector<int> & vec) {
	for (auto it = vec.begin (); it != vec.end (); ++it)
		if (*it == 0)
			return true;
	return false;
}
#endif

// Use what is already made for us.
#include <algorithm>

#ifdef ANY_OF
// C++11 std::any_of version
bool is_zero (int i) {
	return i == 0;
}
bool has_zero (const std::vector<int> & vec) {
	return std::any_of (vec.begin (), vec.end (), &is_zero);
}
#endif

// Lambda syntax:
auto lambda_value = [/* state, see closure.cpp */](/* arguments */) { /* body */ };
auto lv_without_comments = []() {};
auto lv_argument_less_shortened = [] {};

#ifdef LAMBDA
// C++11 any_of with temporary lambda
bool has_zero (const std::vector<int> & vec) {
	return std::any_of (vec.begin (), vec.end (), [](int i) { return i == 0; });
}
#endif

#ifdef STORED_LAMBDA
// C++11 any_of with stored lambda
bool has_zero (const std::vector<int> & vec) {
	auto is_zero = [](int i) { return i == 0; };
	return std::any_of (vec.begin (), vec.end (), is_zero);
}
#endif

#ifdef LAMBDA_REF
// C++11 any_of with lambda taking i by reference
bool has_zero (const std::vector<int> & vec) {
	auto is_zero = [](const int & i) { return i == 0; };
	return std::any_of (vec.begin (), vec.end (), is_zero);
}

// More useful for complex types:
#include <string>
bool has_empty_string (const std::vector<std::string> & vec) {
	return std::any_of (vec.begin (), vec.end (), [](const std::string & s) { return s.empty (); });
}

// Mutable refs are allowed too:
void multiply_by_2 (std::vector<int> & vec) {
	std::for_each (vec.begin (), vec.end (), [](int & i) { i *= 2; });
}
#endif

#ifdef AUTO_LAMBDA
// C++14 ! auto is allowed in lambda arguments
auto is_zero = [](auto num) { return num == 0; };

bool has_zero (const std::vector<int> & vec) {
	return std::any_of (vec.begin (), vec.end (), is_zero);
}
bool has_zero (const std::vector<float> & vec) {
	return std::any_of (vec.begin (), vec.end (), is_zero);
}

// Equivalent to declaring templates functions:
template <typename T> bool is_zero_template (T num) {
	return num == 0;
}
#endif

// Return type can be specified (important when deduction fails, like below)
auto f = [](int i, float f) -> float {
	if (i < f)
		return i;
	else
		return f;
};

// C++14: also variadic lambdas
