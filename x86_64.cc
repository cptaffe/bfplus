
#include "x86_64.h"

using namespace bf;

x86_64::instruction::instruction(size_t len, uint8_t *op) : len(len), op(op) {}

// inst namespace accessible only within this file.
namespace {
	// constants
	enum {
		LOCK_PREFIX = 0xf0,
	};

	uint8_t mov_64[] = {0x48, 0xbe};
	uint8_t mov_cx_si[] = {0x48, 0x8b, 0x0e};
	uint8_t mov_dx_64[] = {0x48, 0xba};
	uint8_t mov_di_64[] = {0x48, 0xbf};
	uint8_t mov_ax_64[] = {0x48, 0xb8};
	uint8_t add_lit8[] = {0x80, 0x06};
	uint8_t add_lit8_lock[] = {LOCK_PREFIX, 0x80, 0x06};
	uint8_t add_lit8_si[] = {0x48, 0x83, 0xc6};
	uint8_t add_lit8_si_lock[] = {LOCK_PREFIX, 0x48, 0x83, 0xc6};
	uint8_t loop[] = {0xe2};
	uint8_t syscall[] = {0x0f, 0x05};
	uint8_t ret[] = {0xc3};
	uint8_t mov_si_ax[] = {0x48, 0x89, 0xf0};
	uint8_t mov_ax_lit64[] = {0x48, 0xa3};
} // namespace

x86_64::x86_64() {
	// long initialization of vector.
	instructions.push_back(instruction(sizeof(mov_64), (uint8_t *) &mov_64));
	instructions.push_back(instruction(sizeof(mov_cx_si), (uint8_t *) &mov_cx_si));
	instructions.push_back(instruction(sizeof(mov_dx_64), (uint8_t *) &mov_dx_64));
	instructions.push_back(instruction(sizeof(mov_di_64), (uint8_t *) &mov_di_64));
	instructions.push_back(instruction(sizeof(mov_ax_64), (uint8_t *) &mov_ax_64));
	instructions.push_back(instruction(sizeof(add_lit8), (uint8_t *) &add_lit8));
	instructions.push_back(instruction(sizeof(add_lit8_lock), (uint8_t *) &add_lit8_lock));
	instructions.push_back(instruction(sizeof(add_lit8_si), (uint8_t *) &add_lit8_si));
	instructions.push_back(instruction(sizeof(add_lit8_si_lock), (uint8_t *) &add_lit8_si_lock));
	instructions.push_back(instruction(sizeof(loop), (uint8_t *) &loop));
	instructions.push_back(instruction(sizeof(syscall), (uint8_t *) &syscall));
	instructions.push_back(instruction(sizeof(ret), (uint8_t *) &ret));
	instructions.push_back(instruction(sizeof(mov_si_ax), (uint8_t *) &mov_si_ax));
	instructions.push_back(instruction(sizeof(mov_ax_lit64), (uint8_t *) &mov_ax_lit64));
}

const uint8_t *x86_64::get(enum operation op) const {
	return instructions[op].op;
}
