#pragma once
#include "Common.h"

static class AudioManager {
public:
	struct Sound {
		YSE::sound* sound;
		std::string name;
		bool looping;
		float volume;
		bool is3D;
		glm::vec3 location;
	};

	static void PlaySoundAtLocation(Sound* sound){
		sound->sound->play();
	}
};