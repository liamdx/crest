#include "EditorPrototyping.h"

EditorPrototyping::EditorPrototyping(GLFWwindow* _window)
{
	pm = std::shared_ptr<PhysicsManager>(new PhysicsManager());
	am = std::make_shared<AssetManager>();
	window = std::shared_ptr<GLFWwindow>(_window);
	scene = std::shared_ptr<Scene>(new Scene("debugScene", pm, am));
	input = std::shared_ptr<InputManager>(new InputManager(_window));

	cubemapShader = new Shader("res/shaders/cubemap.vert", "res/shaders/cubemap.frag");
	skybox = new Cubemap(faces);

	auto m = am->loadModelAsset("res/models/cyborg/cyborg.obj");
	// auto level = am->loadModelAsset("res/models/swamp/map_1.obj");
	auto level = am->loadModelAsset("res/models/sponza/sponza.fbx");
	auto animatedModel = am->loadAnimatedModelAsset("res/models/stormtrooper/silly_dancing.fbx");

	cyborgEntity = scene->AddModelEntity(m->asset);
	cyborgEntity->transform->addPosition(glm::vec3(4, 0, 0));
	// cyborgEntity->transform->addScale(glm::vec3(3.0));
	/*for (int i = 0; i < cyborgEntity->children.size(); i++)
	{
		cyborgEntity->children.at(i)->AddComponent(new RigidbodyComponent(cyborgEntity->children.at(i)));
		cyborgEntity->children.at(i)->AddComponent(new CollisionShapeComponent(cyborgEntity->children.at(i)));
	}
*/
	levelEntity = scene->AddModelEntity(level->asset);
	levelEntity->transform->setScale(glm::vec3(0.03, 0.03, 0.03));
	levelEntity->transform->addPosition(glm::vec3(0, -10, 0));
	/*for (int i = 0; i < levelEntity->children.size(); i++)
	{
		levelEntity->children.at(i)->AddComponent(new RigidbodyComponent(levelEntity->children.at(i)));
		levelEntity->children.at(i)->AddComponent(new CollisionShapeComponent(levelEntity->children.at(i)));
	}*/

	animEntity = scene->AddAnimatedModelEntity(animatedModel->asset);
	animEntity->transform->addPosition(glm::vec3(-4.0, 0.0, 0.0));

	dirLight = scene->AddDirectionalLightEntity();
	dirLightComponent = dirLight->GetComponent<DirectionalLightComponent>();
}

void EditorPrototyping::initBehaviour()
{
	// some sample pointlights, please implement scene xml soon :)

	dirLightComponent->diffuse = glm::vec3(0.0);
	dirLightComponent->ambient = glm::vec3(0.05);

	auto pl1 = scene->AddPointLightEntity();
	pl1->transform->setPosition(glm::vec3(24.8, 3.7, 0.0));
	auto plc1 = pl1->GetComponent<PointLightComponent>();
	plc1->diffuse = glm::vec3(1.0, 0.0, 0.0);
	plc1->distance = 14.5;

	auto pl2 = scene->AddPointLightEntity();
	pl2->transform->setPosition(glm::vec3(7.5, 4.1, 0.0));
	auto plc2 = pl2->GetComponent<PointLightComponent>();
	plc2->diffuse = glm::vec3(0.0, 1.0, 1.0);
	plc2->distance = 14.5;

	auto pl3 = scene->AddPointLightEntity();
	pl3->transform->setPosition(glm::vec3(-1.7, 4.1, 0.0));
	auto plc3 = pl3->GetComponent<PointLightComponent>();
	plc3->diffuse = glm::vec3(1.0, 0.0, 1.0);
	plc3->distance = 14.5;

	auto pl4 = scene->AddPointLightEntity();
	pl4->transform->setPosition(glm::vec3(-15.7, 5.9, 0.0));
	auto plc4 = pl4->GetComponent<PointLightComponent>();
	plc4->diffuse = glm::vec3(1.0, 0.6, 0.1);
	plc4->distance = 12.5;

	auto pl5 = scene->AddPointLightEntity();
	pl5->transform->setPosition(glm::vec3(-35.7, 5.2, 0.0));
	auto plc5 = pl5->GetComponent<PointLightComponent>();
	plc5->diffuse = glm::vec3(0.0, 1.0, 0.0);
	plc5->distance = 8.5;

	auto pl6 = scene->AddPointLightEntity();
	pl6->transform->setPosition(glm::vec3(1.1, 4.3, 0.0));
	auto plc6 = pl6->GetComponent<PointLightComponent>();
	plc6->setDiffuse(glm::vec3(1.0f, 0.9f, 0.7f));
	plc6->setDistance(7.4f);

	// temporarily initialise everything her
	cameraEntity = scene->AddCameraEntity();
	cameraEntity->AddComponent(new CameraControllerComponent(cameraEntity, input));
	std::shared_ptr<CameraControllerComponent> camController = cameraEntity->GetComponent<CameraControllerComponent>();
	camController->window = window;
	cam = cameraEntity->GetComponent<CameraComponent>();
	scene->initBehaviour();
}

void EditorPrototyping::startBehaviour()
{
	//for (int i = 0; i < levelEntity->children.size(); i++)
	//{
	//	auto rib = levelEntity->children.at(i)->GetComponent<RigidbodyComponent>();
	//	rib->setMass(0.0f);
	//	// rib->rib->setType(BodyType::KINEMATIC);
	//	// auto ribTransform = rib->rib->getTransform();
	//}
	scene->startBehaviour();
	cubemapShader->use();
	cubemapShader->setMat4("projection", cam->GetProjectionMatrix());
}

void EditorPrototyping::earlyUpdateBehaviour(float deltaTime)
{
	scene->earlyUpdateBehaviour(deltaTime);
}

void EditorPrototyping::fixedUpdateBehaviour()
{
	scene->fixedUpdateBehaviour();
}

void EditorPrototyping::updateBehaviour(float deltaTime)
{
	scene->updateBehaviour(deltaTime);
}

void EditorPrototyping::renderBehaviour(float deltaTime)
{
	cubemapShader->use();
	cubemapShader->setMat4("view", glm::mat4(glm::mat3(cam->GetViewMatrix())));
	cubemapShader->setInt("cubemap", 0);

	skybox->Draw(*cubemapShader);

	scene->defaultShader->shader->use();

	scene->renderBehaviour(deltaTime);
}

void ImGuiEntityDebug(std::shared_ptr<Entity> e)
{
	if (ImGui::TreeNode(e->name.c_str()))
	{
		if (ImGui::TreeNode("Transform"))
		{
			ImGui::Auto(e->transform->localPosition, "Entity Position");
			ImGui::Auto(e->transform->localEulerAngles, "Entity Rotation");
			ImGui::Auto(e->transform->localScale, "Entity Scale");
			ImGui::TreePop();
		}

		if (e->GetComponent<MeshComponent>() != nullptr)
		{
			if (ImGui::TreeNode("MeshComponent"))
			{
				auto mc = e->GetComponent<MeshComponent>();
				ImGui::Auto(mc->shouldDraw, "Draw Mesh");
				ImGui::TreePop();
			}
		}

		if (e->GetComponent<PointLightComponent>() != nullptr)
		{
			if (ImGui::TreeNode("Point Light Component"))
			{
				auto pl = e->GetComponent<PointLightComponent>();
				ImGui::Auto(pl->diffuse, "Point Light Diffuse");
				ImGui::Auto(pl->distance, "Point Light Distance");
				ImGui::TreePop();
			}
		}

		if (e->GetComponent<DirectionalLightComponent>() != nullptr)
		{
			if (ImGui::TreeNode("Directional Light Component"))
			{
				auto dlc = e->GetComponent<DirectionalLightComponent>();
				ImGui::Auto(dlc->direction, "Direction");
				ImGui::Auto(dlc->diffuse, "Diffuse");
				ImGui::Auto(dlc->ambient, "Ambient");
				ImGui::Auto(dlc->specular, "Specular");
				ImGui::TreePop();
			}
		}

		if (e->GetComponent<RigidbodyComponent>() != nullptr)
		{
			if (ImGui::TreeNode("Rigidbody Component"))
			{
				auto rbc = e->GetComponent<RigidbodyComponent>();
				ImGui::Auto(rbc->mass, "Rigidbody Mass");
				ImGui::TreePop();
			}
		}

		if (ImGui::Button("Add Rigidbody to component"))
		{
			auto rib = std::make_shared<RigidbodyComponent>(e);
			e->AddComponent(rib);
			e->AddComponent(new CollisionShapeComponent(e));
			rib->init();
			rib->setMass(0.0f);
		}

		for (int i = 0; i < e->children.size(); i++)
		{
			ImGuiEntityDebug(e->children.at(i));
		}

		
		ImGui::TreePop();
	}
}

void EditorPrototyping::uiBehaviour(float deltaTime)
{
	if (ImGui::Begin("Editor Prototyping", NULL, ImGuiWindowFlags_NoMove));
	{
		if (ImGui::Button("Debug Draw"))
		{
			bool shouldDebugRender = pm->debugRender;
			pm->debugRender = !shouldDebugRender;
		}

		if (ImGui::Button("Reload Default Shader"))
		{
			scene->defaultShader = std::shared_ptr<ShaderComponent>(new ShaderComponent(NULL));
		}

		if (ImGui::Button("Reload PBR Shader"))
		{
			scene->defaultShader = std::shared_ptr<ShaderComponent>(new ShaderComponent(NULL, "res/shaders/pbr.vert", "res/shaders/pbr.frag"));
		}

		if (ImGui::Button("Reload Anim Shader"))
		{
			scene->defaultAnimShader = std::shared_ptr<ShaderComponent>(new ShaderComponent(NULL, "res/shaders/anim.vert", "res/shaders/anim.frag"));
		}

		if (ImGui::Button("Add Point Light"))
		{
			scene->AddPointLightEntity();
		}

		// load model
		{
			static char text[512] = "res/models/stormtrooper/silly_dancing.fbx";
			ImGui::InputText(" Model Path", text, IM_ARRAYSIZE(text));
			if (ImGui::Button("Load New Model Entity"))
			{
				auto _model = am->loadModelAsset(text);
				scene->AddModelEntity(_model->asset);
			}
		}
		// load animated model
		{
			static char text[512] = "res/models/stormtrooper/silly_dancing.fbx";
			ImGui::InputText("Animated Model Path", text, IM_ARRAYSIZE(text));
			if (ImGui::Button("Load New AnimatedModel Entity"))
			{
				auto _anim = am->loadAnimatedModelAsset(text);
				scene->AddAnimatedModelEntity(_anim->asset);
			}
		}

		if (ImGui::BeginChild("Hierarchy"))
		{
			ImGuiEntityDebug(scene->rootEntity);
		}
		ImGui::EndChild();
	}
	ImGui::End();

	scene->uiBehaviour(deltaTime);
}