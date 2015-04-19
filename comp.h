
#ifndef BF_COMP_H_
#define BF_COMP_H_

#include "jit.h"
#include "lex.h"

#include <istream>
#include <future>

namespace bf {

class comp {
public:
	comp(std::istream *is);
	~comp();

	std::future<void> run();
private:
	lexer l;
	architecture *arch;
	jit j;
};

} // namespace bf

#endif // BF_COMP_H_
