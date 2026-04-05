#include "commands.h"

#include "CommandsExec.h"
#include "../audio/audio.h"

#include <string>
#include <vector>
#include <filesystem>
#include <iostream>
#include <toml++/toml.hpp>
#include <algorithm>

namespace fs = std::filesystem;

//--------------------------------Constructor----------------------------------

CommandsService::CommandsService(std::vector<std::pair<std::string,
						       std::string>>& rlist/*,
				AudioService& audio*/)
				: reply_list(rlist)/*, 
				audioService(audio)*/    //Old constructor commented
{
}

//-----------------------------Init Functions----------------------------------

void CommandsService::audioServicePtr(AudioService* audioPtr) { //Set AudioService pointer (IT SHOULD BE TEMPORARY)
	this->audioService = std::move(audioPtr);
}

void CommandsService::set_cmd_dir(std::string path) {
	this->cmd_dir = fs::path(std::move(path));

	std::cout << "[CORE/COMMANDS]: Set commands directory to " 
		  << this->cmd_dir << '\n';
}



std::vector<command> CommandsService::load_cmd_toml(fs::path rt_dir) {   //Load commands from sigle toml file
	fs::path dir = rt_dir / "commands.toml";   //path to toml file 	//Здесь я чутка забил на правило 60-80 символов
	toml::table tbl = toml::parse_file(dir.string());
	std::vector<command> local_cmd_list;

	if (auto arr = tbl["command"].as_array()) {
		local_cmd_list.reserve(arr->size());

		for (const auto& cmd : *arr) {
       			if (auto t = cmd.as_table()) {
       				command command;
       				command.type = (*t)["type"].value_or<std::string>("");  //Load type
       				command.name = (*t)["name"].value_or<std::string>("");  //Load name
				
				if (const toml::array* arr = (*t)["reply"].as_array()) { //Load replies
					for (auto& rep : *arr) {
						command.reply.push_back(rep.value_or<std::string>(""));
					}
					command.reply_amount = command.reply.size();
				}

				std::string_view file = (*t)["file"].value_or<std::string_view>("");  //Load file
				if (!file.empty()) {
					if (!(fs::path(file).is_absolute())) {
						command.path = (rt_dir / 
								file).string();
					} else {
						command.path = file.data();
					}
				} else {
					command.path = "";
				}
				
       				local_cmd_list.push_back(std::move(command));
       			}
		}
	}

	return local_cmd_list;
}



void CommandsService::load_commands() {  //Load every single command
	this->commands_amount = 0;
	std::vector<command> temp_cmd_list;

	if (!fs::exists(this->cmd_dir) || !fs::is_directory(this->cmd_dir)) {
		std::cerr << "[CORE/COMMANDS]: Commands directory not found.\n";
		return;
	}

	for (const auto& subdir : fs::directory_iterator(this->cmd_dir)) {
		//std::cout << "Toml subdir: " << subdir << '\n';

		for (auto& elem : this->load_cmd_toml(subdir.path())) {
			if (!elem.name.empty() && 
			    !(elem.path.empty() && elem.type != "say")) {
				temp_cmd_list.push_back(std::move(elem));
				this->commands_amount++;
			}
      		}
	}

	this->commands_list = std::move(temp_cmd_list);

	std::cout << "[CORE/COMMANDS]: Loaded " << this->commands_amount 
		  << " commands from " << this->cmd_dir << '\n';
}


//---------------------------Return commands list-------------------------------


std::vector<command>& CommandsService::get_cmd_list() {
	return this->commands_list;
}


//------------------------------Main functions----------------------------------


command* CommandsService::search_cmd(std::string_view text) {
	auto cmd = std::find_if(this->commands_list.begin(), 
				this->commands_list.end(), 
				[&text](const command& tmp_cmd){ 
					return tmp_cmd.name == text;
				});

	if (cmd != commands_list.end()) {
		return &(*cmd);
	} else {
		return nullptr;
	}
}

std::string CommandsService::searchReply(std::string name) {
	auto reply = std::find_if(this->reply_list.begin(), 
				  this->reply_list.end(), 
				  [&name](const auto& temp){ 
					return temp.first == name; 
				  });

	if (reply != this->reply_list.end()) {
		return reply->second;
	} else {
		return "1001001101101111110111";
	}
}


void CommandsService::exec_cmd(std::string_view cmd_txt) {
	const auto* cmd = search_cmd(cmd_txt);

	if (cmd == nullptr) {
		std::cout << "[CORE/COMMANDS]: " << cmd_txt << " not found.\n";
		audioService->play(searchReply("not_found"));
		return;
	} /*else {
		std::cout << "[CORE/COMMANDS]: name: " << cmd->name << "   type: " << cmd->type << "   path: " << cmd->path << '\n';
	}*/
	//std::cout << cmd->name << '\n';
	
	
	if (cmd->type == "exec") {
		run_type_exec(cmd->path);
		audioService->play(searchReply(cmd->reply[rand() % cmd->reply_amount]));
	} else if (cmd->type == "say") {
		audioService->play(searchReply(cmd->reply[rand() % cmd->reply_amount]));
	} else {
		std::cerr << "[CORE/COMMANDS]: Error during command execution: unknown type \"" 
			  << cmd->type << "\"\n";
	}
}
