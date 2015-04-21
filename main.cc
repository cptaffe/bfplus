
#include "comp.h"
#include "log.h"

#include <sstream>
#include <iostream>

class test {
public:
	test();
private:
	// initialized in order.
	std::istringstream in;
	bf::comp c;
};

test::test() :
	in(std::istringstream(" [ + - < > ] ")),
	c(static_cast<std::istringstream *>(&in)) {}

int main() { test t; }
