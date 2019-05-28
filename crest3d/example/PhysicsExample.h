#pragma once
#include "Example.h"
class PhysicsExample : public Example
{
public:
	PhysicsExample(GLFWwindow* _window);
	~PhysicsExample() override {};

	void initBehaviour() override;
	void startBehaviour() override;
	void earlyUpdateBehaviour(float deltaTime) override;
	void fixedUpdateBehaviour() override;
	void updateBehaviour(float deltaTime) override;
	void renderBehaviour(float deltaTime) override;
	void uiBehaviour(float deltaTime) override;

private:
	std::shared_ptr<PhysicsManager> pm;
	std::unique_ptr<Scene> scene;
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