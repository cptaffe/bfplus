
#include "comp.h"
#include "log.h"

#include <sstream>
#include <iostream>

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
	in(static_cast<std::istringstream *>(new std::istringstream("this is a string"))),
	c(in) {
	auto j = c.run();
	bf::err << "c is working";
	j.wait();
}

test::~test() {
	delete in;
}

int main() { test t; }
