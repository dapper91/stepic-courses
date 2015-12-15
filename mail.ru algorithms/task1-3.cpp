#include <utility>
#include <vector>
#include <iterator>
#include <iostream>
#include <cmath>


std::pair<int, int> find_bounds(std::vector<int> vec, int val)
{	
	int upper_bound = vec.size()-1;
	while (val < vec[upper_bound/2] && upper_bound != 0) {
		upper_bound /= 2;		
	}	

	int lower_bound = upper_bound;
	while (val < vec[lower_bound] && lower_bound != 0) {
		lower_bound /= 2;
	}	

	return {lower_bound, upper_bound};
}

int bin_nearest_search(std::vector<int> vec, int val)
{
	auto bounds = find_bounds(vec, val);
	int begin = bounds.first, end = bounds.second, pivot = 0, result;	

	while ((pivot = begin + (end-begin)/2) != begin) {		
		if (val < vec[pivot]) {
			end = pivot;
		}
		else {
			begin = pivot;
		}

	}
	
	if (std::abs(val-vec[begin]) <= std::abs(val-vec[end])) {
		result = begin;
	}
	else {
		result = end;
	}

	return result;
}


int main()
{
	std::vector<int> A;
	std::vector<int> B;
	int n, m, tmp;
	
	std::cin >> n;
	A.reserve(n);
	for (int i = 0; i < n; i++) {
		std::cin >> tmp;
		A.push_back(tmp);		
	}	

	std::cin >> m;	
	B.reserve(m);
	for (int i = 0; i < m; i++) {
		std::cin >> tmp;
		B.push_back(tmp);		
	}	

	for (int b : B) {
		std::cout << bin_nearest_search(A, b) << " ";
	}
}