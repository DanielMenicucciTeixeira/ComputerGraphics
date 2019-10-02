#include "Camera.h"
#include "MMath.h"

Camera::Camera()
{
	createProjection(45.0f, (16.0f / 9.0f), 0.5f, 100.0f);
	createView(Vec3(0.0, 0.0, 10.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));

	Position = Vec3(0.0, 0.0, 10.0f);
	LookAtVector = Vec3(0.0f, 0.0f, 0.0f);
	UpVector = Vec3(0.0f, 1.0f, 0.0f);
}

Camera::~Camera() {}

void Camera::Rotate(float degrees, Vec3 rotation)
{
	ViewRotation = ViewRotation * MMath::rotate(degrees, rotation);
}

void Camera::SetRotaion(float degrees, Vec3 rotation)
{
	ViewRotation = MMath::rotate(degrees, rotation);
}

void Camera::SetPositoin(Vec3 position)
{
	Position = position;
}

void Camera::SetLookAtVector(Vec3 lookAtVector)
{
	LookAtVector = lookAtVector;
}

void Camera::createProjection(float fovy, float aspect, float near, float far) {
	projection = MMath::perspective(fovy, aspect, near, far);
}

void Camera::createView(Vec3 pos, Vec3 at, Vec3 up) {
	view = MMath::lookAt(pos, at, up);
}