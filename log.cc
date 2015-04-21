
#include "log.h"

#include <iostream>

namespace bf { log err(std::cerr); }

using namespace bf;

log::log(std::ostream& os) :
	lambdas(5),
	os(os),
	printer(std::async([this]{
		// asyncronous printing of log messages.
		std::function<void()> f;
		while (lambdas.get(&f)) {
			f();
		}
	})) {}

log::~log() {
	// kills channel, signalling death.
	lambdas.kill();
}

void log::operator<<(const std::string& str) {
	// will fail on dead.
	lambdas.put([this, str] {
		os << str << std::endl;
	});
}
