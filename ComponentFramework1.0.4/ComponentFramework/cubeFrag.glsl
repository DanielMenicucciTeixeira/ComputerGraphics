#version 410

out vec4 FragColor;

in vec3 TexCoords;

uniform samplerCube skybox;

void main()
{    
	mat3 scale = mat3(vec3(-1.0, 0.0, 0.0),
					  vec3(0.0, 1.0 ,0.0),
					  vec3(0.0, 0.0, 1.0));

    FragColor = texture(skybox, TexCoords * scale);
}