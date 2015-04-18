
#include "comp.h"
#include "log.h"

#include <vector>
#include <iostream>

#include "jit.h"
#include "x86_64.h"

using namespace bf;

comp::comp(std::istream *is) :
	arch(static_cast<architecture *>(new x86_64())),
	j(arch),
	l(is) {}

comp::~comp() {
	delete arch;
}

std::future<void> comp::run() {
	return std::async([]{
		err << "hello, bob";
	});
}
