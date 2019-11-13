#ifndef CAMERA_H
#define CAMERA_H
#include "Vector.h"
#include "Matrix.h"
using namespace MATH;
class Camera {
private:

	Matrix4 projection;
	Matrix4 Rotation;
	Matrix4 Position;
	Vec3 PositionVector;
	Matrix4 view;
public:
	inline Matrix4 getProjectionMatrix() const { return projection; }
	inline Matrix4 getViewMatrix() const { return Rotation * Position; }
	inline Vec3 getPositionVector() const { return PositionVector; }
	inline Matrix4 getPosition() const { return Position; }
	inline Matrix4 getRotation() const { return Rotation; }

	void createProjection(float fovy, float aspectRatio, float near, float far);
	void createView(Vec3 pos, Vec3 at, Vec3 up);
	void createView(Vec3 pos, float angle, Vec3 orientation);
	void SetRotation(float angle, Vec3 orientation);
	void SetRotation(Matrix4 rotation);
	Camera();
	~Camera();
};

#endif



