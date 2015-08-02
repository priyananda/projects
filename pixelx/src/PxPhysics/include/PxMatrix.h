#ifndef _PIXELX_MATRIX_h
#define _PIXELX_MATRIX_h

#include "PxVector4d.h"

#define M_PI 3.14159265


class PxMatrix
{
public:
	PxMatrix()
	{	LoadIdentity();	}
	PxMatrix(	float e0, float e1, float e2, float e3,
				float e4, float e5, float e6, float e7,
				float e8, float e9, float e10, float e11,
				float e12, float e13, float e14, float e15);
	PxMatrix(const float * rhs);
	PxMatrix(const PxMatrix & rhs);
	~PxMatrix() {}	//empty

	void SetEntry(int position, float value);
	float GetEntry(int position) const;
	PxVector4d GetRow(int position) const;
	PxVector4d GetColumn(int position) const;
	
	void LoadIdentity(void);
	void LoadZero(void);
	
	//binary operators
	PxMatrix operator+(const PxMatrix & rhs) const;
	PxMatrix operator-(const PxMatrix & rhs) const;
	PxMatrix operator*(const PxMatrix & rhs) const;
	PxMatrix operator*(const float rhs) const;
	PxMatrix operator/(const float rhs) const;
	friend PxMatrix operator*(float scaleFactor, const PxMatrix & rhs);

	bool operator==(const PxMatrix & rhs) const;
	bool operator!=(const PxMatrix & rhs) const;

	//self-add etc
	void operator+=(const PxMatrix & rhs);
	void operator-=(const PxMatrix & rhs);
	void operator*=(const PxMatrix & rhs);
	void operator*=(const float rhs);
	void operator/=(const float rhs);

	//unary operators
	PxMatrix operator-(void) const;
	PxMatrix operator+(void) const {return (*this);}
	
	//multiply a vector by this matrix
	PxVector4d operator*(const PxVector4d rhs) const;

	//rotate a 3d vector by rotation part
	void RotatePxVector(PxVector & rhs) const
	{rhs=GetRotatedPxVector(rhs);}

	void InverseRotatePxVector(PxVector & rhs) const
	{rhs=GetInverseRotatedPxVector(rhs);}

	PxVector GetRotatedPxVector(const PxVector & rhs) const;
	PxVector GetInverseRotatedPxVector(const PxVector & rhs) const;

	//translate a 3d vector by translation part
	void TranslatePxVector(PxVector & rhs) const
	{rhs=GetTranslatedPxVector(rhs);}

	void InverseTranslatePxVector(PxVector & rhs) const
	{rhs=GetInverseTranslatedPxVector(rhs);}
	
	PxVector GetTranslatedPxVector(const PxVector & rhs) const;
	PxVector GetInverseTranslatedPxVector(const PxVector & rhs) const;

	//Other methods
	void Invert(void);
	PxMatrix GetInverse(void) const;
	void Transpose(void);
	PxMatrix GetTranspose(void) const;
	void InvertTranspose(void);
	PxMatrix GetInverseTranspose(void) const;

	//Inverse of a rotation/translation only matrix
	void AffineInvert(void);
	PxMatrix GetAffineInverse(void) const;
	void AffineInvertTranspose(void);
	PxMatrix GetAffineInverseTranspose(void) const;

	//set to perform an operation on space - removes other entries
	void SetTranslation(const PxVector & translation);
	void SetScale(const PxVector & scaleFactor);
	void SetUniformScale(const float scaleFactor);
	void SetRotationAxis(const double angle, const PxVector & axis);
	void SetRotationX(const double angle);
	void SetRotationY(const double angle);
	void SetRotationZ(const double angle);
	void SetRotationEuler(const double angleX, const double angleY, const double angleZ);
	void SetPerspective(float left, float right, float bottom, float top, float n, float f);
	void SetPerspective(float fovy, float aspect, float n, float f);
	void SetOrtho(float left, float right, float bottom, float top, float n, float f);

	//set parts of the matrix
	void SetTranslationPart(const PxVector & translation);
	void SetRotationPartEuler(const double angleX, const double angleY, const double angleZ);
	void SetRotationPartEuler(const PxVector & rotations)
	{
		SetRotationPartEuler((double)rotations.x, (double)rotations.y, (double)rotations.z);
	}

	//cast to pointer to a (float *) for glGetFloatv etc
	operator float* () const {return (float*) this;}
	operator const float* () const {return (const float*) this;}
	
	//member variables
	float entries[16];
};

#endif

