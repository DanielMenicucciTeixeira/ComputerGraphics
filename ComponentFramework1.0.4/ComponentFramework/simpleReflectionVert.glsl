#version 410

layout (location = 0) in  vec4 position;
layout (location = 1) in  vec4 normal;

out vec3 Normal;
out vec3 Direction;
//out vec3 ReflectionVector;
out vec3 Position;
out vec3 CameraPosition;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform mat4 cameraPosition;


void main()
{
	CameraPosition = vec3(cameraPosition[3][0],cameraPosition[3][1],cameraPosition[3][2]);
	Normal = mat3(transpose(inverse(modelMatrix))) * normal.xyz;
	Position = vec3(modelMatrix * position);

	gl_Position =  projectionMatrix * viewMatrix * modelMatrix * position;
}