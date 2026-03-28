#ifndef COMMANDS_ENGINE_HEADER
#define COMMANDS_ENGINE_HEADER

#include <string>
#include <vector>
#include <filesystem>


struct command {
	std::string name;
	
	std::string type; //Type of command: lua, exec

	std::string path; //Path to file (if type == lua, exec)
};


class CommandsService {
public:
	void load_commands();

	void set_cmd_dir(std::string path);
	
	std::vector<command>& get_cmd_list();

private:
	std::vector<command> load_cmd_toml(std::filesystem::path dir);

	std::filesystem::path cmd_dir;

	std::vector<command> commands_list;
	size_t commands_amount;
};


#endif
