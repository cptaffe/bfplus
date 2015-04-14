
#include "comp.h"

#include <sstream>

int main() {
	std::istringstream s("this is a string");
	bf::comp c(&s);

	c.run();
}
