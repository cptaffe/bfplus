
#include "log.h"

#include <iostream>

namespace bf { log logger; }

using namespace bf;

log::log() :
	printer(std::async([this]{
		std::pair<bool, std::function<void()>> p;
		while((p = lambdas.get()).first) {
			p.second();
		}
	})) {}

log::~log() {
	lambdas.kill();
	wait(); // finish prints.
}

void log::println(std::string& str) {
	if (lambdas.alive()) {
		lambdas.put([this, str] {
			std::cerr << str << std::endl;
		});
	} else {
		throw new std::runtime_error("logging to dead logger.");
	}
}

void log::wait() {
	printer.wait();
}
