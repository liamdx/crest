#pragma once

#include "components/EngineComponent.h"

struct AudioFile
{
	std::string filepath;
	YSE::sound* sound;
	bool isReady;
	
	AudioFile(const char* _filepath)
	{
		filepath = _filepath;
		sound = new YSE::sound();
		sound->create(filepath.c_str());
		isReady = sound->isReady();
	}

	AudioFile()
	{
		sound = new YSE::sound();
		isReady = sound->isReady();
	}
	
	~AudioFile()
	{
		delete sound;
	}

	void Load(const char* path)
	{
		if(!sound->isReady())
		{
			filepath = path;
			sound->create(filepath.c_str());
			isReady = sound->isReady();
		}
	}
};

class AudioComponent : public EngineComponent
{

public:

	
	AudioComponent() { name = "AudioComponent"; clip = nullptr; }
	AudioComponent(std::shared_ptr<AudioFile> file) { name = "AudioComponent"; clip = file; }
	~AudioComponent() override {};

	void init() override;
	void start() override;
	void earlyUpdate(float deltaTime) override;
	void update(float deltaTime) override;
	void ui(float deltaTime) override;

	void SetClip(std::shared_ptr<AudioFile> newAudioFile);
	void Play();
	void Stop();
	
	std::shared_ptr<AudioFile> clip;
	bool looping;
	
private:
	bool shouldPlay;
	
};