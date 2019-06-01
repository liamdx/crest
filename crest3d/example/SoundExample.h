

#pragma once
#include "Example.h"
class SoundExample : public Example
{
public:
	SoundExample(GLFWwindow* _window);
	~SoundExample() override { delete cubemapShader; delete skybox; };

	void initBehaviour() override;
	void startBehaviour() override;
	void earlyUpdateBehaviour(float deltaTime) override;
	void fixedUpdateBehaviour() override;
	void updateBehaviour(float deltaTime) override;
	void renderBehaviour(float deltaTime) override;
	void uiBehaviour(float deltaTime) override;


private:
	std::shared_ptr<PhysicsManager> pm;
	std::shared_ptr<Scene> scene;
	std::shared_ptr<InputManager> input;
	std::shared_ptr<GLFWwindow> window;
	std::shared_ptr<CameraComponent> cam;

	std::shared_ptr<Entity> levelEntity;
	std::shared_ptr<Entity> cyborgEntity;
	std::shared_ptr<Entity> cameraEntity;

	ImVec4 levelPosition;
	ImVec4 levelRotation;
	ImVec4 cameraPosition;
	ImVec4 cameraRotation;

	Cubemap* skybox;
	Shader* cubemapShader;

	std::shared_ptr<rp3d::RigidBody> debugRib;
	std::shared_ptr<ProxyShape> e;

	// this stuff needs component-ised
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