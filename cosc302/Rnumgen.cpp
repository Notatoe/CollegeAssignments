#include <vector>
#include <algorithm>
#include <functional>
#include <numeric>
#include <iostream>

using namespace std;

#include "Rnumgen.h"

rnumgen::rnumgen(int seedvalue, vector<int> &vec)
{
	srand(seedvalue);
	v.resize(vec.size());
	partial_sum(vec.begin(), vec.end(), v.begin());
	transform(v.begin(), v.end(), v.begin(), bind2nd(divides<float>(), v.back()));
}

int rnumgen::rand() const 
{
	const double randmax = RAND_MAX+1.0;
	const double p = (double) std::rand()/randmax;
	return upper_bound(v.begin(), v.end(), p ) - v.begin();
}
