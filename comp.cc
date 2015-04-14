
#include "comp.h"

#include <vector>
#include <future>
#include <iostream>

#include "jit.h"

using namespace bf;

comp::comp(std::istream *is) /*: l(is)*/ {}

void comp::run() {
	std::vector<std::future<bool>> futures;
	jit j;

	futures.push_back(std::async(&jit::runnable, &j));

	// wait for result.
	auto i = futures.back().get();
	futures.pop_back();

	std::cout << "have: " << i << std::endl;
}
