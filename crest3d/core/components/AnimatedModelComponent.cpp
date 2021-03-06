#include "components/AnimatedModelComponent.h"
#include "serialization/Serializer.hpp"

AnimatedModelComponent::AnimatedModelComponent(std::shared_ptr<Entity> e, std::shared_ptr<AnimatedModel> _model)
{
	attachedEntity = e;
	anim = _model;
	runningTime = 0.0f;
	shouldDraw = true;
	usingMotionBlur = false;
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
	gPrevBoneShaderIDs.clear();
	for (unsigned int i = 0; i < anim->NumBones(); i++)
	{
		std::stringstream currentBoneLocation;
		currentBoneLocation << "gPrevBones[" << i << "]";
		gPrevBoneShaderIDs.push_back(sc->shader->getMat4Location(currentBoneLocation.str()));
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
	boneTransforms.clear();
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
			if (usingMotionBlur)
			{
				SetBoneTransformID(_shader, gPrevBoneShaderIDs[i], previousBoneTransforms[i]);
			}
		}

		_shader->setView(view);
		_shader->UpdateShader(attachedEntity->transform->getModelMatrix());
		anim->Draw(_shader);
		previousBoneTransforms = boneTransforms;
	}
}

void AnimatedModelComponent::SetBoneTransformID(std::shared_ptr<ShaderComponent> shader, unsigned id, glm::mat4 transform)
{
	shader->shader->setMat4ID(id, transform);
}

tinyxml2::XMLElement* AnimatedModelComponent::serialize_component(tinyxml2::XMLDocument* doc)
{
	auto amcElement = doc->NewElement("AnimatedModelComponent");
	auto amElement = anim->serialize(doc);
	amcElement->LinkEndChild(amElement);
	amcElement->LinkEndChild(Serializer::SerializeBool(shouldDraw, "shouldDraw", doc));
	amcElement->LinkEndChild(Serializer::SerializeBool(usingMotionBlur, "useMotionBlur", doc));
	return amcElement;
}
