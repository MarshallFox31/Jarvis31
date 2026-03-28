#include "app/app.h"
#include <asio.hpp>
#include <thread>


int main() {
	asio::io_context io;

	auto guard = asio::make_work_guard(io);

	//Temporary removed
	/*std::thread io_thread([&io] {
		io.run();
	});*/  
	

	app_main_init(io);

	guard.reset();
	//io_thread.join();

	return 0;
}
