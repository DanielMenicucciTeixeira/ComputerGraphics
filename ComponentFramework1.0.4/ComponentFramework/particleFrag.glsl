#version 410

out vec4 FragmentColor;

in vec3 Normal;
in vec3 Direction;
in vec3 Position;

void main()
{
	FragmentColor = vec4(1.0f, 0.0f, 0.0f, 0.0f);
}