
#ifndef BF_JIT_H_
#define BF_JIT_H_

#include <vector>

namespace bf {

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
