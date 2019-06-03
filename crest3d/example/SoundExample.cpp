#include "SoundExample.h"

SoundExample::SoundExample(GLFWwindow* _window)
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

	levelEntity = scene->AddModelEntity(level);
	levelEntity->transform->addPosition(glm::vec3(0, -30, 0));
	for (int i = 0; i < levelEntity->children.size(); i++)
	{
		levelEntity->children.at(i)->AddComponent(new RigidbodyComponent(levelEntity->children.at(i)));
	}

	cyborgEntity = scene->AddModelEntity(m);
	for (int i = 0; i < cyborgEntity->children.size(); i++)
	{
		cyborgEntity->children.at(i)->AddComponent(new RigidbodyComponent(cyborgEntity->children.at(i)));
	}

	//debugRib = std::shared_ptr<rp3d::RigidBody>(pm->addRigidbody());


}



void SoundExample::initBehaviour()
{
	//temporarily initialise everything her

	cameraEntity = scene->AddCameraEntity();
	cameraEntity->AddComponent(new CameraControllerComponent(cameraEntity, input));
	std::shared_ptr<CameraControllerComponent> camController = cameraEntity->GetComponent<CameraControllerComponent>();
	camController->window = window;

	cam = cameraEntity->GetComponent<CameraComponent>();

	//cyborgEntity->transform->addPosition(glm::vec3(0, 1, 0));
	//cameraEntity->transform->addPosition(glm::vec3(0, 4, 0));
	//levelEntity->transform->addPosition(glm::vec3(0, -3, 0));

	//rp3d::Transform initPhysicsT = rp3d::Transform::identity();
	//initPhysicsT.setPosition(rp3d::Vector3(0, -25, 0));
	//initPhysicsT.setOrientation(rp3d::Quaternion::identity());

	//e = std::shared_ptr<ProxyShape>(debugRib->addCollisionShape(new rp3d::BoxShape(Vector3(1000.0f, 2.0f, 1000.0f)), initPhysicsT, 5.0));

	scene->initBehaviour();
}

void SoundExample::startBehaviour()
{
	/*for (int i = 0; i < levelEntity->children.size(); i++)
	{
		auto rib = levelEntity->children.at(i)->GetComponent<RigidbodyComponent>();
		rib->rib->setType(BodyType::KINEMATIC);
		auto ribTransform = rib->rib->getTransform();
	}

	debugRib->setType(BodyType::KINEMATIC);*/

	scene->startBehaviour();
}

void SoundExample::earlyUpdateBehaviour(float deltaTime)
{
	scene->earlyUpdateBehaviour(deltaTime);
}

void SoundExample::fixedUpdateBehaviour()
{
	scene->fixedUpdateBehaviour();
}

void SoundExample::updateBehaviour(float deltaTime)
{
	scene->updateBehaviour(deltaTime);

	//cameraEntity->transform->setPosition(glm::vec3(cameraPosition.x, cameraPosition.y, cameraPosition.z));
	// cameraEntity->transform->setEulerAngles(glm::vec3(cameraRotation.x, cameraRotation.y, cameraRotation.z));
	/*levelEntity->transform->setPosition(glm::vec3(levelPosition.x, levelPosition.y, levelPosition.z));
	levelEntity->transform->setEulerAngles(glm::vec3(levelRotation.x, levelRotation.y, levelRotation.z));
	cyborgEntity->transform->setPosition(glm::vec3(cameraPosition.x, cameraPosition.y, cameraPosition.z));
	cyborgEntity->transform->setEulerAngles(glm::vec3(cameraRotation.x, cameraRotation.y, cameraRotation.z));*/

}

void SoundExample::renderBehaviour(float deltaTime)
{
	cubemapShader->use();
	cubemapShader->setMat4("projection", cam->GetProjectionMatrix());
	cubemapShader->setMat4("view", glm::mat4(glm::mat3(cam->GetViewMatrix())));
	cubemapShader->setInt("cubemap", 0);

	skybox->Draw(*cubemapShader);

	scene->renderBehaviour(deltaTime);
}

void SoundExample::uiBehaviour(float deltaTime)
{
	if (ImGui::Begin("Physics Example"))
	{
		ImGui::SliderFloat3("Level Position", &levelPosition.x, -100, 100);
		ImGui::SliderFloat3("Level Rotation", &levelRotation.x, -180, 180);
		ImGui::SliderFloat3("Cyborg Position", &cameraPosition.x, -100, 100);
		ImGui::SliderFloat3("Cyborg Rotation", &cameraRotation.x, -180, 180);


		if (ImGui::Button("Add Up Force"))
		{
			std::shared_ptr<RigidbodyComponent>r = cyborgEntity->children.at(0)->GetComponent<RigidbodyComponent>();
			//r->rib->applyForceToCenterOfMass(rp3d::Vector3(0, 1000, 0));
		}
		ImGui::End();
	}
	scene->uiBehaviour(deltaTime);
}


