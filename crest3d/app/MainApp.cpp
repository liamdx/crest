#define _CRT_SECURE_NO_WARNINGS

// #include "SimpleExample.h"
#include "PhysicsExample.h"
//#include "SoundExample.h"

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

	glfwSwapInterval(0);

	//Enable depth
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	YSE::System().init();

	// Example Here 
	PhysicsExample example(window);
	example.initBehaviour();

	////bullet physics (exciting times)
	//btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
	//btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);
	//btBroadphaseInterface* overlappingPairCache = new btDbvtBroadphase();
	//btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver();
	//btDiscreteDynamicsWorld* dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);
	//dynamicsWorld->setGravity(btVector3(0.0, -10.0, 0.0));



	//btAlignedObjectArray<btCollisionShape*> collisionShapes;

	/////create a few basic rigid bodies

	////the ground is a cube of side 100 at position y = -56.
	////the sphere will hit it at y = -6, with center at -5
	//{
	//	btCollisionShape* groundShape = new btBoxShape(btVector3(btScalar(50.), btScalar(50.), btScalar(50.)));

	//	collisionShapes.push_back(groundShape);

	//	btTransform groundTransform;
	//	groundTransform.setIdentity();
	//	groundTransform.setOrigin(btVector3(0, -56, 0));

	//	btScalar mass(0.);

	//	//rigidbody is dynamic if and only if mass is non zero, otherwise static
	//	bool isDynamic = (mass != 0.f);

	//	btVector3 localInertia(0, 0, 0);
	//	if (isDynamic)
	//		groundShape->calculateLocalInertia(mass, localInertia);

	//	//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
	//	btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
	//	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, groundShape, localInertia);
	//	btRigidBody* body = new btRigidBody(rbInfo);

	//	//add the body to the dynamics world
	//	dynamicsWorld->addRigidBody(body);
	//}

	//{
	//	//create a dynamic rigidbody

	//	//btCollisionShape* colShape = new btBoxShape(btVector3(1,1,1));
	//	btCollisionShape* colShape = new btSphereShape(btScalar(1.));
	//	collisionShapes.push_back(colShape);

	//	/// Create Dynamic Objects
	//	btTransform startTransform;
	//	startTransform.setIdentity();

	//	btScalar mass(1.f);

	//	//rigidbody is dynamic if and only if mass is non zero, otherwise static
	//	bool isDynamic = (mass != 0.f);

	//	btVector3 localInertia(0, 0, 0);
	//	if (isDynamic)
	//		colShape->calculateLocalInertia(mass, localInertia);

	//	startTransform.setOrigin(btVector3(2, 10, 0));

	//	//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
	//	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
	//	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, colShape, localInertia);
	//	btRigidBody* body = new btRigidBody(rbInfo);

	//	dynamicsWorld->addRigidBody(body);

	//}







	// Main Frame buffer set up
	FrameBuffer mainFB;
	mainFB.initialise(SCREEN_WIDTH, SCREEN_HEIGHT);
	example.startBehaviour();
	//Mouse input handle
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	float lastWindowWidth = 0.0;
	float lastWindowHeight = 0.0;


	//float accumulator = 0.0f;
	//float fixedTimestep = 1.0f / 60.0f;
	//float factor = 0.0f;

	while (!glfwWindowShouldClose(window)) {

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(1.0, 0.0f, 0.0f, 1.0f);

		//Engine time
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// debug physics stuff
		//accumulator += deltaTime;
		//if (accumulator > 1.0f)
		//{
		//	accumulator = 0.0f;
		//}
		//while (accumulator >= fixedTimestep)
		//{
		//	// update dynamics world with constant timestep
		//	dynamicsWorld->stepSimulation(fixedTimestep, 10);
		//	// decrease the accumulated time
		//	accumulator -= fixedTimestep;
		//}

		//factor = accumulator / fixedTimestep;


		////print positions of all objects
		//for (int j = dynamicsWorld->getNumCollisionObjects() - 1; j >= 0; j--)
		//{
		//	btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[j];
		//	btRigidBody* body = btRigidBody::upcast(obj);
		//	btTransform trans;
		//	if (body && body->getMotionState())
		//	{
		//		body->getMotionState()->getWorldTransform(trans);
		//	}
		//	else
		//	{
		//		trans = obj->getWorldTransform();
		//	}
		//	printf("world pos object %d = %f,%f,%f\n", j, float(trans.getOrigin().getX()), float(trans.getOrigin().getY()), float(trans.getOrigin().getZ()));
		//}

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