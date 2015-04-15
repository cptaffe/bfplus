
#ifndef BF_JIT_H_
#define BF_JIT_H_

#include <vector>

namespace bf {

// interface for architecture
class architecture {
public:
	// listing of operations
	enum operation {
		MOV_64,
		MOV_CX_SI,
		MOV_DX_64,
		MOV_DI_64,
		MOV_AX_64,
		ADD_LIT8,
		ADD_LIT8_LOCK,
		ADD_LIT8_SI,
		ADD_LIT8_SI_LOCK,
		LOOP,
		SYSCALL,
		RET,
		MOV_SI_AX,
		MOV_AS_LIT64
	};

	virtual ~architecture() {}
	virtual const uint8_t *get(enum operation op) const = 0;
};

class x86_64 : public architecture {
public:
	virtual const uint8_t *get(enum operation op) const;
};

class jit {
public:
	jit(size_t mem_pages = 1, size_t exec_pages = 1);
	~jit();

	// give jit tokens
	// void put(tok *t);
	bool runnable() const;
	// void run();

private:
	size_t init_pos = 0,
		exec_pos = 0,
		exec_pages, mem_pages;

	uint8_t *exec = nullptr,
		*mem = nullptr;

	size_t loop_depth = 0; // loop depth
	std::vector<size_t> loop_stack; // exec pos stack

	size_t mem_disp = 0,
		mem_mod = 0;

	// if code is runnable
	bool runnable_ = false;

	// program state
	uint64_t mem_index;
};

} // namespace bf

#endif // BF_JIT_H_
