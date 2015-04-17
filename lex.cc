
#include "lex.h"

using namespace bf;

lex::lex(std::istream *ins) : in(ins) {}

int lex::next() {
	if (!backbuf.empty()) {
		buf.push_back(backbuf.back());
		backbuf.pop_back();
	}
	buf.push_back(in->get());
	return buf.back();
}

void lex::back() {
	backbuf.push_back(buf.back());
	buf.pop_back();
}

int lex::peek() {
	if (!backbuf.empty()) {
		return backbuf.back();
	}
	return in->peek();
}

const std::string *lex::grab() const {
	return &buf;
}

std::string *lex::emit() {
	std::string *nstr = new std::string(buf); // copy constructor.
	buf.clear();
	return nstr;
}
