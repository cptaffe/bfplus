
#include "tok.h"

using namespace bf;

tok::tok(tok::token_type t, std::string msg) :
	token_(std::make_pair(t, msg)) {}

const std::pair<tok::token_type, std::string> *tok::token() const {
	return &token_;
}
