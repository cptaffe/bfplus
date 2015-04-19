
#ifndef BF_LOG_H_
#define BF_LOG_H_

#include "channel.h"

#include <mutex>
#include <string>
#include <future>
#include <iostream>

namespace bf {

class log {
public:
	log(std::ostream& os);
	~log();
	void operator<<(const std::string& str);
	void wait();
private:
	std::ostream& os;
	channel<std::function<void()>> lambdas;
	std::future<void> printer;
};

// extern error log
extern log err;

} // namespace bf

#endif // BF_LOG_H_
