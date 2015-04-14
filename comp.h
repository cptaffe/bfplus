
#ifndef BF_COMP_H_
#define BF_COMP_H_

#include <istream>

namespace bf {

class comp {
public:
	comp(std::istream *is);

	void run();
private:
	//lex l;
	//jit j;
};

} // namespace bf

#endif // BF_COMP_H_
