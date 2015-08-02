#include "PxSteps.h"
#include "PxRectangle.h"

PxSteps::PxSteps( PxDirectionEnum _dir, float len, float num, float height, float x,float y, float z)
	:dir(_dir),length(len),stepHeight(height),numSteps(num)
{
	bBox.x = x;bBox.y = y; bBox.z = z;
	if( dir == eDirectionNorth || dir == eDirectionSouth )
	{
		bBox.length = length;
		bBox.height = numSteps * stepHeight;
	}
	else
	{
		bBox.length = numSteps * stepHeight;
		bBox.height = length;
	}
	bBox.width = numSteps * stepHeight;
}

void PxSteps::Register(PxPolygonCollection * pColl )
{
	switch(dir)
	{
		case eDirectionNorth:
			for( int i = 0 ; i < numSteps; ++i )
			{
				pColl->AddPolygon( new PxRectangle(
					bBox.x,bBox.y + (i + 1)* stepHeight,bBox.z + i * stepHeight,
					length,0,stepHeight,
					"WOOD3"
				));
				pColl->AddPolygon( new PxRectangle(
					bBox.x,bBox.y + (i + 1)* stepHeight,bBox.z + i * stepHeight,
					length,-stepHeight,0,
					"WALL8"
				));
				pColl->AddPolygon( new PxRectangle(
					bBox.x,bBox.y,bBox.z + i * stepHeight,
					0,stepHeight * (i+1), stepHeight,
					"WOOD2"
				));
				pColl->AddPolygon( new PxRectangle(
					bBox.x + length,bBox.y,bBox.z + i * stepHeight,
					0,stepHeight * (i+1), stepHeight,
					"WOOD2"
				));
			}
			pColl->AddPolygon( new PxRectangle(
				bBox.x,bBox.y,bBox.z + numSteps * stepHeight,
				length,numSteps * stepHeight, 0,
				"WOOD2"
			));
			break;
		case eDirectionSouth:
			for( int i = 0 ; i < numSteps; ++i )
			{
				pColl->AddPolygon( new PxRectangle(
					bBox.x,bBox.y + (i + 1)* stepHeight,bBox.z + (numSteps - i - 1 ) * stepHeight,
					length,0,stepHeight,
					"WOOD3"
				));
				pColl->AddPolygon( new PxRectangle(
					bBox.x,bBox.y + (i + 1)* stepHeight,bBox.z + (numSteps- i) * stepHeight,
					length,-stepHeight,0,
					"WALL8"
				));
				pColl->AddPolygon( new PxRectangle(
					bBox.x,bBox.y,bBox.z + (numSteps- i -1 ) * stepHeight,
					0,stepHeight * (i+1), stepHeight,
					"WOOD2"
				));
				pColl->AddPolygon( new PxRectangle(
					bBox.x + length,bBox.y,bBox.z + (numSteps- i - 1) * stepHeight,
					0,stepHeight * (i+1), stepHeight,
					"WOOD2"
				));
			}
			pColl->AddPolygon( new PxRectangle(
				bBox.x,bBox.y,bBox.z,
				length,numSteps * stepHeight, 0,
				"WOOD2"
			));
			break;
		case eDirectionWest:
			for( int i = 0 ; i < numSteps; ++i )
			{
				pColl->AddPolygon( new PxRectangle(
					bBox.x  +  (numSteps - i - 1)  * stepHeight , bBox.y + (i + 1)* stepHeight,bBox.z,
					stepHeight,0,length,
					"WOOD3"
				));
				pColl->AddPolygon( new PxRectangle(
					bBox.x + (numSteps- i) * stepHeight,bBox.y + (i + 1)* stepHeight,bBox.z,
					0,-stepHeight,length,
					"WALL8"
				));
				pColl->AddPolygon( new PxRectangle(
					bBox.x  + (numSteps- i -1 ) * stepHeight,bBox.y,bBox.z,
					stepHeight,stepHeight * (i+1), 0,
					"WOOD2"
				));
				pColl->AddPolygon( new PxRectangle(
					bBox.x + (numSteps- i -1 ) * stepHeight,bBox.y,bBox.z + length,
					stepHeight,stepHeight * (i+1), 0,
					"WOOD2"
				));
			}
			pColl->AddPolygon( new PxRectangle(
				bBox.x,bBox.y,bBox.z,
				0,numSteps * stepHeight, length,
				"WOOD2"
			));
			break;
		case eDirectionEast:
			for( int i = 0 ; i < numSteps; ++i )
			{
				pColl->AddPolygon( new PxRectangle(
					bBox.x  +  (i)  * stepHeight , bBox.y + (i + 1)* stepHeight,bBox.z,
					stepHeight,0,length,
					"WOOD3"
				));
				pColl->AddPolygon( new PxRectangle(
					bBox.x + (i ) * stepHeight,bBox.y + (i + 1)* stepHeight,bBox.z,
					0,-stepHeight,length,
					"WALL8"
				));
				pColl->AddPolygon( new PxRectangle(
					bBox.x  + (i ) * stepHeight,bBox.y,bBox.z,
					stepHeight,stepHeight * (i+1), 0,
					"WOOD2"
				));
				pColl->AddPolygon( new PxRectangle(
					bBox.x + (i) * stepHeight,bBox.y,bBox.z + length,
					stepHeight,stepHeight * (i+1), 0,
					"WOOD2"
				));
			}
			pColl->AddPolygon( new PxRectangle(
				bBox.x+  numSteps * stepHeight,bBox.y,bBox.z,
				0,numSteps * stepHeight, length,
				"WOOD2"
			));
			break;
	}
}

void PxSteps::Render()
{

}

