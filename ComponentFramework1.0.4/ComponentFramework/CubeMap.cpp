#include "CubeMap.h"
#include <SDL_image.h>
#include "ObjLoader.h"
#include "Mesh.h"
#include "Camera.h"
#include "MMath.h"


CubeMap::CubeMap()
{
	if (ObjLoader::loadOBJ("cube.obj") == false)
	{
		printf("Failed to load cube object for CubeMap!");
		return;
	}
	CubeMesh = new Mesh(GL_TRIANGLES, ObjLoader::vertices, ObjLoader::normals, ObjLoader::uvCoords);
}

CubeMap::CubeMap(std::vector<const char*> cubeTextures, Shader* cubeShader)
{
	CubeShader = cubeShader;
	LoadCube(cubeTextures);

	if (ObjLoader::loadOBJ("cube.obj") == false)
	{
		printf("Failed to load cube object for CubeMap!");
		return;
	}
	CubeMesh = new Mesh(GL_TRIANGLES, ObjLoader::vertices, ObjLoader::normals, ObjLoader::uvCoords);
	//SetUp();
}

bool CubeMap::LoadCube(std::vector<const char*>  cubeTextures)
{
	SDL_Surface *textureSurface = nullptr;
	int mode;

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	//Begin loading each of the CubesFaces, this is not in a loop due to the constante number of iterantions (6) and the fact that GL_TEXTURE_CUVE_MAP_* are frammer buffers, rather then enums,
	//and looping through them might compromise the use of this method in newer versions of OpenGL
	textureSurface = IMG_Load(cubeTextures[0]);
	if (textureSurface == nullptr) {
		return false;
	}
	mode = (textureSurface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, mode, textureSurface->w, textureSurface->h, 0, mode, GL_UNSIGNED_BYTE, textureSurface->pixels);
	SDL_FreeSurface(textureSurface);

	textureSurface = IMG_Load(cubeTextures[1]);
	if (textureSurface == nullptr) {
		return false;
	}
	mode = (textureSurface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, mode, textureSurface->w, textureSurface->h, 0, mode, GL_UNSIGNED_BYTE, textureSurface->pixels);
	SDL_FreeSurface(textureSurface);
;
	textureSurface = IMG_Load(cubeTextures[2]);
	if (textureSurface == nullptr) {
		return false;
	}
	mode = (textureSurface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, mode, textureSurface->w, textureSurface->h, 0, mode, GL_UNSIGNED_BYTE, textureSurface->pixels);
	SDL_FreeSurface(textureSurface);
;
	textureSurface = IMG_Load(cubeTextures[3]);
	if (textureSurface == nullptr) {
		return false;
	}
	mode = (textureSurface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, mode, textureSurface->w, textureSurface->h, 0, mode, GL_UNSIGNED_BYTE, textureSurface->pixels);
	SDL_FreeSurface(textureSurface);

	textureSurface = IMG_Load(cubeTextures[4]);
	if (textureSurface == nullptr) {
		return false;
	}
	mode = (textureSurface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, mode, textureSurface->w, textureSurface->h, 0, mode, GL_UNSIGNED_BYTE, textureSurface->pixels);
	SDL_FreeSurface(textureSurface);

	textureSurface = IMG_Load(cubeTextures[5]);
	if (textureSurface == nullptr) {
		return false;
	}
	mode = (textureSurface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, mode, textureSurface->w, textureSurface->h, 0, mode, GL_UNSIGNED_BYTE, textureSurface->pixels);
	SDL_FreeSurface(textureSurface);
	//End loading each cube face

	printf("All CubeMap Faces loaded successfully!\n");

	/// Wrapping and filtering options
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0); /// Unbind the textures
	return true;
}


CubeMap::~CubeMap()
{
	delete(CubeShader); CubeShader = nullptr;
	delete(CubeMesh); CubeMesh = nullptr;
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
	
}


void CubeMap::SetUp()
{
	unsigned int VertexID = 0;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(CubeVertices), CubeVertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(VertexID);
	glVertexAttribPointer(VertexID, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
}

void CubeMap::Render(Camera * camera)
{
	glDepthMask(GL_FALSE);
	glUseProgram(CubeShader->getProgram());
	glUniformMatrix4fv(CubeShader->getUniformID("projectionMatrix"), 1, GL_FALSE, camera->getProjectionMatrix());
	glUniformMatrix4fv(CubeShader->getUniformID("viewMatrix"), 1, GL_FALSE, camera->getViewMatrix());
	glBindVertexArray(vao);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	glDepthMask(GL_TRUE);
}

