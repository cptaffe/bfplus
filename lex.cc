
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

lexer::lexer(std::istream *str, channel<tok *> *chan) :
	chan_(chan),
	scan(str),
	mach(new start(&scan, chan_)),
	thrd(std::async([this]{
		bool m = mach.run();
		chan_->kill();
		return m;
	})) {}

namespace {

bool is_whitespace(char c) {
	std::string ws(" \t\r\n");
	return ws.find(c) != std::string::npos;
}

bool is_cross(char c) {
	return c == '+';
}

bool is_dash(char c) {
	return c == '-';
}

bool is_forward(char c) {
	return c == '>';
}

bool is_back(char c) {
	return c == '<';
}

bool is_loop_begin(char c) {
	return c == '[';
}

bool is_loop_end(char c) {
	return c == ']';
}

} // namespace

start::start(scanner *scan, channel<tok *> *chan) :
	scan_(scan),
	chan_(chan) {}

bool start::try_apply() {
	int c;
	if ((c = scan_->peek()) != EOF) {
		if (is_whitespace(c)) {
			next_ = new whitespace(scan_, chan_);
		} else if (is_cross(c)) {
			next_ = new cross(scan_, chan_);
		} else if (is_dash(c)) {
			next_ = new dash(scan_, chan_);
		} else if (is_forward(c)) {
			next_ = new forward(scan_, chan_);
		} else if (is_back(c)) {
			next_ = new back(scan_, chan_);
		} else if (is_loop_begin(c)) {
			next_ = new loop(scan_, chan_);
		} else if (is_loop_end(c)) {
			return false;
		} else {
			return false; // invalid character.
		}
		return true;
	} else {
		// eof's are acceptable in the start state.
		return true;
	}
}

whitespace::whitespace(scanner *scan, channel<tok *> *chan) :
	scan_(scan),
	chan_(chan) {
	next_ = new start(scan_, chan_);
}

bool whitespace::try_apply() {
	int c;
	while ((c = scan_->next()) != EOF && is_whitespace(c)) {}
	if (c != EOF) {
		scan_->back();
	}
	// throw away whitespace
	delete scan_->emit();
	return true;
}

cross::cross(scanner *scan, channel<tok *> *chan) :
	scan_(scan),
	chan_(chan) {
	next_ = new start(scan_, chan_);
}

bool cross::try_apply() {
	int c;
	while ((c = scan_->next()) != EOF && is_cross(c)) {}
	if (c != EOF) {
		scan_->back();
	}
	// throw away whitespace
	chan_->put(new tok(tok::CROSS, scan_->emit()));
	return true;
}

dash::dash(scanner *scan, channel<tok *> *chan) :
	scan_(scan),
	chan_(chan) {
	next_ = new start(scan_, chan_);
}

bool dash::try_apply() {
	int c;
	while ((c = scan_->next()) != EOF && is_dash(c)) {}
	if (c != EOF) {
		scan_->back();
	}
	// throw away whitespace
	chan_->put(new tok(tok::DASH, scan_->emit()));
	return true;
}

forward::forward(scanner *scan, channel<tok *> *chan) :
	scan_(scan),
	chan_(chan) {
	next_ = new start(scan_, chan_);
}

bool forward::try_apply() {
	int c;
	while ((c = scan_->next()) != EOF && is_forward(c)) {}
	if (c != EOF) {
		scan_->back();
	}
	// throw away whitespace
	chan_->put(new tok(tok::DASH, scan_->emit()));
	return true;
}

back::back(scanner *scan, channel<tok *> *chan) :
	scan_(scan),
	chan_(chan) {
	next_ = new start(scan_, chan_);
}

bool back::try_apply() {
	int c;
	while ((c = scan_->next()) != EOF && is_back(c)) {}
	if (c != EOF) {
		// whitespace can end on eof.
		scan_->back();
	}
	// throw away whitespace
	chan_->put(new tok(tok::BACK, scan_->emit()));
	return true;
}

loop::loop(scanner *scan, channel<tok *> *chan) :
	scan_(scan),
	chan_(chan) {
	next_ = new start(scan_, chan_);
}

bool loop::try_apply() {
	int c;
	if ((c = scan_->next()) != EOF && is_loop_begin(c)) {
		chan_->put(new tok(tok::BEGIN_LOOP, scan_->emit()));

		state_machine mach(new start(scan_, chan_));
		if (!mach.run() && is_loop_end(scan_->next())) {
			// loop has correctly ended
			chan_->put(new tok(tok::END_LOOP, scan_->emit()));
			return true;
		} else {
			return false; // failure.
		}
	} else {
		return false;
	}
	return true;
}
