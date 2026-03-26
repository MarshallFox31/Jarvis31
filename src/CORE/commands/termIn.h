#ifndef MANUAL_TERMINAL_INPUT_HEADER
#define MANUAL_TERMINAL_INPUT_HEADER

#include "CommandsQueue.h"
#include <thread>

std::thread TInput(CommandQueue& CmdQueue);

#endif
