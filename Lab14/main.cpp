#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <string>
#include "ShaderProgram.h"
#include "Mesh.h"
#include "InstancedMesh.h"
#include "SceneObject.h"
#include "Scene.h"



const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;
// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCREEN_WIDTH / 2.0f;
float lastY = SCREEN_HEIGHT / 2.0f;
bool firstMouse = true;
int ff = 1;

void random() {

}

int main()
{
    sf::Window window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Lab14", sf::Style::Default, sf::ContextSettings(24));
    window.setVerticalSyncEnabled(true);
    window.setActive(true);
    glewInit();
    glEnable(GL_DEPTH_TEST);

    Scene mainScene = Scene();

    ShaderProgram phongShader = ShaderProgram("Shaders//sun.vs", "Shaders//sun.frag");
    mainScene.AddShaderProgram(phongShader);
    ShaderProgram toonShader = ShaderProgram("Shaders//sun.vs", "Shaders//toon.frag");
    mainScene.AddShaderProgram(toonShader);
    //TODO
    ShaderProgram olegShader = ShaderProgram("Shaders//sun.vs", "Shaders//minnaert.frag");
    mainScene.AddShaderProgram(olegShader);
    ShaderProgram planetShader = ShaderProgram("Shaders//planet.vs", "Shaders//planet.frag");
    mainScene.AddShaderProgram(planetShader);

    Mesh _barn = Mesh("Meshes//Barn//barn.obj", "Meshes//Barn//barn.jpg");
    SceneObject barn = SceneObject(&_barn, &phongShader);
    barn.scale *= 0.5f;
    barn.position = { 0.0f, 0.0f, 0.0f };
    mainScene.AddSceneObject(barn);

    SceneObject barn2 = SceneObject(&_barn, &phongShader);
    barn2.scale *= 0.5f;
    barn2.position = { 8.0f, 0.0f, 0.0f };
    mainScene.AddSceneObject(barn2);

    SceneObject barn3 = SceneObject(&_barn, &phongShader);
    barn3.scale *= 0.5f;
    barn3.position = { 16.0f, 0.0f, 0.0f };
    mainScene.AddSceneObject(barn3);

    SceneObject barn4 = SceneObject(&_barn, &phongShader);
    barn4.scale *= 0.5f;
    barn4.position = { 24.0f, 0.0f, 0.0f };
    mainScene.AddSceneObject(barn4);

    SceneObject barn5 = SceneObject(&_barn, &phongShader);
    barn5.scale *= 0.5f;
    barn5.position = { -8.0f, 0.0f, 0.0f };
    mainScene.AddSceneObject(barn5);

    SceneObject barn6 = SceneObject(&_barn, &phongShader);
    barn6.scale *= 0.5f;
    barn6.position = { -16.0f, 0.0f, 0.0f };
    mainScene.AddSceneObject(barn6);

    SceneObject barn7 = SceneObject(&_barn, &phongShader);
    barn7.scale *= 0.5f;
    barn7.position = { -24.0f, 0.0f, 0.0f };
    mainScene.AddSceneObject(barn7);

    Mesh _tree = Mesh("Meshes//tree.obj", "Meshes//tree.jpg");
    SceneObject tree = SceneObject(&_tree, &phongShader);
    tree.scale *= 0.1f;
    tree.position = { 0.0f, 8.0f, 0.0f };
    mainScene.AddSceneObject(tree);

    Mesh _air = Mesh("Meshes//air2.obj", "Meshes//air2.jpg");
    SceneObject air = SceneObject(&_air, &phongShader);
    air.scale *= 0.03f;
    air.position = { 0.0f, 27.0f, 0.0f };
    mainScene.AddSceneObject(air);

    Mesh plane = Mesh("Meshes//Ground//cube.obj", "Meshes//Ground//grass.png");
    SceneObject ground = SceneObject(&plane, &phongShader);
    ground.scale = { 200.0f, 0.2f, 200.0f };
    mainScene.AddSceneObject(ground);

    Mesh _snowman = Mesh("Meshes//Snowman//snowman.obj", "Meshes//Snowman//snowman.png");
    SceneObject snowman = SceneObject(&_snowman, &phongShader);
    snowman.position = { 0.0f, 0.0f, -5.0f };
    mainScene.AddSceneObject(snowman);

    SceneObject snowman1 = SceneObject(&_snowman, &phongShader);
    snowman1.position = { 8.0f, 0.0f, -5.0f };
    mainScene.AddSceneObject(snowman1);

    SceneObject snowman2 = SceneObject(&_snowman, &phongShader);
    snowman2.position = { 16.0f, 0.0f, -5.0f };
    mainScene.AddSceneObject(snowman2);

    SceneObject snowman3 = SceneObject(&_snowman, &phongShader);
    snowman3.position = { 24.0f, 0.0f, -5.0f };
    mainScene.AddSceneObject(snowman3);

    SceneObject snowman4 = SceneObject(&_snowman, &phongShader);
    snowman4.position = { -8.0f, 0.0f, -5.0f };
    mainScene.AddSceneObject(snowman4);

    SceneObject snowman5 = SceneObject(&_snowman, &phongShader);
    snowman5.position = { -16.0f, 0.0f, -5.0f };
    mainScene.AddSceneObject(snowman5);

    SceneObject snowman6 = SceneObject(&_snowman, &phongShader);
    snowman6.position = { -24.0f, 0.0f, -5.0f };
    mainScene.AddSceneObject(snowman6);

    Mesh _lamp = Mesh("Meshes//Lamp//lamp.obj", "Meshes//Lamp//lamp.jpg");
    SceneObject lamp = SceneObject(&_lamp, &olegShader);
    lamp.position = { -4.0f, 0.0f, 0.5f };
    mainScene.AddSceneObject(lamp);

    //Mesh _lamp = Mesh("Meshes//Lamp//lamp.obj", "Meshes//Lamp//lamp.jpg");
    SceneObject lamp2 = SceneObject(&_lamp, &olegShader);
    lamp2.position = { 4.0f, 0.0f, 0.5f };
    mainScene.AddSceneObject(lamp2);

    SceneObject lamp3 = SceneObject(&_lamp, &olegShader);
    lamp3.position = { 12.0f, 0.0f, 0.5f };
    mainScene.AddSceneObject(lamp3);

    SceneObject lamp4 = SceneObject(&_lamp, &olegShader);
    lamp4.position = { 20.0f, 0.0f, 0.5f };
    mainScene.AddSceneObject(lamp4);

    SceneObject lamp5 = SceneObject(&_lamp, &olegShader);
    lamp5.position = { 28.0f, 0.0f, 0.5f };
    mainScene.AddSceneObject(lamp5);

    Mesh mesh = Mesh("Meshes//cube.obj", "Meshes//Snowman//snowman.png");
    SceneObject sun = SceneObject(&mesh, &phongShader);
    sun.scale = sun.scale * 0.25f;


    Mesh _present = Mesh("Meshes//present.obj", "Meshes//present.jpg");
    SceneObject f = SceneObject(&_present, &olegShader); 
    f.scale = f.scale * 0.01f;
    f.position = air.position;

    sf::Time elapsedTime;
    sf::Clock clock;
    GLfloat rotationAngle = 0.0f;
    bool running = true;
    while (running)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                running = false;
            }
            else if (event.type == sf::Event::Resized)
            {
                // Изменён размер окна, надо поменять и размер области Opengl отрисовки
                glViewport(0, 0, event.size.width, event.size.height);
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code) {
                case (sf::Keyboard::W): mainScene.camera.ProcessKeyboard(FORWARD, elapsedTime.asSeconds()); break;
                case (sf::Keyboard::S): mainScene.camera.ProcessKeyboard(BACKWARD, elapsedTime.asSeconds()); break;
                case (sf::Keyboard::A): mainScene.camera.ProcessKeyboard(LEFT, elapsedTime.asSeconds()); break;
                case (sf::Keyboard::D): mainScene.camera.ProcessKeyboard(RIGHT, elapsedTime.asSeconds()); break;
                case (sf::Keyboard::R): mainScene.camera.ProcessKeyboard(UP, elapsedTime.asSeconds()); break;
                case (sf::Keyboard::F): mainScene.camera.ProcessKeyboard(DOWN, elapsedTime.asSeconds()); break;
                case (sf::Keyboard::J): mainScene.camera.ProcessKeyboard(LROTATION, elapsedTime.asSeconds()); break;
                case (sf::Keyboard::L): mainScene.camera.ProcessKeyboard(RROTATION, elapsedTime.asSeconds()); break;
                case (sf::Keyboard::I): mainScene.camera.ProcessKeyboard(UPROTATION, elapsedTime.asSeconds()); break;
                case (sf::Keyboard::K): mainScene.camera.ProcessKeyboard(DOWNROTATION, elapsedTime.asSeconds()); break;
                case (sf::Keyboard::Q): 
                    mainScene.AddSceneObject(f);                 
                    ; break;


                case (sf::Keyboard::V):air.position += glm::vec3(0.5f, 0.0f, 0.0f); break;
                case (sf::Keyboard::M): air.position += glm::vec3(-0.5f, 0.0f, 0.0f); break;
                case (sf::Keyboard::B): air.position += glm::vec3(0.0f, 0.0f, 0.5f); break;
                case (sf::Keyboard::N): air.position += glm::vec3(0.0f, 0.0f, - 0.5f); break;
                case (sf::Keyboard::H): air.position += glm::vec3(0.0f, 0.5f, 0.0f); break;
                case (sf::Keyboard::Y): air.position += glm::vec3(0.0f, -0.5f, 0.0f); break;
                default: break;
                }
            }
        }
        elapsedTime = clock.getElapsedTime();
        if (elapsedTime > sf::milliseconds(5))
        {
            f.position -= glm::vec3(0.0f,0.1f, 0.0f);
            if (f.position.y ==  0.0f) {
                //mainScene.DeleteSceneObject();
                //mainScene.AddSceneObject(gift);
            }
            rotationAngle += 0.01f;
            if (rotationAngle > 360)
                rotationAngle = 360.0f;
            elapsedTime = clock.restart();
        }
        //glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        mainScene.Draw(rotationAngle);

        window.display();




    }
    window.close();
    return 0;
}
