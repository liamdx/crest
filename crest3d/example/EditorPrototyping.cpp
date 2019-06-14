#include "EditorPrototyping.h"

EditorPrototyping::EditorPrototyping(GLFWwindow* _window)
{
	pm = std::shared_ptr<PhysicsManager>(new PhysicsManager());
	window = std::shared_ptr<GLFWwindow>(_window);
	scene = std::shared_ptr<Scene>(new Scene("debugScene", pm));
	input = std::shared_ptr<InputManager>(new InputManager(_window));

	cubemapShader = new Shader("res/shaders/cubemap.vert", "res/shaders/cubemap.frag");
	skybox = new Cubemap(faces);

	cameraRotation = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
	cameraPosition = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
	levelRotation = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
	levelPosition = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);


	Model m("res/models/cyborg/cyborg.obj");
	Model level("res/models/swamp/map_1.obj");

	cyborgEntity = scene->AddModelEntity(m);
	cyborgEntity->transform->addPosition(glm::vec3(0, 10, 0));
	for (int i = 0; i < cyborgEntity->children.size(); i++)
	{
		cyborgEntity->children.at(i)->AddComponent(new RigidbodyComponent(cyborgEntity->children.at(i)));
		cyborgEntity->children.at(i)->AddComponent(new CollisionShapeComponent(cyborgEntity->children.at(i)));
	}

	levelEntity = scene->AddModelEntity(level);
	levelEntity->transform->addPosition(glm::vec3(0, -10, 0));
	for (int i = 0; i < levelEntity->children.size(); i++)
	{
		levelEntity->children.at(i)->AddComponent(new RigidbodyComponent(levelEntity->children.at(i)));
		levelEntity->children.at(i)->AddComponent(new CollisionShapeComponent(levelEntity->children.at(i)));
	}

	cyborgRib = cyborgEntity->children.at(0)->GetComponent<RigidbodyComponent>();



}



void EditorPrototyping::initBehaviour()
{
	//temporarily initialise everything her
	cameraEntity = scene->AddCameraEntity();
	cameraEntity->AddComponent(new CameraControllerComponent(cameraEntity, input));
	std::shared_ptr<CameraControllerComponent> camController = cameraEntity->GetComponent<CameraControllerComponent>();
	camController->window = window;

	cam = cameraEntity->GetComponent<CameraComponent>();


	//rp3d::Transform initPhysicsT = rp3d::Transform::identity();
	//initPhysicsT.setPosition(rp3d::Vector3(0, -25, 0));
	//initPhysicsT.setOrientation(rp3d::Quaternion::identity());

	// e = std::shared_ptr<ProxyShape>(debugRib->addCollisionShape(new rp3d::BoxShape(Vector3(1000.0f, 2.0f, 1000.0f)), initPhysicsT, 5.0));

	scene->initBehaviour();
	//cyborgEntity->children.at(0)->GetComponent<RigidbodyComponent>()->createConvexMeshShape();

}

void EditorPrototyping::startBehaviour()
{
	for (int i = 0; i < levelEntity->children.size(); i++)
	{
		auto rib = levelEntity->children.at(i)->GetComponent<RigidbodyComponent>();
		rib->setMass(0.0f);
		//	rib->rib->setType(BodyType::KINEMATIC);
		//	auto ribTransform = rib->rib->getTransform();
	}


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
	if(input->GetKeyR())
	{
		cyborgRib->applyCentralForce(glm::vec3(0, 3000, 0));
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
	if(ImGui::BeginMenu(e->name.c_str()))
	{
		for (int i = 0; i < e->children.size(); i++)
		{
			ImGuiEntityDebug(e->children.at(i));
		}
		ImGui::EndMenu();
	}
}

void EditorPrototyping::uiBehaviour(float deltaTime)
{
	if (ImGui::Begin("Editor Prototyping"))
	{
		ImGui::Text("Bingpot");

		if(ImGui::TreeNode("Cyborg"))
		{
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


	}
	ImGui::End();

	if (ImGui::Begin("Hierarchy"))
	{
		ImGuiEntityDebug(scene->rootEntity);
	}
	ImGui::End();

	scene->uiBehaviour(deltaTime);
}


