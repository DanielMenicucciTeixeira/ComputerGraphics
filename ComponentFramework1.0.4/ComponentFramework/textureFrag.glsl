#version 410
in vec3 vertNormal;
in vec3 lightDir[11];
in vec3 vertDir;
in vec2 uvCoords;
in vec4 Colour[10];
in float Intensity[10];
out vec4 fragColor;

uniform sampler2D myTexture; 

void main() 
{ 
	fragColor = vec4 (0.0f);
	float spec = 0.0;
	vec4 specLightColor;
	vec3 halfwayDir[10];
	vec3 blinnVec = normalize(vertNormal + vertDir);
	for(int i = 0; i < lightDir[10].x; i ++)
	{
		//const vec4 specLightColor = vec4 (0.2f, 0.2f, 0.2f, 0.0f);
		float diff = max(dot(vertNormal, lightDir[i]), 0.0);
		vec4 textureColor = texture(myTexture, uvCoords);
		/*if(diff > 0.0)
		{
			vec3 reflection = normalize(reflect(lightDir[i], vertNormal));
			spec = max(dot(vertDir, reflection), 0.0);
			spec = pow(spec,12.0);
		}*/
		halfwayDir[i] = normalize(vertDir + lightDir[i]);
		spec = max(dot(blinnVec, halfwayDir[i]), 0.0);
		if(diff > 0.0)
		{
			spec = pow(spec,4*12.0);
		}

		vec4 ka = 0.1 * textureColor ;
		//fragColor +=  ka + (diff * textureColor)  + (spec * specLightColor);
		fragColor += ka + (diff * textureColor)  + (spec * Colour[i]);
	}
		
	
	/*vec4 ks;
	vec4 kd;
	vec4 ka;
	float diff[10];
	vec3 halfwayDir[10];
	vec3 blinnVec = normalize(vertNormal + vertDir);
	float spec;
	fragColor = vec4(0.0,0.0,0.0,0.0);
	//I use the last variable of lightDir array to pass the number of lights from the VertShader here
	for (int i; i < lightDir[10].x; i++)
	{
		ks = Colour[i];
		kd = Colour[i];
		ka = 0.1 * kd;

		halfwayDir[i] = normalize(vertDir + lightDir[i]);
		spec = max(dot(blinnVec, halfwayDir[i]), 0.0);
		if(diff[i] > 0.0)
		{
			spec = pow(spec,4*14.0);
		}
		fragColor += ka + (diff[i] * kd) + ( spec * ks);
	}*/
} 

