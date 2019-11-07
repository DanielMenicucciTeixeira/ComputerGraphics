#version 410

layout (location = 0) in vec4 vVertex;

out vec3 TexCoords;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

void main()
{
    TexCoords = vec3(vVertex);
    gl_Position = projectionMatrix * viewMatrix * vVertex;
}