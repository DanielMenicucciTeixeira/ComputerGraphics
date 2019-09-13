#version 410
layout (location = 0) in  vec4 vVertex;
layout (location = 1) in  vec4 vNormal;

out vec3 vertNormal;
//out vec3 lightDir;
out vec3 lightDir[11];
out vec3 vertDir;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform mat3 normalMatrix;
//uniform vec3 lightPos;
//out int NumberOfLightSources;
uniform vec3 lightPos[10];
uniform int NumberOfLights;

void main() {
	vertNormal = normalMatrix * vNormal.xyz; /// Rotate the normal to the correct orientation 
	vec3 vertPos = vec3(viewMatrix * modelMatrix * vVertex); /// Creates the vertex position (-eyeDir)

	for(int i = 0; i < NumberOfLights; i++)
	{
		lightDir[i] = normalize(lightPos[i] +  -vertPos); /// Create the light direction for each light source
		//lightDir[i] = lightPos[i];
	}

	lightDir[10] = vec3 (NumberOfLights, 0.0, 0.0);
	//NumberOfLightSources = NumberOfLights;

	//lightDir = normalize(lightPos +  -vertPos); /// Create the light direction 
	vertDir = normalize(vertPos);
	gl_Position =  projectionMatrix * viewMatrix * modelMatrix * vVertex; 
}
