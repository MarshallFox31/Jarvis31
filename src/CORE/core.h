#ifndef CORE_HEADER
#define CORE_HEADER

#include "commands/commands.h"
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

	CommandsService& getCmdService() { return CmdsService; };

	void forceShutdown(std::string where);

private:
	asio::io_context& io;
	
	std::unique_ptr<CommandQueue> command_queue;

	CommandsService CmdsService;
};

#endif
