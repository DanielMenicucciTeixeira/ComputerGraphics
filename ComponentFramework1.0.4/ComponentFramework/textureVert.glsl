#version 410
layout (location = 0) in  vec4 vVertex;
layout (location = 1) in  vec4 vNormal;
layout (location = 2) in  vec2 texCoords;


out vec3 vertNormal;
out vec3 vertDir; 
out vec2 uvCoords;
out vec3 lightDir[11];
out vec4 Colour[10];

uniform int NumberOfLights;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform mat3 normalMatrix;
uniform vec3 lightPos[10];
uniform vec4 lightColour[10];

void main() 
{
	uvCoords = texCoords;
	Colour = lightColour;
	vertNormal = normalMatrix * vNormal.xyz; // Rotate the normal to the correct orientation 
	vec3 vertPos = vec3(viewMatrix * modelMatrix * vVertex); // Creates the vertex position (-eyeDir)
	for(int i = 0; i < NumberOfLights; i ++)
	{
		lightDir[i] = normalize(lightPos[i] +  -vertPos); // Create the light direction
	}
	
	//I use the last variable of the lightDir array to pass the number of light sources to the FragShader because I cannot pass it through an "out int"
	lightDir[10] = vec3(NumberOfLights, 0.0f, 0.0f);
	vertDir = normalize(vertPos);
	gl_Position =  projectionMatrix * viewMatrix * modelMatrix * vVertex; 
}
