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

find_package(Boost 1.70 REQUIRED)

add_executable(Jarvis
	src/main.cpp
	src/CORE/core.cpp
	src/CORE/commands/commands.cpp
	src/CORE/commands/termIn.cpp
	src/CORE/commands/CommandsExec.cpp
	src/CORE/audio/audio.cpp
	src/CORE/audio/miniaudio_libvorbis.cpp
	src/app/app.cpp
)

target_link_libraries(Jarvis PRIVATE
	Boost::headers
	#Boost::system
	vorbis
	ogg
	vorbisfile
)

target_compile_definitions(Jarvis PRIVATE
	ASIO_STANDALONE
	ASIO_NO_DEPRECATED
)

target_compile_options(Jarvis PRIVATE
	-Wall -Wextra -pthread
	#$<$<CXX_COMPILER_ID:Clang>:-fcoroutines>
)

target_link_options(Jarvis PRIVATE
	-pthread
)

add_custom_command(TARGET Jarvis POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E rm -rf 
		$<TARGET_FILE_DIR:Jarvis>/resources
	COMMAND ${CMAKE_COMMAND} -E copy_directory
		${SOURCE_DIR}/resources
		${CMAKE_BINARY_DIR}/bin/resources
)
