
#ifndef BF_LEX_H_
#define BF_LEX_H_

#include <istream>
#include <string>

namespace bf {

class lex {
public:
	explicit lex(std::istream *str);

	int next(); // next's one character and returns it.
	void back(); // back's one character
	int peek(); // peeks ahead

	// returns non-freeable, immutable pointer.
	const std::string *grab() const;
	// returns an allocated string copy of the internal string.
	// and clears the internal string.
	std::string *emit();
private:
	std::istream *in;
	std::string backbuf;
	std::string buf;
};

} // namespace bf

#endif // BF_LEX_H_
