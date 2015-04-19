
#ifndef BF_TOK_H_
#define BF_TOK_H_

#include <string>
#include <utility>

namespace bf {

class tok {
public:

	typedef enum {
		CROSS,      // +
		DASH,       // -
		FORWARD,    // >
		BACK,       // <
		BEGIN_LOOP, // [
		END_LOOP,   // ]
	} token_type;

	tok(token_type t, std::string msg);
	const std::pair<token_type, std::string> *token() const;
private:
	std::pair<token_type, std::string> token_;
};

} // namespace bf

#endif // BF_TOK_H_
