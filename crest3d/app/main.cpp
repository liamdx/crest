#define _CRT_SECURE_NO_WARNINGS
#define SDL_MAIN_HANDLED
#include "SDL.h";
#include "EditorPrototyping.h"

float SCREEN_WIDTH = 1920.0;
float SCREEN_HEIGHT = 1080.0;

bool* b = new bool(true);

void resizeWindow(int windowWidth, int windowHeight);

void SetImGuiStyle()
{
	ImVec4* colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.44f, 0.44f, 0.44f, 1.00f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.11f, 0.11f, 0.11f, 0.94f);
	colors[ImGuiCol_ChildBg] = ImVec4(0.38f, 0.38f, 0.38f, 0.00f);
	colors[ImGuiCol_PopupBg] = ImVec4(0.28f, 0.28f, 0.28f, 0.94f);
	colors[ImGuiCol_Border] = ImVec4(1.00f, 0.72f, 0.72f, 0.50f);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.41f, 0.41f, 0.41f, 0.54f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.00f, 0.00f, 0.00f, 0.40f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.00f, 0.00f, 0.00f, 0.67f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
	colors[ImGuiCol_CheckMark] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.00f, 0.62f, 1.00f, 1.00f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.38f, 0.94f, 0.99f, 1.00f);
	colors[ImGuiCol_Button] = ImVec4(0.41f, 0.87f, 1.00f, 0.40f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.26f, 0.38f, 0.52f, 1.00f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
	colors[ImGuiCol_Header] = ImVec4(1.00f, 0.57f, 0.57f, 0.31f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.98f, 0.26f, 0.26f, 0.80f);
	colors[ImGuiCol_HeaderActive] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_Separator] = ImVec4(1.00f, 1.00f, 1.00f, 0.50f);
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(0.91f, 0.88f, 0.16f, 0.25f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.00f, 1.00f, 1.00f, 0.67f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(1.00f, 0.91f, 0.46f, 0.95f);
	colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.35f);
	colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
	colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);


}

int main() {

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
	io.Fonts->AddFontFromFileTTF("res/font/Rubik-Light.ttf", 13.0f);
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	// io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

	// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags)
	{
		style.WindowRounding = 0.0f;
		style.WindowPadding = ImVec2(2,2 );
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		style.PopupRounding = 1.0f;
		style.TabRounding = 1.0f;
		style.FrameRounding = 1.0f;
		style.ChildRounding = 5.0f;
		style.GrabRounding = 0.0f;
		style.ScrollbarRounding = 1.0f;
	}

	SetImGuiStyle();
	YSE::System().init();
	
	//// Setup Platform/Renderer bindings
	ImGui_ImplSDL2_InitForOpenGL(engineManager->window, engineManager->context);
	ImGui_ImplOpenGL3_Init("#version 440");
	
#define SOL_NO_EXCEPTIONS
	
	imnodes::Initialize();

	example.initBehaviour();

	// Framebuffer & POST FX shaders
	Shader depthShader("res/shaders/framebuffer.vert", "res/shaders/depthframebuffer.frag");
	Shader volumetricShader("res/shaders/framebuffer.vert", "res/shaders/volumetric.frag");
	Shader blurShader("res/shaders/framebuffer.vert", "res/shaders/blur.frag");
	Shader fbShader("res/shaders/framebuffer.vert", "res/shaders/framebuffer.frag");
	// Quad we use to render framebuffers
	screenQuad renderQuad;

	// Initialise buffers (uniform resolution for now)
	FrameBuffer mainFB;
	mainFB.initialise(SCREEN_WIDTH, SCREEN_HEIGHT, true);
	FrameBuffer depthFB;
	depthFB.initialise(SCREEN_WIDTH, SCREEN_HEIGHT, false);
	FrameBuffer volumetricFB;
	volumetricFB.initialise(SCREEN_WIDTH, SCREEN_HEIGHT, false);
	FrameBuffer blurFB;
	blurFB.initialise(SCREEN_WIDTH, SCREEN_HEIGHT, false);
	FrameBuffer finalFB;
	finalFB.initialise(SCREEN_WIDTH, SCREEN_HEIGHT, false);

	example.startBehaviour();

	float lastWindowWidth = 0.0;
	float lastWindowHeight = 0.0;

	int vsync = 1;
	SDL_GL_SetSwapInterval(vsync);
	SDL_Event windowEvent;
	
	glm::vec2 blurScale = glm::vec2(0.002);
	
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	bool shouldRun = true;
	while (shouldRun) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.05f, 0.05f, 0.05f, 1.0f);

		while(SDL_PollEvent(&windowEvent))
		{
			engineManager->input->processInput(windowEvent);
			
			if(windowEvent.window.event == SDL_WINDOWEVENT_CLOSE)
			{
				shouldRun = false;
			}
			if (windowEvent.window.event == SDL_WINDOWEVENT_RESIZED) {
				resizeWindow(windowEvent.window.data1, windowEvent.window.data2);
			}
			ImGui_ImplSDL2_ProcessEvent(&windowEvent);
		}
		//Engine time
		float currentFrame = SDL_GetPerformanceCounter();
		deltaTime = (double)((currentFrame - lastFrame) / (double)SDL_GetPerformanceFrequency());
		lastFrame = currentFrame;

		engineManager->input->update(deltaTime);
		
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame(engineManager->window);
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

		depthFB.initForDrawing();
		depthShader.use();
		renderQuad.Draw(depthShader, "screenTexture", mainFB.GetDepthTexture());
		depthFB.finishDrawing();

		/*volumetricFB.initForDrawing();
		volumetricShader.use();
		volumetricShader.setMat4("viewMatrix", engineManager->scene->sceneCamera->GetViewMatrix());
		volumetricShader.setVec3("lightDir", engineManager->scene->dirLightComponent->direction);
		renderQuad.Draw(volumetricShader, "screenTexture", depthFB.GetTexture());
		volumetricFB.finishDrawing();

		blurFB.initForDrawing();
		blurShader.use();
		blurShader.setVec2("scale", blurScale);
		renderQuad.Draw(blurShader, "screenTexture", volumetricFB.GetTexture());
		blurFB.finishDrawing();*/
		
		finalFB.initForDrawing();
		fbShader.use();
		fbShader.setFloat("exposure", exposure);
		fbShader.setFloat("gamma", gamma);
		glActiveTexture(GL_TEXTURE1);
		// fbShader.setInt("volumetrics", 1);
		glBindTexture(GL_TEXTURE_2D, blurFB.GetTexture());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		renderQuad.Draw(fbShader, "screenTexture", mainFB.GetTexture());
		finalFB.finishDrawing();

		

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
			if (ImGui::IsWindowFocused())
			{
				ImGui::Text("Focussed on this window");
			}
			else
			{
				ImGui::Text("Not focussed on this window");
			}
			ImVec2 pos = ImGui::GetCursorScreenPos();
			float dWidth = ImGui::GetWindowWidth();
			float dHeight = ImGui::GetWindowHeight();
			if (dHeight != lastWindowHeight || dWidth != lastWindowWidth)
			{
				mainFB.changeScreenSize(dWidth, dHeight);
				volumetricFB.changeScreenSize(dWidth, dHeight);
				blurFB.changeScreenSize(dWidth, dHeight);
				depthFB.changeScreenSize(dWidth, dHeight);
				finalFB.changeScreenSize(dWidth, dHeight);
				glViewport(0, 0, dWidth, dHeight);
				if (engineManager->scene != nullptr)
				{
					engineManager->scene->sceneCamera->updateProjection(75.0f, dWidth, dHeight);
				}
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
			if(ImGui::IsWindowFocused())
			{
				ImGui::Text("Focussed on this window");
			}
			else
			{
				ImGui::Text("Not focussed on this window");
			}
			
			ImGui::GetWindowDrawList()->AddImage(
				(void*)depthFB.GetTexture(), ImVec2(ImGui::GetCursorScreenPos()),
				ImVec2(ImGui::GetCursorScreenPos().x + ImGui::GetWindowWidth(), ImGui::GetCursorScreenPos().y + ImGui::GetWindowHeight()), ImVec2(0, 1), ImVec2(1, 0));
		}
		ImGui::End();

		ImGui::SetNextWindowDockID(dockspaceID, ImGuiCond_FirstUseEver);
		if (ImGui::Begin("Volumetrics Blurred Window", NULL, ImVec2(0, 0)))
		{
			if (ImGui::IsWindowFocused())
			{
				ImGui::Text("Focussed on this window");
			}
			else
			{
				ImGui::Text("Not focussed on this window");
			}

			ImGui::GetWindowDrawList()->AddImage(
				(void*)blurFB.GetTexture(), ImVec2(ImGui::GetCursorScreenPos()),
				ImVec2(ImGui::GetCursorScreenPos().x + ImGui::GetWindowWidth(), ImGui::GetCursorScreenPos().y + ImGui::GetWindowHeight()), ImVec2(0, 1), ImVec2(1, 0));
		}
		ImGui::End();
		
		ImGui::SetNextWindowDockID(dockspaceID, ImGuiCond_FirstUseEver);
		if (ImGui::Begin("Final Window", NULL, ImVec2(0, 0)))
		{
			if (ImGui::IsWindowFocused())
			{
				ImGui::Text("Focussed on this window");
			}
			else
			{
				ImGui::Text("Not focussed on this window");
			}
			ImGui::GetWindowDrawList()->AddImage(
				(void*)finalFB.GetTexture(), ImVec2(ImGui::GetCursorScreenPos()),
				ImVec2(ImGui::GetCursorScreenPos().x + ImGui::GetWindowWidth(), ImGui::GetCursorScreenPos().y + ImGui::GetWindowHeight()), ImVec2(0, 1), ImVec2(1, 0));
		}
		ImGui::End();

		ImGui::SetNextWindowDockID(dockspaceID, ImGuiCond_FirstUseEver);
		if(ImGui::Begin("Node Editor"))
		{
			imnodes::BeginNodeEditor();
			// node 1
			imnodes::BeginNode(1);

			imnodes::BeginInputAttribute(2);
			ImGui::Text("input");
			imnodes::EndAttribute();

			imnodes::BeginOutputAttribute(3);
			ImGui::Indent(40);
			ImGui::Text("output");
			imnodes::EndAttribute();

			imnodes::EndNode();

			// node 2
			imnodes::BeginNode(4);

			imnodes::BeginInputAttribute(5);
			ImGui::Text("input");
			imnodes::EndAttribute();

			imnodes::BeginOutputAttribute(6);
			ImGui::Indent(80);
			ImGui::Text("output");
			imnodes::EndAttribute();

			imnodes::EndNode();
			imnodes::EndNodeEditor();
		}
		ImGui::End();

		ImGui::SetNextWindowDockID(dockspaceID, ImGuiCond_FirstUseEver);

		if (ImGuiFileDialog::Instance()->FileDialog("File Browser"))
		{
		}

		ImGui::SetNextWindowDockID(dockspaceID, ImGuiCond_FirstUseEver);
		if(ImGui::Begin("Graphics"))
		{
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			if (ImGui::Button("Enable VSYNC"))
			{
				if (vsync == 0)
				{
					SDL_GL_SetSwapInterval(0);
					vsync = 1;
				}
				else
				{
					SDL_GL_SetSwapInterval(1);
					vsync = 0;
				}
			}
			ImGui::SliderFloat("Exposure", &exposure, 0, 10);
			ImGui::SliderFloat("Gamma", &gamma, 0, 10);
			if (ImGui::Button("Enable Debug Physics Drawing"))
			{
				engineManager->physicsManager->debugRender = !engineManager->physicsManager->debugRender;
			}

			if(engineManager->physicsManager->debugRender)
			{
				ImGui::Text("Rendering Debug Bullet Shapes");
			}
			else
			{
				ImGui::Text("Not Rendering Debug Bullet Shapes");
			}

			if(ImGui::Button("Reload Framebuffer Shader"))
			{
				fbShader = Shader("res/shaders/framebuffer.vert", "res/shaders/framebuffer.frag");
				volumetricShader = Shader("res/shaders/framebuffer.vert", "res/shaders/volumetric.frag");
				blurShader = Shader("res/shaders/framebuffer.vert", "res/shaders/blur.frag");
			}

			ImGui::Auto(blurScale, "Blue Scale");
		}
		ImGui::End();
		Debug::DrawConsole();
		
		example.uiBehaviour(deltaTime);

		YSE::System().update();
		// Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		
		//// ImGui_ImplSd

		//// Update and Render additional Platform Windows
		//// (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
		////  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
		//if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		//{
		//	GLFWwindow* backup_current_context = glfwGetCurrentContext();
		//	ImGui::UpdatePlatformWindows();
		//	ImGui::RenderPlatformWindowsDefault();
		//	glfwMakeContextCurrent(backup_current_context);
		//}
		SDL_GL_SwapWindow(engineManager->window);
	}

	YSE::System().close();
	imnodes::Shutdown();

	
	
}

void resizeWindow(int windowWidth, int windowHeight) {
	glViewport(0, 0, windowWidth, windowHeight);
	SCREEN_WIDTH = windowWidth;
	SCREEN_HEIGHT = windowHeight;
}
//void window_size_callback(GLFWwindow* window, int width, int height)
//{
//	SCREEN_WIDTH = width;
//	SCREEN_HEIGHT = height;
//	glViewport(0, 0, width, height);
//}
