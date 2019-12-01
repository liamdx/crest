#include "components/AnimatedModelComponent.h"

AnimatedModelComponent::AnimatedModelComponent(std::shared_ptr<Entity> e, std::shared_ptr<AnimatedModel> _model)
{
	attachedEntity = e;
	anim = _model;
	runningTime = 0.0f;
	shouldDraw = true;
}

void AnimatedModelComponent::getBoneShaderIDLocations(std::shared_ptr<ShaderComponent> sc)
{
	gBoneShaderIDs.clear();
	for (unsigned int i = 0; i < anim->NumBones(); i++)
	{
		std::stringstream currentBoneLocation;
		currentBoneLocation << "gBones[" << i << "]";
		gBoneShaderIDs.push_back(sc->shader->getMat4Location(currentBoneLocation.str()));
		currentBoneLocation.clear();
	}
}

void AnimatedModelComponent::init()
{
}

void AnimatedModelComponent::start()
{
}

void AnimatedModelComponent::earlyUpdate(float deltaTime)
{
}

void AnimatedModelComponent::update(float deltaTime)
{
	runningTime += deltaTime;
	if (runningTime >= anim->currentAnimationLengthInSeconds)
	{
		runningTime = 0.0f;
	}

	if (shouldDraw)
	{
		anim->BoneTransform(runningTime, boneTransforms);
	}
}

void AnimatedModelComponent::render(float deltaTime, glm::mat4 view)
{
}

void AnimatedModelComponent::ui(float deltaTime)
{
}

void AnimatedModelComponent::draw(glm::mat4 view, std::shared_ptr<ShaderComponent> _shader)
{
	if (shouldDraw)
	{
		for (int i = 0; i < anim->NumBones(); i++)
		{
			SetBoneTransformID(_shader, gBoneShaderIDs[i], boneTransforms[i]);
		}

		_shader->setView(view);
		_shader->UpdateShader(attachedEntity->transform->getModelMatrix());
		anim->Draw(_shader);
		boneTransforms.clear();
	}
}

void AnimatedModelComponent::SetBoneTransformID(std::shared_ptr<ShaderComponent> shader, unsigned id, glm::mat4 transform)
{
	shader->shader->setMat4ID(id, transform);
}