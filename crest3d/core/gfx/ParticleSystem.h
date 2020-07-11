#pragma once
#include "Common.h"
#include "Shader.h"
#include "components/CameraComponent.h"

struct Particle
{
	glm::vec3 position, speed;
	unsigned char r, g, b, a;
	float size, angle, weight;
	float life;
	float cameradistance;

	bool operator<(const Particle& that) const {
		// Sort in reverse order : far particles drawn first.
		return this->cameradistance > that.cameradistance;
	}
};

class ParticleSystem
{
public:
	static constexpr unsigned int MAX_PARTICLES = 100000;
	unsigned int lastUsedParticle;
	unsigned int shaderTextureLoc, shaderCamRightLoc, shaderCamUpLoc, viewProjMatrixLoc;
	GLuint billboard_vertex_buffer, vertex_array_id;
	GLfloat* g_particule_position_size_data;
	GLubyte* g_particule_color_data;
	static constexpr GLfloat g_vertex_buffer_data[] = {
		 -0.5f, -0.5f, 0.0f,
		  0.5f, -0.5f, 0.0f,
		 -0.5f,  0.5f, 0.0f,
		  0.5f,  0.5f, 0.0f,
	};
	
	unsigned int particles_position_buffer, particles_colour_buffer;

	ParticleSystem();
	~ParticleSystem() {};

	void init();
	void update(float deltaTime, std::shared_ptr<CameraComponent> cam);
	void render(float deltaTime, std::shared_ptr<CameraComponent> cam, std::shared_ptr<Shader> shader);
	void clear();
	void reset();
	
	unsigned int particleCount;
	std::vector<Particle> particles;
	unsigned int texture;
	
	unsigned int FindUnusedParticle();
	void GenerateParticles(unsigned int _togenerate);
	void SortParticles();
	std::string path;
	float avg_cam_distance;

	char sortCounter;

	unsigned int viewProjId, textureId, camRightId, camUpId;
	

	glm::vec3 position, eulerAngles, scale;

	
};