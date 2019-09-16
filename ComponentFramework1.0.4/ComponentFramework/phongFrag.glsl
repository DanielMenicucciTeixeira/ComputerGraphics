#version 410
in vec3 vertNormal;
in vec3 lightDir[11];
in vec3 vertDir;
in vec4 Colour[10];
in float Intensity[10];

out vec4 fragColor;



void main() 
{
	/*
	const vec4 ks = vec4(0.6, 0.6, 0.6, 0.0);
	const vec4 kd = vec4(0.6, 0.6, 0.6, 0.0); // const means it cannot be changed just like C++
	const vec4 ka = 0.1 * kd;
	*/

	vec4 ks;
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
	}
}

