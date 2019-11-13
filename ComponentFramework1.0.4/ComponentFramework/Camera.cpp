#include "Camera.h"
#include "MMath.h"
#include "VMath.h"

Camera::Camera() {
	createProjection(45.0f, (16.0f / 9.0f), 0.5f, 100.0f);
	//createView(Vec3(0.0, 0.0, 10.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));
	createView(Vec3(0.0f, 0.0f, -10.0f), 0.0f, Vec3(1.0f, 0.0f, 0.0f));
}

Camera::~Camera() {}

void Camera::createProjection(float fovy, float aspect, float near, float far) {
	projection = MMath::perspective(fovy, aspect, near, far);
}

void Camera::createView(Vec3 pos, Vec3 at, Vec3 up)
{

	view = MMath::lookAt(pos, at, up);
}

void Camera::createView(Vec3 pos, float angle, Vec3 orientation)
{
	PositionVector = pos;
	Position = MMath::translate(pos);
	Rotation = MMath::rotate(angle, orientation);
}

void Camera::SetRotation(float angle, Vec3 orientation)
{
	Rotation = MMath::rotate(angle, orientation);
}

void Camera::SetRotation(Matrix4 rotation)
{
	Rotation = rotation;
}
