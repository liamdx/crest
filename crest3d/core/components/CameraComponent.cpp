#include "CameraComponent.h"
#include "Entity.h"
#include "Common.h"

CameraComponent::CameraComponent(std::shared_ptr<Entity> e)
{
	attachedEntity = e;
	name = "CameraComponent";
	nearPlane = 0.1;
	farPlane = 1000;
	width = 1280;
	height = 720;
	fov = 70;
	updateProjection(fov, width, height);
}

glm::mat4 CameraComponent::GetViewProjectionMatrix()
{
	glm::mat4 view = glm::lookAt(attachedEntity->transform->position,
		attachedEntity->transform->position + attachedEntity->transform->forward,
		attachedEntity->transform->up);

	return projection * view;
}

glm::mat4 CameraComponent::GetViewMatrix()
{
	return glm::lookAt(attachedEntity->transform->position,
		attachedEntity->transform->position + attachedEntity->transform->forward,
		attachedEntity->transform->up);
}

void CameraComponent::updateProjection(float _fov, float _width, float _height)
{
	projection = glm::perspectiveFov(glm::radians(_fov), _width, _height, nearPlane, farPlane);
	fov = _fov;
	width = _width;
	height = _height;
}

void CameraComponent::MakeFrustum()
{
	//float screenDepth = farPlane - nearPlane;
	//float zMinimum = -projection[2][3] / projection[2][2];
	//float r = screenDepth / (screenDepth - zMinimum);

	//projection[2][2] = r;
	// projection[3][2] = -r * zMinimum;
	//

	//auto vp = GetViewMatrix() * GetProjectionMatrix();

	//// near plane
	//glm::vec4 np;
	//np.x = vp[3][0] + vp[2][0];
	//np.y = vp[3][1] + vp[2][1];
	//np.z = vp[3][2] + vp[2][2];
	//np.w = vp[3][3] + vp[2][3];
	//np = glm::normalize(np);

	//// far plane
	//glm::vec4 fp;
	//fp.x = vp[3][0] - vp[2][0];
	//fp.y = vp[3][1] - vp[2][1];
	//fp.z = vp[3][2] - vp[2][2];
	//fp.w = vp[3][3] - vp[2][3];
	//fp = glm::normalize(fp);
	//
	//// left plane
	//glm::vec4 lp;
	//lp.x = vp[3][0] + vp[0][0];
	//lp.y = vp[3][1] + vp[0][1];
	//lp.z = vp[3][2] + vp[0][2];
	//lp.w = vp[3][3] + vp[0][3];
	//lp = glm::normalize(lp);

	//// right plane
	//glm::vec4 rp;
	//rp.x = vp[3][0] - vp[0][0];
	//rp.y = vp[3][1] - vp[0][1];
	//rp.z = vp[3][2] - vp[0][2];
	//rp.w = vp[3][3] - vp[0][3];
	//rp = glm::normalize(rp);

	//// top plane
	//glm::vec4 tp;
	//tp.x = vp[3][0] - vp[1][0];
	//tp.y = vp[3][1] - vp[1][1];
	//tp.z = vp[3][2] - vp[1][2];
	//tp.w = vp[3][3] - vp[1][3];
	//tp = glm::normalize(tp);

	//// bottom plane
	//glm::vec4 bp;
	//tp.x = vp[3][0] + vp[1][0];
	//tp.y = vp[3][1] + vp[1][1];
	//tp.z = vp[3][2] + vp[1][2];
	//tp.w = vp[3][3] + vp[1][3];
	//bp = glm::normalize(bp);

	//frustumPlanes.clear();
	//frustumPlanes.emplace_back(np);
	//frustumPlanes.emplace_back(fp);
	//frustumPlanes.emplace_back(lp);
	//frustumPlanes.emplace_back(rp);
	//frustumPlanes.emplace_back(tp);
	//frustumPlanes.emplace_back(bp);

	glm::mat4 clip = glm::mat4(1.0);
	glm::mat4 view = GetViewMatrix();

	clip[0][0] = view[0][0] * projection[0][0] + view[0][1] * projection[1][0] + view[0][2] * projection[2][0] + view[0][3] * projection[3][0];
	clip[0][1] = view[0][0] * projection[0][1] + view[0][1] * projection[1][1] + view[0][2] * projection[2][1] + view[0][3] * projection[3][1];
	clip[0][2] = view[0][0] * projection[0][2] + view[0][1] * projection[1][2] + view[0][2] * projection[2][2] + view[0][3] * projection[3][2];
	clip[0][3] = view[0][0] * projection[0][3] + view[0][1] * projection[1][3] + view[0][2] * projection[2][3] + view[0][3] * projection[3][3];

	clip[1][0] = view[1][0] * projection[0][0] + view[1][1] * projection[1][0] + view[1][2] * projection[2][0] + view[1][3] * projection[3][0];
	clip[1][1] = view[1][0] * projection[0][1] + view[1][1] * projection[1][1] + view[1][2] * projection[2][1] + view[1][3] * projection[3][1];
	clip[1][2] = view[1][0] * projection[0][2] + view[1][1] * projection[1][2] + view[1][2] * projection[2][2] + view[1][3] * projection[3][2];
	clip[1][3] = view[1][0] * projection[0][3] + view[1][1] * projection[1][3] + view[1][2] * projection[2][3] + view[1][3] * projection[3][3];

	clip[2][0] = view[2][0] * projection[0][0] + view[2][1] * projection[1][0] + view[2][2] * projection[2][0] + view[2][3] * projection[3][0];
	clip[2][1] = view[2][0] * projection[0][1] + view[2][1] * projection[1][1] + view[2][2] * projection[2][1] + view[2][3] * projection[3][1];
	clip[2][2] = view[2][0] * projection[0][2] + view[2][1] * projection[1][2] + view[2][2] * projection[2][2] + view[2][3] * projection[3][2];
	clip[2][3] = view[2][0] * projection[0][3] + view[2][1] * projection[1][3] + view[2][2] * projection[2][3] + view[2][3] * projection[3][3];

	clip[3][0] = view[3][0] * projection[0][0] + view[3][1] * projection[1][0] + view[3][2] * projection[2][0] + view[3][3] * projection[3][0];
	clip[3][1] = view[3][0] * projection[0][1] + view[3][1] * projection[1][1] + view[3][2] * projection[2][1] + view[3][3] * projection[3][1];
	clip[3][2] = view[3][0] * projection[0][2] + view[3][1] * projection[1][2] + view[3][2] * projection[2][2] + view[3][3] * projection[3][2];
	clip[3][3] = view[3][0] * projection[0][3] + view[3][1] * projection[1][3] + view[3][2] * projection[2][3] + view[3][3] * projection[3][3];

	frustumPlanes.clear();

	glm::vec4 rp;
	rp.x = clip[0][3] - clip[0][0];
	rp.y = clip[1][3] - clip[1][0];
	rp.z = clip[2][3] - clip[2][0];
	rp.w = clip[3][3] - clip[3][0];
	rp = normalizePlane(rp);
	frustumPlanes.emplace_back(rp);

	glm::vec4 lp;
	lp.x = clip[0][3] + clip[0][0];
	lp.y = clip[1][3] + clip[1][0];
	lp.z = clip[2][3] + clip[2][0];
	lp.w = clip[3][3] + clip[3][0];
	lp = normalizePlane(lp);
	frustumPlanes.emplace_back(lp);

	glm::vec4 bp;
	bp.x = clip[0][3] + clip[0][1];
	bp.y = clip[1][3] + clip[1][1];
	bp.z = clip[2][3] + clip[2][1];
	bp.w = clip[3][3] + clip[3][1];
	bp = normalizePlane(bp);
	frustumPlanes.emplace_back(bp);

	glm::vec4 tp;
	tp.x = clip[0][3] - clip[0][1];
	tp.y = clip[1][3] - clip[1][1];
	tp.z = clip[2][3] - clip[2][1];
	tp.w = clip[3][3] - clip[3][1];
	tp = normalizePlane(tp);
	frustumPlanes.emplace_back(tp);

	glm::vec4 fp;
	fp.x = clip[0][3] - clip[0][2];
	fp.y = clip[1][3] - clip[1][2];
	fp.z = clip[2][3] - clip[2][2];
	fp.w = clip[3][3] - clip[3][2];
	fp = normalizePlane(fp);
	frustumPlanes.emplace_back(fp);

	glm::vec4 bkp;
	bkp.x = clip[0][3] + clip[0][2];
	bkp.y = clip[1][3] + clip[1][2];
	bkp.z = clip[2][3] + clip[2][2];
	bkp.w = clip[3][3] + clip[3][2];
	bkp = normalizePlane(bkp);
	frustumPlanes.emplace_back(bkp);
}

float CameraComponent::planeDotCoord(glm::vec4 a, glm::vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z + a.w);
}

bool CameraComponent::checkSphere(glm::vec3 position, float radius)
{
	for (unsigned int i = 0; i < 6; i++)
	{
		if (planeDotCoord(frustumPlanes[i], position) < -radius)
		{
			return false;
		}
	}
	return true;
}

bool CameraComponent::checkPoint(glm::vec3 position)
{
	for (unsigned int i = 0; i < 6; i++)
	{
		float d = planeDotCoord(frustumPlanes[i], position);
		if (d <= 0)
		{
			return false;
		}
	}

	return true;
}

glm::vec4 CameraComponent::normalizePlane(glm::vec4 plane)
{
	glm::vec4 normVec;
	double magnitude = glm::sqrt(
		plane[0] * plane[0] +
		plane[1] * plane[1] +
		plane[2] * plane[2]
	);

	normVec.x = plane.x / magnitude;
	normVec.y = plane.y / magnitude;
	normVec.z = plane.z / magnitude;
	normVec.w = plane.w / magnitude;

	return normVec;
}

tinyxml2::XMLElement* CameraComponent::serialize_component(tinyxml2::XMLDocument* doc)
{
	auto cameraElement = doc->NewElement("CameraComponent");
	cameraElement->SetAttribute("fov", fov);
	cameraElement->SetAttribute("width", width);
	cameraElement->SetAttribute("height", height);
	cameraElement->SetAttribute("nearPlane", nearPlane);
	cameraElement->SetAttribute("farPlane", farPlane);
	return cameraElement;
}
