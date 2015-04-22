
#include "comp.h"
#include "log.h"
#include "jit.h"
#include "tree.h"

#include <vector>
#include <iostream>

using namespace bf;

comp::comp(std::istream *is) :
	chan_(5),
	j(static_cast<architecture *>(&arch)),
	l(is, &chan_),
	run_(std::async([this]{
		tok *t;
		tree tr;
		while (chan_.get(&t)) {
			std::string str(*t->token()->second);
			err << str;
			delete t;
		}
	})) {
}
