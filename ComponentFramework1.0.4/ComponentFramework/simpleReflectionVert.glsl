#version 410

layout (location = 0) in  vec4 position;
layout (location = 1) in  vec4 normal;

out vec3 Normal;
out vec3 Direction;
out vec3 ReflectionVector;
out vec3 Position;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform vec3 cameraPosition;


void main()
{
	Normal = mat3(transpose(inverse(modelMatrix))) * normal.xyz;
	//Normal = mat3(modelMatrix) * normal.xyz;
	Position = vec3(modelMatrix * position);
	vec3 unitNormal = normalize(Normal);
	vec3 viewVector = normalize(Position - cameraPosition);
	ReflectionVector = reflect(viewVector, unitNormal);

	Position = vec3(position);

	vec3 vertexPositon = vec3(viewMatrix * modelMatrix * position);
	Direction = normalize(vertexPositon);

	gl_Position =  projectionMatrix * viewMatrix * modelMatrix * position;
}