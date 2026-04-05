#include "core.h"
#include "commands/CommandsQueue.h"
#include <iostream>
#include <asio.hpp>

Core::Core(asio::io_context& ioctx)
	: io(ioctx)
	, command_queue(std::make_unique<CommandQueue>())
	, CmdsService(reply_list/*, AudioService*/)
	, AudioService()
{
	printf("JARVIS31 v0.1 ALPHA by Marshall31\n\n");
}

Core::~Core() = default;

/*bool Core::checkIsActive() {
	return this->active;
}

void Core::forceShutdown(std::string where) {
	std::cout << "\n[CORE]: FORCED SHUTDOWN FROM: " << where << '\n';
	this->active = false;
}*/


CommandQueue& Core::getCmdQ() {
	return *command_queue;
}

void Core::loadReply() {
	this->reply_list = AudioService.loadReplyList(this->reply_path);
}
