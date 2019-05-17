#define _CRT_SECURE_NO_WARNINGS

#include "Common.h"
#include "Model.h"
#include "Camera.h"
#include "InputManager.h"
#include "Cubemap.h"


// imgui stuff (will more than likely have to move);
#include "ext/imgui/imgui.h"
#include "ext/imgui/imgui_impl_glfw_gl3.h"
#include "ext/imgui/imgui_internal.h"
#include "ext/imgui/imconfig.h"

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
	window = glfwCreateWindow(1280.0, 720.0, "Crest", NULL, NULL);

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
	ImGui::StyleColorsDark();

	// YSE::System().init();

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
	Model someModel("res/models/cyborg/cyborg.obj");
	Cubemap skybox(faces);

	glm::vec3 modelPosition(0.0, 0.0, 4.0);
	glm::mat4 model, view, projection;

	projection = glm::perspectiveFov(90.0, 1920.0, 1080.0, 0.1, 500.0);

	model = glm::mat4(1.0);
	model = glm::translate(model, modelPosition);
	model = glm::scale(model, glm::vec3(2.0));

	//Enable depth
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glfwSwapInterval(0);

	//Mouse input handle

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	while (!glfwWindowShouldClose(window)) {

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Engine time
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		ImGui_ImplGlfwGL3_NewFrame();

		glEnable(GL_DEPTH_TEST);



		BoneCam.ProcessMouseMovement(input.xpos, input.ypos);
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
			BoneCam.ProcessMouseMovement(input.xpos, -input.ypos);
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

		if (ImGui::BeginMenu("Suck my entire yeet please"))
		{
			ImGui::Text("HELLO");

			ImGui::End();
		}

		//ui render	
		ImGui::Render();
		ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		/* Poll for and process events */
		glfwPollEvents();

	}

}