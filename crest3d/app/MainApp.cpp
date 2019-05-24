#define _CRT_SECURE_NO_WARNINGS

#include "CrestCore.h"
#include "components/MeshComponent.h"
#include "SimpleExample.h"

const float SCREEN_WIDTH = 1280.0;
const float SCREEN_HEIGHT = 720.0;

int main() {

	std::cout << "Hello World!\n";

	float deltaTime = 0.0;
	float lastFrame = 0.0;

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

	// ok to start doing stuff with the opengl window & context

	ImGui::CreateContext();
	ImGui_ImplGlfwGL3_Init(window, true);

	SetImGuiStyle();
	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->AddFontFromFileTTF("res/font/Rubik-Light.ttf", 14.0f);


	//Enable depth
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glfwSwapInterval(0);

	// YSE::System().init();

	// Example Here 
	SimpleExample example(window);
	example.initBehaviour();

	// Main Frame buffer set up
	FrameBuffer mainFB;
	mainFB.initialise(SCREEN_WIDTH, SCREEN_HEIGHT);
	example.startBehaviour();
	//Mouse input handle
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	glfwSwapInterval(1);
	float lastWindowWidth = 0.0;
	float lastWindowHeight = 0.0;

	while (!glfwWindowShouldClose(window)) {

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(1.0, 0.0f, 0.0f, 1.0f);

		//Engine time
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		ImGui_ImplGlfwGL3_NewFrame();

		//Render scene normally
		glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		glCullFace(GL_BACK);
		

		mainFB.initForDrawing();
		example.earlyUpdateBehaviour(deltaTime);

		example.updateBehaviour(deltaTime);

		mainFB.finishDrawing();

		example.uiBehaviour(deltaTime);

		ImGui::Begin("Scene Window");


		ImVec2 pos = ImGui::GetCursorScreenPos();
		float dWidth = ImGui::GetWindowWidth();
		float dHeight = ImGui::GetWindowHeight();

		if (dHeight != lastWindowHeight || dWidth != lastWindowWidth)
		{
			mainFB.changeScreenSize(dWidth, dHeight);
		}

		ImGui::GetWindowDrawList()->AddImage(
			(void *)mainFB.GetTexture(), ImVec2(ImGui::GetCursorScreenPos()),
			ImVec2(ImGui::GetCursorScreenPos().x + ImGui::GetWindowWidth(), ImGui::GetCursorScreenPos().y + ImGui::GetWindowHeight()), ImVec2(0, 1), ImVec2(1, 0));
		
		ImGui::End();

		//  UI
		if (ImGui::BeginMenu("DebugMenu"))
		{
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

			ImGui::End();
		}


		//ui render	
		ImGui::Render();
		ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

		/* Swap front and back buffers */
		glfwSwapBuffers(window);
		
		/* Poll for and process events */
		glfwPollEvents();
		lastWindowWidth = dWidth;
		lastWindowHeight = dHeight;

	}

}