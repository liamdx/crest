#include "components/AudioComponent.h"
#include "Entity.h"

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
		if(is3D)
		{
			YSE::Vec pos = YSE::Vec(attachedEntity->transform->position.x, attachedEntity->transform->position.y, attachedEntity->transform->position.z);
			clip->sound->setPosition(pos);
		}
		else
		{
			clip->sound->play();
		}
		
	}
}
