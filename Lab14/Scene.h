#ifndef SCENE_H
#define SCENE_H

#include "ShaderProgram.h"
#include "Mesh.h"
#include "SceneObject.h"
#include "Camera.h";
#include "Skybox.h"

#include "Lights.h"

class Scene
{
	DirectionalLight directionalLight;
	SpotLight spotLight;
	PointLight pointLight;
	PointLight pointLight2;
	PointLight pointLight3;
	PointLight pointLight4;
	PointLight pointLight5;

public:
	std::vector<ShaderProgram*> shaders;
	std::vector<SceneObject*> sceneObjects;
	Camera camera;
	Skybox skybox;


	Scene() 
	{
		skybox = Skybox();
		Camera camera();
		pointLight.position = { -4.0f, 2.0f, 0.5f };
		pointLight2.position = { 4.0f, 2.0f, 0.5f };
		pointLight3.position = { 12.0f, 2.0f, 0.5f };
		pointLight4.position = { 20.0f, 2.0f, 0.5f };
		pointLight5.position = { 28.0f, 2.0f, 0.5f };
	}

	void SetDirectionalLight(DirectionalLight dirLight)
	{
		this->directionalLight = dirLight;
	}

	void AddShaderProgram(ShaderProgram& sp)
	{
		shaders.push_back(&sp);
	}

	void AddSceneObject(SceneObject& so)
	{
		sceneObjects.push_back(&so);
	}
	void DeleteSceneObject()
	{
		sceneObjects.pop_back();
	}

	void Draw(float rotationAngle)
	{
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)800, 0.1f, 1000.0f);

		for (auto& shaderProgram : shaders) 
		{
			shaderProgram->Use();
			shaderProgram->SetUniformMat4("projection", projection);
			shaderProgram->SetUniformMat4("view", camera.GetViewMatrix());
			shaderProgram->SetUniformVec3("viewPos", camera.Position);

			shaderProgram->SetUniformFloat("shadeCount", 5.0f);


			shaderProgram->SetUniformVec3("directionalLight.direction", directionalLight.direction);
			shaderProgram->SetUniformVec3("directionalLight.ambient", directionalLight.ambient);
			shaderProgram->SetUniformVec3("directionalLight.diffuse", directionalLight.diffuse);
			shaderProgram->SetUniformVec3("directionalLight.specular", directionalLight.specular);


			shaderProgram->SetUniformVec3("pointLight.position", pointLight.position);
			shaderProgram->SetUniformVec3("pointLight.ambient", pointLight.ambient);
			shaderProgram->SetUniformVec3("pointLight.diffuse", pointLight.diffuse);
			shaderProgram->SetUniformVec3("pointLight.specular", pointLight.specular);
			shaderProgram->SetUniformVec3("pointLight.attenuation", pointLight.attenuation);


			shaderProgram->SetUniformVec3("pointLight2.position", pointLight2.position);
			shaderProgram->SetUniformVec3("pointLight2.ambient", pointLight2.ambient);
			shaderProgram->SetUniformVec3("pointLight2.diffuse", pointLight2.diffuse);
			shaderProgram->SetUniformVec3("pointLight2.specular", pointLight2.specular);
			shaderProgram->SetUniformVec3("pointLight2.attenuation", pointLight2.attenuation);

			shaderProgram->SetUniformVec3("pointLight3.position", pointLight3.position);
			shaderProgram->SetUniformVec3("pointLight3.ambient", pointLight3.ambient);
			shaderProgram->SetUniformVec3("pointLight3.diffuse", pointLight3.diffuse);
			shaderProgram->SetUniformVec3("pointLight3.specular", pointLight3.specular);
			shaderProgram->SetUniformVec3("pointLight3.attenuation", pointLight3.attenuation);

			shaderProgram->SetUniformVec3("pointLight4.position", pointLight4.position);
			shaderProgram->SetUniformVec3("pointLight4.ambient", pointLight4.ambient);
			shaderProgram->SetUniformVec3("pointLight4.diffuse", pointLight4.diffuse);
			shaderProgram->SetUniformVec3("pointLight4.specular", pointLight4.specular);
			shaderProgram->SetUniformVec3("pointLight4.attenuation", pointLight4.attenuation);

			shaderProgram->SetUniformVec3("pointLight5.position", pointLight5.position);
			shaderProgram->SetUniformVec3("pointLight5.ambient", pointLight5.ambient);
			shaderProgram->SetUniformVec3("pointLight5.diffuse", pointLight5.diffuse);
			shaderProgram->SetUniformVec3("pointLight5.specular", pointLight5.specular);
			shaderProgram->SetUniformVec3("pointLight5.attenuation", pointLight5.attenuation);

			shaderProgram->SetUniformVec3("spotLight.position", camera.Position);
			shaderProgram->SetUniformVec3("spotLight.direction", camera.Front);
			
			shaderProgram->SetUniformVec3("spotLight.ambient", spotLight.ambient);
			shaderProgram->SetUniformVec3("spotLight.diffuse", spotLight.diffuse);
			shaderProgram->SetUniformVec3("spotLight.specular", spotLight.specular);
			shaderProgram->SetUniformVec3("spotLight.attenuation", spotLight.attenuation);

			shaderProgram->SetUniformFloat("spotLight.innerAngle", 5.0f);
			shaderProgram->SetUniformFloat("spotLight.outerAngle", 9.0f);

			glUseProgram(0);
		}
		
		for (auto& sceneObject : sceneObjects) 
		{
			sceneObject->rotation.y = rotationAngle;
			sceneObject->Draw();
		}
		skybox.Draw(camera.GetViewMatrix(), projection);
	}

private:
	std::vector<Mesh> meshes;
};


#endif
