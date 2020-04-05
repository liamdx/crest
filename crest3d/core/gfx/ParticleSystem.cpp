#include "ParticleSystem.h"
#include "Model.h"
#include "components/CameraComponent.h"

ParticleSystem::ParticleSystem()
{
	g_particule_position_size_data = new GLfloat[MAX_PARTICLES * 4];
	g_particule_color_data = new GLubyte[MAX_PARTICLES * 4];
	lastUsedParticle = 0;
	for(unsigned int i = 0; i < MAX_PARTICLES; i++)
	{
		particles.emplace_back(Particle());
		particles[i].life = -1.0f;
		particles[i].cameradistance = -1.0f;
	}
	sortCounter = 0;


}

void ParticleSystem::init()
{
	GLCall(glGenVertexArrays(1, &vertex_array_id));
	GLCall(glBindVertexArray(vertex_array_id));
	
	GLCall(glGenBuffers(1, &billboard_vertex_buffer));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, billboard_vertex_buffer));
	GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW));

	// The VBO containing the positions and sizes of the particles
	GLCall(glGenBuffers(1, &particles_position_buffer));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer));
	// Initialize with empty (NULL) buffer : it will be updated later, each frame.
	GLCall(glBufferData(GL_ARRAY_BUFFER, MAX_PARTICLES * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW));

	// The VBO containing the colors of the particles
	GLCall(glGenBuffers(1, &particles_colour_buffer));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, particles_colour_buffer));
	// Initialize with empty (NULL) buffer : it will be updated later, each frame.
	GLCall(glBufferData(GL_ARRAY_BUFFER, MAX_PARTICLES * 4 * sizeof(GLubyte), NULL, GL_STREAM_DRAW));

	GLCall(glBindVertexArray(0));

}

void ParticleSystem::clear()
{
	glDeleteVertexArrays(1, &vertex_array_id);
}

void ParticleSystem::reset()
{
	clear();
	init();
}


void ParticleSystem::update(float deltaTime, std::shared_ptr<CameraComponent> cam)
{
	glm::vec3 CameraPosition = cam->attachedEntity->transform->position;

	float numSpawn = 10000;
	int newparticles = (int)(deltaTime * numSpawn);
	if (newparticles > (int)(0.016f * numSpawn))
		newparticles = (int)(0.016f * numSpawn);

	for (int i = 0; i < newparticles; i++) {
		int particleIndex = FindUnusedParticle();
		particles[particleIndex].life = 5.0f; // This particle will live 5 seconds.
		particles[particleIndex].position = position;

		float spread = 1.5f;
		glm::vec3 maindir = glm::vec3(0.0f, 10.0f, 0.0f);
		// Very bad way to generate a random direction; 
		// See for instance http://stackoverflow.com/questions/5408276/python-uniform-spherical-distribution instead,
		// combined with some user-controlled parameters (main direction, spread, etc)
		glm::vec3 randomdir = glm::vec3(
			(rand() % 2000 - 1000.0f) / 1000.0f,
			(rand() % 2000 - 1000.0f) / 1000.0f,
			(rand() % 2000 - 1000.0f) / 1000.0f
		);

		particles[particleIndex].speed = maindir + randomdir * spread;


		// Very bad way to generate a random color
		particles[particleIndex].r = rand() % 256;
		particles[particleIndex].g = rand() % 256;
		particles[particleIndex].b = rand() % 256;
		particles[particleIndex].a = (rand() % 256) / 3;

		particles[particleIndex].size = ((rand() % 1000) / 2000.0f + 0.1f) * glm::length(scale);

	}

	
	unsigned int ParticlesCount = 0;
	avg_cam_distance = 0.0f;
	for (int i = 0; i < MAX_PARTICLES; i++) {

		Particle& p = particles[i]; // shortcut

		if (p.life > 0.0f) {

			// Decrease life
			p.life -= deltaTime;
			if (p.life > 0.0f) {

				// Simulate simple physics : gravity only, no collisions
				p.speed += glm::vec3(0.0f, -3.81f, 0.0f) * (float)deltaTime * 0.5f;
				p.position += p.speed * (float)deltaTime;
				p.cameradistance = glm::length2(p.position - CameraPosition);
				//ParticlesContainer[i].pos += glm::vec3(0.0f,10.0f, 0.0f) * (float)delta;

				// Fill the GPU buffer
				g_particule_position_size_data[4 * ParticlesCount + 0] = p.position.x;
				g_particule_position_size_data[4 * ParticlesCount + 1] = p.position.y;
				g_particule_position_size_data[4 * ParticlesCount + 2] = p.position.z;

				g_particule_position_size_data[4 * ParticlesCount + 3] = p.size;

				g_particule_color_data[4 * ParticlesCount + 0] = p.r;
				g_particule_color_data[4 * ParticlesCount + 1] = p.g;
				g_particule_color_data[4 * ParticlesCount + 2] = p.b;
				g_particule_color_data[4 * ParticlesCount + 3] = p.a;

			}
			else {
				// Particles that just died will be put at the end of the buffer in SortParticles();
				p.cameradistance = -1.0f;
			}

			ParticlesCount++;
			avg_cam_distance += (p.cameradistance / MAX_PARTICLES);
		}
	}

	particleCount = ParticlesCount;

	if ((sortCounter + 1) >= 4)
	{
		SortParticles();
		sortCounter = 0;
	}
	else
	{
		sortCounter += 1;
	}
	

}

void ParticleSystem::render(float deltaTime, std::shared_ptr<CameraComponent> cam, std::shared_ptr<Shader> shader)
{
	// Update the buffers that OpenGL uses for rendering.
// There are much more sophisticated means to stream data from the CPU to the GPU,
// but this is outside the scope of this tutorial.
// http://www.opengl.org/wiki/Buffer_Object_Streaming
// 
	GLCall(glBlendFunc(GL_ONE_MINUS_SRC_ALPHA, GL_ONE));
	GLCall(glBindVertexArray(vertex_array_id));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer));
	GLCall(glBufferData(GL_ARRAY_BUFFER, MAX_PARTICLES * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW)); // Buffer orphaning, a common way to improve streaming perf. See above link for details.
	GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, particleCount * sizeof(GLfloat) * 4, g_particule_position_size_data));

	GLCall(glBindBuffer(GL_ARRAY_BUFFER, particles_colour_buffer));
	GLCall(glBufferData(GL_ARRAY_BUFFER, MAX_PARTICLES * 4 * sizeof(GLubyte), NULL, GL_STREAM_DRAW)); // Buffer orphaning, a common way to improve streaming perf. See above link for details.
	GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, particleCount * sizeof(GLubyte) * 4, g_particule_color_data));

	shader->use();

	GLCall(glActiveTexture(GL_TEXTURE0 ));
	shader->setInt("mat.m_Diffuse", 0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glm::vec3 camr = cam->attachedEntity->transform->right;
	glm::vec3 camu = cam->attachedEntity->transform->up;
	glm::mat4 viewProj = cam->GetViewProjectionMatrix();
	shader->setMat4("viewProj", viewProj);
	shader->setVec3("camRightWS", camr);
	shader->setVec3("camUpWS", camu);

	// 1rst attribute buffer : vertices
	GLCall(glEnableVertexAttribArray(0));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, billboard_vertex_buffer));
	GLCall(glVertexAttribPointer(
		0, // attribute. No particular reason for 0, but must match the layout in the shader.
		3, // size
		GL_FLOAT, // type
		GL_FALSE, // normalized?
		0, // stride
		(void*) 0// array buffer offset
	));

	// 2nd attribute buffer : positions of particles' centers
	GLCall(glEnableVertexAttribArray(1));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer));
	GLCall(glVertexAttribPointer(
		1, // attribute. No particular reason for 1, but must match the layout in the shader.
		4, // size : x + y + z + size => 4
		GL_FLOAT, // type
		GL_FALSE, // normalized?
		0, // stride
		(void*)0 // array buffer offset
	));

	// 3rd attribute buffer : particles' colors
	GLCall(glEnableVertexAttribArray(2));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, particles_colour_buffer));
	GLCall(glVertexAttribPointer(
		2, // attribute. No particular reason for 1, but must match the layout in the shader.
		4, // size : r + g + b + a => 4
		GL_UNSIGNED_BYTE, // type
		GL_TRUE, // normalized? *** YES, this means that the unsigned char[4] will be accessible with a vec4 (floats) in the shader ***
		0, // stride
		(void*)0 // array buffer offset
	));

	// These functions are specific to glDrawArrays*Instanced*.
	// The first parameter is the attribute buffer we're talking about.
	// The second parameter is the "rate at which generic vertex attributes advance when rendering multiple instances"
	// http://www.opengl.org/sdk/docs/man/xhtml/glVertexAttribDivisor.xml
	GLCall(glVertexAttribDivisor(0, 0)); // particles vertices : always reuse the same 4 vertices -> 0
	GLCall(glVertexAttribDivisor(1, 1)); // positions : one per quad (its center) -> 1
	GLCall(glVertexAttribDivisor(2, 1)); // color : one per quad -> 1

	// Draw the particules !
	// This draws many times a small triangle_strip (which looks like a quad).
	// This is equivalent to :
	// for(i in ParticlesCount) : glDrawArrays(GL_TRIANGLE_STRIP, 0, 4),
	// but faster.
	GLCall(glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, particleCount));

	GLCall(glDisableVertexAttribArray(0));
	GLCall(glDisableVertexAttribArray(1));
	GLCall(glDisableVertexAttribArray(2));
	GLCall(glBindVertexArray(0));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
}



unsigned int ParticleSystem::FindUnusedParticle()
{
	for(unsigned int i = lastUsedParticle; i < MAX_PARTICLES; i++)
	{
		if(particles[i].life <= 0.0f)
		{
			lastUsedParticle = i;
			return i;
		}
	}

	for(unsigned int i =0; i < lastUsedParticle; i++)
	{
		if(particles[i].life <= 0.0f)
		{
			lastUsedParticle = i;
			return i;
		}
	}

	return 0;
}

void ParticleSystem::GenerateParticles(unsigned int _togenerate)
{
	for (int i = 0; i < _togenerate; i++) {
		int particleIndex = FindUnusedParticle();
		particles[particleIndex].life = 5.0f; // This particle will live 5 seconds.
		particles[particleIndex].position = glm::vec3(0, 0, -20.0f);

		float spread = 1.5f;
		glm::vec3 maindir = glm::vec3(0.0f, 10.0f, 0.0f);
		// Very bad way to generate a random direction; 
		// See for instance http://stackoverflow.com/questions/5408276/python-uniform-spherical-distribution instead,
		// combined with some user-controlled parameters (main direction, spread, etc)
		glm::vec3 randomdir = glm::vec3(
			(rand() % 2000 - 1000.0f) / 1000.0f,
			(rand() % 2000 - 1000.0f) / 1000.0f,
			(rand() % 2000 - 1000.0f) / 1000.0f
		);

		particles[particleIndex].speed = maindir + randomdir * spread;


		// Very bad way to generate a random color
		particles[particleIndex].r = rand() % 256;
		particles[particleIndex].g = rand() % 256;
		particles[particleIndex].b = rand() % 256;
		particles[particleIndex].a = (rand() % 256) / 3;

		particles[particleIndex].size = (rand() % 1000) / 2000.0f + 0.1f;

	}
}

void ParticleSystem::SortParticles()
{
	std::sort(&particles[0], &particles[MAX_PARTICLES]);
}
