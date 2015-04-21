
#ifndef BF_COMP_H_
#define BF_COMP_H_

#include "jit.h"
#include "lex.h"
#include "x86_64.h"

#include <istream>
#include <future>

namespace bf {

class comp {
public:
	comp(std::istream *is);
private:
	channel<tok *> chan_;
	lexer l;
	x86_64 arch;
	jit j;
	std::future<void> run_;
};

} // namespace bf

#endif // BF_COMP_H_
