#include "stdafx.h"
#include "Camera.h"
#include "../Utilities/Math.h"


Camera::Camera(Vector3 pos, Vector3 tar, Vector3 u, GLfloat mSpeed, GLfloat rSpeed, GLfloat nPlane, GLfloat fPlane, GLfloat f)
    : position(pos), target(tar), up(u), moveSpeed(mSpeed), rotateSpeed(rSpeed), nearPlane(nPlane), farPlane(fPlane), fov(f)
{
    updateWorldView();
}

Camera::~Camera()
{
}

void Camera::moveOx(int sens)
{
	Vector3 forward = xAxis * sens;
	Vector3 vectorDeplasare = forward * moveSpeed * deltaTime;
	position += vectorDeplasare;
	target += vectorDeplasare;
	updateWorldView();
}

void Camera::moveOy(int sens)
{
	Vector3 forward = yAxis * sens;
	Vector3 vectorDeplasare = forward * moveSpeed * deltaTime;
	position += vectorDeplasare;
	target += vectorDeplasare;
	updateWorldView();
}

void Camera::moveOz(int sens)
{
	Vector3 forward = zAxis * sens;
	Vector3 vectorDeplasare = forward * moveSpeed * deltaTime;
	position += vectorDeplasare;
	target += vectorDeplasare;
	updateWorldView();
}

void Camera::rotateOx(int sens)
{
	float unghiRotatie = sens * rotateSpeed * deltaTime;
	Matrix mr;
	mr.SetRotationX(unghiRotatie);

	Vector4 localUp;
	Matrix mRotateOX;
	Vector4 rotatedLocalUp = localUp * mRotateOX;
	Vector4 up = rotatedLocalUp * worldMatrix;
	up = up.Normalize();

	Vector4 localTarget = Vector4(0.0f, 0.0f, -(target - position).Length(), 1.0f);
	Vector4 rotatedTarget = localTarget * mRotateOX;
	Vector4 target = rotatedTarget * worldMatrix;
	updateWorldView();

}

void Camera::rotateOy(int sens)
{
	float unghiRotatie = sens * rotateSpeed * deltaTime;
	Matrix mr;
	mr.SetRotationY(unghiRotatie);

	Matrix mRotateOY;
	Vector4 localTarget = Vector4(0.0f, 0.0f, -(target - position).Length(), 1.0f);
	Vector4 rotatedTarget = localTarget * mRotateOY;
	Vector4 target = rotatedTarget * worldMatrix;
	updateWorldView();
	

}

void Camera::rotateOz(int sens)
{
	float unghiRotatie = sens * rotateSpeed * deltaTime;
	Matrix mr;
	mr.SetRotationY(unghiRotatie);
	Matrix mRotateOY;
	//target este pe oz
}

void Camera::updateAxes()
{
	zAxis = (target - position).Normalize();
	xAxis = (zAxis.Cross(up)).Normalize();
	yAxis = (xAxis.Cross(zAxis)).Normalize();
}

void Camera::updateWorldView()
{
	Matrix R;
	Matrix T;
	worldMatrix = R * T;
		/*
		unde T reprezinta matricea de translație pentru vectorul(position.x, position.y, position.z);
	viewMatrix = worldMatrix la -1
		R este matrice ortogonala => R−1 = Rt
		viewMatrix = T−1 * Rt
		Rt = R transpus
		iar T−1 e chiar translația cu vectorul(-position.x, -position.y, -position.z)
		Matricea de rotație are formula de mai jos : :
		R =
		xAxis.x   xAxis.y   xAxis.z   0
		yAxis.x   yAxis.y   yAxis.z   0
		zAxis.x   zAxis.y   zAxis.z    0
		0               0                0                 1
		Valorile se vor seta pentru variabila R direct în proprietatea m care e de tip GLfloat[4][4], declarată deja în clasa Matrix.De exemplu :
	R.m[0][0] = x.axis.x; //etc.
	*/

	R.m[0][0] = xAxis.x; R.m[0][1] = xAxis.y; R.m[0][2] = xAxis.z; R.m[0][3] = 0.0f; 
	R.m[1][0] = yAxis.x; R.m[1][1] = yAxis.y; R.m[1][2] = yAxis.z; R.m[1][3] = 0.0f; 
	R.m[2][0] = zAxis.x; R.m[2][1] = zAxis.y; R.m[2][2] = zAxis.z; R.m[2][3] = 0.0f; 
	R.m[3][0] = 0.0f; R.m[3][1] = 0.0f; R.m[3][2] = 0.0f; R.m[3][3] = 1.0f;

	T.SetTranslation(-position.x, -position.y, -position.z);
	viewMatrix = T * R.Transpose();
}

void Camera::setDeltaTime(GLfloat deltaTime)
{
	this->deltaTime = deltaTime;
}


