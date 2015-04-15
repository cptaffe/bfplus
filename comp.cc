
#include "comp.h"

#include <vector>
#include <future>
#include <iostream>

#include "jit.h"
#include "x86_64.h"

using namespace bf;

comp::comp(std::istream *is) /*: l(is)*/ {}

void comp::run() {
	std::vector<std::future<bool>> futures;
	x86_64 arch;
	jit j((architecture *) &arch);

	futures.push_back(std::async(&jit::runnable, &j));

	// wait for result.
	auto i = futures.back().get();
	futures.pop_back();

	std::cout << "have: " << i << std::endl;
}
