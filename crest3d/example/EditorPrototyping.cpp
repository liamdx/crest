#include "EditorPrototyping.h"

EditorPrototyping::EditorPrototyping(EngineManager *em)
{
	engineManager = em;
	cubemapShader = new Shader("res/shaders/cubemap.vert", "res/shaders/cubemap.frag");
	skybox = new Cubemap(faces);

	auto m = engineManager->assetManager->loadModelAsset("res/models/cyborg/cyborg.obj");
	auto level = engineManager->assetManager->loadModelAsset("res/models/swamp/map_1.obj");
	//auto level = engineManager->assetManager->loadModelAsset("res/models/sponza/sponza.fbx");
	auto animatedModel = engineManager->assetManager->loadAnimatedModelAsset("res/models/stormtrooper/silly_dancing.fbx");

	Entity *someEntity = new Entity("N", engineManager);

	entities["cyborgEntity"] = engineManager->AddModelEntity(m->asset);
	entities["cyborgEntity"]->transform->addPosition(glm::vec3(4, 0, 0));
	// cyborgEntity->transform->addScale(glm::vec3(3.0));
	/*for (int i = 0; i < cyborgEntity->children.size(); i++)
	{
		cyborgEntity->children.at(i)->AddComponent(new RigidbodyComponent(cyborgEntity->children.at(i)));
		cyborgEntity->children.at(i)->AddComponent(new CollisionShapeComponent(cyborgEntity->children.at(i)));
	}
*/
	entities["levelEntity"] = engineManager->AddModelEntity(level->asset);
	entities["levelEntity"]->transform->setScale(glm::vec3(0.03, 0.03, 0.03));
	entities["levelEntity"]->transform->addPosition(glm::vec3(0, -10, 0));
	/*for (int i = 0; i < levelEntity->children.size(); i++)
	{
		levelEntity->children.at(i)->AddComponent(new RigidbodyComponent(levelEntity->children.at(i)));
		levelEntity->children.at(i)->AddComponent(new CollisionShapeComponent(levelEntity->children.at(i)));
	}*/

	entities["animEntity"] = engineManager->AddAnimatedModelEntity(animatedModel->asset);
	entities["animEntity"]->transform->addPosition(glm::vec3(-4.0, 0.0, 0.0));

	entities["dirLight"] = engineManager->AddDirectionalLightEntity();
	components["dirLightComponent"] = entities.at("dirLight")->GetComponent<DirectionalLightComponent>();
}

void EditorPrototyping::initBehaviour()
{
	// some sample pointlights, please implement scene xml soon :)
	auto dirLightComponent = std::dynamic_pointer_cast<DirectionalLightComponent>(components["dirLightComponent"]);
	dirLightComponent->diffuse = glm::vec3(0.0);
	dirLightComponent->ambient = glm::vec3(0.05);

	auto pl1 = engineManager->AddPointLightEntity();
	pl1->transform->setPosition(glm::vec3(24.8, 3.7, 0.0));
	auto plc1 = pl1->GetComponent<PointLightComponent>();
	plc1->diffuse = glm::vec3(1.0, 0.0, 0.0);
	plc1->distance = 14.5;

	auto pl2 = engineManager->AddPointLightEntity();
	pl2->transform->setPosition(glm::vec3(7.5, 4.1, 0.0));
	auto plc2 = pl2->GetComponent<PointLightComponent>();
	plc2->diffuse = glm::vec3(0.0, 1.0, 1.0);
	plc2->distance = 14.5;

	auto pl3 = engineManager->AddPointLightEntity();
	pl3->transform->setPosition(glm::vec3(-1.7, 4.1, 0.0));
	auto plc3 = pl3->GetComponent<PointLightComponent>();
	plc3->diffuse = glm::vec3(1.0, 0.0, 1.0);
	plc3->distance = 14.5;

	auto pl4 = engineManager->AddPointLightEntity();
	pl4->transform->setPosition(glm::vec3(-15.7, 5.9, 0.0));
	auto plc4 = pl4->GetComponent<PointLightComponent>();
	plc4->diffuse = glm::vec3(1.0, 0.6, 0.1);
	plc4->distance = 12.5;

	auto pl5 = engineManager->AddPointLightEntity();
	pl5->transform->setPosition(glm::vec3(-35.7, 5.2, 0.0));
	auto plc5 = pl5->GetComponent<PointLightComponent>();
	plc5->diffuse = glm::vec3(0.0, 1.0, 0.0);
	plc5->distance = 8.5;

	auto pl6 = engineManager->AddPointLightEntity();
	pl6->transform->setPosition(glm::vec3(1.1, 4.3, 0.0));
	auto plc6 = pl6->GetComponent<PointLightComponent>();
	plc6->setDiffuse(glm::vec3(1.0f, 0.9f, 0.7f));
	plc6->setDistance(7.4f);

	// temporarily initialise everything her
	entities["cameraEntity"] = engineManager->AddCameraEntity();
	entities["cameraEntity"]->AddComponent(new CameraControllerComponent(entities.at("cameraEntity"), engineManager->input));
	std::shared_ptr<CameraControllerComponent> camController = entities.at("cameraEntity")->GetComponent<CameraControllerComponent>();
	camController->window = engineManager->window;
	components["cam"] = entities.at("cameraEntity")->GetComponent<CameraComponent>();
	engineManager->scene->initBehaviour();
}

void EditorPrototyping::startBehaviour()
{
	

	std::shared_ptr<CameraComponent> cam = std::dynamic_pointer_cast<CameraComponent>(components["cam"]);

	engineManager->scene->startBehaviour();
	cubemapShader->use();
	cubemapShader->setMat4("projection", cam->GetProjectionMatrix());
}

void EditorPrototyping::earlyUpdateBehaviour(float deltaTime)
{
	engineManager->scene->earlyUpdateBehaviour(deltaTime);
}

void EditorPrototyping::fixedUpdateBehaviour()
{
	engineManager->scene->fixedUpdateBehaviour();
}

void EditorPrototyping::updateBehaviour(float deltaTime)
{
	engineManager->scene->updateBehaviour(deltaTime);
}

void EditorPrototyping::renderBehaviour(float deltaTime)
{
	std::shared_ptr<CameraComponent> cam = std::dynamic_pointer_cast<CameraComponent>(components["cam"]);
	cubemapShader->use();
	cubemapShader->setMat4("view", glm::mat4(glm::mat3(cam->GetViewMatrix())));
	cubemapShader->setInt("cubemap", 0);

	skybox->Draw(*cubemapShader);

	engineManager->shaderManager->defaultShader->shader->use();

	engineManager->scene->renderBehaviour(deltaTime);
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
	if (ImGui::Begin("Editor Prototyping", NULL, ImGuiWindowFlags_None))
		;
	{
		if (ImGui::Button("Debug Draw"))
		{
			bool shouldDebugRender = engineManager->physicsManager->debugRender;
			engineManager->physicsManager->debugRender = !shouldDebugRender;
		}

		if (ImGui::Button("Reload Default Shaders"))
		{
			engineManager->shaderManager->ReloadDefaultShaders();
		}

		if (ImGui::Button("Add Point Light"))
		{
			engineManager->AddPointLightEntity();
		}

		// load model
		{
			static char text[512] = "res/models/stormtrooper/silly_dancing.fbx";
			ImGui::InputText(" Model Path", text, IM_ARRAYSIZE(text));
			if (ImGui::Button("Load New Model Entity"))
			{
				auto _model = engineManager->assetManager->loadModelAsset(text);
				engineManager->AddModelEntity(_model->asset);
			}
		}
		// load animated model
		{
			static char text[512] = "res/models/stormtrooper/silly_dancing.fbx";
			ImGui::InputText("Animated Model Path", text, IM_ARRAYSIZE(text));
			if (ImGui::Button("Load New AnimatedModel Entity"))
			{
				auto _anim = engineManager->assetManager->loadAnimatedModelAsset(text);
				engineManager->AddAnimatedModelEntity(_anim->asset);
			}
		}

		if (ImGui::BeginChild("Hierarchy"))
		{
			ImGuiEntityDebug(engineManager->scene->rootEntity);
		}
		ImGui::EndChild();
	}
	ImGui::End();

	engineManager->scene->uiBehaviour(deltaTime);
}