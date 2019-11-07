#ifndef TRACKBALL_H
#define	TRACKBALL_H
#include "MMath.h"
union SDL_Event;

using namespace MATH;
class Trackball
{
public:
	Trackball();
	~Trackball();

private:
	bool MousePressFlag = false;
	Matrix4 MouseRotation;
	Matrix4 RotationMatrix;
	Matrix4 ViewportInverse;//inverse of the NDC viewport
	Vec3 StartPoint;//Stores the mouse position on the time of left button press, then is updated each frame the mouse moves
	Vec3 EndPoint;//Calculates the mouse position each frame when the left button is pressed and the mouse moves
	float BallRadius = 1.0f;
	bool XAxisLockFlag = false;
	bool YAxisLockFlag = false;
	int MouseCoordX = 0;
	int MouseCoordY = 0;
	float MinimumMovement = 1.0e-7f;//!!!MUST AWAYS BE BIGGER THEN ZERO!!!
	float AngleSnapGap = 0.001f;//This is needed to avoid error acumulation.
	
	const Vec3 GetMouseVector(int x, int y);
	void SetWindowDimensions();
	void OnLeftMouseDown(int x, int y);
	void OnLeftMouseUp();
	void OnMouseMove(int x, int y);
	float SnapToAngle(float angle, float angleSnapGap);

public:
	const Matrix4 GetMouseRotation() const { return MouseRotation; }
	const Matrix3 GetMouseRotationM3() const { return Matrix3(MouseRotation); }
	const Matrix4 GetRotationMatrix() const { return RotationMatrix; }
	void HandleEvents(const SDL_Event &sdlEvent);
	bool IsTrackballTurning() { return MousePressFlag; }
	bool HasMoved = false;

};
#endif

