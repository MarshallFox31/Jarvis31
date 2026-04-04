#ifndef AUDIO_ENGINE_HEADER
#define AUDIO_ENGINE_HEADER

#include <memory>
#include <string>
#include <vector>
#include <utility>

class AudioService {
public:
	AudioService();
	~AudioService();

	bool init();
	void uninit();
	void play(const std::string file_cxx);
	
	std::vector<std::pair<std::string, std::string>> loadReplyList(std::string path);

	//bool waitUntilFinished();

private:
	struct Impl;
	std::unique_ptr<Impl> pImpl;
};

#endif

