#include "MeshComponent.h"

void MeshComponent::init() {
	shader = attachedEntity->GetComponent<ShaderComponent>();
	shouldDraw = true;
}

void MeshComponent::start() {
}

void MeshComponent::earlyUpdate(float deltaTime)
{
	
}

void MeshComponent::update(float deltaTime) {

}

void MeshComponent::render(float deltaTime, glm::mat4 view)
{
	/*if(shouldDraw)
	{
		draw(view);
	}*/
}


void MeshComponent::ui(float deltaTime) {

}

void MeshComponent::draw(glm::mat4 view)
{
	if(shouldDraw)
	{
		attachedEntity->transform->updateModelMatrix();
		shader->shader->use();
		shader->setView(view);
		shader->UpdateShader(attachedEntity->transform->getModelMatrix());
		mesh->Draw(*shader->shader);
	}
}

void MeshComponent::draw(glm::mat4 view, std::shared_ptr<ShaderComponent> _shader)
{
	if (shouldDraw)
	{
		// attachedEntity->transform->updateModelMatrix();
		// shader->shader->use();
		// shader->setView(view);
		_shader->UpdateModel(attachedEntity->transform->getModelMatrix());
		mesh->Draw(_shader->shader);
	}
}

bool MeshComponent::isConvex(std::vector<glm::vec3> points, std::vector<unsigned int> triangles, float threshold = 0.001)
{
	for (unsigned long i = 0; i < triangles.size() / 3; i++)
	{
		glm::vec3 A = points[triangles[i * 3 + 0]];
		glm::vec3 B = points[triangles[i * 3 + 1]];
		glm::vec3 C = points[triangles[i * 3 + 2]];

		B = B - A;
		C = C - A;

		glm::vec3 BCNorm =glm::normalize( glm::cross(B,C));  // B.cross(C).normalized();

		// float checkPoint = btVector3(points[0].x - A.x(), points[0].y - A.y(), points[0].z - A.z()).dot(BCNorm);
		float checkPoint = glm::dot(glm::vec3(points[0].x - A.x, points[0].y - A.y, points[0].z - A.z), BCNorm);
		for (unsigned long j = 0; j < points.size(); j++)
		{

			float dist = glm::dot(glm::vec3(points[j].x - A.x, points[j].y - A.y, points[j].z - A.z), BCNorm);

			if (std::abs(checkPoint) > threshold & std::abs(dist) > threshold & checkPoint * dist < 0)
			{
				return false;
			}
		}
	}

	return true;
}
