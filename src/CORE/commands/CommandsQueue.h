#ifndef COMMAND_QUEUE_HEADER
#define COMMAND_QUEUE_HEADER

#include <deque>
#include <mutex>
#include <condition_variable>
#include <string>

struct CommandInput {
	std::string source; //Where command comes from
	std::string text;  //Command
};

class CommandQueue {
public:
	void push(CommandInput command) { //Add command to queue
		{
			std::lock_guard<std::mutex> lock(mtx);
			queue.push_back(std::move(command));
		}
		cv.notify_one();  
	}

	CommandInput wait() {  //Wait for command
		std::unique_lock<std::mutex> lock(mtx);
		cv.wait(lock, [this] { return !queue.empty(); });

		CommandInput cmd = std::move(queue.front());
		queue.pop_front();
		return cmd;
	}

	bool empty() {
		std::lock_guard<std::mutex> lock(mtx);
		return queue.empty();
	}

private:
	std::deque<CommandInput> queue; //I changed std::vector to std::deque
	std::mutex mtx;
	std::condition_variable cv;
};

#endif
