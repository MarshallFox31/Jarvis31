#ifndef COMMANDS_ENGINE_HEADER
#define COMMANDS_ENGINE_HEADER

#include <string>
#include <vector>
#include <filesystem>
#include <utility>

class AudioService;

struct command {
	std::string name;
	
	std::string type; //Type of command: lua, exec

	std::string path; //Path to file (if type == lua, exec)
	
	std::vector<std::string> reply; //Audio reply
	size_t reply_amount; //Amount of replies
	
};


class CommandsService {
public:
	CommandsService(
		std::vector<std::pair<std::string, std::string>>& rlist/*,
		AudioService& audio*/);

	void audioServicePtr(AudioService* audioPtr);

	void load_commands();

	void set_cmd_dir(std::string path);
	
	std::vector<command>& get_cmd_list();

	void exec_cmd(std::string_view cmd_txt); //Execute command

private:
	std::vector<command> load_cmd_toml(std::filesystem::path dir);

	std::filesystem::path cmd_dir;

	std::vector<command> commands_list;
	size_t commands_amount;

	command* search_cmd(std::string_view text); //Search in list
	
	std::string searchReply(std::string name);
	std::vector<std::pair<std::string, std::string>>& reply_list;
	AudioService* audioService; //TEMPORARY, I HOPE HOPE HOPE
};


#endif
