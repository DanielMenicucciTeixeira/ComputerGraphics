#version 410

layout (location = 0) in vec3 vVertex;

out vec3 TexCoords;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

void main()
{
    TexCoords = vVertex;
	vec4 WorldViewPosition = projectionMatrix * viewMatrix * vec4(vVertex, 1.0);
    gl_Position = WorldViewPosition;
	//gl_Position = projectionMatrix * viewMatrix * vec4(vVertex, 1.0);
}