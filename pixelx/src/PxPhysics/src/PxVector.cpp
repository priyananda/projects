#include "PxVector.h"

PxVector::PxVector(float X,float Y,float Z)
{
	x = X; y = Y; z = Z;
}
PxVector PxVector::operator+(const PxVector & vVector) const
{
	return PxVector(vVector.x + x, vVector.y + y, vVector.z + z);
}
PxVector PxVector::operator-(const PxVector & vVector) const
{
	return PxVector(x - vVector.x, y - vVector.y, z - vVector.z);
}
PxVector PxVector::operator*(float num) const
{
	return PxVector(x * num, y * num, z * num);
}
PxVector PxVector::operator/(float num) const
{
	return PxVector(x / num, y / num, z / num);
}
PxVector PxVector::Cross(const PxVector & vVector1,const PxVector & vVector2)
{
	PxVector vNormal;	
	vNormal.x = ((vVector1.y * vVector2.z) - (vVector1.z * vVector2.y));
	vNormal.y = ((vVector1.z * vVector2.x) - (vVector1.x * vVector2.z));
	vNormal.z = ((vVector1.x * vVector2.y) - (vVector1.y * vVector2.x));
	return vNormal;
}
float PxVector::GetSquaredLength() const
{
	return (x * x) + (y * y) + (z * z);
}
float PxVector::Magnitude() const
{
	return (float)std::sqrt( (x * x) + (y * y) + (z * z) );
}
void PxVector::Normalize()
{
	float magnitude = Magnitude();
	x /= magnitude;
	y /= magnitude;
	z /= magnitude;
}

float PxVector::Distance(const PxVector & vPoint1,const PxVector & vPoint2)
{
	double distance = sqrt( (vPoint2.x - vPoint1.x) * (vPoint2.x - vPoint1.x) +
						    (vPoint2.y - vPoint1.y) * (vPoint2.y - vPoint1.y) +
						    (vPoint2.z - vPoint1.z) * (vPoint2.z - vPoint1.z) );
	return (float)distance;
}

float PxVector::Dot(const PxVector &vVector1,const PxVector &vVector2) 
{
	return ( (vVector1.x * vVector2.x) + (vVector1.y * vVector2.y) + (vVector1.z * vVector2.z) );
}

PxVector PxVector::operator -() const
{
	return PxVector(-x,-y,-z);
}

bool PxVector::operator ==( const PxVector & v ) const
{
	return x == v.x && y == v.y && z == v.z;
}

PxVector PxVector::GetRotatedX(double angle) const
{
	if(angle==0.0)
		return (*this);

	float sinAngle=(float)sin(M_PI*angle/180);
	float cosAngle=(float)cos(M_PI*angle/180);

	return PxVector(	x,
						y*cosAngle - z*sinAngle,
						y*sinAngle + z*cosAngle);
}

void PxVector::RotateX(double angle)
{
	(*this)=GetRotatedX(angle);
}

PxVector PxVector::GetRotatedY(double angle) const
{
	if(angle==0.0)
		return (*this);

	float sinAngle=(float)sin(M_PI*angle/180);
	float cosAngle=(float)cos(M_PI*angle/180);

	return PxVector(	x*cosAngle + z*sinAngle,
						y,
						-x*sinAngle + z*cosAngle);
}

void PxVector::RotateY(double angle)
{
	(*this)=GetRotatedY(angle);
}

PxVector PxVector::GetRotatedZ(double angle) const
{
	if(angle==0.0)
		return (*this);

	float sinAngle=(float)sin(M_PI*angle/180);
	float cosAngle=(float)cos(M_PI*angle/180);
	
	return PxVector(x*cosAngle - y*sinAngle,
					x*sinAngle + y*cosAngle,
					z);
}

void PxVector::RotateZ(double angle)
{
	(*this)=GetRotatedZ(angle);
}

PxVector PxVector::GetRotatedAxis(double angle, const PxVector & axis) const
{
	if(angle==0.0)
		return (*this);

	PxVector u=axis;
	u.Normalize();

	PxVector rotMatrixRow0, rotMatrixRow1, rotMatrixRow2;

	float sinAngle=(float)sin(M_PI*angle/180);
	float cosAngle=(float)cos(M_PI*angle/180);
	float oneMinusCosAngle=1.0f-cosAngle;

	rotMatrixRow0.x=(u.x)*(u.x) + cosAngle*(1-(u.x)*(u.x));
	rotMatrixRow0.y=(u.x)*(u.y)*(oneMinusCosAngle) - sinAngle*u.z;
	rotMatrixRow0.z=(u.x)*(u.z)*(oneMinusCosAngle) + sinAngle*u.y;

	rotMatrixRow1.x=(u.x)*(u.y)*(oneMinusCosAngle) + sinAngle*u.z;
	rotMatrixRow1.y=(u.y)*(u.y) + cosAngle*(1-(u.y)*(u.y));
	rotMatrixRow1.z=(u.y)*(u.z)*(oneMinusCosAngle) - sinAngle*u.x;
	
	rotMatrixRow2.x=(u.x)*(u.z)*(oneMinusCosAngle) - sinAngle*u.y;
	rotMatrixRow2.y=(u.y)*(u.z)*(oneMinusCosAngle) + sinAngle*u.x;
	rotMatrixRow2.z=(u.z)*(u.z) + cosAngle*(1-(u.z)*(u.z));

	return PxVector(	Dot(*this,rotMatrixRow0),
						Dot(*this,rotMatrixRow1),
						Dot(*this,rotMatrixRow2));
}

void PxVector::RotateAxis(double angle, const PxVector & axis)
{
	(*this)=GetRotatedAxis(angle, axis);
}

