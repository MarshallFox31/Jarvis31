#include <asio.hpp>
#include <thread>
#include "CORE/core.h"

int main() {
	asio::io_context io;

	auto guard = asio::make_work_guard(io);

	std::thread io_thread([&io] {
		io.run();
	});


	main_loop(io);

	guard.reset();
	io_thread.join();

	return 0;
}
