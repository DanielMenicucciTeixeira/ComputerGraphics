#ifndef MESH_H
#define MESH_H
#include <Vector>
#include <glew.h>
#include "Vector.h"

using namespace MATH;

class Mesh {
public:
	GLenum drawmode;
	std::vector<Vec3> vertices;
	std::vector<Vec3> normals;
	std::vector<Vec2> uvCoords;
	std::vector<GLuint> indices;

	Mesh(GLenum drawmode_, std::vector<Vec3>&, std::vector<Vec3>&, std::vector<Vec2>&);
	~Mesh();
	void Render() const;
	inline GLuint GetVAO() const { return vao; }
	inline GLenum GetDrawMode() const { return drawmode; }
	inline std::vector<Vec3> GetVertices() const { return vertices; }


private:
	GLuint vao, vbo;
	void setupMesh();
};

#endif
