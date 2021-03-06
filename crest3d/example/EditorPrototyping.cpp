#include "EditorPrototyping.h"

// horrible and needs to go :/ 

EditorPrototyping::EditorPrototyping(EngineManager* em)
{

	engineManager = em;
	cubemapShader = new Shader("res/shaders/cubemap.vert", "res/shaders/cubemap.frag");
	skybox = new Cubemap(faces);

	clapTimer = 0.0f;

	auto m = engineManager->assetManager->loadModelAsset("res/models/cyborg/cyborg.obj");
	auto level = engineManager->assetManager->loadModelAsset("res/models/sponza/sponza.fbx");
	auto animatedModel = engineManager->assetManager->loadAnimatedModelAsset("res/models/stormtrooper/silly_dancing.fbx");
	auto barrelModel = engineManager->assetManager->loadModelAsset("res/models/barrel/barrel.obj");
	barrelAssetID = barrelModel->assetID;

	entities["cyborgEntity"] = engineManager->AddModelEntity(m->asset);
	entities["cyborgEntity"]->transform->position = (glm::vec3(0, 8, 0));
	entities["cyborgEntity"]->AddComponent(new ParticleSystemComponent(entities["cyborgEntity"]));

	entities["levelEntity"] = engineManager->AddModelEntity(level->asset);
	entities["levelEntity"]->transform->position = (glm::vec3(0.03, 0.03, 0.03));
	entities["levelEntity"]->transform->position += (glm::vec3(0, 0, 0));
	entities["levelEntity"]->transform->scale = glm::vec3(0.07, 0.07, 0.07);


	int res = 4;
	int counter = 0;
	for (int x = 0; x < res; x++)
	{
		for (int y = 0; y < res; y++)
		{
			for (int z = 0; z < res; z++)
			{
				std::string s = "RigidbodyEntity" + std::to_string(counter);
				ribEntityNames.emplace_back(s);
				counter += 1;
				entities[s] = engineManager->AddModelEntity(barrelModel->asset);
				entities[s]->transform->position = (glm::vec3(x * 2, 20 + z * 2, y * 2));
				entities[s]->transform->scale = glm::vec3(0.25, 0.25, 0.25);
				entities[s]->AddComponent(new RigidbodyComponent(entities[s]));
			}
		}
	}
	counter = 0;
	for (int x = 0; x < res; x++)
	{
		for (int y = 0; y < res; y++)
		{
			std::string s = "AnimEntity" + std::to_string(counter);
			counter += 1;
			entities[s] = engineManager->AddAnimatedModelEntity(animatedModel->asset);
			entities[s]->state = UpdateState::halfRate;
			entities[s]->transform->position = (glm::vec3(x * 2, 0, y * 2));
			entities[s]->transform->scale = glm::vec3(1, 1, 1);
		}
	}
	entities["floorEntity"] = engineManager->AddEntity();
	entities["floorEntity"]->AddComponent(new RigidbodyComponent(entities["floorEntity"]));
	components["floorRib"] = entities["floorEntity"]->GetComponent<RigidbodyComponent>();
	auto floorRib = GetUsableComponent<RigidbodyComponent>("floorRib");
	entities["floorEntity"]->transform->position = glm::vec3(0, -10, 0);
	floorRib->cubeDimensions = glm::vec3(100000, 0.2, 100000);
	floorRib->SetCubeShape();
	floorRib->setMass(0.0f);


	// temporarily initialise everything her
	entities["cameraEntity"] = engineManager->AddCameraEntity();
	entities["cameraEntity"]->AddComponent(new CameraControllerComponent(entities.at("cameraEntity"), engineManager->input));

	components["cam"] = entities.at("cameraEntity")->GetComponent<CameraComponent>();

	entities["dirLight"] = engineManager->AddDirectionalLightEntity();
	components["dirLightComponent"] = entities.at("dirLight")->GetComponent<DirectionalLightComponent>();
}

void EditorPrototyping::DeleteRigidbodies()
{
	for (int i = 0; i < ribEntityNames.size(); i++)
	{
		engineManager->DeleteEntity(entities[ribEntityNames.at(i)]->GetID());
	}
	ribEntityNames.clear();
}

void EditorPrototyping::AddRigidbodies()
{
	auto barrelModel = engineManager->assetManager->getModelAssetID(barrelAssetID);
	int res = 6;
	int counter = ribEntityNames.size();
	for (int x = 0; x < res; x++)
	{
		for (int y = 0; y < res; y++)
		{
			for (int z = 0; z < res; z++)
			{
				std::string s = "RigidbodyEntity" + std::to_string(counter);
				ribEntityNames.emplace_back(s);
				counter += 1;
				entities[s] = engineManager->AddModelEntity(barrelModel->asset);
				entities[s]->transform->position = (glm::vec3(x * 2, 20 + z * 2, y * 2));
				entities[s]->transform->scale = glm::vec3(0.25, 0.25, 0.25);
				entities[s]->AddComponent(new RigidbodyComponent(entities[s]));
			}
		}
	}
	std::stringstream message;
	message << "Number of rigidbodies: " << ribEntityNames.size();
	Debug::Warn(message.str().c_str());
}

void EditorPrototyping::RigidbodyTest()
{
	for (int i = 0; i < 10; i++)
	{
		std::stringstream s;
		s << "Iteration" + std::to_string(i) << "\n";
		std::cout << s.str();
		DeleteRigidbodies();
		AddRigidbodies();
	}
}


void EditorPrototyping::initBehaviour()
{
	if (engineManager->scene != nullptr)
	{
		// some sample pointlights, please implement scene xml soon :)
		auto dirLightComponent = std::dynamic_pointer_cast<DirectionalLightComponent>(components["dirLightComponent"]);
		dirLightComponent->diffuse = glm::vec3(0.0);
		dirLightComponent->ambient = glm::vec3(0.0);

		auto pl1 = engineManager->AddPointLightEntity();
		pl1->transform->position = glm::vec3(24.8, 3.7, 0.0);
		auto plc1 = pl1->GetComponent<PointLightComponent>();
		plc1->diffuse = glm::vec3(1.0, 0.0, 0.0);
		plc1->distance = 14.5;

		auto pl2 = engineManager->AddPointLightEntity();
		pl2->transform->position = (glm::vec3(7.5, 4.1, 0.0));
		auto plc2 = pl2->GetComponent<PointLightComponent>();
		plc2->diffuse = glm::vec3(0.0, 1.0, 1.0);
		plc2->distance = 14.5;

		auto pl3 = engineManager->AddPointLightEntity();
		pl3->transform->position = (glm::vec3(-1.7, 4.1, 0.0));
		auto plc3 = pl3->GetComponent<PointLightComponent>();
		plc3->diffuse = glm::vec3(1.0, 0.0, 1.0);
		plc3->distance = 14.5;

		auto pl4 = engineManager->AddPointLightEntity();
		pl4->transform->position = (glm::vec3(-15.7, 5.9, 0.0));
		auto plc4 = pl4->GetComponent<PointLightComponent>();
		plc4->diffuse = glm::vec3(1.0, 0.6, 0.1);
		plc4->distance = 12.5;

		auto pl5 = engineManager->AddPointLightEntity();
		pl5->transform->position = (glm::vec3(-35.7, 5.2, 0.0));
		auto plc5 = pl5->GetComponent<PointLightComponent>();
		plc5->diffuse = glm::vec3(0.0, 1.0, 0.0);
		plc5->distance = 8.5;

		auto pl6 = engineManager->AddPointLightEntity();
		pl6->transform->position = (glm::vec3(1.1, 4.3, 0.0));
		auto plc6 = pl6->GetComponent<PointLightComponent>();
		plc6->setDiffuse(glm::vec3(1.0f, 0.9f, 0.7f));
		plc6->setDistance(7.4f);


		engineManager->scene->initBehaviour();
	}
}

void EditorPrototyping::startBehaviour()
{
	if (engineManager->scene != nullptr)
	{

		// std::shared_ptr<CameraComponent> cam = std::dynamic_pointer_cast<CameraComponent>(components["cam"]);
		std::shared_ptr<DirectionalLightComponent> dir = GetUsableComponent < DirectionalLightComponent>("dirLightComponent");
		std::shared_ptr<CameraComponent> cam = GetUsableComponent<CameraComponent>("cam");

		engineManager->scene->startBehaviour();
		cubemapShader->use();
		cubemapShader->setMat4("projection", cam->GetProjectionMatrix());
	}

	engineManager->scene->updateDrawables();
}

void EditorPrototyping::earlyUpdateBehaviour(float deltaTime)
{
	if (engineManager->scene != nullptr)
	{
		engineManager->scene->earlyUpdateBehaviour(deltaTime);
	}
}

void EditorPrototyping::fixedUpdateBehaviour()
{
	if (engineManager->scene != nullptr)
	{
		engineManager->scene->fixedUpdateBehaviour();
	}
}

void EditorPrototyping::updateBehaviour(float deltaTime)
{
	if (engineManager->scene != nullptr)
	{
		engineManager->scene->updateBehaviour(deltaTime);

		/*clapTimer += deltaTime;

		if(clapTimer >= 2.0f)
		{
			auto audio_component = GetUsableComponent<AudioComponent>("someAudioComponent");
			audio_component->Play();
			clapTimer = 0.0f;
		}*/
	}
}

void EditorPrototyping::renderBehaviour(float deltaTime)
{
	if (engineManager->scene != nullptr)
	{
		std::shared_ptr<CameraComponent> cam = std::dynamic_pointer_cast<CameraComponent>(components["cam"]);
		cubemapShader->use();
		cubemapShader->setMat4("view", glm::mat4(glm::mat3(cam->GetViewMatrix())));
		cubemapShader->setMat4("projection", cam->GetProjectionMatrix());
		cubemapShader->setInt("cubemap", 0);

		skybox->Draw(*cubemapShader);

		engineManager->shaderManager->defaultShader->shader->use();


		engineManager->scene->renderBehaviour(deltaTime);
	}

}

void EditorPrototyping::ImGuiEntityDebug(std::shared_ptr<Entity> e)
{
	if (ImGui::TreeNode(e->name.c_str()))
	{
		if (e->state == UpdateState::fullRate)
		{
			ImGui::Text("Full rate Update");
		}
		if (e->state == UpdateState::halfRate)
		{
			ImGui::Text("Half rate Update");
		}
		if (e->state == UpdateState::quarterRate)
		{
			ImGui::Text("Quarter rate Update");
		}
		if (ImGui::TreeNode("Transform"))
		{
			ImGui::Auto(e->transform->position, "Entity Position");
			ImGui::Auto(e->transform->eulerAngles, "Entity Rotation");
			ImGui::Auto(e->transform->scale, "Entity Scale");
			ImGui::Auto(e->transform->localPosition, "Entity Local Position");
			ImGui::Auto(e->transform->localEulerAngles, "Entity Local Rotation");
			ImGui::Auto(e->transform->localScale, "Entity Local Scale");
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
				ImGui::Auto(forceAmount, "Force Amount");
				ImGui::Auto(rbc->centerOffset, "Collision Shape Offset");
				ImGui::Auto(rbc->shouldLog, "Should log debug information");
				ImGui::Auto(rbc->cubeDimensions, "Cube Dimensions");
				ImGui::Auto(rbc->capsuleRadius, "Capsule Radius");
				ImGui::Auto(rbc->capsuleHeight, "Capsule Height");
				ImGui::Auto(rbc->sphereRadius, "Sphere Radius");
				ImGui::Auto(rbc->collisionScale, "Collision Scale");

				if (ImGui::Button("Change to box shape"))
				{
					rbc->SetCubeShape();
				}
				if (ImGui::Button("Change to sphere shape"))
				{
					rbc->SetSphereShape();
				}
				if (ImGui::Button("Change to capsule shape"))
				{
					rbc->SetCapsuleShape();
				}
				if (ImGui::Button("Add Force"))
				{
					rbc->applyCentralForce(glm::vec3(0, forceAmount, 0));
				}
				ImGui::TreePop();
			}
		}

		if (e->GetComponent<CameraControllerComponent>() != nullptr)
		{
			if (ImGui::TreeNode("CameraControllerComponent"))
			{
				auto controller = e->GetComponent<CameraControllerComponent>();
				ImGui::Auto(controller->initMoveSpeed, "Init Cam speed");
				ImGui::Auto(controller->movementSpeed, "Cam speed");
				ImGui::Auto(controller->useContoller, "Use Controller");
				ImGui::TreePop();
			}
			
		}

		if (e->GetComponent<ParticleSystemComponent>())
		{
			if (ImGui::TreeNode("Particle System Component"))
			{
				ImGui::TreePop();
			}
		}


		if (ImGui::Button("Add Rigidbody to component"))
		{
			e->AddComponent(new RigidbodyComponent(e));
		}

		if (ImGui::Button("Delete Entity"))
		{
			engineManager->DeleteEntity(e->GetID());
		}

		if (ImGui::Button("Full Rate"))
		{
			e->state = UpdateState::fullRate;
		}

		if (ImGui::Button("Half Rate"))
		{
			e->state = UpdateState::halfRate;
		}

		if (ImGui::Button("Quarter Rate"))
		{
			e->state = UpdateState::quarterRate;
		}
		if (ImGui::Button("Frozen"))
		{
			e->state = UpdateState::frozen;
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

		if (ImGui::Button("Add Entity"))
		{
			engineManager->AddEntity();
		}

		if (ImGui::Button("Write scene to file"))
		{
			Serializer s;
			s.SerializeScene(engineManager->scene);
		}

		if (ImGui::Button("Open scene from file"))
		{
			Serializer s;
			s.DeserializeScene("res/test/debug.xml", engineManager);
		}

		if (ImGui::Button("Reset Scene"))
		{
			engineManager->ResetScene();
		}

		// load model
		{
			static char text[512] = "res/models/stormtrooper/silly_dancing.fbx";
			ImGui::InputText(" Model Path", text, IM_ARRAYSIZE(text));
			if (ImGui::Button("Load New Model Entity"))
			{
				auto _model = engineManager->assetManager->loadModelAsset(text);
				if (engineManager->scene != nullptr)
				{
					engineManager->AddModelEntity(_model->asset);
				}
			}
		}
		// load animated model
		{
			static char text[512] = "res/models/stormtrooper/silly_dancing.fbx";
			ImGui::InputText("Animated Model Path", text, IM_ARRAYSIZE(text));
			if (ImGui::Button("Load New AnimatedModel Entity"))
			{
				auto _anim = engineManager->assetManager->loadAnimatedModelAsset(text);
				if (engineManager->scene != nullptr)
				{
					engineManager->AddAnimatedModelEntity(_anim->asset);
				}
			}
		}

		if (ImGui::Button("Add Default Rigidbodies"))
		{
			AddRigidbodies();
		}

		if (ImGui::Button("Delete All Default Rigidbodies"))
		{
			DeleteRigidbodies();
		}

		if (ImGui::Button("Rigidbody Test"))
		{
			RigidbodyTest();
		}
		if (engineManager->scene != nullptr)
		{
			if (ImGui::BeginChild("Hierarchy"))
			{
				ImGuiEntityDebug(engineManager->scene->rootEntity);
			}
			ImGui::EndChild();
		}


	}
	ImGui::End();
	if (engineManager->scene != nullptr)
	{
		engineManager->scene->uiBehaviour(deltaTime);
	}
}