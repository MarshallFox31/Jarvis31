#include "commands.h"

#include <asio.hpp>
#include <string>
#include <stdexcept>
#include <iostream>



asio::awaitable<void> timer(size_t time) {
	auto ex = co_await asio::this_coro::executor;
	asio::steady_timer t(ex);
	t.expires_after(std::chrono::seconds(time));
	
	std::cout << "Timer command executed. 5 seconds.\n";

	co_await t.async_wait(asio::use_awaitable);
	std::cout << "Timer ended.\n";
}

void run(std::string command, asio::io_context& io) {
	if (command == "timer") {
		std::cout << "Ok\n";
		asio::co_spawn(io, timer(5), asio::detached);
	} else {
		throw std::invalid_argument("Unknown command");
	}
}


