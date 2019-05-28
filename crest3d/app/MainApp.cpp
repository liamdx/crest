#define _CRT_SECURE_NO_WARNINGS

// #include "SimpleExample.h"
#include "PhysicsExample.h"

const float SCREEN_WIDTH = 1280.0;
const float SCREEN_HEIGHT = 720.0;

int main() {

	std::cout << "Hello World!\n";

	float deltaTime = 0.0;
	float lastFrame = 0.0;

	//// physics
	///
	// PhysicsManager pm;
	//float timeStep = 1.0 / 60.0;
	//float accumulator = 0.0;
	//decimal factor;

	//rp3d::Vector3 gravity(0.0, -9.81, 0.0);
	//rp3d::DynamicsWorld world(gravity);


	//rp3d::Vector3 initPosition(0.0, 200.0, 0.0);
	//rp3d::Quaternion initRotation = rp3d::Quaternion::identity();
	//rp3d::Transform transform(initPosition, initRotation);

	//std::unique_ptr<rp3d::RigidBody> body(world.createRigidBody(transform));


	//const std::unique_ptr<rp3d::BoxShape> shape(new rp3d::BoxShape(Vector3(2,2,2)));
	//body->addCollisionShape(shape.get(), transform, 4.0);

	//rp3d::Transform prevTransform = body->getTransform();


	//initPosition = Vector3(0, -100, 0);
	//transform = Transform(initPosition, initRotation);
	//std::unique_ptr<rp3d::RigidBody> ground(world.createRigidBody(transform));
	//const std::unique_ptr<rp3d::BoxShape> groundShape(new rp3d::BoxShape(Vector3(200, 2, 200)));
	//ground->addCollisionShape(groundShape.get(), transform, 4.0);
	//ground->setType(BodyType::KINEMATIC);

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

	glfwSwapInterval(0);

	//Enable depth
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// YSE::System().init();

	// Example Here 
	PhysicsExample example(window);
	example.initBehaviour();

	// Main Frame buffer set up
	FrameBuffer mainFB;
	mainFB.initialise(SCREEN_WIDTH, SCREEN_HEIGHT);
	example.startBehaviour();
	//Mouse input handle
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	float lastWindowWidth = 0.0;
	float lastWindowHeight = 0.0;

	while (!glfwWindowShouldClose(window)) {

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(1.0, 0.0f, 0.0f, 1.0f);

		//Engine time
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		//accumulator += deltaTime;

		//while (accumulator >= timeStep) {

		//	// Update the Dynamics world with a constant time step 
		//	world.update(timeStep);

		//	// Decrease the accumulated time 
		//	accumulator -= timeStep;
		//}

		////Physics debug stuff
		////
		////
		//factor = accumulator / timeStep;
		//rp3d::Transform currTransform = body->getTransform();
		//rp3d::Transform interpolatedTransform = Transform::interpolateTransforms(prevTransform, currTransform, factor);
		//prevTransform = currTransform;

		//std::cout << "RP3d body position: " << interpolatedTransform.getPosition().to_string() << std::endl;
		
		ImGui_ImplGlfwGL3_NewFrame();

		//Render scene normally
		glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		glCullFace(GL_BACK);
		

		mainFB.initForDrawing();
		example.earlyUpdateBehaviour(deltaTime);

		example.updateBehaviour(deltaTime);

		example.renderBehaviour(deltaTime);
		mainFB.finishDrawing();

		if(ImGui::Begin("Scene Window"))
		{
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
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

			lastWindowWidth = dWidth;
			lastWindowHeight = dHeight;

			ImGui::End();
		}

		example.uiBehaviour(deltaTime);

		//ui render	
		ImGui::Render();
		ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

		/* Swap front and back buffers */
		glfwSwapBuffers(window);
		
		/* Poll for and process events */
		glfwPollEvents();
		

	}

}