#include "components/AudioComponent.h"


void AudioComponent::init()
{

}

void AudioComponent::start()
{
	
}


void AudioComponent::earlyUpdate(float deltaTime)
{
	
}

void AudioComponent::update(float deltaTime)
{
	
}

void AudioComponent::ui(float deltaTime)
{
	
}


void AudioComponent::SetClip(std::shared_ptr<AudioFile> newAudioFile)
{
	clip = newAudioFile;
}

void AudioComponent::Play()
{
	if(clip != nullptr)
	{
		clip->sound->play();
	}
}
