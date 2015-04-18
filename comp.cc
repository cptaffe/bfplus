
#include "comp.h"
#include "log.h"

#include <vector>
#include <iostream>

#include "jit.h"
#include "x86_64.h"

using namespace bf;

namespace {
	char test(lex *l) {
		return l->next();
	}
}

comp::comp(std::istream *is) :
	arch(static_cast<architecture *>(new x86_64())),
	j(arch),
	l(is) {}

comp::~comp() {
	delete arch;
}

std::future<void> comp::run() {
	std::vector<std::future<char>> *futures = new std::vector<std::future<char>>();

	for (int i = 0; i < 100; i++) {
		futures->push_back(std::async(&test, &l));
	}

	// wait for result.
	std::future<void> next = std::async([](std::vector<std::future<char>> *futures){
		for (auto i = futures->begin(); i != futures->end(); i++) {
			auto j = (*i).get();
			if (j == EOF) break;

			// make string
			std::string str("have: '");
			str.push_back(j);
			str.append("'");

			logerr.println(str);
		}
		delete futures;

		// creepy message thing.
		/*std::string str("Hello, want to play a game?\n");
		for (auto i = str.begin(); i != str.end(); i++) {
			std::cout << *i << std::flush;
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}*/
	}, futures);

	return next;
}
