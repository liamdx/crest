#define _CRT_SECURE_NO_WARNINGS

#include "EditorPrototyping.h"

float SCREEN_WIDTH = 1280.0;
float SCREEN_HEIGHT = 720.0;

void window_size_callback(GLFWwindow* window, int width, int height);

int main() {
	// SDL_Init(SDL_INIT_EVERYTHING);

	float deltaTime = 0.0;
	float lastFrame = 0.0;
	float exposure = 2.2f;
	float gamma = 0.912f;

	//DEBUG
	int success;
	char infoLog[512];


	EngineManager* engineManager = new EngineManager();
	EditorPrototyping example(engineManager);
	engineManager->initialiseExample(&example);

	
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.Fonts->AddFontFromFileTTF("res/font/Rubik-Light.ttf", 14.0f);
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	// io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

	// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.2f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	SetImGuiStyle();

	//// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(engineManager->window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
	imnodes::Initialize();

	example.initBehaviour();

	// Framebuffer shader
	Shader depthShader("res/shaders/framebuffer.vert", "res/shaders/depthframebuffer.frag");
	Shader fbShader("res/shaders/framebuffer.vert", "res/shaders/framebuffer.frag");
	screenQuad renderQuad;

	// Main Frame buffer set up
	FrameBuffer mainFB;
	mainFB.initialise(SCREEN_WIDTH, SCREEN_HEIGHT, true);
	FrameBuffer depthFB;
	depthFB.initialise(SCREEN_WIDTH, SCREEN_HEIGHT, false);
	FrameBuffer finalFB;
	finalFB.initialise(SCREEN_WIDTH, SCREEN_HEIGHT, false);

	example.startBehaviour();
	
	//Mouse input handle
	glfwSetInputMode(engineManager->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	glfwSetWindowSizeCallback(engineManager->window, window_size_callback);
	
	float lastWindowWidth = 0.0;
	float lastWindowHeight = 0.0;

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	while (!glfwWindowShouldClose(engineManager->window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.05f, 0.05f, 0.05f, 1.0f);

		//Engine time
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		// ImGui_ImplSDL2_NewFrame(sdl_window);
		ImGui::NewFrame();

		//Render scene normally
		glCullFace(GL_BACK);

		mainFB.initForDrawing();
		// perform scene pre-render stuff
		example.earlyUpdateBehaviour(deltaTime);
		// main game loop update
		example.updateBehaviour(deltaTime);
		// draw everything in the scene
		example.renderBehaviour(deltaTime);
		mainFB.finishDrawing();

		glDisable(GL_DEPTH_TEST);
		// framebuffers 
		finalFB.initForDrawing();
		fbShader.use();
		fbShader.setFloat("exposure", exposure);
		fbShader.setFloat("gamma", gamma);
		renderQuad.Draw(fbShader, "screenTexture", mainFB.GetTexture());

		finalFB.finishDrawing();

		depthFB.initForDrawing();
		depthShader.use();
		renderQuad.Draw(depthShader, "screenTexture", mainFB.GetDepthTexture());
		depthFB.finishDrawing();

		glEnable(GL_DEPTH_TEST);

		// docking stuff
		static ImGuiID dockspaceID = 0;
		ImGui::SetNextWindowSize(ImVec2(SCREEN_WIDTH, SCREEN_HEIGHT));
		ImGui::SetNextWindowPos(ImVec2(0, 0));
		if (ImGui::Begin("Master Window", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBringToFrontOnFocus))
		{
			// Declare Central dockspace
			dockspaceID = ImGui::GetID("HUB_DockSpace");
			ImGui::DockSpace(dockspaceID, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None | ImGuiDockNodeFlags_PassthruCentralNode/*|ImGuiDockNodeFlags_NoResize*/);
		}
		ImGui::End();
		
		ImGui::SetNextWindowDockID(dockspaceID, ImGuiCond_FirstUseEver);
		// this is so bleh and needs refactored.
		if (ImGui::Begin("Scene Window", NULL, ImVec2(0, 0)))
		{
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImVec2 pos = ImGui::GetCursorScreenPos();
			float dWidth = ImGui::GetWindowWidth();
			float dHeight = ImGui::GetWindowHeight();
			ImGui::SliderFloat("Exposure", &exposure, 0, 10);
			ImGui::SliderFloat("Gamma", &gamma, 0, 10);
			if (dHeight != lastWindowHeight || dWidth != lastWindowWidth)
			{
				mainFB.changeScreenSize(dWidth, dHeight);
				depthFB.changeScreenSize(dWidth, dHeight);
				finalFB.changeScreenSize(dWidth, dHeight);
				glViewport(0, 0, dWidth, dHeight);
				engineManager->scene->sceneCamera->updateProjection(75.0f, dWidth, dHeight);
			}

			ImGui::GetWindowDrawList()->AddImage(
				(void*)mainFB.GetTexture(), ImVec2(ImGui::GetCursorScreenPos()),
				ImVec2(ImGui::GetCursorScreenPos().x + ImGui::GetWindowWidth(), ImGui::GetCursorScreenPos().y + ImGui::GetWindowHeight()), ImVec2(0, 1), ImVec2(1, 0));

			lastWindowWidth = dWidth;
			lastWindowHeight = dHeight;
		}
		ImGui::End();
		
		ImGui::SetNextWindowDockID(dockspaceID, ImGuiCond_FirstUseEver);
		if (ImGui::Begin("Depth Window", NULL, ImVec2(0, 0)))
		{
			ImGui::GetWindowDrawList()->AddImage(
				(void*)depthFB.GetTexture(), ImVec2(ImGui::GetCursorScreenPos()),
				ImVec2(ImGui::GetCursorScreenPos().x + ImGui::GetWindowWidth(), ImGui::GetCursorScreenPos().y + ImGui::GetWindowHeight()), ImVec2(0, 1), ImVec2(1, 0));
		}
		ImGui::End();
		
		ImGui::SetNextWindowDockID(dockspaceID, ImGuiCond_FirstUseEver);
		if (ImGui::Begin("Final Window", NULL, ImVec2(0, 0)))
		{
			ImGui::GetWindowDrawList()->AddImage(
				(void*)finalFB.GetTexture(), ImVec2(ImGui::GetCursorScreenPos()),
				ImVec2(ImGui::GetCursorScreenPos().x + ImGui::GetWindowWidth(), ImGui::GetCursorScreenPos().y + ImGui::GetWindowHeight()), ImVec2(0, 1), ImVec2(1, 0));
		}
		ImGui::End();

		ImGui::SetNextWindowDockID(dockspaceID, ImGuiCond_FirstUseEver);
		if(ImGui::Begin("Node Editor"))
		{
			imnodes::BeginNodeEditor();
			imnodes::BeginNode(1);

			imnodes::BeginInputAttribute(2);
			ImGui::Text("input");
			imnodes::EndAttribute();

			imnodes::BeginOutputAttribute(3);
			ImGui::Indent(40);
			ImGui::Text("output");
			imnodes::EndAttribute();

			imnodes::EndNode();
			imnodes::EndNodeEditor();
		}
		ImGui::End();

		ImGui::SetNextWindowDockID(dockspaceID, ImGuiCond_FirstUseEver);
		if(ImGui::Begin("File Browser"))
		{
		}
		ImGui::End();

		example.uiBehaviour(deltaTime);

		// Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		// ImGuiSDL::Render(ImGui::GetDrawData());
		// ImGui_ImplSd

		// Update and Render additional Platform Windows
		// (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
		//  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}

		glfwSwapBuffers(engineManager->window);
		/* Poll for and process events */
		glfwPollEvents();

		// SDL_GL_SwapWindow(sdl_window);
	}

	imnodes::Shutdown();

	
	
}

void window_size_callback(GLFWwindow* window, int width, int height)
{
	SCREEN_WIDTH = width;
	SCREEN_HEIGHT = height;
	glViewport(0, 0, width, height);
}