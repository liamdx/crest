#include "PhysicsExample.h"

PhysicsExample::PhysicsExample(GLFWwindow* _window)
{
	pm = std::shared_ptr<PhysicsManager>(new PhysicsManager());
	scene = std::unique_ptr<Scene>(new Scene("debugScene",pm));
}


void PhysicsExample::initBehaviour()
{
	//temporarily initialise everything here

	Model m("res/models/cyborg/cyborg.obj");
	Model level("res/models/swamp/map_1.obj");
	cyborgEntity = scene->AddModelEntity(m);
	levelEntity = scene->AddModelEntity(level);
	cameraEntity = scene->AddCameraEntity();





	scene->initBehaviour();
}

void PhysicsExample::startBehaviour()
{
	scene->startBehaviour();
}

void PhysicsExample::earlyUpdateBehaviour(float deltaTime)
{
	pm->update(deltaTime);
	scene->earlyUpdateBehaviour(deltaTime);
}

void PhysicsExample::fixedUpdateBehaviour()
{
	scene->fixedUpdateBehaviour();
}

void PhysicsExample::updateBehaviour(float deltaTime)
{
	scene->updateBehaviour(deltaTime);
}

void PhysicsExample::renderBehaviour(float deltaTime)
{
	scene->renderBehaviour(deltaTime);
}

void PhysicsExample::uiBehaviour(float deltaTime)
{
	scene->uiBehaviour(deltaTime);
}


