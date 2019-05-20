#define _CRT_SECURE_NO_WARNINGS

#include "CrestCore.h"

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


	//Enable depth
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glfwSwapInterval(0);

	// YSE::System().init();

	// start


	// example def
	// my stuff
	InputManager input(window);
	//self explanatory
	Camera BoneCam(glm::vec3(0.0,0.0,0.0));
	// all images requried to make a subemap (star system image)
	std::vector<std::string> faces
	{
		"res/textures/starfield/starfield_rt.tga",
		"res/textures/starfield/starfield_lf.tga",
		"res/textures/starfield/starfield_up.tga",
		"res/textures/starfield/starfield_dn.tga",
		"res/textures/starfield/starfield_bk.tga",
		"res/textures/starfield/starfield_ft.tga"
	};

	Shader testShader("res/shaders/default.vert", "res/shaders/default.frag");
	Shader cubemapShader("res/shaders/cubemap.vert", "res/shaders/cubemap.frag");
	Shader fbShader("res/shaders/framebuffer.vert", "res/shaders/framebuffer.frag");

	Model someModel("res/models/cyborg/cyborg.obj");
	Cubemap skybox(faces);
	screenQuad renderQuad;

	glm::vec3 modelPosition(0.0, 0.0, 4.0);
	glm::mat4 model, view, projection;

	projection = glm::perspectiveFov(glm::radians(75.0), (double)SCREEN_WIDTH, (double)SCREEN_HEIGHT, 0.1, 250.0);


	model = glm::mat4(1.0);
	model = glm::translate(model, modelPosition);
	model = glm::scale(model, glm::vec3(2.0));

	Entity debugEntity("Peter Andre");
	// debugEntity.AddComponent(new DebugComponent());

	debugEntity.startBehaviour();

	// end of example def

	// frame buffer
	//Framebuffer
	//Frame buffer set up

	FrameBuffer mainFB;
	mainFB.initialise(SCREEN_WIDTH, SCREEN_HEIGHT);

	//Mouse input handle
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	float lastWindowWidth = 0.0;
	float lastWindowHeight = 0.0;
	while (!glfwWindowShouldClose(window)) {

		// early update
		// clear everything
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
		
		debugEntity.transform->position;

		mainFB.initForDrawing();

		debugEntity.earlyUpdateBehaviour();

		// example update()

		debugEntity.updateBehaviour();

		BoneCam.ProcessMouseMovement(input.xpos, -input.ypos, deltaTime);

		if (input.GetKeyW())
		{
			BoneCam.ProcessKeyboard(FORWARD, deltaTime);

		}

		if (input.GetKeyS())
		{
			BoneCam.ProcessKeyboard(BACKWARD, deltaTime);
		}

		if (input.GetKeyA())
		{
			BoneCam.ProcessKeyboard(LEFT, deltaTime);
		}

		if (input.GetKeyD())
		{
			BoneCam.ProcessKeyboard(RIGHT, deltaTime);
		}

		if (input.GetRightClick())
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			BoneCam.canMove = true;
			input.GetMouseMovement();
			BoneCam.ProcessMouseMovement(input.xpos, -input.ypos, deltaTime);
		}
		else
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}


		view = BoneCam.GetViewMatrix();


		//skybox shader
		cubemapShader.use();
		cubemapShader.setMat4("projection", projection);
		cubemapShader.setMat4("view", view);
		cubemapShader.setInt("cubemap", 0);
		skybox.Draw(cubemapShader, view, projection);

		//  test shader
		testShader.use();

		testShader.setMat4("model", model);
		testShader.setMat4("view", view);
		testShader.setMat4("projection", projection);

		someModel.Draw(testShader);

		// end of example update()

		mainFB.finishDrawing();

		


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
		if (ImGui::BeginMenu("Suck my entire yeet please"))
		{
			ImGui::Text("HELLO");

			ImGui::End();
		}

		// end of exammple ui

		debugEntity.uiBehaviour();

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