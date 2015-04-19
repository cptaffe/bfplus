
#include "log.h"

#include <iostream>

namespace bf { log err(std::cerr); }

using namespace bf;

log::log(std::ostream& os) :
	lambdas(5),
	os(os),
	printer(std::async([this]{
		// asyncronous printing of log messages.
		while (true) {
			std::function<void()> f;
			lambdas.get(&f);
			if (f) {
				f();
			} else {
				// queue is empty, die.
				break;
			}
		}
	})) {}

log::~log() {
	lambdas.kill();
	wait(); // finish prints.
}

void log::operator<<(const std::string& str) {
	// will fail on dead.
	lambdas.put([this, str] {
		os << str << std::endl;
	});
}

void log::wait() {
	printer.wait();
}
