#include "Scene.h"

void childInit(Entity* e) {
	e->initBehaviour();
	for (int i = 0; i < e->children.size(); i++)
	{
		childInit(e->children.at(i).get());
	}
}

void Scene::initBehaviour()
{
	childInit(rootEntity);
}

void childStart(Entity* e) {
	e->startBehaviour();
	for (int i = 0; i < e->children.size(); i++)
	{
		childStart(e->children.at(i).get());
	}
}

void Scene::startBehaviour()
{
	childStart(rootEntity);
}

void childEarlyUpdate(Entity* e)
{
	e->earlyUpdateBehaviour();
	for (int i = 0; i < e->children.size(); i++)
	{
		childEarlyUpdate(e->children.at(i).get());
	}
}

void Scene::earlyUpdateBehaviour()
{
	childEarlyUpdate(rootEntity);
}

void childUpdate(Entity* e)
{
	e->updateBehaviour();
	for (int i = 0; i < e->children.size(); i++)
	{
		childUpdate(e->children.at(i).get());
	}
}

void Scene::updateBehaviour()
{
	childUpdate(rootEntity);
}

void childUi(Entity* e)
{
	e->uiBehaviour();
	for (int i = 0; i < e->children.size(); i++)
	{
		childUi(e->children.at(i).get());
	}
}
void Scene::uiBehaviour()
{
	childUi(rootEntity);
}