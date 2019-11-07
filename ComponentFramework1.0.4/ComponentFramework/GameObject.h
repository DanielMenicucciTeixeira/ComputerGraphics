#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <glew.h>
#include "Matrix.h"
using namespace MATH;
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

public:
	GameObject(Vec3 position, Shader * _shader);
	GameObject(Mesh *mesh_, Shader *shader_, Texture *texture_);
	GameObject(Mesh *mesh_, Shader *shader_, const char texturePath[]);

	~GameObject();
	virtual void Render() const;
	virtual void Update(float deltaTime_);
	inline Shader* getShader() const { return shader; }
	inline void setModelMatrix(const Matrix4 &modelMatrix_) { modelMatrix = modelMatrix_; }
	inline Matrix4& getModelMatrix() { return modelMatrix; }

	void addRotatation(float angle, Vec3 orientation);
	void addTranslation(Vec3 direction, float distance = 1.0f, bool useDistance = false);
	Matrix4 GetRotationMatrix() { return RotationMatrix; }
	Matrix4 GetPositionMatrix() { return PositionMatrix; }
	void SetOriginalTransform(Vec3 position, float angle, Vec3 rotation, Vec3 scale);

	Vec3 Position;

	Vec3 GetPosition();
	void SetTexture(Texture * TextureToSet);
};

#endif

