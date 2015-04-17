
#include "comp.h"

#include <sstream>

class test {
public:
	test();
	~test();
private:
	// initialized in order.
	std::istream *in;
	bf::comp c;
};

test::test() :
	in(static_cast<std::istream *>(new std::istringstream("this is a string"))),
	c(in) {
	c.run();
}

test::~test() {
	delete in;
}

int main() { test t; }
