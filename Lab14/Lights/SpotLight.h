#ifndef SPOT_LIGHT_H
#define SPOT_LIGHT_H

#include "..//ShaderProgram.h"


struct SpotLight
{
    glm::vec3 position;

    glm::vec3 attenuation = { 1.0f, 0.09f, 0.032f };

    glm::vec3 ambient = { 0.05f, 0.05f, 0.05f };
    glm::vec3 diffuse = { 1.0f, 1.0f, 0.8f };
    glm::vec3 specular = { 1.0f, 1.0f, 0.8f };

    SpotLight() {};
};

#endif // !DIRECTIONAL_LIGHT_H
