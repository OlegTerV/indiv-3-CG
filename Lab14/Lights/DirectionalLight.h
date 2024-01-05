#ifndef DIRECTIONAL_LIGHT_H
#define DIRECTIONAL_LIGHT_H

#include "..//ShaderProgram.h"


struct DirectionalLight
{
	glm::vec3 direction = { -0.3f, -1.0f, 1.8f };

	glm::vec3 ambient = {0.2f, 0.2f, 0.2f};
	glm::vec3 diffuse = { 1.0f, 1.0f, 0.95f } ; 
	glm::vec3 specular = { 1.0f, 1.0f, 0.95f };

	DirectionalLight() {};
};

#endif // !DIRECTIONAL_LIGHT_H
