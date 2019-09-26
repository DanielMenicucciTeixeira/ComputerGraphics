#include "CubeMap.h"
#include <SDL_image.h>


CubeMap::CubeMap()
{
}

bool CubeMap::LoadCube(const char * filename[6])
{
	SDL_Surface *textureSurface = nullptr;
	int mode;

	glGenTextures(1, &textureID[0]);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID[0]);
	textureSurface = IMG_Load(filename[0]);
	if (textureSurface == nullptr) {
		return false;
	}
	mode = (textureSurface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, mode, textureSurface->w, textureSurface->h, 0, mode, GL_UNSIGNED_BYTE, textureSurface->pixels);
	SDL_FreeSurface(textureSurface);

	glGenTextures(1, &textureID[1]);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID[1]);
	textureSurface = IMG_Load(filename[1]);
	if (textureSurface == nullptr) {
		return false;
	}
	mode = (textureSurface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, mode, textureSurface->w, textureSurface->h, 0, mode, GL_UNSIGNED_BYTE, textureSurface->pixels);
	SDL_FreeSurface(textureSurface);

	glGenTextures(1, &textureID[2]);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID[2]);
	textureSurface = IMG_Load(filename[2]);
	if (textureSurface == nullptr) {
		return false;
	}
	mode = (textureSurface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, mode, textureSurface->w, textureSurface->h, 0, mode, GL_UNSIGNED_BYTE, textureSurface->pixels);
	SDL_FreeSurface(textureSurface);

	glGenTextures(1, &textureID[3]);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID[3]);
	textureSurface = IMG_Load(filename[3]);
	if (textureSurface == nullptr) {
		return false;
	}
	mode = (textureSurface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, mode, textureSurface->w, textureSurface->h, 0, mode, GL_UNSIGNED_BYTE, textureSurface->pixels);
	SDL_FreeSurface(textureSurface);

	glGenTextures(1, &textureID[4]);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID[4]);
	textureSurface = IMG_Load(filename[4]);
	if (textureSurface == nullptr) {
		return false;
	}
	mode = (textureSurface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, mode, textureSurface->w, textureSurface->h, 0, mode, GL_UNSIGNED_BYTE, textureSurface->pixels);
	SDL_FreeSurface(textureSurface);

	glGenTextures(1, &textureID[5]);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID[5]);
	textureSurface = IMG_Load(filename[5]);
	if (textureSurface == nullptr) {
		return false;
	}
	mode = (textureSurface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, mode, textureSurface->w, textureSurface->h, 0, mode, GL_UNSIGNED_BYTE, textureSurface->pixels);
	SDL_FreeSurface(textureSurface);


	

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
}
