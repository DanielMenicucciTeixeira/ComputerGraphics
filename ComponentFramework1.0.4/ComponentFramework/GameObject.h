#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <glew.h>
#include <vector>
#include "Matrix.h"
using namespace MATH;

class CubeMap;
class Camera;

class GameObject
{
	
protected:

	GLuint modelMatrixID;
	GLuint normalMatrixID;
	class Mesh *mesh;
	class Shader *shader;
	class Texture *texture;

protected:

	Matrix4 modelMatrix;
	Matrix4 BaseMatrix;
	Matrix4 PositionMatrix;
	Matrix4 RotationMatrix;

	CubeMap * EnviroMap = nullptr;
	int reflectionCoeficientID;
	//GLfloat ReflectionCoeficient = 0.0f;

public:
	GameObject(Vec3 position, Shader * _shader);
	GameObject(Mesh *mesh_, Shader *shader_, Texture *texture_);
	GameObject(Mesh *mesh_, Shader *shader_, const char texturePath[], CubeMap * enviroMap = nullptr, GLfloat reflectionCoeficient = 0.0f);

	~GameObject();
	virtual void Render(Camera * camera) const;
	virtual void Update(float deltaTime_);
	inline Shader* getShader() const { return shader; }
	inline void setModelMatrix(const Matrix4 &modelMatrix_) { modelMatrix = modelMatrix_; }
	inline Matrix4& getModelMatrix() { return modelMatrix; }

	void addRotatation(float angle, Vec3 orientation);
	void addTranslation(Vec3 direction, float distance = 1.0f, bool useDistance = false);
	Matrix4 GetRotationMatrix() { return RotationMatrix; }
	Matrix4 GetPositionMatrix() { return PositionMatrix; }
	void SetOriginalTransform(Vec3 position, float angle, Vec3 rotation, Vec3 scale);
	bool LoadCube(std::vector<const char*>  cubeTextures);

	Vec3 Position;

	Vec3 GetPosition();
	//inline int GetReflectionCoeficient() { return ReflectionCoeficient; }
	void SetTexture(Texture * TextureToSet);
	bool HasEnviromap = false;
	float deltaTime;

	GLuint enviroMapID;
};

#endif

