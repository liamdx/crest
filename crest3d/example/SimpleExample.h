#pragma once
#include "Example.h"

class SimpleExample : public Example
{
public:
	SimpleExample(GLFWwindow* _window);
	~SimpleExample() override { delete cubemapShader; delete model; delete skybox; };

	void initBehaviour() override;
	void startBehaviour() override;
	void earlyUpdateBehaviour(float deltaTime) override;
	void updateBehaviour(float deltaTime) override;
	void renderBehaviour(float deltaTime) override;
	void uiBehaviour(float deltaTime) override;


	// example vars
	Camera cam;
	glm::mat4 projection;

	std::shared_ptr<Entity> debugEntity;
	std::shared_ptr<Entity> cameraEntity;
	std::shared_ptr<ShaderComponent> debugShader;
	std::shared_ptr<TransformComponent> debugTransform;
	std::shared_ptr<TransformComponent> camTransform;
	std::shared_ptr<CameraComponent> debugCamera;

	float rotateCounter;

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

	GLFWwindow* window;
	Shader* cubemapShader;
	InputManager input;
	Model* model;
	Model* sponza;
	Cubemap* skybox;

private:
	float zOffset;
	float yOffset;
	float cameraRotation;

};