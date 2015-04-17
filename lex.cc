
#include "lex.h"

using namespace bf;

lex::lex(std::istream *ins) : in(ins) {}

int lex::next() {
	std::lock_guard<std::mutex> lock(m);

	if (!backbuf.empty()) {
		buf.push_back(backbuf.back());
		backbuf.pop_back();
	} else {
		buf.push_back(in->get());
	}
	return buf.back();
}

void lex::back() {
	std::lock_guard<std::mutex> lock(m);

	backbuf.push_back(buf.back());
	buf.pop_back();
}

int lex::peek() {
	std::lock_guard<std::mutex> lock(m);

	if (!backbuf.empty()) {
		return backbuf.back();
	}
	return in->peek();
}

std::string *lex::grab() {
	std::lock_guard<std::mutex> lock(m);
	return new std::string(buf);
}

std::string *lex::emit() {
	std::lock_guard<std::mutex> lock(m);

	std::string *nstr = new std::string(buf); // copy constructor.
	buf.clear();
	return nstr;
}
