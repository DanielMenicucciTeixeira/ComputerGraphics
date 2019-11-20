#version 410

out vec4 FragmentColor;

in vec3 Normal;
in vec3 Direction;
//in vec3 ReflectionVector;
in vec3 Position;
in vec3 CameraPosition;
in float AngleOfInsidenseCos;

uniform samplerCube enviroMap;

void main()
{
	float refractionRatio = 1.0/1.309;
	float reflectionRation = AngleOfInsidenseCos;

	vec3 viewVector = normalize(Position + CameraPosition);

    vec3 ReflectionVector = reflect(viewVector, normalize(Normal));
	vec3 RefractionVector = refract(Position, normalize(Normal), refractionRatio);
	vec4 RefractionColor = texture(enviroMap, RefractionVector);
	vec4 ReflectionColor = texture(enviroMap, ReflectionVector);
	FragmentColor = mix(RefractionColor, ReflectionColor, reflectionRation);
	FragmentColor = mix(FragmentColor, vec4(0.2f, 0.2f, 1.0f, 0.0f), 0.2f);
	//FragmentColor = vec4 (1.0f, 0.0f, 0.0f, 0.0f);FragmentColor = texture(enviroMap, Normal);
}
