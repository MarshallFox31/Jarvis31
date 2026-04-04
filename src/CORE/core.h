#ifndef CORE_HEADER
#define CORE_HEADER

#include "commands/commands.h"
#include "audio/audio.h"

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

	AudioService& getAudioService() { return AudioService; };
	void loadReply();
	void setReplyDir(std::string path) { this->reply_path = path; };
	std::string& getReplyDir() { return reply_path; };

	/*void forceShutdown(std::string where);

	bool checkIsActive();*/
private:
	asio::io_context& io;

	AudioService AudioService;
	std::vector<std::pair<std::string, std::string>> reply_list;
	std::string reply_path;

	std::unique_ptr<CommandQueue> command_queue;
	CommandsService CmdsService;

	//bool active = true;
};

#endif
