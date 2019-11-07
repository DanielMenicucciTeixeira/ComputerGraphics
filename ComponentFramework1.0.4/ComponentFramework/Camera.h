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
	Matrix4 view;
public:
	inline Matrix4 getProjectionMatrix() const { return projection; }
	inline Matrix4 getViewMatrix() const { return Rotation * Position; }
	inline Matrix4 getRotation() const { return Rotation; }

	void createProjection(float fovy, float aspectRatio, float near, float far);
	void createView(Vec3 pos, Vec3 at, Vec3 up);
	void createView(Vec3 pos, float angle, Vec3 orientation);
	void SetRotation(float angle, Vec3 orientation);
	Camera();
	~Camera();
};

#endif



