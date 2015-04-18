
#ifndef BF_LOG_H_
#define BF_LOG_H_

#include "channel.h"

#include <mutex>
#include <string>
#include <future>

namespace bf {

class log {
public:
	log();
	~log();
	void println(std::string& str);
	void wait();
private:
	channel<std::function<void()>> lambdas;
	std::future<void> printer;
};

// global log
extern log logger;

} // namespace bf

#endif // BF_LOG_H_
