#include "core.h"
#include "commands.h"
#include <iostream>
#include <stdexcept>
#include <asio.hpp>

void main_loop(asio::io_context& io) {
	std::string cmd;

	while(true) {
		std::cin >> cmd;
		try {
			run(cmd, io);
		} catch (const std::invalid_argument &e) {
			std::cout << "Error: " << e.what() << '\n';
		}
	}
}
