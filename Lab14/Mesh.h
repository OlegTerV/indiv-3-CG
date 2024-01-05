#ifndef MESH_H
#define MESH_H

#include <SFML/Graphics.hpp>

#include <initializer_list>
#include <array>
#include <vector>
#include <string>

#include "ShaderProgram.h"
#include "Material.h"

using std::string;

std::vector<string> Split(const string& str, char separator) 
{
	std::stringstream ss(str);
	std::string word;
	std::vector<std::string> elems;
	while (std::getline(ss, word, separator))
	{
		if (word.empty()) 
			continue;
		elems.push_back(word);
	}
	return elems;
}


struct Vertex 
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};


class Mesh 
{
protected:
    GLuint VAO, VBO, EBO;
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
public:
    
	Material* material;
    Texture texture;    

    //TODO indexing
    Mesh(const char* filePath, const char* texturePath)
    {
		try 
		{
			std::ifstream reader(filePath);

			if (!reader.is_open()) 
			{
				throw std::exception("File cannot be opened");
			}

			std::vector<glm::vec3> _vertices;
			std::vector<glm::vec3> _vn;
			std::vector<glm::vec2> _vt;
			

			std::vector <std::string> indexAccordance{};
			std::string line;
			while (std::getline(reader, line))
			{
				std::istringstream iss(line);
				std::string typeOfElement;
				iss >> typeOfElement;
				if (typeOfElement == "v") 
				{
					string word;
					glm::vec3 cv{};
					for (GLuint i = 0; i < 3; i++)
					{
						iss >> word;
						cv[i] = std::stof(word);
					}
					_vertices.push_back(cv);
				}
				else if (typeOfElement == "vn") 
				{
					string word;
					glm::vec3 cv{}; 
					for (GLuint i = 0; i < 3; i++)
					{
						iss >> word;
						cv[i] = std::stof(word);
					}
					_vn.push_back(cv);
				}
				else if (typeOfElement == "vt") 
				{
					string word;
					glm::vec2 cv{};
					for (GLuint i = 0; i < 2; i++)
					{
						iss >> word;
						cv[i] = std::stof(word);
					}
					_vt.push_back(cv);
				}
				else if (typeOfElement == "f") 
				{
					auto splitted = Split(line, ' ');
					auto first = Split(splitted[1], '/');
					for (int i = 2; i < splitted.size() - 1; i++)
					{
						auto cur = Split(splitted[i], '/');
						auto next = Split(splitted[i+1], '/');

						Vertex vertex0;
						int positionIndex = std::stoi(first[0]) - 1;
						vertex0.Position = glm::vec3(_vertices[positionIndex][0], _vertices[positionIndex][1], _vertices[positionIndex][2]);
						if (first.size() > 1)
						{
							int textureIndex = std::stoi(first[1]) - 1;
							vertex0.TexCoords = glm::vec2(_vt[textureIndex][0], _vt[textureIndex][1]);
							if (first.size() > 2)
							{
								int normalIndex = std::stoi(first[2]) - 1;
								vertex0.Normal = glm::vec3(_vn[normalIndex][0], _vn[normalIndex][1], _vn[normalIndex][2]);
							}
						}
						vertices.push_back(vertex0);
						indices.push_back(indices.size());

						Vertex vertex1;
						positionIndex = std::stoi(cur[0]) - 1;
						vertex1.Position = glm::vec3(_vertices[positionIndex][0], _vertices[positionIndex][1], _vertices[positionIndex][2]);
						if (cur.size() > 1)
						{
							int textureIndex = std::stoi(cur[1]) - 1;
							vertex1.TexCoords = glm::vec2(_vt[textureIndex][0], _vt[textureIndex][1]);
							if (cur.size() > 2)
							{
								int normalIndex = std::stoi(cur[2]) - 1;
								vertex1.Normal = glm::vec3(_vn[normalIndex][0], _vn[normalIndex][1], _vn[normalIndex][2]);
							}
						}
						vertices.push_back(vertex1);
						indices.push_back(indices.size());

						Vertex vertex2;
						positionIndex = std::stoi(next[0]) - 1;
						vertex2.Position = glm::vec3(_vertices[positionIndex][0], _vertices[positionIndex][1], _vertices[positionIndex][2]);
						if (next.size() > 1)
						{
							int textureIndex = std::stoi(next[1]) - 1;
							vertex2.TexCoords = glm::vec2(_vt[textureIndex][0], _vt[textureIndex][1]);
							if (next.size() > 2)
							{
								int normalIndex = std::stoi(next[2]) - 1;
								vertex2.Normal = glm::vec3(_vn[normalIndex][0], _vn[normalIndex][1], _vn[normalIndex][2]);
							}
						}
						vertices.push_back(vertex2);
						indices.push_back(indices.size());
					}
				}
				else 
				{
					continue;
				}
			}
			

		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
		std::cout << "Total vertices count: " << vertices.size() << std::endl;
		InitializeBuffers();
		InitializeTexture(texturePath);
    }

    Mesh(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices, const std::vector<Texture>& textures)
    {
        this->vertices = vertices;
        this->indices = indices;
        this->texture = textures[0];

        InitializeBuffers();
    }

    virtual void Draw(ShaderProgram& shader) const
    {
        shader.Use();
		material->Use(&shader);
        {
			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
            sf::Texture::bind(NULL);
            
        }
        glUseProgram(0);
    }

	~Mesh()
	{
		delete material;
		Release();
	}
protected:
	void InitializeTexture(const char* texturePath)
	{
		material = new Material(texturePath);

		sf::Texture texture1;
		texture1.loadFromFile(texturePath);
		texture1.setRepeated(true);
		texture = { 0, "testing", texture1 };
	}

    virtual void InitializeBuffers()
    {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), &indices[0], GL_STATIC_DRAW);

        // Position
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
        glEnableVertexAttribArray(0);
        // Normal
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(1);
        // Texture
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(6 * sizeof(GLfloat)));
        glEnableVertexAttribArray(2);

        glBindVertexArray(0); // Unbind VAO
    }


    void Release()
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDeleteBuffers(1, &VBO);
        glDeleteVertexArrays(1, &VAO);
    }
};

#endif