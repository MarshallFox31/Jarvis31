#include "core.h"
#include "commands/CommandsQueue.h"
#include <iostream>
#include <asio.hpp>

Core::Core(asio::io_context& ioctx)
	: io(ioctx)
	, command_queue(std::make_unique<CommandQueue>())
{
}

Core::~Core() = default;

void Core::forceShutdown(std::string where) {
	std::cout << "\n[CORE]: FORCED SHUTDOWN FROM: " << where << '\n';
}


CommandQueue& Core::getCmdQ() {
	return *command_queue;
}
