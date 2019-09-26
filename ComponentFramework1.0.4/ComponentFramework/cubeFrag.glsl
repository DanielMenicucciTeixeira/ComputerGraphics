#version 410

in vec3 textureDir; // direction vector representing a 3D texture coordinate
uniform samplerCube cubemap; // cubemap texture sampler
out vec4 FragColor;

void main()
{             
    FragColor = texture(cubemap, textureDir);
}  