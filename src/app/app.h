#ifndef CORE_HEADER
#define CORE_HEADER

namespace asio {
	class io_context;
}

class Core;

void main_loop(Core& core);

void app_main_init(asio::io_context& io);

#endif
