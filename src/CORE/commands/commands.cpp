#include "commands.h"

#include <string>
#include <vector>
#include <filesystem>
#include <iostream>
#include <toml++/toml.hpp>


namespace fs = std::filesystem;

void CommandsService::set_cmd_dir(std::string path) {
	this->cmd_dir = fs::path(std::move(path));

	std::cout << "[CORE/COMMANDS]: Set commands directory to " << this->cmd_dir << '\n';
}

std::vector<command> CommandsService::load_cmd_toml(fs::path dir) {
	dir = dir / "commands.toml";
	toml::table tbl = toml::parse_file(dir.string());
	std::vector<command> local_cmd_list;

	if (auto arr = tbl["command"].as_array()) {
		local_cmd_list.reserve(arr->size());

		for (const auto& cmd : *arr) {
       			if (auto t = cmd.as_table()) {
       				command command;
       				command.type = (*t)["type"].value_or<std::string>("");
       				command.name = (*t)["name"].value_or<std::string>("");
       				command.path = (*t)["file"].value_or<std::string>("");

       				local_cmd_list.push_back(std::move(command));
       			}
		}
	}

	return local_cmd_list;
}

void CommandsService::load_commands() {
	this->commands_amount = 0;
	std::vector<command> temp_cmd_list;

	if (!fs::exists(this->cmd_dir) || !fs::is_directory(this->cmd_dir)) {
		std::cerr << "[CORE/COMMANDS]: Commands directory not found.\n";
		return;
	}

	for (const auto& subdir : fs::directory_iterator(this->cmd_dir)) {
		//std::cout << "Toml subdir: " << subdir << '\n';

		for (auto& elem : this->load_cmd_toml(subdir.path())) {
			if (!elem.name.empty() && !elem.path.empty()) {
				temp_cmd_list.push_back(std::move(elem));
				this->commands_amount++;
			}
      		}
	}

	this->commands_list = std::move(temp_cmd_list);

	std::cout << "[CORE/COMMANDS]: Loaded " << this->commands_amount << " commands from " << this->cmd_dir << '\n';
}

std::vector<command>& CommandsService::get_cmd_list() {
	return this->commands_list;
}
