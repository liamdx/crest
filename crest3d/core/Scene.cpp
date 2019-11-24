#include "Scene.h"
#include "components/MeshComponent.h"
#include "components/lighting/DirectionalLightComponent.h"
#include "EngineManager.h"


Scene::Scene(const char* _name, EngineManager* em)
{
	rootEntity = std::shared_ptr<Entity>(new Entity("root", nullptr));
	DEBUG_SPHERE_RADIUS = 1.0f;
	engineManager = em;
}


std::shared_ptr<Entity> Scene::AddEntity()
{
	return(rootEntity->AddEntity());
}

void childInit(std::shared_ptr<Entity> e) {
	e->initBehaviour();
	for (int i = 0; i < e->children.size(); i++)
	{
		childInit(e->children.at(i));
	}
}

void Scene::initBehaviour()
{
	childInit(rootEntity);
}

void childStart(std::shared_ptr<Entity> e) {
	e->startBehaviour();
	for (int i = 0; i < e->children.size(); i++)
	{
		childStart(e->children.at(i));
	}
}

void Scene::startBehaviour()
{
	childStart(rootEntity);
	// update every entity with a shader
	updateShaderProjections(rootEntity);
	engineManager->physicsManager->setProjection(sceneCamera->GetProjectionMatrix());
}

void childEarlyUpdate(std::shared_ptr<Entity> e, float deltaTime)
{
	e->earlyUpdateBehaviour(deltaTime);
	for (int i = 0; i < e->children.size(); i++)
	{
		childEarlyUpdate(e->children.at(i), deltaTime);
	}
}

void Scene::earlyUpdateBehaviour(float deltaTime)
{
	engineManager->physicsManager->update(deltaTime);
	childEarlyUpdate(rootEntity, deltaTime);
}

void childFixedUpdate(std::shared_ptr<Entity> e)
{
	e->fixedUpdateBehaviour();
	for (int i = 0; i < e->children.size(); i++)
	{
		childFixedUpdate(e->children.at(i));
	}
}

void Scene::fixedUpdateBehaviour()
{
	childFixedUpdate(rootEntity);
}

void childUpdate(std::shared_ptr<Entity> e, float deltaTime)
{
	e->updateBehaviour(deltaTime);
	for (int i = 0; i < e->children.size(); i++)
	{
		childUpdate(e->children.at(i), deltaTime);
	}
}

void Scene::updateBehaviour(float deltaTime)
{
	childUpdate(rootEntity, deltaTime);
}

void childRender(std::shared_ptr<Entity> e, float deltaTime, glm::mat4 view)
{
	e->renderBehaviour(deltaTime, view);
	for (int i = 0; i < e->children.size(); i++)
	{
		childRender(e->children.at(i), deltaTime, view);
	}
}

void Scene::renderBehaviour(float deltaTime)
{
	glm::mat4 view = sceneCamera->GetViewMatrix();
	updateSceneLighting();
	// childRender(rootEntity, deltaTime, view);

	sceneCamera->MakeFrustum();
	engineManager->shaderManager->defaultShader->shader->use();
	engineManager->shaderManager->defaultShader->setProjection(sceneCamera->GetProjectionMatrix());
	engineManager->shaderManager->defaultShader->setView(view);
	engineManager->shaderManager->defaultShader->UpdateShader(view);
	updateShaderComponentLightSources(engineManager->shaderManager->defaultShader);
	engineManager->shaderManager->defaultShader->shader->setVec3("viewPosition", sceneCamera->attachedEntity->transform->position);

	//// separate frustum check from mesh drawing, fix this
	//for (std::shared_ptr<MeshComponent> mesh : meshes)
	//{
	//	if (sceneCamera->checkPoint(mesh->attachedEntity->transform->position))
	//	{
	//		mesh->shouldDraw = true;
	//	}
	//	else
	//	{
	//		mesh->shouldDraw = false;
	//	}
	//}
	//

	bindDefaultTextures(engineManager->shaderManager->defaultShader);
	for (std::shared_ptr<MeshComponent> mesh : meshes)
	{
		mesh->draw(view, engineManager->shaderManager->defaultShader);
	}

	engineManager->shaderManager->defaultAnimShader->shader->use();
	engineManager->shaderManager->defaultAnimShader->setProjection(sceneCamera->GetProjectionMatrix());
	engineManager->shaderManager->defaultAnimShader->setView(view);
	engineManager->shaderManager->defaultAnimShader->UpdateShader(view);
	engineManager->shaderManager->defaultAnimShader->shader->setVec3("viewPosition", sceneCamera->attachedEntity->transform->position);
	updateShaderComponentLightSources(engineManager->shaderManager->defaultAnimShader);

	bindDefaultTextures(engineManager->shaderManager->defaultAnimShader);
	for (std::shared_ptr<AnimatedModelComponent> anim : animatedModels)
	{
		anim->draw(view, engineManager->shaderManager->defaultAnimShader);
	}
	engineManager->physicsManager->setView(view);
	engineManager->physicsManager->setProjection(sceneCamera->GetProjectionMatrix());
	engineManager->physicsManager->render(deltaTime);
}

void Scene::bindDefaultTextures(std::shared_ptr<ShaderComponent> sc)
{
	// Diffuse
	glActiveTexture(GL_TEXTURE0);
	sc->shader->setIntID(sc->shader->textureIdMappings[TextureType::diffuse], 0);
	glBindTexture(GL_TEXTURE_2D, engineManager->assetManager->defaultDiffuse->asset->t_Id);
	// Normal
	glActiveTexture(GL_TEXTURE1);
	sc->shader->setIntID(sc->shader->textureIdMappings[TextureType::normal], 1);
	glBindTexture(GL_TEXTURE_2D, engineManager->assetManager->defaultNormal->asset->t_Id);
	// AO
	glActiveTexture(GL_TEXTURE2);
	sc->shader->setIntID(sc->shader->textureIdMappings[TextureType::ao], 2);
	glBindTexture(GL_TEXTURE_2D, engineManager->assetManager->defaultAO->asset->t_Id);
	// Roughness
	glActiveTexture(GL_TEXTURE3);
	sc->shader->setIntID(sc->shader->textureIdMappings[TextureType::roughness], 3);
	glBindTexture(GL_TEXTURE_2D, engineManager->assetManager->defaultRoughness->asset->t_Id);
	// metallic
	glActiveTexture(GL_TEXTURE4);
	sc->shader->setIntID(sc->shader->textureIdMappings[TextureType::metallic], 4);
	glBindTexture(GL_TEXTURE_2D, engineManager->assetManager->defaultMetallic->asset->t_Id);
}

void childUi(std::shared_ptr<Entity> e, float deltaTime)
{
	e->uiBehaviour(deltaTime);
	for (int i = 0; i < e->children.size(); i++)
	{
		childUi(e->children.at(i), deltaTime);
	}
}
void Scene::uiBehaviour(float deltaTime)
{
	childUi(rootEntity, deltaTime);
}

std::shared_ptr<Entity> Scene::AddCameraEntity()
{
	std::shared_ptr<Entity> e = rootEntity->AddEntity();
	e->AddComponent(new CameraComponent(e));
	sceneCamera = e->GetComponent<CameraComponent>();
	return e;
}

std::shared_ptr<Entity> Scene::AddMeshEntity(std::shared_ptr<Mesh> mesh)
{
	std::shared_ptr<Entity> e = std::shared_ptr<Entity>(new Entity("Mesh Entity", nullptr));
	e->AddComponent(new MeshComponent(e, mesh));
	return e;
}

std::shared_ptr<Entity> Scene::AddMeshEntity(std::shared_ptr<Mesh> mesh, std::string name)
{
	std::shared_ptr<Entity> e = std::shared_ptr<Entity>(new Entity(name.c_str(), nullptr));
	e->AddComponent(new MeshComponent(e, mesh));

	auto mc = e->GetComponent<MeshComponent>();
	if (mc != nullptr)
	{
		meshes.emplace_back(e->GetComponent<MeshComponent>());
	}

	return e;
}

std::shared_ptr<Entity> Scene::AddModelEntity(std::shared_ptr<Model> model)
{
	std::shared_ptr<Entity> e = rootEntity->AddEntity();
	e->name = model->name;

	for (int i = 0; i < model->meshes.size(); i++)
	{
		std::shared_ptr<Entity> newE = AddMeshEntity(model->meshes.at(i), std::to_string(i));
		newE->transform->parent = e->transform;
		e->children.emplace_back(newE);
	}
	return e;
}

std::shared_ptr<Entity> Scene::AddAnimatedModelEntity(std::shared_ptr<AnimatedModel> model)
{
	std::shared_ptr<Entity> e = rootEntity->AddEntity();
	e->name = model->directory;
	e->AddComponent(new AnimatedModelComponent(e, model));
	auto amc = e->GetComponent<AnimatedModelComponent>();
	amc->getBoneShaderIDLocations(engineManager->shaderManager->defaultAnimShader);
	animatedModels.emplace_back(amc);
	return e;
}

std::shared_ptr<Entity> Scene::AddDirectionalLightEntity()
{
	std::shared_ptr<Entity> e = rootEntity->AddEntity();
	e->name = "Directional Light";
	e->AddComponent(new DirectionalLightComponent(e));
	return(e);
}

std::shared_ptr<Entity> Scene::AddPointLightEntity()
{
	std::shared_ptr<Entity> e = rootEntity->AddEntity();
	std::stringstream ss;
	ss << "Point Light " << (pointLightComponents.size() + 1);
	std::string s = ss.str();
	e->name = s;
	e->AddComponent(new PointLightComponent(e));
	auto plc = e->GetComponent<PointLightComponent>();
	pointLightComponents.emplace_back(plc);
	return(e);
}

void Scene::updateShaderProjections(std::shared_ptr<Entity> e)
{
	std::shared_ptr<ShaderComponent> sc = e->GetComponent<ShaderComponent>();

	if (sc != nullptr)
		sc->setProjection(sceneCamera->GetProjectionMatrix());

	for (int i = 0; i < e->children.size(); i++)
	{
		updateShaderProjections(e->children.at(i));
	}
}

void Scene::updateShaderLightSources(std::shared_ptr<Entity> e)
{
	std::shared_ptr<ShaderComponent> sc = e->GetComponent<ShaderComponent>();

	updateShaderComponentLightSources(sc);

	for (int i = 0; i < e->children.size(); i++)
	{
		updateShaderLightSources(e->children.at(i));
	}
}

void Scene::updateShaderComponentLightSources(std::shared_ptr<ShaderComponent> sc)
{
	if (sc != nullptr) {
		// do the lighting stuff
		dirLightComponent->Bind(sc);
		sc->SetNumPointLights(pointLightComponents.size());
		for (int i = 0; i < pointLightComponents.size(); i++)
		{
			pointLightComponents.at(i)->Bind(sc, i);
		}
	}
}


void Scene::updateLightComponentsVector(std::shared_ptr<Entity> e)
{
	// pointLightComponents.clear();
	for (int i = 0; i < e->components.size(); i++)
	{
		if (e->components.at(i)->name == "DirectionalLightComponent")
		{
			dirLightComponent = std::shared_ptr<DirectionalLightComponent>(e->GetComponent<DirectionalLightComponent>());
		}
		/*if (e->components.at(i)->name == "PointLightComponent")
		{
			pointLightComponents.emplace_back(std::shared_ptr<PointLightComponent>(e->GetComponent<PointLightComponent>()));
		}*/
	}

	if (e->children.size() > 0)
	{
		for (int i = 0; i < e->children.size(); i++)
		{
			updateLightComponentsVector(e->children.at(i));
		}
	}
}

void Scene::updateSceneLighting()
{
	updateLightComponentsVector(rootEntity);
	// updateShaderLightSources(rootEntity);
}