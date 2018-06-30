//--------------------------------------------------------------------------
//
//	Numerous graphics definitions.
//	Using 3rd party math library GLM
//
//--------------------------------------------------------------------------

#ifndef GFXDEFS_H_
#define GFXDEFS_H_

#include <climits>
#include <gl/glew.h>
#include <gl/wglew.h>
#include <glm\glm.hpp>
#include <glm\gtc\constants.hpp>
#include <vector>

/*
======================================================================
	Vertex Structs
======================================================================
*/

enum EVertexType
{
	eVertexUnknown,
	eVertexPC,		// Position & colour
	eVertexPT,		// Position & texture coordinate
	eVertexPNC,		// Position, normal & colour
	eVertexPNT,		// Position, normal & texture coordinate 
	eVertexPNTC,	// Position, normal, tangent, colour
	eVertexPNTT,	// Position, normal, tangent, texture coordinate
	eVertexPNBTC,	// Position, normal, tangent, bi-tangent, colour
	eVertexPNBTT,	// Position, normal, tangent, bi-tangent, texture coordinate
	eVertTypeCount
};


// Base type
struct SVertexType
{
	glm::vec3 position;
};


struct SVertexTypePC : public SVertexType
{
	glm::vec3 colour;
};



struct SVertexTypePT : public SVertexType
{
	glm::vec2 textureCoord;
};


struct SVertexTypePNC : public SVertexType
{
	glm::vec3 normal;
	glm::vec4 colour;
};


struct SVertexTypePNT : public SVertexType
{
	glm::vec3 normal;
	glm::vec2 textureCoord;
};


struct SVertexTypePNTC : public SVertexType
{
	glm::vec3 normal;
	glm::vec3 tangent;
	glm::vec3 colour;
};


struct SVertexTypePNTT : public SVertexType
{
	glm::vec3 normal;
	glm::vec3 tangent;
	glm::vec2 textureCoord;
};


struct SVertexTypePNBTC : public SVertexType
{
	glm::vec3 normal;
	glm::vec3 tangent;
	glm::vec3 biTangent;
	glm::vec3 colour;
};


struct SVertexTypePNBTT : public SVertexType
{
	glm::vec3 normal;
	glm::vec3 tangent;
	glm::vec3 biTangent;
	glm::vec2 textureCoord;
};


// Helper method
inline int GetSizeOfVertexType(EVertexType type)
{
	switch(type)
	{
	case eVertexPC:
		return sizeof(SVertexTypePC);
		break;

	case eVertexPT:
		return sizeof(SVertexTypePT);
		break;

	case eVertexPNC:
		return sizeof(SVertexTypePNC);
		break;

	case eVertexPNT:
		return sizeof(SVertexTypePNT);
		break;

	case eVertexPNTC:
		return sizeof(SVertexTypePNTC);
		break;

	case eVertexPNTT:
		return sizeof(SVertexTypePNTT);
		break;

	case eVertexPNBTC:
		return sizeof(SVertexTypePNBTC);
		break;

	case eVertexPNBTT:
		return sizeof(SVertexTypePNBTT);
		break;

	default:
		return -1;
	}

	// Should'nt reach here anyway
	return -1;
}


/*
======================================================================
	Matrix stack
======================================================================
*/

class CMatrixStack	// <------------------- Not even used anywhere atm
{
private:
	std::vector<glm::mat4x4> m_vMatrices;

public:
	CMatrixStack(void) {};
	~CMatrixStack(void) {};

	// Adds matrix to top of stack
	void Push(const glm::mat4x4 &matrix)
	{
		m_vMatrices.push_back(matrix);
	}

	// Removes a matrix from the top of the stack and returns it
	glm::mat4x4 Pop(void)
	{
		glm::mat4x4 temp = m_vMatrices[(m_vMatrices.size() - 1)];
		m_vMatrices.pop_back();

		return temp;
	}

	// Clears stack
	void Empty(void)
	{
		m_vMatrices.clear();
	}

	// Gets the top matrix (doesn't remove it like pop)
	glm::mat4x4 GetTop(void)
	{
		return m_vMatrices[(m_vMatrices.size() - 1)];
	}
};


/*
======================================================================
	Internal Mesh Data structure
======================================================================
*/

struct MeshData
{
	std::string				m_ID;				// Unique ID of mesh
	SVertexType*			pVertices;			// Pointer to vertex data
	GLuint*					pIndices;			// Pointer to index data
	int						vertexCount;		// Vertex count
	int						indexCount;			// Index count
	EVertexType				vertexType;			// Format of vertices
			
	glm::vec3				minVertex;			// Smallest value for XYZ
	glm::vec3				maxVertex;			// Largest values for XYZ

	// Allocates memory for buffer for specified vertex type
	MeshData(EVertexType vertType, int vertCount, int idxCount)
	{
		vertexCount = vertCount;
		indexCount = idxCount;
		vertexType = vertType;

		// Create vertex array depending on type
		switch (vertType)
		{
		case eVertexPC:
			pVertices = new SVertexTypePC[vertCount];
			break;

		case eVertexPT:
			pVertices = new SVertexTypePT[vertCount];
			break;

		case eVertexPNC:
			pVertices = new SVertexTypePNC[vertCount];
			break;

		case eVertexPNT:
			pVertices = new SVertexTypePNT[vertCount];
			break;

		case eVertexPNTC:
			pVertices = new SVertexTypePNTC[vertCount];
			break;

		case eVertexPNTT:
			pVertices = new SVertexTypePNTT[vertCount];
			break;

		case eVertexPNBTC:
			pVertices = new SVertexTypePNBTC[vertCount];
			break;

		case eVertexPNBTT:
			pVertices = new SVertexTypePNBTT[vertCount];
			break;

		default:
			pVertices = nullptr;
			break;
		}

		// Create index array
		pIndices = new unsigned int[idxCount];
	}

	// Copy constructor, copies everything including arrays
	MeshData(const MeshData& other) {
		m_ID = other.m_ID;
		pVertices = other.pVertices;
		pIndices = other.pIndices;
		vertexCount = other.vertexCount;
		indexCount = other.indexCount;
		vertexType = other.vertexType;
		minVertex = other.minVertex;
		maxVertex = other.maxVertex;

		// Create vertex array depending on type
		switch (vertexType)
		{
		case eVertexPC:
			pVertices = new SVertexTypePC[vertexCount];
			memcpy(pVertices, other.pVertices, GetSizeOfVertexType(eVertexPC) * vertexCount);
			break;

		case eVertexPT:
			pVertices = new SVertexTypePT[vertexCount];
			memcpy(pVertices, other.pVertices, GetSizeOfVertexType(eVertexPT) * vertexCount);
			break;

		case eVertexPNC:
			pVertices = new SVertexTypePNC[vertexCount];
			memcpy(pVertices, other.pVertices, GetSizeOfVertexType(eVertexPNC) * vertexCount);
			break;

		case eVertexPNT:
			pVertices = new SVertexTypePNT[vertexCount];
			memcpy(pVertices, other.pVertices, GetSizeOfVertexType(eVertexPNT) * vertexCount);
			break;

		case eVertexPNTC:
			pVertices = new SVertexTypePNTC[vertexCount];
			memcpy(pVertices, other.pVertices, GetSizeOfVertexType(eVertexPNTC) * vertexCount);
			break;

		case eVertexPNTT:
			pVertices = new SVertexTypePNTT[vertexCount];
			memcpy(pVertices, other.pVertices, GetSizeOfVertexType(eVertexPNTT) * vertexCount);
			break;

		case eVertexPNBTC:
			pVertices = new SVertexTypePNBTC[vertexCount];
			memcpy(pVertices, other.pVertices, GetSizeOfVertexType(eVertexPNBTC) * vertexCount);
			break;

		case eVertexPNBTT:
			pVertices = new SVertexTypePNBTT[vertexCount];
			memcpy(pVertices, other.pVertices, GetSizeOfVertexType(eVertexPNBTT) * vertexCount);
			break;

		default:
			pVertices = nullptr;
			break;
		}

		// Create index array
		pIndices = new unsigned int[indexCount];
		memcpy(pIndices, other.pIndices, sizeof(unsigned int) * indexCount);
	}

	MeshData() {
		m_ID = "";
		pVertices = nullptr;
		pIndices = nullptr;
		vertexCount = 0;
		indexCount = 0;
		vertexType = eVertexPC;
	}

	~MeshData(void)
	{
		CleanUp();
	}

	void operator=(const MeshData& other) {
		m_ID = other.m_ID;
		pVertices = other.pVertices;
		pIndices = other.pIndices;
		vertexCount = other.vertexCount;
		indexCount = other.indexCount;
		vertexType = other.vertexType;
		minVertex = other.minVertex;
		maxVertex = other.maxVertex;
	}

	void CleanUp(void)
	{
		if(pIndices)
			delete [] pIndices;
		

		if(pVertices)
			delete [] pVertices;

		pIndices = nullptr;
		pVertices = nullptr;
	}
};



/*
======================================================================
	Light types
======================================================================
*/

enum ELightType
{
	eLightNone,
	eLightAmb,
	eLightDir,
	eLightPoint,
	eLightSpot,
	eTotalLights
};


struct SLight
{
	ELightType		type;
	glm::vec3		colour;
	glm::vec3		direction;
	glm::vec3		position;
	float			intensity;
	float			attenuation;
	float			coneAngle;
	float			coneAttenuation;

	SLight()
	{
		type = ELightType::eLightNone;
		colour = glm::vec3(0, 0, 0);
		direction = glm::vec3(0, 0, 0);
		position = glm::vec3(0, 0, 0);
		intensity = 0;
		attenuation = 0;
		coneAngle = 0;
		coneAttenuation = 0;
	}
};


/*
======================================================================
	Texture Formats
======================================================================
*/

enum ETextureFormat
{
	eTextureFormatNone,
	eTextureFormatBMP,				// Bitmap
	eTextureFormatTGA,				// Targa
	eTextureFormatPNG,				// PNG
	eTextureFormatTotal
};


const std::string TEXTURETYPE_DIFFUSE = "texture_diffuse";
const std::string TEXTURETYPE_SPECULAR = "texture_specular";


struct STexture
{
	std::string textureID;
	std::string type;
};


/*
======================================================================
Material Format
======================================================================
*/

// Using CMaterial instead at the moment
struct SMaterial {
	glm::vec3 diffuseColour;
	glm::vec3 specularColour;
	double specularExp;
	std::string textureID;
};


#endif