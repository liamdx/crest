#include "EditorPrototyping.h"

EditorPrototyping::EditorPrototyping(GLFWwindow* _window)
{
	pm = std::shared_ptr<PhysicsManager>(new PhysicsManager());
	am = std::make_shared<AssetManager>();
	window = std::shared_ptr<GLFWwindow>(_window);
	scene = std::shared_ptr<Scene>(new Scene("debugScene", pm));
	input = std::shared_ptr<InputManager>(new InputManager(_window));

	cubemapShader = new Shader("res/shaders/cubemap.vert", "res/shaders/cubemap.frag");
	skybox = new Cubemap(faces);

	cameraRotation = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
	cameraPosition = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
	levelRotation = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
	levelPosition = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);


	auto m = am->loadModelAsset("res/models/cyborg/cyborg.obj");
	auto level = am->loadModelAsset("res/models/swamp/map_1.obj");
	// auto level = am->loadModelAsset("res/models/sponza/sponza.obj");

	cyborgEntity = scene->AddModelEntity(m->asset);
	cyborgEntity->transform->addPosition(glm::vec3(0, 0, 0));
	// cyborgEntity->transform->addScale(glm::vec3(3.0));
	for (int i = 0; i < cyborgEntity->children.size(); i++)
	{
		cyborgEntity->children.at(i)->AddComponent(new RigidbodyComponent(cyborgEntity->children.at(i)));
		cyborgEntity->children.at(i)->AddComponent(new CollisionShapeComponent(cyborgEntity->children.at(i)));
	}

	levelEntity = scene->AddModelEntity(level->asset);
	// levelEntity->transform->setScale(glm::vec3(0.01, 0.01, 0.01));
	levelEntity->transform->addPosition(glm::vec3(0, -10, 0));
	/*for (int i = 0; i < levelEntity->children.size(); i++)
	{
		levelEntity->children.at(i)->AddComponent(new RigidbodyComponent(levelEntity->children.at(i)));
		levelEntity->children.at(i)->AddComponent(new CollisionShapeComponent(levelEntity->children.at(i)));
	}*/

	cyborgRib = cyborgEntity->children.at(0)->GetComponent<RigidbodyComponent>();

	dirLight = scene->AddDirectionalLightEntity();
	dirLightComponent = dirLight->GetComponent<DirectionalLightComponent>();

}



void EditorPrototyping::initBehaviour()
{
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
	if (input->GetKeyR())
	{
		cyborgRib->applyCentralForce(glm::vec3(0, 100, 0));
	}
}

void EditorPrototyping::renderBehaviour(float deltaTime)
{
	cubemapShader->use();
	cubemapShader->setMat4("view", glm::mat4(glm::mat3(cam->GetViewMatrix())));
	cubemapShader->setInt("cubemap", 0);

	skybox->Draw(*cubemapShader);

	scene->renderBehaviour(deltaTime);
}

void ImGuiEntityDebug(std::shared_ptr<Entity> e)
{
	if(ImGui::TreeNode(e->name.c_str()))
	{
		if(e->GetComponent<MeshComponent>() != nullptr)
		{
			auto mc = e->GetComponent<MeshComponent>();
			ImGui::Auto(mc->shouldDraw, "Draw Mesh");
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

		if (ImGui::Begin("Directional Light"))
		{
			ImGui::Auto(dirLightComponent->direction, "Direction");
			ImGui::Auto(dirLightComponent->diffuse, "Diffuse");
			ImGui::Auto(dirLightComponent->ambient, "Ambient");
			ImGui::Auto(dirLightComponent->specular, "Specular");
		}
		ImGui::End();

		if(ImGui::TreeNode("Cyborg"))
		{
			// ImGui::Auto(cyborgEntity->transform->position, "Cyborg Position");
			if (ImGui::Button("Change Mesh Shape to Cube"))
			{
				auto c = cyborgEntity->children.at(0)->GetComponent<CollisionShapeComponent>();
				c->createCubeShape();
				c->updateRigidbodyShape();
			}

			if (ImGui::Button("Change Mesh Shape to Sphere"))
			{
				auto c = cyborgEntity->children.at(0)->GetComponent<CollisionShapeComponent>();
				c->createSphereShape();
				c->updateRigidbodyShape();
			}

			if (ImGui::Button("Change Mesh Shape to Capsule"))
			{
				auto c = cyborgEntity->children.at(0)->GetComponent<CollisionShapeComponent>();
				c->createCapsuleShape();
				c->updateRigidbodyShape();
			}
			if (ImGui::Button("Change Mesh Shape to Convex Hull"))
			{
				auto c = cyborgEntity->children.at(0)->GetComponent<CollisionShapeComponent>();
				auto m = cyborgEntity->children.at(0)->GetComponent<MeshComponent>();
				c->createConvexHullShape(m);
				c->updateRigidbodyShape();
			}

			ImGui::TreePop();
		}

		if (ImGui::TreeNode("Level"))
		{
			ImGui::Auto(levelEntity->transform->localPosition, "Level Position");
			ImGui::Auto(levelEntity->transform->localEulerAngles, "Level Rotation");
			ImGui::Auto(levelEntity->transform->localScale, "Level Scale");
			if (ImGui::Button("Change Mesh Shape to Cube"))
			{
				for(int i = 0; i < levelEntity->children.size(); i++)
				{
					auto c = levelEntity->children.at(i)->GetComponent<CollisionShapeComponent>();
					c->createCubeShape();
					c->updateRigidbodyShape();
				}
				
			}

			if (ImGui::Button("Change Mesh Shape to Sphere"))
			{
				for (int i = 0; i < levelEntity->children.size(); i++)
				{
					auto c = levelEntity->children.at(i)->GetComponent<CollisionShapeComponent>();
					c->createSphereShape();
					c->updateRigidbodyShape();
				}
			}

			if (ImGui::Button("Change Mesh Shape to Capsule"))
			{
				for (int i = 0; i < levelEntity->children.size(); i++)
				{
					auto c = levelEntity->children.at(i)->GetComponent<CollisionShapeComponent>();
					c->createCapsuleShape();
					c->updateRigidbodyShape();
				}
			}
			if (ImGui::Button("Change Mesh Shape to Convex Hull"))
			{

				for (int i = 0; i < levelEntity->children.size(); i++)
				{
					auto c = levelEntity->children.at(i)->GetComponent<CollisionShapeComponent>();
					auto m = levelEntity->children.at(i)->GetComponent<MeshComponent>();
					c->createConvexHullShape(m);
					c->updateRigidbodyShape();
				}
			}

			ImGui::TreePop();
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


