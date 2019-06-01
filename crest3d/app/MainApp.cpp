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




	//debug mesh collider stuff
	Model colModel("res/models/cyborg/cyborg.obj");
	Mesh colMesh = colModel.meshes[0];

	int numFaces = colMesh.faces.size();
	std::vector<float> vertices = colMesh.getVertexValues();
	std::vector<int> indices = colMesh.getIndexValues();

	rp3d::TriangleVertexArray* triangleArray =
		new rp3d::TriangleVertexArray(colMesh.vertices.size(), &vertices[0], 3 * sizeof(float), colMesh.indices.size() / 3,
			&indices[0], 3 * sizeof(int),
			rp3d::TriangleVertexArray::VertexDataType::VERTEX_FLOAT_TYPE,
			rp3d::TriangleVertexArray::IndexDataType::INDEX_INTEGER_TYPE);

	rp3d::TriangleMesh triangleMesh;

	// Add the triangle vertex array to the triangle mesh 
	triangleMesh.addSubpart(triangleArray);

	// Create the concave mesh shape 
	ConcaveMeshShape* concaveMesh = new rp3d::ConcaveMeshShape(&triangleMesh);

	//rp3d::PolygonVertexArray::PolygonFace *polygonFaces = new rp3d::PolygonVertexArray::PolygonFace[numFaces];

	//rp3d::PolygonVertexArray::PolygonFace* face = polygonFaces;
	//for (int f = 0; f < numFaces; f++) {

	//	// First vertex of the face in the indices array 
	//	face->indexBase = f * 3;

	//	// Number of vertices in the face 
	//	face->nbVertices = 3;

	//	face++;
	//}

	//PolygonVertexArray* polygonVertexArray = new rp3d::PolygonVertexArray(colMesh.vertices.size(), 
	//	&(vertices[0]), 3 * sizeof(float),
	//	&(indices[0]), sizeof(int), numFaces, polygonFaces,
	//	rp3d::PolygonVertexArray::VertexDataType::VERTEX_FLOAT_TYPE,
	//	rp3d::PolygonVertexArray::IndexDataType::INDEX_INTEGER_TYPE);

	//PolyhedronMesh* polyhedronMesh = new rp3d::PolyhedronMesh(polygonVertexArray);

	//ConvexMeshShape* convexMeshShape = new rp3d::ConvexMeshShape(polyhedronMesh);


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