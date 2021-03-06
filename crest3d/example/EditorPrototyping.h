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
	Cubemap* skybox;
	Shader* cubemapShader;
	unsigned int barrelAssetID;
	void AddRigidbodies();
	void DeleteRigidbodies();
	void RigidbodyTest();
	std::vector<std::string> ribEntityNames;
	
	float clapTimer;

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

	float forceAmount = 5.0f;

	glm::vec3 boxScale;
	// private functions
	void ImGuiEntityDebug(std::shared_ptr<Entity> e);
};