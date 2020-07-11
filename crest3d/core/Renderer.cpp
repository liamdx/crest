#include "Renderer.h"

Renderer::Renderer()
{
	
}

void Renderer::RenderMesh(const std::shared_ptr<Mesh>& m, const std::shared_ptr<Shader>& _shader, const PropertyGroup& props)
{
	int diffuseCount = 0;
	int specularCount = 0;
	int reflectionCount = 0;
	int normalCount = 0;

	for (unsigned int i = 0; i < m->textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		unsigned int uniformLocation = _shader->textureIdMappings[m->textures[i].t_Type];
		_shader->setIntID(uniformLocation, i);
		glBindTexture(GL_TEXTURE_2D, m->textures[i].t_Id);
	}

	glBindVertexArray(m->vao);
	glDrawElements(GL_TRIANGLES, m->indices.size(), GL_UNSIGNED_INT, 0);
	for (int i = 0; i < m->textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	glBindVertexArray(0);
}

void Renderer::RenderAnim(const std::shared_ptr<AnimatedModel>& anim, const std::shared_ptr<Shader>& _shader, const PropertyGroup& props)
{
	glBindVertexArray(anim->m_VAO);

	for (unsigned int i = 0; i < anim->m_Entries.size(); i++) {
		const unsigned int MaterialIndex = anim->m_Entries[i].MaterialIndex;

		for (unsigned int j = 0; j < anim->m_Entries[i].Textures.size(); j++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			if (anim->m_Entries[i].Textures[j].t_Type == TextureType::diffuse)
			{
				_shader->setInt("mat.m_Diffuse", i);
				glBindTexture(GL_TEXTURE_2D, anim->m_Entries[i].Textures[j].t_Id);
			}
		}

		glDrawElementsBaseVertex(GL_TRIANGLES,
			anim->m_Entries[i].NumIndices,
			GL_UNSIGNED_INT,
			(void*)(sizeof(unsigned int) * anim->m_Entries[i].BaseIndex),
			anim->m_Entries[i].BaseVertex);
	}
	// Make sure the VAO is not changed from the outside
	glBindVertexArray(0);
}

void Renderer::RenderParticleSystem(const std::shared_ptr<ParticleSystem>& ps, const std::shared_ptr<Shader>& _shader, const PropertyGroup& props)
{
	GLCall(glBlendFunc(GL_ONE_MINUS_SRC_ALPHA, GL_ONE));
	GLCall(glBindVertexArray(ps->vertex_array_id));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, ps->particles_position_buffer));
	GLCall(glBufferData(GL_ARRAY_BUFFER, ps->MAX_PARTICLES * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW)); // Buffer orphaning, a common way to improve streaming perf. See above link for details.
	GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, ps->particleCount * sizeof(GLfloat) * 4, ps->g_particule_position_size_data));

	GLCall(glBindBuffer(GL_ARRAY_BUFFER, ps->particles_colour_buffer));
	GLCall(glBufferData(GL_ARRAY_BUFFER, ps->MAX_PARTICLES * 4 * sizeof(GLubyte), NULL, GL_STREAM_DRAW)); // Buffer orphaning, a common way to improve streaming perf. See above link for details.
	GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, ps->particleCount * sizeof(GLubyte) * 4, ps->g_particule_color_data));

	_shader->use();

	GLCall(glActiveTexture(GL_TEXTURE0));
	_shader->setInt("mat.m_Diffuse", 0);
	glBindTexture(GL_TEXTURE_2D, ps->texture);

	//glm::vec3 camr = cam->attachedEntity->transform->right;
	//glm::vec3 camu = cam->attachedEntity->transform->up;
	//glm::mat4 viewProj = cam->GetViewProjectionMatrix();
	//shader->setMat4("viewProj", viewProj);
	//shader->setVec3("camRightWS", camr);
	//shader->setVec3("camUpWS", camu);

	//// 1rst attribute buffer : vertices
	//GLCall(glEnableVertexAttribArray(0));
	//GLCall(glBindBuffer(GL_ARRAY_BUFFER, billboard_vertex_buffer));
	//GLCall(glVertexAttribPointer(
	//	0, // attribute. No particular reason for 0, but must match the layout in the shader.
	//	3, // size
	//	GL_FLOAT, // type
	//	GL_FALSE, // normalized?
	//	0, // stride
	//	(void*)0// array buffer offset
	//));

	//// 2nd attribute buffer : positions of particles' centers
	//GLCall(glEnableVertexAttribArray(1));
	//GLCall(glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer));
	//GLCall(glVertexAttribPointer(
	//	1, // attribute. No particular reason for 1, but must match the layout in the shader.
	//	4, // size : x + y + z + size => 4
	//	GL_FLOAT, // type
	//	GL_FALSE, // normalized?
	//	0, // stride
	//	(void*)0 // array buffer offset
	//));

	//// 3rd attribute buffer : particles' colors
	//GLCall(glEnableVertexAttribArray(2));
	//GLCall(glBindBuffer(GL_ARRAY_BUFFER, particles_colour_buffer));
	//GLCall(glVertexAttribPointer(
	//	2, // attribute. No particular reason for 1, but must match the layout in the shader.
	//	4, // size : r + g + b + a => 4
	//	GL_UNSIGNED_BYTE, // type
	//	GL_TRUE, // normalized? *** YES, this means that the unsigned char[4] will be accessible with a vec4 (floats) in the shader ***
	//	0, // stride
	//	(void*)0 // array buffer offset
	//));

	//// These functions are specific to glDrawArrays*Instanced*.
	//// The first parameter is the attribute buffer we're talking about.
	//// The second parameter is the "rate at which generic vertex attributes advance when rendering multiple instances"
	//// http://www.opengl.org/sdk/docs/man/xhtml/glVertexAttribDivisor.xml
	//GLCall(glVertexAttribDivisor(0, 0)); // particles vertices : always reuse the same 4 vertices -> 0
	//GLCall(glVertexAttribDivisor(1, 1)); // positions : one per quad (its center) -> 1
	//GLCall(glVertexAttribDivisor(2, 1)); // color : one per quad -> 1

	//// Draw the particules !
	//// This draws many times a small triangle_strip (which looks like a quad).
	//// This is equivalent to :
	//// for(i in ParticlesCount) : glDrawArrays(GL_TRIANGLE_STRIP, 0, 4),
	//// but faster.
	//GLCall(glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, particleCount));

	//GLCall(glDisableVertexAttribArray(0));
	//GLCall(glDisableVertexAttribArray(1));
	//GLCall(glDisableVertexAttribArray(2));
	//GLCall(glBindVertexArray(0));
	//GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
}