#define _CRT_SECURE_NO_WARNINGS

#include "EditorPrototyping.h"

const float SCREEN_WIDTH = 1280.0;
const float SCREEN_HEIGHT = 720.0;

int main() {

	SDL_Init(SDL_INIT_EVERYTHING);

	float deltaTime = 0.0;
	float lastFrame = 0.0;
	float exposure = 2.22f;
	float gamma = 0.9f;

	SDL_Window* sdl_window = SDL_CreateWindow("SDL2 ImGui Renderer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
	SDL_GLContext mainContext = SDL_GL_CreateContext(sdl_window);
	SDL_Renderer* sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
	// ImGuiSDL::Initialize(sdl_renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 0);
	SDL_GL_SetSwapInterval(0);

	//DEBUG
	int success;
	char infoLog[512];
	//GL initialisation
	GLFWwindow * window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Crest", NULL, NULL);

	if (!window) {
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) {
		std::cout << "failed to initalise glew" << std::endl;
	}

	glfwSwapInterval(0);

	// ok to start doing stuff with the opengl window & context

	
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.Fonts->AddFontFromFileTTF("res/font/Rubik-Light.ttf", 14.0f);
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
	//io.ConfigViewportsNoAutoMerge = true;
	//io.ConfigViewportsNoTaskBarIcon = true;



	// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.2f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	SetImGuiStyle();

	//// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

	// ImGui_ImplSDL2_InitForOpenGL(sdl_window, mainContext);
	

	//Enable depth
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	YSE::System().init();

	// Example Here 
	EditorPrototyping example(window);
	example.initBehaviour();

	

	// Framebuffer shader 
	Shader depthShader("res/shaders/framebuffer.vert", "res/shaders/depthframebuffer.frag");
	Shader fbShader("res/shaders/framebuffer.vert", "res/shaders/framebuffer.frag");
	screenQuad renderQuad;

	// Main Frame buffer set up
	FrameBuffer mainFB;
	mainFB.initialise(SCREEN_WIDTH, SCREEN_HEIGHT);
	FrameBuffer depthFB;
	depthFB.initialise(SCREEN_WIDTH, SCREEN_HEIGHT);
	FrameBuffer finalFB;
	finalFB.initialise(SCREEN_WIDTH, SCREEN_HEIGHT);

	example.startBehaviour();
	//Mouse input handle
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	float lastWindowWidth = 0.0;
	float lastWindowHeight = 0.0;

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	while (1) {

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
		// perform scene pre-render stuff
		example.earlyUpdateBehaviour(deltaTime);
		example.updateBehaviour(deltaTime);
		// init framebuffer for drawing scene
		mainFB.initForDrawing();
		// draw everything in the scene
		example.renderBehaviour(deltaTime);
		mainFB.finishDrawing();


		glDisable(GL_DEPTH_TEST);

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

		if(ImGui::Begin("Scene Window", NULL, ImVec2(0,0)))
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
				glViewport(0, 0, dWidth, dHeight);
				example.getScene()->sceneCamera->updateProjection(75.0f, dWidth, dHeight);
			}

			ImGui::GetWindowDrawList()->AddImage(
				(void *)mainFB.GetTexture(), ImVec2(ImGui::GetCursorScreenPos()),
				ImVec2(ImGui::GetCursorScreenPos().x + ImGui::GetWindowWidth(), ImGui::GetCursorScreenPos().y + ImGui::GetWindowHeight()), ImVec2(0, 1), ImVec2(1, 0));

			lastWindowWidth = dWidth;
			lastWindowHeight = dHeight;

			
		}
		ImGui::End();

		if (ImGui::Begin("Depth Window", NULL, ImVec2(0, 0)))
		{
			ImGui::GetWindowDrawList()->AddImage(
				(void *)depthFB.GetTexture(), ImVec2(ImGui::GetCursorScreenPos()),
				ImVec2(ImGui::GetCursorScreenPos().x + ImGui::GetWindowWidth(), ImGui::GetCursorScreenPos().y + ImGui::GetWindowHeight()), ImVec2(0, 1), ImVec2(1, 0));

		}
		ImGui::End();

		if (ImGui::Begin("Final Window", NULL, ImVec2(0, 0)))
		{
			ImGui::GetWindowDrawList()->AddImage(
				(void *)finalFB.GetTexture(), ImVec2(ImGui::GetCursorScreenPos()),
				ImVec2(ImGui::GetCursorScreenPos().x + ImGui::GetWindowWidth(), ImGui::GetCursorScreenPos().y + ImGui::GetWindowHeight()), ImVec2(0, 1), ImVec2(1, 0));

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

		glfwSwapBuffers(window);
		/* Poll for and process events */
		glfwPollEvents();

		SDL_GL_SwapWindow(sdl_window);
	}

}