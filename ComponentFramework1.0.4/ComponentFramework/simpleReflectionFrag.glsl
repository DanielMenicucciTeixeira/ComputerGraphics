#version 410

out vec4 FragmentColor;

in vec3 Normal;
in vec3 Direction;
//in vec3 ReflectionVector;
in vec3 Position;
in vec3 CameraPosition;

uniform samplerCube enviroMap;

void main()
{
	vec3 viewVector = normalize(Position + CameraPosition);
    vec3 ReflectionVector = reflect(viewVector, normalize(Normal));
	FragmentColor = texture(enviroMap, ReflectionVector);
	//FragmentColor = vec4 (1.0f, 0.0f, 0.0f, 0.0f);FragmentColor = texture(enviroMap, Normal);
}
