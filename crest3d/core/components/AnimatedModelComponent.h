#pragma once
#include "EngineComponent.h"
#include "gfx/AnimatedModel.h"
#include "components/ShaderComponent.h"

class AnimatedModelComponent : public EngineComponent
{
public:
	AnimatedModelComponent(std::shared_ptr<Entity> e, std::shared_ptr<AnimatedModel> _model);

	void init() override;
	void start() override;
	void earlyUpdate(float deltaTime) override;
	void update(float deltaTime) override;
	void render(float deltaTime, glm::mat4 view) override;
	void ui(float deltaTime) override;
	void draw(glm::mat4 view, std::shared_ptr<ShaderComponent> _shader);
	void setShouldDraw(bool newValue) { shouldDraw = newValue; }

	bool shouldDraw;
	void SetBoneTransformID(std::shared_ptr<ShaderComponent> shader, unsigned int id, glm::mat4 transform);

	// can be a reference from the asset manager
	std::shared_ptr<AnimatedModel> anim;
	void getBoneShaderIDLocations(std::shared_ptr<ShaderComponent> sc);

private:
	float runningTime;
	static const int MAX_NUM_BONES = 250;
	std::vector<unsigned int> gBoneShaderIDs;
	std::vector<glm::mat4> boneTransforms;
};