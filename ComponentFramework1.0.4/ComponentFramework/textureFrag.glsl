#version 410
in vec3 vertNormal;
in vec3 lightDir[11];
in vec3 vertDir;
in vec2 uvCoords;
in vec4 Colour[10];
out vec4 fragColor;

uniform sampler2D myTexture; 

void main() 
{ 
	fragColor = vec4 (0.0f);
	float spec = 0.0;
	vec4 specLightColor;
	vec3 halfwayDir[10];
	vec3 blinnVec = normalize(vertNormal + vertDir);
	float specularStrength = 0.2;
	
	for(int i = 0; i < lightDir[10].x; i ++)
	{
		spec = 0.0f;
		float diff = max(dot(vertNormal, lightDir[i]), 0.0);
		if (diff < 0.0f) diff = 0.0f;
		vec4 textureColor = texture(myTexture, uvCoords);
		if(diff > 0.0)
		{
		halfwayDir[i] = normalize(vertDir + lightDir[i]);
		spec = max(dot(blinnVec, halfwayDir[i]), 0.0);
		spec = pow(spec,12.0);
		}

		float ka = 0.1;
		fragColor += (ka + diff + (spec * specularStrength)) * textureColor * Colour[i];
	}
	
	fragColor = texture(myTexture, uvCoords);
} 

