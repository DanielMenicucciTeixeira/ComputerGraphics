#ifndef CUBEMAP_H
#define CUBEMAP_H

#include <glew.h>
class CubeMap
{
protected:
	GLuint textureID[6];

public:
	CubeMap();
	bool LoadCube(const char* filename[6]);
	inline GLuint getTextureID(int CubeFace) const { return textureID[CubeFace]; }
	~CubeMap();
};
#endif

