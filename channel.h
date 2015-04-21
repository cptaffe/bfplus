
#ifndef BF_CHANNEL_H_
#define BF_CHANNEL_H_

#include <mutex>
#include <condition_variable>
#include <queue>
#include <atomic>
#include <utility> // std::pair
#include <iostream>

namespace bf {

class get_channel;
class put_channel;

template <typename t>
class channel {
public:
	channel(uint64_t max) : alive_(true), max_count(max), count_(0) {}

	bool get(t *item) {
		// aquire mutex & wait for empty.
		std::unique_lock<std::mutex> lock(mut);
		while (count_ == 0 && alive_) {
			empty.wait(lock);
		}

		if (!alive_ && queue.empty()) {
			return false;
		}

		*item = queue.front();
		queue.pop();
		--count_;

		lock.unlock();
		full.notify_one();
		return true;
	}

	void put(const t& item) {
		// aquire mutex & wait for empty.
		std::unique_lock<std::mutex> lock(mut);
		while (count_ == max_count && alive_) {
			full.wait(lock);
		}

		if (!alive_) {
			return;
		}

		queue.push(item);

		++count_;
		lock.unlock();
		empty.notify_one();
	}

	bool alive() const {
		return alive_;
	}

	void kill() {
		alive_ = false;
		// wake up all waiting because death.
		full.notify_all();
		empty.notify_all();
	}
private:
	std::mutex mut;
	std::queue<t> queue;

	// dead queue.
	std::atomic<bool> alive_;

	// atomic access full/empty
	const uint64_t max_count;
	std::atomic<uint64_t> count_;

	std::condition_variable full;
	std::condition_variable empty;
};

} // namespace bf

#endif // BF_CHANNEL_H_
