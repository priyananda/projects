#include "PxCamera.h"
#include "PxFrustrum.h"
#include "..\..\PxPhysics\include\PxCollisionManager.h"
#include "..\..\PxInput\include\PxConfiguration.h"

PxVector g_vVelocity(0, 0, 0);

extern bool g_debug_collision;
#define ISKEYPRESSED(e) GetKeyState( PxConfiguration::MapKey(e)) & 0x80
PxCamera::PxCamera()
{
	boundingSphere.centre = PxVector(0.0, 0.0, 0.0);
	m_vView = PxVector(0.0, 1.0, 0.5);
	m_vUpVector= PxVector(0.0, 0.0, 1.0);

	JumpHeight = PxConfiguration::GetLong( "i_jumpheight" );
	MouseSpeed = PxConfiguration::GetLong( "i_mousespeed" );
	RunFactor = PxConfiguration::GetLong( "i_runfactor" );
	CrouchHeight = PxConfiguration::GetLong( "i_crouchheight" );
	GravityFactor = PxConfiguration::GetFloat("p_gravity_factor");
	CenterX = PxConfiguration::GetLong("g_screenwidth") / 2;
	CenterY = PxConfiguration::GetLong("g_screenheight") / 2;

	DEFINE_VARF(w_cam_radius);
	boundingSphere.radius = w_cam_radius;
}

void PxCamera::PositionCamera(float positionX, float positionY, float positionZ,
				  		     float viewX,     float viewY,     float viewZ,
							 float upVectorX, float upVectorY, float upVectorZ)
{
	PxVector vPosition	= PxVector(positionX, positionY, positionZ);
	PxVector vView		= PxVector(viewX, viewY, viewZ);
	PxVector vUpVector	= PxVector(upVectorX, upVectorY, upVectorZ);

	boundingSphere.centre = vPosition;
	m_vView     = vView;
	m_vUpVector = vUpVector;
}

void PxCamera::SetViewByMouse()
{
	POINT mousePos;
	float angleY = 0.0f;
	float angleZ = 0.0f;
	static float currentRotX = 0.0f;
	
	GetCursorPos(&mousePos);						
	
	if( (mousePos.x == CenterX) && (mousePos.y == CenterY) ) return;

	SetCursorPos(CenterX, CenterY);

	angleY = (float)( (CenterX - mousePos.x) ) / 500.0f;		
	angleZ = (float)( (CenterY - mousePos.y) ) / 500.0f;		

	currentRotX -= angleZ;  

	if(currentRotX > 1.0f)
		currentRotX = 1.0f;

	else if(currentRotX < -1.0f)
		currentRotX = -1.0f;

	else
	{
		PxVector vAxis = PxVector::Cross(m_vView - boundingSphere.centre, m_vUpVector);
		vAxis.Normalize();

		RotateView(angleZ, vAxis.x, vAxis.y, vAxis.z);
		RotateView(angleY, 0, 1, 0);
	}
}

void PxCamera::RotateView(float angle, float x, float y, float z)
{
	PxVector vNewView;
	PxVector vView = m_vView - boundingSphere.centre;		

	float cosTheta = (float)cos(angle);
	float sinTheta = (float)sin(angle);

	vNewView.x  = (cosTheta + (1 - cosTheta) * x * x)		* vView.x;
	vNewView.x += ((1 - cosTheta) * x * y - z * sinTheta)	* vView.y;
	vNewView.x += ((1 - cosTheta) * x * z + y * sinTheta)	* vView.z;

	vNewView.y  = ((1 - cosTheta) * x * y + z * sinTheta)	* vView.x;
	vNewView.y += (cosTheta + (1 - cosTheta) * y * y)		* vView.y;
	vNewView.y += ((1 - cosTheta) * y * z - x * sinTheta)	* vView.z;

	vNewView.z  = ((1 - cosTheta) * x * z - y * sinTheta)	* vView.x;
	vNewView.z += ((1 - cosTheta) * y * z + x * sinTheta)	* vView.y;
	vNewView.z += (cosTheta + (1 - cosTheta) * z * z)		* vView.z;

	m_vView = boundingSphere.centre + vNewView;
}

void PxCamera::StrafeCamera(float speed)
{	
	boundingSphere.centre.x += m_vStrafe.x * speed;
	boundingSphere.centre.z += m_vStrafe.z * speed;

	m_vView.x += m_vStrafe.x * speed;
	m_vView.z += m_vStrafe.z * speed;
}



void PxCamera::MoveCamera(float speed)
{
	PxVector vVector = m_vView - boundingSphere.centre;

	boundingSphere.centre.x += vVector.x * speed;
	boundingSphere.centre.z += vVector.z * speed;
	m_vView.x += vVector.x * speed;
	m_vView.z += vVector.z * speed;
}

void PxCamera::UpCamera(float speed)
{
	boundingSphere.centre.y += 0.05f * speed;
	m_vView.y += 0.05f * speed;
}
void PxCamera::CheckForMovement(float frameInterval)
{
	m_vOldPosition = boundingSphere.centre;

	float speed = MouseSpeed * frameInterval;

	if( g_debug_collision )
		g_vVelocity.y -= (float)(frameInterval * GravityFactor);
	
	boundingSphere.centre = boundingSphere.centre + g_vVelocity;

	if( ISKEYPRESSED( eKeyRun ))
		speed *= RunFactor;
	if( ISKEYPRESSED( eKeyMoveUp ))
		MoveCamera(speed/20);
	if( ISKEYPRESSED( eKeyMoveDown ))
		MoveCamera(-speed/20);
	if( ISKEYPRESSED( eKeyStrafeLeft ))
		StrafeCamera(-speed);
	if( ISKEYPRESSED( eKeyStrafeRight ))
		StrafeCamera(speed);
	if( ISKEYPRESSED( eKeyPrevWeapon ))
		UpCamera(speed);
	if( ISKEYPRESSED( eKeyNextWeapon ))
		UpCamera(-speed);

	if( g_debug_collision )
	{
		PxVector oldPosition = this->boundingSphere.centre;
		PxCollisionManager::Collides( *this );
		float y = m_vView.y;
		m_vView = m_vView + ( this->boundingSphere.centre - oldPosition );
		m_vView.y = y;
	}
	frustrum.Update();
	if(! PxCollisionManager::IsOnGround(*this))
		m_vView = m_vView + g_vVelocity;
	else
		if(g_vVelocity.y < 0)
			g_vVelocity.y = 0;
}

void PxCamera::Update(float frameInterval) 
{
	m_vStrafe = PxVector::Cross(m_vView - boundingSphere.centre, m_vUpVector);
	m_vStrafe.Normalize();
	SetViewByMouse();
	CheckForMovement(frameInterval);
}

void PxCamera::Look()
{
	gluLookAt(boundingSphere.centre.x, boundingSphere.centre.y, boundingSphere.centre.z,	
			  m_vView.x,	 m_vView.y,     m_vView.z,	
			  m_vUpVector.x, m_vUpVector.y, m_vUpVector.z);
}

void PxCamera::Jump()
{
	if( g_debug_collision && PxCollisionManager::IsOnGround(*this) )
		g_vVelocity.y = JumpHeight;
	else
		PxLog::LogMessage( "Centre:%f", boundingSphere.centre.y );
}

