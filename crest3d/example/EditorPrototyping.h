
#pragma once
#include "Example.h"
class EditorPrototyping : public Example
{
public:
	EditorPrototyping(GLFWwindow* _window);
	~EditorPrototyping() override { delete cubemapShader; delete skybox; };

	void initBehaviour() override;
	void startBehaviour() override;
	void earlyUpdateBehaviour(float deltaTime) override;
	void fixedUpdateBehaviour() override;
	void updateBehaviour(float deltaTime) override;
	void renderBehaviour(float deltaTime) override;
	void uiBehaviour(float deltaTime) override;

	// use with caution!
	inline std::shared_ptr<Scene> getScene() { return std::shared_ptr<Scene>(scene); }

private:

	std::shared_ptr<RigidbodyComponent> cyborgRib;

	std::shared_ptr<AssetManager> am;
	std::shared_ptr<PhysicsManager> pm;
	std::shared_ptr<Scene> scene;
	std::shared_ptr<InputManager> input;
	std::shared_ptr<GLFWwindow> window;
	std::shared_ptr<CameraComponent> cam;

	std::shared_ptr<Entity> levelEntity;
	std::shared_ptr<Entity> cyborgEntity;
	std::shared_ptr<Entity> cameraEntity;
	std::shared_ptr<Entity> dirLight;
	std::shared_ptr<DirectionalLightComponent> dirLightComponent;

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