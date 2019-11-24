#pragma once

#include "EngineManager.h"
#include "Example.h"

class EditorPrototyping : public Example
{
public:
	EditorPrototyping(EngineManager* em);
	~EditorPrototyping() override { delete cubemapShader; delete skybox; };

	void initBehaviour() override;
	void startBehaviour() override;
	void earlyUpdateBehaviour(float deltaTime) override;
	void fixedUpdateBehaviour() override;
	void updateBehaviour(float deltaTime) override;
	void renderBehaviour(float deltaTime) override;
	void uiBehaviour(float deltaTime) override;


private:
	// every scene needs these, should be organised in a game manager

	// specific to this example
	std::shared_ptr<Entity> levelEntity;
	std::shared_ptr<Entity> cyborgEntity;
	std::shared_ptr<Entity> animEntity;
	std::shared_ptr<Entity> cameraEntity;
	std::shared_ptr<Entity> dirLight;
	std::shared_ptr<DirectionalLightComponent> dirLightComponent;
	std::shared_ptr<CameraComponent> cam;

	Cubemap* skybox;
	Shader* cubemapShader;

	//skybox faces
	std::vector<std::string> faces
	{
		"res/textures/violentdays/violentdays_rt.png",
		"res/textures/violentdays/violentdays_lf.png",
		"res/textures/violentdays/violentdays_up.png",
		"res/textures/violentdays/violentdays_dn.png",
		"res/textures/violentdays/violentdays_bk.png",
		"res/textures/violentdays/violentdays_ft.png"
	};
};