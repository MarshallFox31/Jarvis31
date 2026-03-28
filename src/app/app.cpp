#include "../CORE/core.h"
//#include "../CORE/commands/commands.h"
#include <iostream>
#include <thread>
#include <asio.hpp>
#include "../CORE/commands/termIn.h"


void main_loop(Core& core) {
	std::cout << "[MAIN]: Main loop started.\n";


	std::thread tin = TInput(core.getCmdQ());
	
	core.getCmdQ().push({"experement", "test"});

	while (true) {
		CommandInput cmd = core.getCmdQ().wait();
		std::cout << "[MAIN]: Received command '" << cmd.text << "' from " << cmd.source << '\n';


		
	}
}
	
	

void app_main_init(asio::io_context& io) {
	Core core(io);
	
	CommandsService& cmd = core.getCmdService();

	printf("[INIT]: Initialisation...\n");

	cmd.set_cmd_dir("resources/commands");

	cmd.load_commands();

	std::cout << cmd.get_cmd_list().at(0).name << '\n';

	std::cout << "[INIT]: Application initialized.\n";
	
	main_loop(core);
}


