#ifndef INSTANCED_MESH_H
#define INSTANCED_MESH_H


#include "Mesh.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <chrono>
#include <ctime>  

class InstansedMesh : public Mesh
{
    GLuint buffer;
    GLuint count;
    glm::mat4* modelMatrices;
public:
	

	InstansedMesh(const char* filePath, const char* texturePath, int count): Mesh(filePath, texturePath)
	{
		this->count = count;

        InitializeBuffers();
	}

	InstansedMesh(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices, const std::vector<Texture>& textures, GLuint count)
		: Mesh(vertices, indices, textures)
	{
		this->count = count;

		InitializeBuffers();
	}


	virtual void Draw(ShaderProgram& shader) const override
	{
		shader.Use();

        {
            glActiveTexture(GL_TEXTURE0);

            shader.SetUniformInt("texture1", 0);
            sf::Texture::bind(&texture.texture);

            glBindVertexArray(VAO);
            glDrawElementsInstanced(GL_TRIANGLES, static_cast<GLuint>(indices.size()), GL_UNSIGNED_INT, 0, count);
            glBindVertexArray(0);

            sf::Texture::bind(NULL);
        }
		glUseProgram(0);
	}
private:
    void InitializeBuffers()
    {
		Mesh::InitializeBuffers();
        
        modelMatrices = new glm::mat4[count];
        //srand(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()));
        //float radius = 12.0;
        //float offset = 53.1f;
        for (GLuint i = 0; i < count; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);         
            float x = rand() % 100 + (-(rand() % 100)) ;
            float z = rand() % 100 + (-(rand() % 100));
            model = glm::translate(model, glm::vec3(x, 0, z));
            modelMatrices[i] = model;
        }


		glGenBuffers(1, &buffer);
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glBufferData(GL_ARRAY_BUFFER, count * sizeof(glm::mat4), &modelMatrices[0], GL_STATIC_DRAW);

        glBindVertexArray(VAO);
        // set attribute pointers for matrix (4 times vec4)
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
        glEnableVertexAttribArray(5);
        glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
        glEnableVertexAttribArray(6);
        glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));

        glVertexAttribDivisor(3, 1);
        glVertexAttribDivisor(4, 1);
        glVertexAttribDivisor(5, 1);
        glVertexAttribDivisor(6, 1);

        glBindVertexArray(0);
    }
};

#endif
