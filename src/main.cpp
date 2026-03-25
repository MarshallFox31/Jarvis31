#include <iostream>
#include <boost/asio.hpp>


void hmm(const boost::system::error_code& /*e*/) {
	std::cout << "Okay, maybe I have timer." << '\n';
}

int main(int argc, char* argv[]) {
	boost::asio::io_context io;

	std::cout << "There is... nothing." << '\n';
		
	boost::asio::steady_timer t(io, boost::asio::chrono::seconds(3));
	t.async_wait(&hmm);

	io.run();


	return 0;
}
