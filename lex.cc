
#include "log.h"
#include "lex.h"

using namespace bf;

scanner::scanner(std::istream *ins) : in(ins) {}

int scanner::next() {
	std::lock_guard<std::mutex> lock(m);

	if (!backbuf.empty()) {
		buf.push_back(backbuf.back());
		backbuf.pop_back();
	} else {
		buf.push_back(in->get());
	}
	return buf.back();
}

void scanner::back() {
	std::lock_guard<std::mutex> lock(m);

	backbuf.push_back(buf.back());
	buf.pop_back();
}

int scanner::peek() {
	std::lock_guard<std::mutex> lock(m);

	if (!backbuf.empty()) {
		return backbuf.back();
	}
	return in->peek();
}

std::string *scanner::grab() {
	std::lock_guard<std::mutex> lock(m);

	return new std::string(buf);
}

std::string *scanner::emit() {
	std::lock_guard<std::mutex> lock(m);

	std::string *nstr = new std::string(buf); // copy constructor.
	buf.clear();
	return nstr;
}

state_machine::state_machine(state *start) :
	current_(start) {}

bool state_machine::run() {
	if (current_ == nullptr) {
		throw std::runtime_error("current cannot be null on call to run.");
	}
	while (current_->try_apply()) {
		state *next;
		next = current_->next();
		delete current_;
		current_ = next;
		if (current_ == nullptr) {
			return true; // successful completion.
		}
	}
	delete current_;
	return false; // error
}

lexer::lexer(std::istream *str) :
	scan(str),
	mach(new start(&scan, &chan_)),
	thrd(std::async([this]{
		bool m = mach.run();
		chan_.kill();
		return m;
	})) {}

lexer::~lexer() {
	thrd.wait();
}

channel<tok *> *lexer::chan() {
	return &chan_;
}

namespace {
	bool whitespace_char(char c) {
		std::string ws(" \t\r\n");
		return ws.find(c) != std::string::npos;
	}
} // namespace

start::start(scanner *scan, channel<tok *> *chan) :
	scan_(scan),
	chan_(chan) {}

bool start::try_apply() {
	int c;
	if ((c = scan_->next()) != EOF) {
		if (whitespace_char(c)) {
			next_ = nullptr; // still unimplemented.
			return true;
		} else {
			return true;
		}
	} else {
		// eof's are acceptable in the start state.
		return true;
	}
}
