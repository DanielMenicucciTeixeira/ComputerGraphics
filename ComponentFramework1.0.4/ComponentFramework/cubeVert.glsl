#version 410

layout (location = 0) in vec3 TexturePos;

out vec3 TexCoords;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

void main()
{
    TexCoords = TexturePos;
    gl_Position = projectionMatrix * viewMatrix * vec4(TexturePos, 1.0);
}  