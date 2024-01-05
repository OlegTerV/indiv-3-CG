#version 330 core
layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 normals;
layout (location = 2) in vec2 textPosition;
layout (location = 3) in mat4 instancedModelMatrix;

out vec2 TexCoord;

uniform mat4 projection;
uniform mat4 view;
uniform float rotationY;

void main() 
{
    vec3 rotatedAlongAxis = mat3(
            cos(rotationY),  0, sin(rotationY),
            0,               1, 0,
            -sin(rotationY), 0, cos(rotationY))
        * vertexPosition;
    mat4 position = mat4(
            cos(rotationY),  0, sin(rotationY), 0,
            0,               1, 0,              0,
            -sin(rotationY), 0, cos(rotationY), 0,
            0,               0, 0,              1) 
        * instancedModelMatrix ;
    gl_Position = projection * view * position * vec4(rotatedAlongAxis, 1.0f); 
    TexCoord = textPosition;
}