#include "audio.h"

#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"
#include "miniaudio_libvorbis.h"

#include <iostream>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

struct AudioService::Impl {
	ma_resource_manager resourceManager;
	ma_engine engine;
	ma_sound currentSound;
	bool isPlaying;
	bool isInitialized;

	ma_decoding_backend_vtable* pCustomBackendVTables[1] = {
		ma_decoding_backend_libvorbis
	};
};

AudioService::AudioService() : pImpl(std::make_unique<Impl>()) {}

AudioService::~AudioService() = default;

std::vector<std::pair<std::string, std::string>> AudioService::loadReplyList(std::string path) {
	std::vector<std::pair<std::string, std::string>> temp_arr;
	try {
		size_t temp { 0 };
		for (const auto& file : fs::directory_iterator(path)) {
			if(file.is_regular_file()) {
				std::string name = file.path().stem().string();
				std::string path = file.path().string();
				temp_arr.emplace_back(name, path);
				temp++;
			}
		}
		return temp_arr;
		std::cout << "[CORE/AUDIO]: Loaded " << temp << " replies from " << path << '\n';
		
	} catch (const fs::filesystem_error& e) {
		std::cerr << "[CORE/AUDIO]: Error during loading responses list: " << e.what() << '\n';
	}
	//return temp_arr;
}
				


bool AudioService::init() {
	auto& impl = *pImpl;
	if (impl.isInitialized) {
		printf("AudioService is already initialized\n");
		return true;
	}

	ma_resource_manager_config resourceManagerConfig;
	ma_engine_config engineConfig;
	ma_result result;

	resourceManagerConfig = ma_resource_manager_config_init();
	resourceManagerConfig.ppCustomDecodingBackendVTables = impl.pCustomBackendVTables;
	resourceManagerConfig.customDecodingBackendCount = sizeof(impl.pCustomBackendVTables) / sizeof(impl.pCustomBackendVTables[0]);
	resourceManagerConfig.pCustomDecodingBackendUserData = NULL;

	result = ma_resource_manager_init(&resourceManagerConfig, &impl.resourceManager);
	if (result != MA_SUCCESS) {
		std::cerr << "[INIT]: Failed to initialize MA resource manager\n";
	}
	
	engineConfig = ma_engine_config_init();
	engineConfig.pResourceManager = &impl.resourceManager;
	
	result = ma_engine_init(&engineConfig, &impl.engine);
	if (result != MA_SUCCESS) {
		std::cerr << "[INIT]: Failed to initialize MA engine\n";
	}

	impl.isInitialized = true;
	return true;
}

void AudioService::uninit() {
	auto& impl = *pImpl;
	if (impl.isPlaying) {
		ma_sound_uninit(&impl.currentSound);
		printf("[UNINIT]: Stopped playing sound\n");
	}

	if (impl.isInitialized) {
		ma_engine_uninit(&impl.engine);
		printf("[UNINIT]: Uninitialized MA engine\n");
		ma_resource_manager_uninit(&impl.resourceManager);
		printf("[UNINIT]: Uninitialized MA engine\n");
		impl.isInitialized = false;
	}
}

void AudioService::play(const std::string file_cxx) {
	auto& impl = *pImpl;
	if (!impl.isInitialized) {
		std::cerr << "[CORE/AUDIO]: Failed to play sound: AudioService is not initialized";
		return;
	}

	const char* file = file_cxx.c_str();
	ma_result result;

	if (impl.isPlaying) {
		ma_sound_uninit(&impl.currentSound);
		impl.isPlaying = false;
	}

	result = ma_sound_init_from_file(&impl.engine, file, 0, NULL, NULL, &impl.currentSound);
	if (result != MA_SUCCESS) {
		std::cerr << "[AUDIO]: Failed to load sound: " << file_cxx << '\n';
		return;
	}

	result = ma_sound_start(&impl.currentSound);
	if (result != MA_SUCCESS) {
		std::cerr << "[AUDIO]: Failed to play sound: " << file_cxx << '\n';
		ma_sound_uninit(&impl.currentSound);
		return;
	}

	impl.isPlaying = true;
	std::cout << "[AUDIO]: Playing sound: " << file_cxx << '\n';
}


