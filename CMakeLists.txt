cmake_minimum_required(VERSION 3.20)

project(Jarvis31 LANGUAGES CXX)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")


find_path(ASIO_INCLUDE_DIR NAMES asio.hpp
	HINTS /usr/include/asio /usr/local/include
)
if(NOT ASIO_INCLUDE_DIR)
	message(FATAL_ERROR "There is no Asio.")
endif()

add_executable(jarvis
	src/main.cpp
	src/CORE/core.cpp
	src/CORE/commands/commands.cpp
	src/CORE/commands/termIn.cpp
	src/app/app.cpp
)

target_compile_definitions(jarvis PRIVATE
	ASIO_STANDALONE
	ASIO_NO_DEPRECATED
)

target_compile_options(jarvis PRIVATE
	-Wall -Wextra -pthread
	#$<$<CXX_COMPILER_ID:Clang>:-fcoroutines>
)

target_link_options(jarvis PRIVATE
	-pthread
)

add_custom_command(TARGET jarvis POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E rm -rf 
		$<TARGET_FILE_DIR:jarvis>/resources
	COMMAND ${CMAKE_COMMAND} -E copy_directory
		${SOURCE_DIR}/resources
		${CMAKE_BINARY_DIR}/bin/resources
)
