#pragma once
#include "Example.h"

class SimpleExample : public Example
{
public:
	SimpleExample();
	~SimpleExample() override {};
	void startBehaviour() override;
	void earlyUpdateBehaviour() override;
	void updateBehaviour() override;
	void uiBehaviour() override;


	// example vars
	// Camera BoneCam;

	//skybox faces
	std::vector<std::string> faces
	{
		"res/textures/starfield/starfield_rt.tga",
		"res/textures/starfield/starfield_lf.tga",
		"res/textures/starfield/starfield_up.tga",
		"res/textures/starfield/starfield_dn.tga",
		"res/textures/starfield/starfield_bk.tga",
		"res/textures/starfield/starfield_ft.tga"
	};

	Shader* testShader;
	Shader* cubemapShader;


	Model* model;
	Cubemap* skybox;

};