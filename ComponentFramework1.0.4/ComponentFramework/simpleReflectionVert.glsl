#version 410

layout (location = 0) in  vec4 position;
layout (location = 1) in  vec4 normal;

out vec3 Normal;
out vec3 Direction;
//out vec3 ReflectionVector;
out vec3 Position;
out vec3 CameraPosition;
out float AngleOfInsidenseCos;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform mat4 cameraPosition;
uniform float time;


void main()
{
	float distortionLevel = 0.0;
	float distortionSpeed = 5.0;
	CameraPosition = vec3(cameraPosition[3][0],cameraPosition[3][1],cameraPosition[3][2]);
	
	AngleOfInsidenseCos = dot(normalize(CameraPosition), normalize(normal.xyz));
	Normal = mat3(transpose(inverse(modelMatrix))) * normal.xyz;
	Position = vec3(position + (distortionLevel * cos(time) * normalize(normal)));
	//Position = vec3(modelMatrix * position);
	
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position + (distortionLevel * cos(time * distortionSpeed) * normalize(normal)));
}