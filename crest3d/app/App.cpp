#define _CRT_SECURE_NO_WARNINGS
#include "EditorPrototyping.h"

// Debug example to minimise launching the engine code. 
int main()
{
	float deltaTime = 0.0;
	float lastFrame = 0.0;

	EngineManager* engineManager = new EngineManager();
	EditorPrototyping example(engineManager);
	engineManager->initialiseExample(&example);

	ImGui::CreateContext();

	ImGui_ImplGlfw_InitForOpenGL(engineManager->window, false);
	ImGui_ImplOpenGL3_Init("#version 440");
}