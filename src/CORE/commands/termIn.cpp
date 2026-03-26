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
		printf("\n");
		}
	});
}

