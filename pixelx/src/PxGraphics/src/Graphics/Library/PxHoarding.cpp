#include "PxHoarding.h"
#include "PxCube.h"
#include "PxRectangle.h"

PxHoarding::PxHoarding(float x,float y,float z, float length,float height, float width , cstrref tname)
	:m_texname(tname)
{
	bbox.x = x;bbox.y = y;bbox.z = z;
	bbox.length=length;bbox.width=height;bbox.height=width;
	if( bbox.length < bbox.height )
		bbox.length = 0.5;
	else
		bbox.height = 0.5;
}

PxBoundingBox & PxHoarding::GetBoundingBox()
{
	return bbox;
}

void PxHoarding::Register(PxPolygonCollection * coll)
{
	PxRectangle * s1,*s2;
	if( bbox.length < bbox.height )
	{
		s1 = new PxRectangle(	bbox.x	,bbox.y + bbox.width, bbox.z,
								0		,- bbox.width * 0.75f	, bbox.height,
								m_texname );
		s2 = new PxRectangle(	bbox.x + bbox.length,bbox.y + bbox.width,bbox.z+bbox.height,
								0					,-bbox.width * 0.75f	,-bbox.height,
								m_texname );
		PxCube c1(bbox.x,bbox.y,bbox.z,bbox.length,bbox.width *0.25f,bbox.length );
		c1.SetTexture("WOOD1");
		c1.Register(coll);
		PxCube c2(bbox.x,bbox.y,bbox.z+ bbox.height,bbox.length,bbox.width *0.25f,-bbox.length );
		c2.SetTexture("WOOD1");
		c2.Register(coll);
	}
	else
	{
		s1 = new PxRectangle(	bbox.x,		bbox.y + bbox.width	,bbox.z,
								bbox.length,-bbox.width  * 0.75f			,0,
								m_texname );
		s2 = new PxRectangle(	bbox.x+bbox.length,		bbox.y + bbox.width ,bbox.z + bbox.height,
								-bbox.length,-bbox.width * 0.75f			,0,
								m_texname );
		PxCube c1(bbox.x,bbox.y,bbox.z,bbox.height,bbox.width *0.25f,bbox.height );
		c1.SetTexture("WOOD1");
		c1.Register(coll);
		PxCube c2(bbox.x+bbox.length,bbox.y,bbox.z,bbox.height,bbox.width *0.25f,-bbox.height );
		c2.SetTexture("WOOD1");
		c2.Register(coll);
	}
	coll->AddPolygon(s1);
	coll->AddPolygon(s2);
}

void PxHoarding::Render()
{
}

