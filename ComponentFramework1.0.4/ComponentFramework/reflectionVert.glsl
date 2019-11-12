#version 410

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 normal;
layout (location = 2) in vec2 textureCoords;

out vec3 Normal;
out vec2 TextureCoords;
out vec3 Direction;
out vec3 ReflectionVector;
out vec3 lightDir[11];
out vec4 Colour[10];
out int ReflectionCoeficient;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat3 normalMatrix;
//uniform vec3 cameraPositoin;
uniform vec3 LightPos[10];
uniform vec4 colour[10];
uniform int NumberOfLights;
//uniform int reflectionCoeficient;

void main()
{
	TextureCoords = textureCoords;
	Colour = colour;
	Normal = normalMatrix * normal.xyz; // Rotate the normal to the correct orientation 
	vec3 vertPos = vec3(viewMatrix * modelMatrix * position); // Creates the vertex position (-eyeDir)
	for(int i = 0; i < NumberOfLights; i ++)
	{
		lightDir[i] = normalize(LightPos[i] +  -vertPos); // Create the light direction
	}
	
	//I use the last variable of the lightDir array to pass the number of light sources to the FragShader because I cannot pass it through an "out int"
	lightDir[10] = vec3(NumberOfLights, 0.0f, 0.0f);
	Direction = normalize(vertPos);
	gl_Position =  projectionMatrix * viewMatrix * modelMatrix * position;

	vec3 unitNormal = normalize(normal.xyz);
	vec3 viewVector = normalize((modelMatrix * position).xyz /*- cameraPositoin*/);
	ReflectionVector = reflect(viewVector, unitNormal);
}