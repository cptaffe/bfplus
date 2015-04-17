
#ifndef BF_LEX_H_
#define BF_LEX_H_

#include <istream>
#include <string>
#include <mutex>

namespace bf {

class lex {
public:
	explicit lex(std::istream *str);

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

} // namespace bf

#endif // BF_LEX_H_
