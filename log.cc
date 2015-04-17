
#include "log.h"

#include <iostream>

namespace bf { log logger; }

using namespace bf;

log::~log() {
	wait(); // finish prints.
}

void log::println(std::string& str) {
	prints.push_back(std::async([=]{
		std::lock_guard<std::mutex> lock(mut);
		std::cerr << str << std::endl;
	}));
}

void log::clean() {
	std::lock_guard<std::mutex> lock(mclean);
	std::async([=]{
		prints.remove_if([](std::future<void>& i){
			return i.wait_for(std::chrono::nanoseconds(0)) == std::future_status::ready;
		});
	});
}

void log::wait() {
	// no cleaning while waiting
	std::lock_guard<std::mutex> lock(mclean);
	for (auto i = prints.begin(); i != prints.end(); i++) {
		(*i).wait();
	}
}
