#version 410

layout (location = 0) in  vec4 position;
layout (location = 1) in  vec4 normal;

out vec3 Normal;
out vec3 Direction;
out vec3 Position;
out vec3 CameraPosition;
out float AngleOfInsidenseCos;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform mat4 cameraPosition;
uniform vec3 directionArray[500];
uniform float time;
uniform float lifeSpan;
uniform int verticalInstances;
uniform int horizontalInstances;
uniform float airDrag;
uniform float speed;
uniform float gravity;
uniform float deltaTime;

int cycleCount = 0;

void main()
{
	CameraPosition = vec3(cameraPosition[3][0],cameraPosition[3][1],cameraPosition[3][2]);
	AngleOfInsidenseCos = dot(normalize(CameraPosition), normalize(normal.xyz));


	int arrayPosition = gl_InstanceID - cycleCount * horizontalInstances;
	while(arrayPosition >= horizontalInstances)
	{
		cycleCount ++;
		arrayPosition = gl_InstanceID - cycleCount * horizontalInstances;
	}

	float realTime = time + float(lifeSpan * cycleCount)/float(verticalInstances);
	if(realTime > lifeSpan)
	{
		realTime = realTime - lifeSpan;
	}
	
	float displacement = speed * realTime;
	vec3 movement = directionArray[arrayPosition] * displacement + vec3(0,-1,0) * gravity * realTime * realTime * 0.5f ;
	Normal = mat3(transpose(inverse(modelMatrix))) * normal.xyz;
	Position = vec3(position) + movement;
	
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * (position + vec4(movement, 1.0));
}