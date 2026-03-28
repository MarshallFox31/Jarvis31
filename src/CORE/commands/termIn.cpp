#include "termIn.h"
#include "CommandsQueue.h"

#include <thread>
#include <iostream>
#include <string>

std::thread TInput(CommandQueue& CmdQueue) {
	return std::thread([&CmdQueue]() {
		printf("(terminal): Manual terminal input activated. Write 'break' to disable.\n");
		
		std::string in;

		while (true) {
			//printf("Enter command: ");
			if (!std::getline(std::cin, in) || in == "break") {
				//printf("\nTerminal input disabled.");
				break;
			}
		
		CmdQueue.push({"terminal", in});
		//CmdQueue.push({"terminal", "test"}); //It was for test and debug
		//CmdQueue.push({"terminal", "test1"});
		printf("\n");
		}
	});
}

