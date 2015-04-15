
#ifndef BF_X86_64_H_
#define BF_X86_64_H_

#include "jit.h"

namespace bf {

class x86_64 : public architecture {
public:
	x86_64();
	virtual const uint8_t *get(enum operation op) const;
private:

	// variable length instructions.
	class instruction {
	public:
		instruction(size_t len, uint8_t *op);
		size_t len;
		uint8_t *op;
	};

	std::vector<instruction> instructions;
};

} // namespace bf

#endif // BF_X86_64_H_
