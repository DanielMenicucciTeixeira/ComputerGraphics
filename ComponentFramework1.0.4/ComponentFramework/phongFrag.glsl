#version 410
in  vec3 vertNormal;
//in  vec3 lightDir;
in vec3 lightDir[11];
in  vec3 vertDir;
out vec4 fragColor;


void main() { 
	const vec4 ks = vec4(0.6, 0.6, 0.6, 0.0);
	const vec4 kd = vec4(0.6, 0.6, 0.6, 0.0); /// const means it cannot be changed just like C++
	const vec4 ka = 0.1 * kd;
	
	/*
	if (lightDir[0] == vec3(3.0, 16.0, 0.0))
	{
		fragColor =  vec4(1.0,1.0,1.0,0.0);
	}
	else
	{
		fragColor =  ka;
	}
	*/
	
	
	
	/*
	float diff = max(dot(vertNormal, lightDir), 0.0);
	vec3 reflection = normalize(reflect(lightDir, vertNormal));
	float spec = max(dot(vertDir, reflection), 0.0);
	*/

	float diff[10];
	vec3 halfwayDir[10];
	vec3 blinnVec = normalize(vertNormal + vertDir);
	float spec;
	fragColor =  ka;
	for (int i; i < lightDir[10].x; i++)
	{
		halfwayDir[i] = normalize(vertDir + lightDir[i]);
		spec = max(dot(blinnVec, halfwayDir[i]), 0.0);
		if(diff[i] > 0.0){
			spec = pow(spec,4*14.0);
		}
		fragColor += (diff[i] * kd) + ( spec * ks);
	}
}

