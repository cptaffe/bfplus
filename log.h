
#ifndef BF_LOG_H_
#define BF_LOG_H_

#include "channel.h"

#include <mutex>
#include <string>
#include <future>

namespace bf {

class log {
public:
	log(std::ostream& os);
	~log();
	void println(std::string& str);
	void wait();
private:
	std::ostream& os;
	channel<std::function<void()>> lambdas;
	std::future<void> printer;
};

// global log
extern log logerr;

} // namespace bf

#endif // BF_LOG_H_
