#include "PxRectangle.h"

PxRectangle::PxRectangle( 
	float x,float y , float z,
	float l, float w , float h , cstrref tex)
{
	this->AddVertex(x,y,z,0,0);
	if( l == 0 )
	{
		this->AddVertex(x,y + w ,z,0,1);
		this->AddVertex(x,y + w,z + h,1,1);
		this->AddVertex(x,y, z + h,1,0);
	}
	if( w == 0 )
	{
		this->AddVertex(x + l,y ,z,0,1);
		this->AddVertex(x + l,y ,z + h,1,1);
		this->AddVertex(x ,y ,z + h,1,0);
	}
	if( h == 0 )
	{
		this->AddVertex(x + l,y ,z,0,1);
		this->AddVertex(x + l,y + w ,z,1,1);
		this->AddVertex(x,y + w,z,1,0);
	}
	if( tex.length() > 0 )
		this->SetTexture( tex );
}

