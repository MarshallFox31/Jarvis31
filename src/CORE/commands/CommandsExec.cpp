#include "CommandsExec.h"

#include <boost/process.hpp>
#include <iostream>


#ifdef _WIN32
	#include <boost/process/windows.hpp>
#else
	#include <boost/process/extend.hpp>
	#include <unistd.h>

	struct new_session : boost::process::extend::handler {
		template<typename Executor>
		void on_exec_setup(Executor&) const {
			::setsid();
		}
	};
#endif


//--------------------------------MAIN FUNCTIONS--------------------------------

bool run_type_exec(const std::string& file_path) {
	try {
		#ifdef _WIN32
			auto flags = boost::process::windows::creation_flags(
							      DETACHED_PROCESS);
		#else
			auto flags = new_session{};
		#endif
		//auto c = std::make_shared<boost::process::child>(file_path);
		boost::process::child c(
			file_path,
			boost::process::std_in < boost::process::null,
			boost::process::std_out > boost::process::null,
			boost::process::std_err > boost::process::null,
			flags
		);
		c.detach();
		//boost::process::spawn(file_path);


		std::cout << "[CORE/COMMANDS]: Executed " << file_path << '\n';
	} catch (const std::exception& e) {
		std::cerr << "[CORE/COMMANDS]: Error during command execution: "
			  << e.what() << '\n';
		return false;
	}

	return true;
}
