
#include "x86_64.h"

using namespace bf;

x86_64::instruction::instruction(size_t len, uint8_t *op) : len(len), op(op) {}

namespace {
	uint8_t mov_64[] = {0x48, 0xbe};
} // namespace

x86_64::x86_64() {
	// long initialization of vector class
	instructions.push_back(instruction(sizeof(mov_64), (uint8_t *) &mov_64));
}

const uint8_t *x86_64::get(enum operation op) const {
	return instructions[op].op;
}
