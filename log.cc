
#include "log.h"

#include <iostream>

namespace bf { log err(std::cerr); }

using namespace bf;

log::log(std::ostream& os) :
	os(os),
	printer(std::async([this]{
		// asyncronous printing of log messages.
		std::pair<bool, std::function<void()>> p;
		while((p = lambdas.get()).first) {
			p.second();
		}
	})) {}

log::~log() {
	lambdas.kill();
	wait(); // finish prints.
}

void log::operator<<(const std::string& str) {
	if (lambdas.alive()) {
		lambdas.put([this, str] {
			os << str << std::endl;
		});
	} else {
		throw new std::runtime_error("logging to dead logger.");
	}
}

void log::wait() {
	printer.wait();
}
