#include "../CORE/core.h"
#include "../CORE/commands/commands.h"
#include <iostream>
#include <thread>
#include <asio.hpp>
#include "../CORE/commands/termIn.h"


void main_loop(Core& core) {
	std::cout << "[MAIN]: Main loop started.\n";

	std::thread tin = TInput(core.getCmdQ());
	

	while (true) {
		CommandInput cmd = core.getCmdQ().wait();

		std::cout << "[MAIN]: Received command '" << cmd.text << "' from " << cmd.source << '\n';

	}
}
	
	

void app_main_init(asio::io_context& io) {
	Core core(io);
	

	std::cout << "[INIT]: Application initialized.\n";
	
	main_loop(core);
}


