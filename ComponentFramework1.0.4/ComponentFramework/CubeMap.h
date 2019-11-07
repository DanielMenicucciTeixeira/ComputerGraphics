#ifndef CUBEMAP_H
#define CUBEMAP_H

#include <glew.h>
#include <vector>
#include "Shader.h"

class Camera;

class CubeMap
{
private:
	Shader* CubeShader = nullptr;

	unsigned int vao;
	unsigned int vbo;

protected:
	GLuint textureID;

public:
	CubeMap();
	CubeMap(std::vector<const char*> cubeTextures, Shader* cubeShader = new Shader("cubeVert.glsl", "cubeFrag.glsl"));
	bool LoadCube(std::vector<const char*> cubeTextures);
	inline GLuint getTextureID() const { return textureID; }
	~CubeMap();

	class Mesh* CubeMesh = nullptr;

	Shader* GetShader() { return CubeShader; }
	void Render(Camera * camera);
};
#endif

