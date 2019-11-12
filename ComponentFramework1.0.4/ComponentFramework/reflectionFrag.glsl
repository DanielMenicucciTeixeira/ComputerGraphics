#version 410

in vec3 Normal;
in vec2 TextureCoords;
in vec3 Direction;
in vec3 ReflectionVector;
in vec3 lightDir[11];
in vec4 Colour[10];
in float ReflectionCoeficient;
out vec4 fragColor;

uniform sampler2D myTexture;
uniform samplerCube enviroMap;

void main() 
{ 
	fragColor = vec4 (0.0f);
	float spec = 0.0;
	vec4 specLightColor;
	vec3 halfwayDir[10];
	vec3 blinnVec = normalize(Normal + Direction);
	float specularStrength = 0.2;
	//float reflectionCoeficient;
	
	for(int i = 0; i < lightDir[10].x; i ++)
	{
		spec = 0.0f;
		float diff = max(dot(Normal, lightDir[i]), 0.0);
		if (diff < 0.0f) diff = 0.0f;
		vec4 textureColor = texture(myTexture, TextureCoords);
		if(diff > 0.0)
		{
		halfwayDir[i] = normalize(Direction + lightDir[i]);
		spec = max(dot(blinnVec, halfwayDir[i]), 0.0);
		spec = pow(spec,12.0);
	}

		float ka = 0.1;
		fragColor += (ka + diff + (spec * specularStrength)) * textureColor * Colour[i];
	}

	//if (ReflectionCoeficient < 0.0f || ReflectionCoeficient > 1.0f) reflectionCoeficient = 1.0f;
	//else reflectionCoeficient = ReflectionCoeficient;

		//vec4 ReflectionColor = texture(enviroMap, ReflectionVector);
		//fragColor = mix(fragColor, ReflectionColor, 0.6); 
} 
