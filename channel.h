
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
	channel() : alive_(true) {}

	std::pair<bool, t> get() {
		std::unique_lock<std::mutex> lock(mut);
		while (queue.empty() && alive()) {
			cond.wait(lock);
		}
		if (queue.empty()) {
			// FIXME: this line causes death and destruction (most likely)
			// the second type of the pair must never be touched when
			// the first is false (as in failure).
			// static_cast-ing some junk data (nullptr) seems to work
			// for avoiding compile errors/warnings, but I'm not sure
			// if it absorbs surrounding memory or does other schetchy
			// operations.
			return std::make_pair(false, static_cast<t>(nullptr));
		}
		auto p = std::make_pair(true, queue.front());
		queue.pop();
		return p;
	}

	void put(const t& item) {
		std::unique_lock<std::mutex> lock(mut);
		queue.push(item);
		lock.unlock();
		cond.notify_one();
	}

	bool empty() const {
		std::lock_guard<std::mutex> lock(mut);
		return queue.empty();
	}

	bool alive() const {
		return alive_;
	}

	void kill() {
		alive_ = false;
	}
private:
	mutable std::mutex mut;
	std::condition_variable cond;
	std::queue<t> queue;
	std::atomic<bool> alive_;
};

} // namespace bf

#endif // BF_CHANNEL_H_
