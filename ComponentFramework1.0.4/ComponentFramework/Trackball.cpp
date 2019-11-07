#include <glew.h>
#include <SDL.h>
#include "Trackball.h"
#include "VMath.h"
#include "MMath.h"


using namespace MATH;

Trackball::Trackball()
{
	SetWindowDimensions();
	MousePressFlag = false;
}

Trackball::~Trackball()
{
}

const Vec3 Trackball::GetMouseVector(int x, int y)
{
	Vec3 mousePosition;

	if (XAxisLockFlag)//Restricts movement to the X axis
	{
		mousePosition = Vec3(static_cast<float>(x), static_cast<float>(MouseCoordY), 0.0f);
		MouseCoordX = x;
	}
	else if (YAxisLockFlag)//Restricts movement to the Y axis
	{
		mousePosition = Vec3(static_cast<float>(MouseCoordX), static_cast<float>(y), 0.0f);
		MouseCoordY = y;
	}
	else//Movent allowed for both axis
	{
		mousePosition = Vec3(static_cast<float>(x), static_cast<float>(y), 0.0f);
		MouseCoordX = x;
		MouseCoordY = y;
	}


	Vec3 mouseVector = ViewportInverse * mousePosition;//Ajust mouse position to window coordinates
	
	//This next two floats are not strictly needed, but they make the program much easer to read
	float xSquared = mouseVector.x * mouseVector.x;
	float ySquared = mouseVector.y * mouseVector.y;

	if (xSquared + ySquared <= BallRadius * 0.5f) 
	{
		mouseVector.z = sqrt(1.0f - (xSquared + ySquared));
	}
	else 
	{
		mouseVector.z = (BallRadius * 0.5f) / sqrt(xSquared + ySquared);
		mouseVector = VMath::normalize(mouseVector);
	}
	return mouseVector;
}

void Trackball::SetWindowDimensions()
{
	int Viewport[4];//Store array
	glGetIntegerv(GL_VIEWPORT, Viewport);//This function stores the opGL default window X and Y coords and the window's width and heith respectively in the given array.

	ViewportInverse = MMath::inverse(MMath::viewportNDC(Viewport[2], Viewport[3]));
}

void Trackball::OnLeftMouseDown(int x, int y)
{
	MouseCoordX = x;
	MouseCoordY = y;
	StartPoint = GetMouseVector(x, y);
	MousePressFlag = true;
}

void Trackball::OnLeftMouseUp()
{
	MousePressFlag = false;
}

void Trackball::OnMouseMove(int x, int y)
{
	if (!MousePressFlag) return;

	HasMoved = true;
	EndPoint = GetMouseVector(x, y);

	float cosAngle = VMath::dot(StartPoint, EndPoint);
	float angle = acos(cosAngle) * 180.0f / M_PI; /// acos() returns radians must convert to degrees
	Vec3 rotAxis = VMath::cross(StartPoint, EndPoint);

	if (VMath::mag(rotAxis) <= MinimumMovement)//Make sure there was some movement, otherwise input a rotation of 0 to avoid division by 0 when normalizing the rotAxis.
	{
		RotationMatrix = MMath::rotate(0.0f, Vec3(1.0f, 0.0f, 0.0f));
		MouseRotation = RotationMatrix * MouseRotation;
		/// reset for the next mousemove
		StartPoint = EndPoint;
	}
	else if(XAxisLockFlag)//Rotate only around Y axis
	{
		RotationMatrix = MMath::rotate(angle, Vec3(0.0f, rotAxis.y, 0.0f));
		MouseRotation = RotationMatrix * MouseRotation;
		/// reset for the next mousemove
		StartPoint = EndPoint;
	}
	else if (YAxisLockFlag)//Rotate only around X axis
	{
		RotationMatrix = MMath::rotate(angle, Vec3(rotAxis.x, 0.0f, 0.0f));
		MouseRotation = RotationMatrix * MouseRotation;
		/// reset for the next mousemove
		StartPoint = EndPoint;
	}
	else//Rotate on both axis
	{
		RotationMatrix = MMath::rotate(angle, rotAxis);
		MouseRotation = RotationMatrix * MouseRotation;
		/// reset for the next mousemove
		StartPoint = EndPoint;
	}
}

float Trackball::SnapToAngle(float angle, float angleSnapGap)
{
	return 0.0f;
}

void Trackball::HandleEvents(const SDL_Event & sdlEvent)
{
	if (sdlEvent.type == SDL_EventType::SDL_KEYDOWN)
	{
	if (sdlEvent.key.keysym.sym == SDLK_LCTRL) XAxisLockFlag = true;
	if (sdlEvent.key.keysym.sym == SDLK_LSHIFT) YAxisLockFlag = true;
	}
	else if (sdlEvent.type == SDL_EventType::SDL_KEYUP)
	{
	if (sdlEvent.key.keysym.sym == SDLK_LCTRL) XAxisLockFlag = false;
	if (sdlEvent.key.keysym.sym == SDLK_LSHIFT) YAxisLockFlag = false;
	}
	else if (sdlEvent.type == SDL_EventType::SDL_MOUSEBUTTONDOWN) 
	{
		OnLeftMouseDown(sdlEvent.button.x, sdlEvent.button.y);
	}
	else if (sdlEvent.type == SDL_EventType::SDL_MOUSEBUTTONUP) 
	{
		OnLeftMouseUp();
	}
	else if (sdlEvent.type == SDL_EventType::SDL_MOUSEMOTION && SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) 
	{
		OnMouseMove(sdlEvent.button.x, sdlEvent.button.y);
	}
	else if (sdlEvent.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) 
	{
		SetWindowDimensions();
	}
}
