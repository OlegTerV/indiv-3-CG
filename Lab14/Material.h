#ifndef MATERIAL_H
#define MATERIAL_H

#include <SFML/Graphics.hpp>
#include <string>

#include "ShaderProgram.h"

struct Texture
{
	GLuint id;
	std::string type;
	sf::Texture texture;
};

struct Material
{
	Texture texture;
	GLfloat specular = 0.1f;
	GLfloat shininess = 10.f;
public:
	Material() {}
	Material(const char* texturePath)
	{
		InitializeTexture(texturePath);
	}


	void Use(ShaderProgram* s)
	{
		glActiveTexture(GL_TEXTURE0);
		sf::Texture::bind(&texture.texture);

		s->SetUniformFloat("material.specular", specular);
		s->SetUniformFloat("material.shininess", shininess);
		
	}
private:
	void InitializeTexture(const char* texturePath)
	{
		sf::Texture texture1;
		texture1.loadFromFile(texturePath);
		texture1.setRepeated(true);
		texture = { 0, "testing", texture1 };
	}
};

#endif
