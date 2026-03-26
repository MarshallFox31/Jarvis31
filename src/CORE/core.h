#ifndef CORE_HEADER
#define CORE_HEADER

#include <memory>
#include <string>

namespace asio {
	class io_context;
}

class CommandQueue;


class Core {
public:
	explicit Core(asio::io_context& ioctx);
	~Core();

	CommandQueue& getCmdQ();

	void forceShutdown(std::string where);

private:
	asio::io_context& io;
	
	std::unique_ptr<CommandQueue> command_queue;
};

#endif
