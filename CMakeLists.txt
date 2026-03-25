cmake_minimum_required(VERSION 3.20)

project(Jarvis31 LANGUAGES CXX)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_path(ASIO_INCLUDE_DIR NAMES asio.hpp
	HINTS /usr/include/asio /usr/local/include
)
if(NOT ASIO_INCLUDE_DIR)
	message(FATAL_ERROR "There is no Asio.")
endif()

add_executable(jarvis
	src/main.cpp
)

target_compile_definitions(jarvis PRIVATE
	ASIO_STANDALONE
	ASIO_NO_DEPRECATED
)

target_compile_options(jarvis PRIVATE
	-Wall -Wextra -pthread
)


