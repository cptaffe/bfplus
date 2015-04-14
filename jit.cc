
#include "jit.h"

#include <string>
#include <sys/mman.h>
#include <unistd.h>

using namespace bf;

jit::jit(size_t mem_pages, size_t exec_pages) :
	// mmap pages with PROT_WRITE or PROT_EXEC at once to allow
	// for w^x compatibility.
	mem_pages(mem_pages),
	exec_pages(exec_pages),
	mem((uint8_t *) mmap(NULL,
		mem_pages * sysconf(_SC_PAGESIZE),
		PROT_WRITE,
		MAP_ANON | MAP_PRIVATE,
		-1, 0)),
	exec((uint8_t *) mmap(NULL,
		exec_pages * sysconf(_SC_PAGESIZE),
		PROT_WRITE,
		MAP_ANON | MAP_PRIVATE,
		-1, 0)),
	mem_index((int64_t) (intptr_t) mem) {

	// check for mmap errors
	if (mem == MAP_FAILED || exec == MAP_FAILED) {
		throw new std::runtime_error("mmap failed.");
	}
}

jit::~jit() {

	// unmap memory
	int munmap_err(0);
	munmap_err |= munmap(exec, exec_pages * sysconf(_SC_PAGESIZE));
	munmap_err |= munmap(mem, mem_pages * sysconf(_SC_PAGESIZE));

	// possibly throw error
	if (munmap_err == true) {
		throw new std::runtime_error("munmap failed with " + std::to_string(munmap_err) + ".");
	}
}

bool jit::runnable() const {
	return runnable_;
}
