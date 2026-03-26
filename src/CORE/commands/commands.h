#ifndef COMMANDS_HEADER
#define COMMANDS_HEADER

#include <asio.hpp>
#include <string>

asio::awaitable<void> timer(size_t time);

void run(std::string command, asio::io_context& io);

#endif
