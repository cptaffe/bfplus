
#ifndef BF_LOG_H_
#define BF_LOG_H_

#include <mutex>
#include <string>
#include <list>
#include <future>

namespace bf {

class log {
public:
	~log();
	void println(std::string& str);
	void wait();
	void clean();
private:
	std::list<std::future<void>> prints;
	std::mutex mclean;
	std::mutex mut;
};

// global log
extern log logger;

} // namespace bf

#endif // BF_LOG_H_
