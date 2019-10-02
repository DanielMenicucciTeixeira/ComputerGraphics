#ifndef CUBEMAP_H
#define CUBEMAP_H

#include <glew.h>
#include <vector>
#include "Shader.h"
#include "MMath.h"

class Camera;

class CubeMap
{
private:
	Shader* CubeShader = nullptr;

	float CubeVertices[108] = {
		// positions, each block is one of the cubes faces, each line the three coord of each of the faces vertexes          
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f
	};
	float SuperVertices[108];
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
	float Scale = 1.0f;

	class Mesh* CubeMesh = nullptr;

	Shader* GetShader() { return CubeShader; }
	inline float* GetSkyboxVertices() { return CubeVertices; }
	void SetUp();
	void Render(Camera * camera);
};
#endif

