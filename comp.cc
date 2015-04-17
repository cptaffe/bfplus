
#include "comp.h"

#include <vector>
#include <future>
#include <iostream>

#include "jit.h"
#include "x86_64.h"

using namespace bf;

namespace {
	char test(lex *l) {
		return l->peek();
	}
}

comp::comp(std::istream *is) :
	j(static_cast<architecture *>(new x86_64())),
	l(is) {}

void comp::run() {
	std::vector<std::future<char>> futures;

	futures.push_back(std::async(&test, &l));

	// wait for result.
	auto i = futures.back().get();
	futures.pop_back();

	std::cout << "have: '" << i << "'" << std::endl;
}
