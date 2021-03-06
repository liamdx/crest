#define _CRT_SECURE_NO_WARNINGS

#include "EditorPrototyping.h"

static void window_size_callback(GLFWwindow* window, int width, int height);

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
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	auto normal_font = io.Fonts->AddFontFromFileTTF("res/font/Rubik-Light.ttf", 13.0f);
	auto text_editor_font = io.Fonts->AddFontFromFileTTF("res/font/Cascadia.ttf", 16.0f);
	
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	
	//// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(engineManager->window, false);
	ImGui_ImplOpenGL3_Init("#version 440");
	
#define SOL_NO_EXCEPTIONS

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
	mainFB.initialise(CREST_WINDOW_WIDTH, CREST_WINDOW_HEIGHT, true);
	FrameBuffer depthFB;
	depthFB.initialise(CREST_WINDOW_WIDTH, CREST_WINDOW_HEIGHT, false);
	FrameBuffer volumetricFB;
	volumetricFB.initialise(CREST_WINDOW_WIDTH, CREST_WINDOW_HEIGHT, false);
	FrameBuffer blurFB;
	blurFB.initialise(CREST_WINDOW_WIDTH, CREST_WINDOW_HEIGHT, false);
	FrameBuffer finalFB;
	finalFB.initialise(CREST_WINDOW_WIDTH, CREST_WINDOW_HEIGHT, false);

	example.startBehaviour();

	float lastWindowWidth = 0.0;
	float lastWindowHeight = 0.0;

	int vsync = 1;
	
	glm::vec2 blurScale = glm::vec2(0.002);

	// TEXT EDITOR SAMPLE
	TextEditor editor;
	auto lang = TextEditor::LanguageDefinition::Lua();
	editor.SetLanguageDefinition(lang);

	// error markers
	TextEditor::ErrorMarkers markers;
	/*markers.insert(std::make_pair<int, std::string>(6, "Example error here:\nInclude file not found: \"TextEditor.h\""));
	markers.insert(std::make_pair<int, std::string>(41, "Another example error"));*/
	editor.SetErrorMarkers(markers);

	std::string currentLuaFile = "res/scripts/template.lua";

	// END OF TEXT EDITOR SAMPLE
	// FILE BROWSER SAMPLE

	ImGui::FileBrowser luaFileDialog;

	// (optional) set browser properties
	luaFileDialog.SetTitle("Open a Lua Script");
	luaFileDialog.SetTypeFilters({ ".lua"});

	// END OF FILE BROWSER SAMPLE
	glViewport(0, 0, CREST_WINDOW_WIDTH, CREST_WINDOW_HEIGHT);

	bool shouldRun = true;
	while (!glfwWindowShouldClose(engineManager->window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.05f, 0.05f, 0.05f, 1.0f);

		
		//Engine time
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		int eventCounter = 0;


		engineManager->update();

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
		glDepthFunc(GL_LESS);

		depthFB.initForDrawing();
		depthShader.use();
		renderQuad.Draw(depthShader, "screenTexture", mainFB.GetDepthTexture());
		depthFB.finishDrawing();
		
		finalFB.initForDrawing();
		fbShader.use();
		fbShader.setFloat("exposure", exposure);
		fbShader.setFloat("gamma", gamma);
		glActiveTexture(GL_TEXTURE1);

		glBindTexture(GL_TEXTURE_2D, blurFB.GetTexture());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		renderQuad.Draw(fbShader, "screenTexture", mainFB.GetTexture());
		finalFB.finishDrawing();

		

		glEnable(GL_DEPTH_TEST);

		// docking stuff
		static ImGuiID dockspaceID = 0;
		ImGui::SetNextWindowSize(ImVec2(CREST_WINDOW_WIDTH, CREST_WINDOW_HEIGHT));
		ImGui::SetNextWindowPos(ImVec2(0, 0));
		if (ImGui::Begin("Master Window", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBringToFrontOnFocus))
		{
			// Declare Central dockspace
			dockspaceID = ImGui::GetID("HUB_DockSpace");
			ImGui::DockSpace(dockspaceID, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None | ImGuiDockNodeFlags_PassthruCentralNode);
		}
		ImGui::End();
		
		ImGui::SetNextWindowDockID(dockspaceID, ImGuiCond_FirstUseEver);
		// this is so bleh and needs refactored.
		if (ImGui::Begin("Scene Window", NULL, ImVec2(0, 0)))
		{
			if (ImGui::IsWindowFocused()){
				ImGui::Text("Focussed on this window");
			}
			else{
				ImGui::Text("Not focussed on this window");
			}
			ImVec2 pos = ImGui::GetCursorScreenPos();
			float dWidth = ImGui::GetWindowWidth();
			float dHeight = ImGui::GetWindowHeight();
			if (dHeight != lastWindowHeight || dWidth != lastWindowWidth){
				mainFB.changeScreenSize(dWidth, dHeight);
				volumetricFB.changeScreenSize(dWidth, dHeight);
				blurFB.changeScreenSize(dWidth, dHeight);
				depthFB.changeScreenSize(dWidth, dHeight);
				finalFB.changeScreenSize(dWidth, dHeight);
				glViewport(0, 0, dWidth, dHeight);
				if (engineManager->scene != nullptr){
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
		if(ImGui::Begin("Graphics"))
		{
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			if (ImGui::Button("Enable VSYNC"))
			{
				if (vsync == 0)
				{
					glfwSwapInterval(0);
					vsync = 1;
				}
				else
				{
					glfwSwapInterval(1);
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

			if(ImGui::Button("Reload Assets"))
			{
				engineManager->scene->updateDrawables();
			}
			
			ImGui::Auto(blurScale, "Blue Scale");
		}
		ImGui::End();
		
		ImGui::SetNextWindowDockID(dockspaceID, ImGuiCond_FirstUseEver);
		Debug::DrawConsole();

		ImGui::PushFont(text_editor_font);

		// TEXT EDITOR SAMPLE RENDER
		auto cpos = editor.GetCursorPosition();
		ImGui::Begin("Text Editor Demo", nullptr, ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_MenuBar);
		ImGui::SetWindowSize(ImVec2(800, 600), ImGuiCond_FirstUseEver);
		if (ImGui::BeginMenuBar())
		{
			auto save_func = [&]() {auto textToSave = editor.GetText();
			/// save text....
			std::ofstream out(currentLuaFile.c_str());
			out << textToSave;
			out.close(); };
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Save"))
				{
					save_func();
					
				}
				if(ImGui::MenuItem("Open"))
				{
					luaFileDialog.Open();
				}
				ImGui::EndMenu();

			}
			if (ImGui::BeginMenu("Edit"))
			{
				bool ro = editor.IsReadOnly();
				if (ImGui::MenuItem("Read-only mode", nullptr, &ro))
					editor.SetReadOnly(ro);
				ImGui::Separator();

				if (ImGui::MenuItem("Undo", "ALT-Backspace", nullptr, !ro && editor.CanUndo()))
					editor.Undo();
				if (ImGui::MenuItem("Redo", "Ctrl-Y", nullptr, !ro && editor.CanRedo()))
					editor.Redo();

				ImGui::Separator();

				if (ImGui::MenuItem("Copy", "Ctrl-C", nullptr, editor.HasSelection()))
					editor.Copy();
				if (ImGui::MenuItem("Cut", "Ctrl-X", nullptr, !ro && editor.HasSelection()))
					editor.Cut();
				if (ImGui::MenuItem("Delete", "Del", nullptr, !ro && editor.HasSelection()))
					editor.Delete();
				if (ImGui::MenuItem("Paste", "Ctrl-V", nullptr, !ro && ImGui::GetClipboardText() != nullptr))
					editor.Paste();
				if (ImGui::MenuItem("Save", "Ctrl-S", nullptr, !ro && ImGui::GetClipboardText() != nullptr))
					save_func();

				ImGui::Separator();

				if (ImGui::MenuItem("Select all", nullptr, nullptr))
					editor.SetSelection(TextEditor::Coordinates(), TextEditor::Coordinates(editor.GetTotalLines(), 0));

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("View"))
			{
				if (ImGui::MenuItem("Dark palette"))
					editor.SetPalette(TextEditor::GetDarkPalette());
				if (ImGui::MenuItem("Light palette"))
					editor.SetPalette(TextEditor::GetLightPalette());
				if (ImGui::MenuItem("Retro blue palette"))
					editor.SetPalette(TextEditor::GetRetroBluePalette());
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

		luaFileDialog.Display();

		ImGui::Text("%6d/%-6d %6d lines  | %s | %s | %s | %s", cpos.mLine + 1, cpos.mColumn + 1, editor.GetTotalLines(),
			editor.IsOverwrite() ? "Ovr" : "Ins",
			editor.CanUndo() ? "*" : " ",
			editor.GetLanguageDefinition().mName.c_str(), currentLuaFile.c_str());

		editor.Render("TextEditor");
		ImGui::End();

		
		// TEXT EDITOR SAMPLE END


		if (luaFileDialog.HasSelected())
		{
			std::stringstream s;
			s << "Selected filename" << luaFileDialog.GetSelected().string() << std::endl;
			currentLuaFile = luaFileDialog.GetSelected().string();
			Debug::Log(s.str().c_str());
			{
				std::ifstream t(luaFileDialog.GetSelected().string());
				if (t.good())
				{
					std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
					editor.SetText(str);
				}
			}
			luaFileDialog.ClearSelected();
		}

		ImGui::PopFont();

		example.uiBehaviour(deltaTime);

		YSE::System().update();

		// Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwPollEvents();
		glfwSwapBuffers(engineManager->window);
	}

	glfwTerminate();
	YSE::System().close();	
}

