#ifndef _PIXELX_QUAKE3MODEL_H
#define _PIXELX_QUAKE3MODEL_H

#include "..\..\PxPhysics\include\PxVector.h"
#include "PxModel.h"

#include <vector>
using std::vector;

// This file stores all of our structures and classes (besides the modular model ones in main.h)
// in order to read in and display a Quake3 character.  The file format is of type
// .MD3 and comes in many different files for each main body part section.  We convert
// these Quake3 structures to our own structures in Md3.cpp so that we are not dependant
// on their model data structures.  You can do what ever you want, but I like mine :P :)

struct tMaterialInfo
{
	char  strName[255];			// The texture name
	char  strFile[255];			// The texture file name (If this is set it's a texture map)
	BYTE  color[3];				// The color of the object (R, G, B)
	int   texureId;				// the texture ID
	float uTile;				// u tiling of texture  
	float vTile;				// v tiling of texture	
	float uOffset;			    // u offset of texture
	float vOffset;				// v offset of texture

	tMaterialInfo():texureId(0){}
} ;

struct tFace
{
	int vertIndex[3];			// indicies for the verts that make up this triangle
	int coordIndex[3];			// indicies for the tex coords to texture this face
};

class CVector2 
{
public:
	float x, y;
};
// This holds all the information for our model/scene. 
// You should eventually turn into a robust class that 
// has loading/drawing/querying functions like:
// LoadModel(...); DrawObject(...); DrawModel(...); DestroyModel(...);
struct t3DObject 
{
	int  numOfVerts;			// The number of verts in the model
	int  numOfFaces;			// The number of faces in the model
	int  numTexVertex;			// The number of texture coordinates
	int  materialID;			// The texture ID to use, which is the index into our texture array
	bool bHasTexture;			// This is TRUE if there is a texture map for this object
	char strName[255];			// The name of the object
	PxVector  *pVerts;			// The object's vertices
	PxVector  *pNormals;		// The object's normals
	CVector2  *pTexVerts;		// The texture's UV coordinates
	tFace *pFaces;				// The faces information of the object
};

struct t3DModel 
{
	int numOfObjects;					// The number of objects in the model
	int numOfMaterials;					// The number of materials for the model
	vector<tMaterialInfo> pMaterials;	// The list of material information (Textures and colors)
	vector<t3DObject> pObject;			// The object list for our model
	
	int numOfTags;						// This stores the number of tags in the model
	t3DModel	**pLinks;				// This stores a list of pointers that are linked to this model
	struct tMd3Tag		*pTags;			// This stores all the tags for the model animations
};

// This holds the header information that is read in at the beginning of the file
struct tMd3Header
{ 
	char	fileID[4];					// This stores the file ID - Must be "IDP3"
	int		version;					// This stores the file version - Must be 15
	char	strFile[68];				// This stores the name of the file
	int		numFrames;					// This stores the number of animation frames
	int		numTags;					// This stores the tag count
	int		numMeshes;					// This stores the number of sub-objects in the mesh
	int		numMaxSkins;				// This stores the number of skins for the mesh
	int		headerSize;					// This stores the mesh header size
	int		tagStart;					// This stores the offset into the file for tags
	int		tagEnd;						// This stores the end offset into the file for tags
	int		fileSize;					// This stores the file size
};

// This structure is used to read in the mesh data for the .md3 models
struct tMd3MeshInfo
{
	char	meshID[4];					// This stores the mesh ID (We don't care)
	char	strName[68];				// This stores the mesh name (We do care)
	int		numMeshFrames;				// This stores the mesh aniamtion frame count
	int		numSkins;					// This stores the mesh skin count
	int     numVertices;				// This stores the mesh vertex count
	int		numTriangles;				// This stores the mesh face count
	int		triStart;					// This stores the starting offset for the triangles
	int		headerSize;					// This stores the header size for the mesh
	int     uvStart;					// This stores the starting offset for the UV coordinates
	int		vertexStart;				// This stores the starting offset for the vertex indices
	int		meshSize;					// This stores the total mesh size
};

// This is our tag structure for the .MD3 file format.  These are used link other
// models to and the rotate and transate the child models of that model.
struct tMd3Tag
{
	char		strName[64];			// This stores the name of the tag (I.E. "tag_torso")
	PxVector	vPosition;				// This stores the translation that should be performed
	float		rotation[3][3];			// This stores the 3x3 rotation matrix for this frame
};

// This stores the bone information (useless as far as I can see...)
struct tMd3Bone
{
	float	mins[3];					// This is the min (x, y, z) value for the bone
	float	maxs[3];					// This is the max (x, y, z) value for the bone
	float	position[3];				// This supposedly stores the bone position???
	float	scale;						// This stores the scale of the bone
	char	creator[16];				// The modeler used to create the model (I.E. "3DS Max")
};


// This stores the normals and vertex indices 
struct tMd3Triangle
{
   signed short	 vertex[3];				// The vertex for this face (scale down by 64.0f)
   unsigned char normal[2];				// This stores some crazy normal values (not sure...)
};


// This stores the indices into the vertex and texture coordinate arrays
struct tMd3Face
{
   int vertexIndices[3];				
};


// This stores UV coordinates
struct tMd3TexCoord
{
   float textureCoord[2];
};


// This stores a skin name (We don't use this, just the name of the model to get the texture)
struct tMd3Skin 
{
	char strName[68];
};


// This class handles all of the main loading code
class PxQuake3ModelLoader
{

public:

	// This inits the data members
	PxQuake3ModelLoader();								

	// This is the function that you call to load the MD3 model
	bool ImportMD3(t3DModel *pModel, char *strFileName);

	// This loads a model's .skin file
	bool LoadSkin(t3DModel *pModel, LPSTR strSkin);

	// This loads a weapon's .shader file
	bool LoadShader(t3DModel *pModel, LPSTR strShader);

private:


	// This reads in the data from the MD3 file and stores it in the member variables,
	// later to be converted to our cool structures so we don't depend on Quake3 stuff.
	void ReadMD3Data(t3DModel *pModel);

	// This converts the member variables to our pModel structure, and takes the model
	// to be loaded and the mesh header to get the mesh info.
	void ConvertDataStructures(t3DModel *pModel, tMd3MeshInfo meshHeader);

	// This frees memory and closes the file
	void CleanUp();
	
	// Member Variables		

	// The file pointer
	FILE *m_FilePointer;

	tMd3Header				m_Header;			// The header data

	tMd3Skin				*m_pSkins;			// The skin name data (not used)
	tMd3TexCoord			*m_pTexCoords;		// The texture coordinates
	tMd3Face				*m_pTriangles;		// Face/Triangle data
	tMd3Triangle			*m_pVertices;		// Vertex/UV indices
	tMd3Bone				*m_pBones;			// This stores the bone data (not used)
};

// This is our model class that we use to load and draw and free the Quake3 characters
class PxQuake3ModelCore : public PxModelCore
{
public:
	void Register(PxPolygonCollection *){}
	void Render();
	void Animate( int StartFrame , int EndFrame, float interp);
	void SetTexture( cstrref name ){}
public:

	// These our our init and deinit() C++ functions (Constructor/Deconstructor)
	PxQuake3ModelCore(cstrref pathname);
	~PxQuake3ModelCore();
	
	// This loads the model from a path and name prefix.   It takes the path and
	// model name prefix to be added to _upper.md3, _lower.md3 or _head.md3.
	bool LoadModel(
		char *, char * , char *, char *, char *, char *, char *
	);

	// This loads the weapon and takes the same path and model name to be added to .md3
	bool LoadWeapon(LPSTR strPath, LPSTR strModel);

	// This links a model to another model (pLink) so that it's the parent of that child.
	// The strTagName is the tag, or joint, that they will be linked at (I.E. "tag_torso").
	void LinkModel(t3DModel *pModel, t3DModel *pLink, LPSTR strTagName);

	// This renders the character to the screen
	void DrawModel();

	// This frees the character's data
	void DestroyModel(t3DModel *pModel);
	
private:

	// This loads the models textures with a given path
	void LoadModelTextures(t3DModel *pModel, LPSTR strPath);

	// This recursively draws the character models, starting with the lower.md3 model
	void DrawLink(t3DModel *pModel);

	// This a md3 model to the screen (not the whole character)
	void RenderModel(t3DModel *pModel);

	// Member Variables

	// This stores the texture array for each of the textures assigned to this model
	UINT m_Textures[100];	

	// This stores a list of all the names of the textures that have been loaded.  
	// This was created so that we could check to see if a texture that is assigned
	// to a mesh has already been loaded.  If so, then we don't need to load it again
	// and we can assign the textureID to the same textureID as the first loaded texture.
	// You could get rid of this variable by doing something tricky in the texture loading
	// function, but I didn't want to make it too confusing to load the textures.
	vector<string> strTextures;

	// These are are models for the character's head and upper and lower body parts
	t3DModel m_Head;
	t3DModel m_Upper;
	t3DModel m_Lower;

	// This store the players weapon model (optional load)
	t3DModel m_Weapon;
};


#endif

