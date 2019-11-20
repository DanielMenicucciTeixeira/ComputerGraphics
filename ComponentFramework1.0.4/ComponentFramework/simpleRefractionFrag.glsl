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
	float ratio = 1.0/1.309;
	vec3 viewVector = normalize(Position + CameraPosition);
	vec3 RefractionVector = refract(Position, normalize(Normal), ratio);
	FragmentColor = texture(enviroMap, RefractionVector);
	FragmentColor = mix(FragmentColor, vec4(0.2f, 0.2f, 1.0f, 0.0f), 0.3f);
	//FragmentColor = vec4 (1.0f, 0.0f, 0.0f, 0.0f);FragmentColor = texture(enviroMap, Normal);
}
