#include "CommandsExec.h"

#include <boost/process.hpp>
#include <iostream>

/*
#ifdef(_WIN32)
	#include <windows.h>
#else
	#include <unistd.h>
	#include <cstring>
#endif
*/


bool run_type_exec(const std::string& file_path) {
	try {
		//auto c = std::make_shared<boost::process::child>(file_path);
		boost::process::child c(
			file_path,
			boost::process::std_in < boost::process::null,
			boost::process::std_out > boost::process::null,
			boost::process::std_err > boost::process::null
		);
		c.detach();
		//boost::process::spawn(file_path);


		std::cout << "[CORE/COMMANDS]: Executed " << file_path << '\n';
	} catch (const std::exception& e) {
		std::cerr << "[CORE/COMMANDS]: Error during command execution: " << e.what() << '\n';
		return false;
	}

	return true;
}
