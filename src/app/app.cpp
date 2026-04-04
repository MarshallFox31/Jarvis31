#include "../CORE/core.h"
//#include "../CORE/commands/commands.h"
#include <iostream>
#include <thread>
#include <asio.hpp>
#include "../CORE/commands/termIn.h"


void main_loop(Core& core/*, CommandsService& cmd*/) {
	std::cout << "[MAIN]: Main loop started.\n";

	std::thread tin = TInput(core.getCmdQ());  //TEMPORARY, I HOPE HOPE HOPE
	
	//core.getCmdQ().push({"test", "test"});

	core.getAudioService().play("resources/audio/run.ogg");

	while (true) {
		//core.forceShutdown("TEST main loop");
		CommandInput command = core.getCmdQ().wait();
		std::cout << "[MAIN]: Received command '" << command.text << "' from " << command.source << '\n';

		
		core.getCmdService().exec_cmd(command.text);
	}
}
	
	

void app_main_init(asio::io_context& io) {
	Core core(io);
	
	//CommandsService& cmd = core.getCmdService();

	printf("[INIT]: Initialization...\n");

	core.getCmdService().set_cmd_dir("resources/commands"); //Setting commands directory

	core.getCmdService().load_commands();

	if (!core.getAudioService().init()) { //Initializing audio
		return;
	}
	
	core.setReplyDir("resources/audio");
	core.loadReply();

	//std::cout << core.getCmdService().get_cmd_list().at(0).path << '\n';

	std::cout << "[INIT]: Application initialized.\n";
	
	main_loop(core/*, cmd*/);

	core.getAudioService().uninit();
}


