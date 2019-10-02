#ifndef CAMERA_H
#define CAMERA_H
#include "Matrix.h"
#include "Vector.h"
using namespace MATH;;

class Camera 
{
private:

	Matrix4 projection;
	Matrix4 view;
	Matrix4 ViewRotation = Matrix4(1.0f);// Matrix4(1.0f) loads identity

public:
	inline Matrix4 getProjectionMatrix() const { return projection; }
	inline Matrix4 getViewMatrix() const { return view * ViewRotation; }

	void createProjection(float fovy, float aspectRatio, float near, float far);
	void createView(Vec3 pos, Vec3 at, Vec3 up);
	Camera();
	~Camera();

	void Rotate(float degrees, Vec3 rotation);
	void SetRotaion(float degrees, Vec3 rotation);
};

#endif



