#ifndef SCENE_OBJECT_H
#define SCENE_OBJECT_H

#include <glm/glm.hpp>

#include "ShaderProgram.h"
#include "Mesh.h"


class SceneObject
{
private:
	Mesh* mesh;
	ShaderProgram* shaderProgram;
public:
	glm::vec3 position{ 0.f, 0.f, 0.f };
	glm::vec3 rotation{ 0.f, 0.f, 0.f };
	glm::vec3 scale{ 1.f, 1.f, 1.f };

	SceneObject(Mesh* mesh, ShaderProgram* sp)
	{
		this->mesh = mesh;
		this->shaderProgram = sp;
	}
	
	void Draw()
	{
		glm::mat4 model = glm::rotate(glm::mat4(1.0f), rotation.x, glm::vec3(1.0f, 0.0f, 0.0f))
			* glm::rotate(glm::mat4(1.0f), rotation.z, glm::vec3(0.0f, 0.0f, 1.0f))
			* glm::translate(glm::mat4(1.f), position)
			* glm::scale(glm::mat4(1.f), scale);
		shaderProgram->Use();
		shaderProgram->SetUniformMat4("model", model);
		shaderProgram->SetUniformFloat("rotationY", rotation.y);
		mesh->Draw(*shaderProgram);
		glUseProgram(0);
	}


};

#endif
