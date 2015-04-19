
#ifndef BF_LEX_H_
#define BF_LEX_H_

#include "tok.h"
#include "channel.h"

#include <istream>
#include <string>
#include <mutex>
#include <future>

namespace bf {

// state interface
class state {
public:
	// all possible states.
	enum {
		UNDEFINED,
		START,
		WHITESPACE,
	};

	virtual ~state() {};
	// attempts to apply.
	virtual bool try_apply() = 0;
	// returns next state.
	virtual state *next() const { return next_; };
	// returns current state number.
	virtual int current() const { return current_; };
protected:
	static const int current_ = UNDEFINED;
	bf::state *next_ = nullptr;
};

class scanner {
public:
	explicit scanner(std::istream *str);

	int next(); // next's one character and returns it.
	void back(); // back's one character
	int peek(); // peeks ahead

	// returns an allocated string copy of the internal string.
	std::string *grab();
	// returns an allocated string copy of the internal string.
	// and clears the internal string.
	std::string *emit();
private:
	std::istream *in;
	std::string backbuf;
	std::string buf;
	std::mutex m;
};

class state_machine {
public:
	state_machine(state *start);
	bool run(); // returns success.
private:
	channel<tok *> *chan_;
	state *current_;
};

class lexer {
public:
	explicit lexer(std::istream *str);
	~lexer();
	channel<tok *> *chan();
private:
	scanner scan;
	channel<tok *> chan_;
	state_machine mach;
	std::future<bool> thrd;
};

class start : public state {
public:
	start(scanner *scan, channel<tok *> *chan);
	virtual bool try_apply();
private:
	static const int current_ = START; // current state.
	scanner *scan_;
	channel<tok *> *chan_;
};

} // namespace bf

#endif // BF_LEX_H_
