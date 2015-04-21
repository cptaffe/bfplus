
#include "comp.h"
#include "log.h"
#include "jit.h"

#include <vector>
#include <iostream>

using namespace bf;

comp::comp(std::istream *is) :
	chan_(5),
	j(static_cast<architecture *>(&arch)),
	l(is, &chan_),
	run_(std::async([this]{
		tok *t;
		while (chan_.get(&t)) {
			err << *(t->token()->second);
			delete t;
		}
	})) {
	err << "comp constructing";
}
