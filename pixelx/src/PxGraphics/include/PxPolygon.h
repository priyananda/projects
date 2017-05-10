#ifndef _PIXELX_POLYGON_H
#define _PIXELX_POLYGON_H

#include "PxVertex.h"
#include "../../PxPhysics/include/PxVector.h"

#include <vector>
using std::vector;

enum class TextureMode : uint8_t;

class PxPolygon
{
	GLint texture = -1;
	string texturename;
	GLint dList = -1;
	vector<std::unique_ptr<PxVertex>> vertices;

	// This will use only the first 3 vertices of the polygon.
	// If the vertex data is non planar, well, god knows!!
	void CalculateNormal();
public:
	// This is always in a consistent state
    PxVector Normal;

	// After this, normal is updated
	void AddVertex( const PxVertex &);
	void AddVertex(  GLfloat _x ,GLfloat _y ,GLfloat _z,GLuint _u = -1,GLuint _v = -1);
	void AddVertexF(GLfloat _x, GLfloat _y, GLfloat _z, GLfloat _u = -1, GLfloat _v = -1)
	{
		AddVertex(_x, _y, _z, static_cast<GLuint>(_u), static_cast<GLuint>(_v));
	}

	// Gets the n'th vertex( slow )
	PxVector operator[](int index) const;
	int GetVertexCount() const{ return (int)vertices.size(); }

	//This will create a vertex array, and then use that only to 
	//Render. Any verices added after call to Finalize will only
	//be used after the next call to Finalize
	void Finalize();

	// draws it!!
	void Render(bool isWireFrame = false);

	void SetTexture( GLuint texId ){ texture = texId; }
	void SetTexture( cstrref tname = "");

	string GetTexture(){ return texturename; }
	TextureMode GetTextureMode();
	vector<std::unique_ptr<PxVertex>> & GetVertices(){ return vertices; }

	PxPolygon()
	{
	}

	PxPolygon(const PxPolygon& other) :
		texture(other.texture),
		texturename(other.texturename),
		dList(other.dList)
	{
		for (const auto& spOtherVertex : other.vertices)
			this->vertices.emplace_back(std::make_unique<PxVertex>(*spOtherVertex));
	}
};

#endif

