#ifndef _PIXELX_CAMERA_H
#define _PIXELX_CAMERA_H

class PxCollisionManager;
class PxDirector;
#include "PxFrustrum.h"
#include "..\..\PxPhysics\include\PxBoundingSphere.h"

class PxCamera {
public:
	PxCamera();	
	PxBoundingSphere boundingSphere;
	PxFrustrum frustrum;

	PxVector Position() {	return boundingSphere.centre;		}
	PxVector View()		{	return m_vView;			}
	PxVector UpVector() {	return m_vUpVector;		}
	PxVector Strafe()	{	return m_vStrafe;		}
	PxVector OldPosition()	{	return m_vOldPosition;		}

	void PositionCamera(float positionX, float positionY, float positionZ,
			 		    float viewX,     float viewY,     float viewZ,
						float upVectorX, float upVectorY, float upVectorZ);
	void RotateView(float angle, float X, float Y, float Z);
	void SetViewByMouse(); 
	void RotateAroundPoint(PxVector vCenter, float X, float Y, float Z);
	void StrafeCamera(float speed);
	void MoveCamera(float speed);
	void UpCamera(float speed);
	void CheckForMovement(float frameInterval);
	void Update(float frameInterval);
	void Look();
	void Jump();
private:
	PxVector m_vView;
	PxVector m_vUpVector;
	PxVector m_vStrafe;
	PxVector m_vOldPosition;
	long MouseSpeed,JumpHeight,RunFactor,CrouchHeight,GravityFactor;
	long CenterX, CenterY;
	friend PxCollisionManager;
	friend PxDirector;
};

#endif

