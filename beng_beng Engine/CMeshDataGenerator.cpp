#include "CMeshDataGenerator.h"
#include "CVoxel.h"

CMeshDataGenerator::CMeshDataGenerator()
{
}


CMeshDataGenerator::~CMeshDataGenerator()
{
}


//-------------------------------------------------------------------------------------
//
//	CreateTriangle(..)
//
//	Params:
//	geometryID		-	String name stored in MeshData
//	size			-	size of triangle
//	type			-	type of vertices to use
//	colour			-	colour of triangle if vertex type supports colour
//
//	Description:
//	Method creates a single triangle specifed of size "size".
//	Note that this creates a equilateral triangle hence only the single param of size.
//
//-------------------------------------------------------------------------------------
MeshData* CMeshDataGenerator::CreateTriangle(const std::string &geometryID, float size, EVertexType type,
	const glm::vec4 &colour)
{
	// Create mesh data
	MeshData* pNewGeometry = nullptr;

	// Input validity check
	if (geometryID != "" && size > 0)
	{
		pNewGeometry = new MeshData(type, 3, 3);
		pNewGeometry->m_ID = geometryID;

		// Distance of each vertex from origin (0,0,0)
		float dist = size / 2;

		// Calculate vertex data
		switch (type)
		{
		case eVertexPC:
			/*
			Used a simple approach for creating a triangle.
			Think of placing the triangle in a square. Thats how the points are positioned.
				 1
				 *
				/ \
			   /   \
			2 *-----* 3
			*/

			SVertexTypePC* pVertexPC;

			// Top vertex
			pVertexPC = static_cast<SVertexTypePC*>(pNewGeometry->pVertices);
			pVertexPC[0].position.x = 0;
			pVertexPC[0].position.y = dist;
			pVertexPC[0].position.z = 0;
			pVertexPC[0].colour.x = colour.x;
			pVertexPC[0].colour.y = colour.y;
			pVertexPC[0].colour.z = colour.z;

			// Bottom left vertex
			pVertexPC[1].position.x = -dist;
			pVertexPC[1].position.y = -dist;
			pVertexPC[1].position.z = 0;
			pVertexPC[1].colour.x = colour.x;
			pVertexPC[1].colour.y = colour.y;
			pVertexPC[1].colour.z = colour.z;

			// Bottom right vertex
			pVertexPC[2].position.x = dist;
			pVertexPC[2].position.y = -dist;
			pVertexPC[2].position.z = 0;
			pVertexPC[2].colour.x = colour.x;
			pVertexPC[2].colour.y = colour.y;
			pVertexPC[2].colour.z = colour.z;
			break;

		case eVertexPT:
			/*
			Used a simple approach for creating a triangle.
			Think of placing the triangle in a square. Thats how the points are positioned.
				 1
				 *
				/ \
			   /   \
			2 *-----* 3
			*/

			SVertexTypePT* pVertexPT;

			// Top vertex
			pVertexPT = static_cast<SVertexTypePT*>(pNewGeometry->pVertices);
			pVertexPT[0].position.x = 0;
			pVertexPT[0].position.y = dist;
			pVertexPT[0].position.z = 0;
			pVertexPT[0].textureCoord.x = 0.5;
			pVertexPT[0].textureCoord.y = 1;

			// Bottom left vertex
			pVertexPT[1].position.x = -dist;
			pVertexPT[1].position.y = -dist;
			pVertexPT[1].position.z = 0;
			pVertexPT[1].textureCoord.x = 0;
			pVertexPT[1].textureCoord.y = 0;

			// Bottom right vertex
			pVertexPT[2].position.x = dist;
			pVertexPT[2].position.y = -dist;
			pVertexPT[2].position.z = 0;
			pVertexPT[2].textureCoord.x = 1;
			pVertexPT[2].textureCoord.y = 0;
			break;

		case eVertexPNC:
			/*
			Used a simple approach for creating a triangle.
			Think of placing the triangle in a square. Thats how the points are positioned.
				 1
				 *
				/ \
			   /   \
			2 *-----* 3
			*/

			SVertexTypePNC* pVert;

			// Top vertex
			pVert = static_cast<SVertexTypePNC*>(pNewGeometry->pVertices);
			pVert[0].position.x = 0;
			pVert[0].position.y = dist;
			pVert[0].position.z = 0;
			pVert[0].normal.x = 0;
			pVert[0].normal.y = 0;
			pVert[0].normal.z = 1;
			pVert[0].colour.x = colour.x;
			pVert[0].colour.y = colour.y;
			pVert[0].colour.y = colour.z;
			pVert[0].colour.w = colour.w;

			// Bottom left vertex
			pVert[1].position.x = -dist;
			pVert[1].position.y = -dist;
			pVert[1].position.z = 0;
			pVert[1].normal.x = 0;
			pVert[1].normal.y = 0;
			pVert[1].normal.z = 1;
			pVert[1].colour.x = colour.x;
			pVert[1].colour.y = colour.y;
			pVert[1].colour.y = colour.z;
			pVert[1].colour.w = colour.w;

			// Bottom right vertex
			pVert[2].position.x = dist;
			pVert[2].position.y = -dist;
			pVert[2].position.z = 0;
			pVert[2].normal.x = 0;
			pVert[2].normal.y = 0;
			pVert[2].normal.z = 1;
			pVert[2].colour.x = colour.x;
			pVert[2].colour.y = colour.y;
			pVert[2].colour.y = colour.z;
			pVert[2].colour.w = colour.w;
			break;

		case eVertexPNT:
			/*
			Used a simple approach for creating a triangle, therefore will probably not be equilateral.
			Think of placing the triangle in a square. Thats how the points are positioned.
				 1
				 *
				/ \
			   /   \
			2 *-----* 3
			*/

			SVertexTypePNT* pVertexPNT;

			// Top vertex
			pVertexPNT = static_cast<SVertexTypePNT*>(pNewGeometry->pVertices);
			pVertexPNT[0].position.x = 0;
			pVertexPNT[0].position.y = dist;
			pVertexPNT[0].position.z = 0;
			pVertexPNT[0].normal.x = 0;
			pVertexPNT[0].normal.y = 0;
			pVertexPNT[0].normal.z = 1;
			pVertexPNT[0].textureCoord.x = 0.5;
			pVertexPNT[0].textureCoord.y = 1;

			// Bottom left vertex
			pVertexPNT[1].position.x = -dist;
			pVertexPNT[1].position.y = -dist;
			pVertexPNT[1].position.z = 0;
			pVertexPNT[1].normal.x = 0;
			pVertexPNT[1].normal.y = 0;
			pVertexPNT[1].normal.z = 1;
			pVertexPNT[1].textureCoord.x = 0;
			pVertexPNT[1].textureCoord.y = 0;

			// Bottom right vertex
			pVertexPNT[2].position.x = dist;
			pVertexPNT[2].position.y = -dist;
			pVertexPNT[2].position.z = 0;
			pVertexPNT[2].normal.x = 0;
			pVertexPNT[2].normal.y = 0;
			pVertexPNT[2].normal.z = 1;
			pVertexPNT[2].textureCoord.x = 1;
			pVertexPNT[2].textureCoord.y = 0;
			break;

			// shouldn't end up here (invalid vertex type)
		default:
			delete pNewGeometry;
			pNewGeometry = nullptr;
			break;
		}

		if (pNewGeometry)
		{
			// Add indices
			pNewGeometry->pIndices[0] = 0;
			pNewGeometry->pIndices[1] = 1;
			pNewGeometry->pIndices[2] = 2;
		}
	}

	return pNewGeometry;
}


//-------------------------------------------------------------------------------------
//
//	CreateQuad(..)
//
//	Params:
//	geometryID		-	String name stored in MeshData
//	size			-	size of the quad
//	type			-	type of vertices to use
//	colour			-	colour of triangle if vertex type supports colour
//
//	Description:
//	Method creates a 2D quad consisting of 2 triangles
//
//-------------------------------------------------------------------------------------
MeshData* CMeshDataGenerator::CreateQuad(const std::string &geometryID, float size, EVertexType type,
	const glm::vec4 &colour)
{
	MeshData *pNewGeometry = nullptr;

	// Check valid inputs
	if (geometryID != "" && size > 0)
	{
		pNewGeometry = new MeshData(type, 4, 6);

		pNewGeometry->m_ID = geometryID;

		// Basing mesh at origin 0,0,0
		float dist = size / 2;

		// Create vertex data
		switch (type)
		{
		case eVertexPC:

			SVertexTypePC *pVertPC;

			pVertPC = static_cast<SVertexTypePC*>(pNewGeometry->pVertices);

			pVertPC[0].position.x = -dist;
			pVertPC[0].position.y = dist;
			pVertPC[0].position.z = 0;
			pVertPC[0].colour.r = colour.r;
			pVertPC[0].colour.g = colour.g;
			pVertPC[0].colour.b = colour.b;

			pVertPC[1].position.x = dist;
			pVertPC[1].position.y = dist;
			pVertPC[1].position.z = 0;
			pVertPC[1].colour.r = colour.r;
			pVertPC[1].colour.g = colour.g;
			pVertPC[1].colour.b = colour.b;

			pVertPC[2].position.x = -dist;
			pVertPC[2].position.y = -dist;
			pVertPC[2].position.z = 0;
			pVertPC[2].colour.r = colour.r;
			pVertPC[2].colour.g = colour.g;
			pVertPC[2].colour.b = colour.b;

			pVertPC[3].position.x = dist;
			pVertPC[3].position.y = -dist;
			pVertPC[3].position.z = 0;
			pVertPC[3].colour.r = colour.r;
			pVertPC[3].colour.g = colour.g;
			pVertPC[3].colour.b = colour.b;
			break;

		case eVertexPT:
			SVertexTypePT *pVertPT;

			pVertPT = static_cast<SVertexTypePT*>(pNewGeometry->pVertices);

			pVertPT[0].position.x = -dist;
			pVertPT[0].position.y = dist;
			pVertPT[0].position.z = 0;
			pVertPT[0].textureCoord.x = 0.f;
			pVertPT[0].textureCoord.y = 1.f;

			pVertPT[1].position.x = dist;
			pVertPT[1].position.y = dist;
			pVertPT[1].position.z = 0;
			pVertPT[1].textureCoord.x = 1.f;
			pVertPT[1].textureCoord.y = 1.f;

			pVertPT[2].position.x = -dist;
			pVertPT[2].position.y = -dist;
			pVertPT[2].position.z = 0;
			pVertPT[2].textureCoord.x = 0.f;
			pVertPT[2].textureCoord.y = 0.f;

			pVertPT[3].position.x = dist;
			pVertPT[3].position.y = -dist;
			pVertPT[3].position.z = 0;
			pVertPT[3].textureCoord.x = 1.f;
			pVertPT[3].textureCoord.y = 0.f;
			break;

		case eVertexPNC:
			SVertexTypePNC *pVertPNC;
			pVertPNC = static_cast<SVertexTypePNC*>(pNewGeometry->pVertices);

			pVertPNC[0].position.x = -dist;
			pVertPNC[0].position.y = dist;
			pVertPNC[0].position.z = 0;
			pVertPNC[0].normal.x = 0;
			pVertPNC[0].normal.y = 0;
			pVertPNC[0].normal.z = 1;
			pVertPNC[0].colour.r = colour.r;
			pVertPNC[0].colour.g = colour.g;
			pVertPNC[0].colour.b = colour.b;

			pVertPNC[1].position.x = dist;
			pVertPNC[1].position.y = dist;
			pVertPNC[1].position.z = 0;
			pVertPNC[1].normal.x = 0;
			pVertPNC[1].normal.y = 0;
			pVertPNC[1].normal.z = 1;
			pVertPNC[1].colour.r = colour.r;
			pVertPNC[1].colour.g = colour.g;
			pVertPNC[1].colour.b = colour.b;

			pVertPNC[2].position.x = -dist;
			pVertPNC[2].position.y = -dist;
			pVertPNC[2].position.z = 0;
			pVertPNC[2].normal.x = 0;
			pVertPNC[2].normal.y = 0;
			pVertPNC[2].normal.z = 1;
			pVertPNC[2].colour.r = colour.r;
			pVertPNC[2].colour.g = colour.g;
			pVertPNC[2].colour.b = colour.b;

			pVertPNC[3].position.x = dist;
			pVertPNC[3].position.y = -dist;
			pVertPNC[3].position.z = 0;
			pVertPNC[3].normal.x = 0;
			pVertPNC[3].normal.y = 0;
			pVertPNC[3].normal.z = 1;
			pVertPNC[3].colour.r = colour.r;
			pVertPNC[3].colour.g = colour.g;
			pVertPNC[3].colour.b = colour.b;
			break;

		case eVertexPNT:
			SVertexTypePNT *pVertPNT;

			pVertPNT = static_cast<SVertexTypePNT*>(pNewGeometry->pVertices);

			pVertPNT[0].position.x = -dist;
			pVertPNT[0].position.y = dist;
			pVertPNT[0].position.z = 0;
			pVertPNT[0].normal.x = 0;
			pVertPNT[0].normal.y = 0;
			pVertPNT[0].normal.z = 1;
			pVertPNT[0].textureCoord.x = 0.f;
			pVertPNT[0].textureCoord.y = 1.f;

			pVertPNT[1].position.x = dist;
			pVertPNT[1].position.y = dist;
			pVertPNT[1].position.z = 0;
			pVertPNT[1].normal.x = 0;
			pVertPNT[1].normal.y = 0;
			pVertPNT[1].normal.z = 1;
			pVertPNT[1].textureCoord.x = 1.f;
			pVertPNT[1].textureCoord.y = 1.f;

			pVertPNT[2].position.x = -dist;
			pVertPNT[2].position.y = -dist;
			pVertPNT[2].position.z = 0;
			pVertPNT[2].normal.x = 0;
			pVertPNT[2].normal.y = 0;
			pVertPNT[2].normal.z = 1;
			pVertPNT[2].textureCoord.x = 0.f;
			pVertPNT[2].textureCoord.y = 0.f;

			pVertPNT[3].position.x = dist;
			pVertPNT[3].position.y = -dist;
			pVertPNT[3].position.z = 0;
			pVertPNT[3].normal.x = 0;
			pVertPNT[3].normal.y = 0;
			pVertPNT[3].normal.z = 1;
			pVertPNT[3].textureCoord.x = 1.f;
			pVertPNT[3].textureCoord.y = 0.f;
			break;

			// Should not end up here
		default:
			delete pNewGeometry;
			pNewGeometry = nullptr;
			break;
		}

		if (pNewGeometry)
		{
			// Create index data
			pNewGeometry->pIndices[0] = 0;
			pNewGeometry->pIndices[1] = 2;
			pNewGeometry->pIndices[2] = 1;
			pNewGeometry->pIndices[3] = 1;
			pNewGeometry->pIndices[4] = 2;
			pNewGeometry->pIndices[5] = 3;
		}
	}

	return pNewGeometry;
}



//-------------------------------------------------------------------------------------
//	
//	CreatePlane(..)
//
//	Params:
//	geometryID		-	String name stored in MeshData
//	size			-	size of the quad
//	type			-	type of vertices to use
//	colour			-	colour of triangle if vertex type supports colour
//
//	Description:
//	Method creates a 2D quad consisting of 2 triangles
//
//-------------------------------------------------------------------------------------
MeshData* CMeshDataGenerator::CreatePlane(const std::string &geometryID, float size, EVertexType type, unsigned int numFaces,
	const glm::vec4 &colour)
{
	// Number of vertices on plane
	int totalVerts = (numFaces + 1) * (numFaces + 1);

	// Calculate number of indices
	//
	//	numFaces * numFaces = number of faces/cells on a face of cube
	//	2 = 2 triangles per side
	//	3 = 3 indices per triangle
	//
	int numIndices = ((numFaces * numFaces) * 2) * 3;

	MeshData *pNewGeometry = new MeshData(type, totalVerts, numIndices);

	pNewGeometry->m_ID = geometryID;

	// Step size between vertices
	float incrementDist = size / numFaces;
	int vertexCounter = 0;

	// Create vertex data
	switch(type)
	{
	case eVertexPC:

		SVertexTypePC *pVertPC;

		pVertPC = static_cast<SVertexTypePC*>(pNewGeometry->pVertices);

		// Generate plane vertices
		for(int y = 0; y < (int)(numFaces + 1); y++)
		{
			float xStart = -(size / 2);
			float yStart = 0;
			float zStart = (size / 2);

			for(int x = 0; x < (int)(numFaces + 1); x++)
			{
				pVertPC[vertexCounter].position.x = xStart + (x * incrementDist);
				pVertPC[vertexCounter].position.y = yStart;
				pVertPC[vertexCounter].position.z = zStart - (y * incrementDist);
				pVertPC[vertexCounter].colour.x = colour.x;
				pVertPC[vertexCounter].colour.y = colour.y;
				pVertPC[vertexCounter].colour.z = colour.z;

				vertexCounter++;
			}
		}
		break;

	case eVertexPT:
		SVertexTypePT *pVertPT;

		pVertPT = static_cast<SVertexTypePT*>(pNewGeometry->pVertices);

		// Generate plane vertices
		for(int y = 0; y < (int)(numFaces + 1); y++)
		{
			float xStart = -(size / 2);
			float yStart = 0;
			float zStart = (size / 2);

			for(int x = 0; x < (int)(numFaces + 1); x++)
			{
				pVertPT[vertexCounter].position.x = xStart + (x * incrementDist);
				pVertPT[vertexCounter].position.y = yStart;
				pVertPT[vertexCounter].position.z = zStart - (y * incrementDist);
				pVertPT[vertexCounter].textureCoord.x = (float)x / (float)numFaces;
				pVertPT[vertexCounter].textureCoord.y = ((float)(numFaces + 1) - (float)y) / (float)numFaces;

				vertexCounter++;
			}
		}
		break;

	case eVertexPNC:
		SVertexTypePNC *pVertPNC;

		pVertPNC = static_cast<SVertexTypePNC*>(pNewGeometry->pVertices);

		// Generate plane vertices
		for(int y = 0; y < (int)(numFaces + 1); y++)
		{
			float xStart = -(size / 2);
			float yStart = 0;
			float zStart = (size / 2);

			for(int x = 0; x < (int)(numFaces + 1); x++)
			{
				pVertPNC[vertexCounter].position.x = xStart + (x * incrementDist);
				pVertPNC[vertexCounter].position.y = yStart;
				pVertPNC[vertexCounter].position.z = zStart - (y * incrementDist);
				pVertPNC[vertexCounter].normal.x = 0;
				pVertPNC[vertexCounter].normal.y = 1;
				pVertPNC[vertexCounter].normal.z = 0;
				pVertPNC[vertexCounter].colour.x = colour.x;
				pVertPNC[vertexCounter].colour.y = colour.y;
				pVertPNC[vertexCounter].colour.z = colour.z;

				vertexCounter++;
			}
		}
		break;

	case eVertexPNT:
		SVertexTypePNT *pVertPNT;

		pVertPNT = static_cast<SVertexTypePNT*>(pNewGeometry->pVertices);

		// Generate plane vertices
		for(int y = 0; y < (int)(numFaces + 1); y++)
		{
			float xStart = -(size / 2);
			float yStart = 0;
			float zStart = (size / 2);

			for(int x = 0; x < (int)(numFaces + 1); x++)
			{
				pVertPNT[vertexCounter].position.x = xStart + (x * incrementDist);
				pVertPNT[vertexCounter].position.y = yStart;
				pVertPNT[vertexCounter].position.z = zStart - (y * incrementDist);
				pVertPNT[vertexCounter].normal.x = 0;
				pVertPNT[vertexCounter].normal.y = 1;
				pVertPNT[vertexCounter].normal.z = 0;
				pVertPNT[vertexCounter].textureCoord.x = (float)x / (float)numFaces;
				pVertPNT[vertexCounter].textureCoord.y = ((float)(numFaces + 1) - (float)y) / (float)numFaces;

				vertexCounter++;
			}
		}
		break;

		// Should not end up here
	default:
		delete pNewGeometry;
		pNewGeometry = NULL;
		break;
	}

	// Create index data
	int indexCounter = 0;
	int vIndex = 0;
	int numVertsX = numFaces + 1;

	// Loops for generating indices for a face
	for (int y = 0; y < (int)numFaces; y++)
	{
		for (int x = 0; x < (int)numFaces; x++)
		{
			// first triangle
			pNewGeometry->pIndices[indexCounter++] = vIndex;
			pNewGeometry->pIndices[indexCounter++] = vIndex + numVertsX + 1;
			pNewGeometry->pIndices[indexCounter++] = vIndex + numVertsX;


			// second triangle
			pNewGeometry->pIndices[indexCounter++] = vIndex;
			pNewGeometry->pIndices[indexCounter++] = vIndex + 1;
			pNewGeometry->pIndices[indexCounter++] = vIndex + numVertsX + 1;

			vIndex++;
		}

		vIndex++;
	}

	return pNewGeometry;
}



//-------------------------------------------------------------------------------------
//
//	CreateCube(..)
//
//	Params:
//	geometryID		-	String name stored in MeshData
//	size			-	size of the quad
//	type			-	type of vertices to use
//	numFaces		-	the number of faces per each axis of a side
//	colour			-	colour of triangle if vertex type supports colour
//
//	Description:
//	Method creates a 2D quad consisting of 2 triangles.
//	Note: Cube generated as we are looking right at it. i.e. Left face is our (perspective) left
//		not the cube's left.
//
//-------------------------------------------------------------------------------------
MeshData* CMeshDataGenerator::CreateCube(const std::string &geometryID, float size, EVertexType type, unsigned int numFaces,
	const glm::vec4 &colour)
{
	// Number of vertices per side of cube
	int faceVerts = (numFaces + 1) * (numFaces + 1);

	// Total vertices
	int totalVerts = faceVerts * 6;		// 6 - total number of sides of a cube

	// Calculate number of indices
	//
	//	numFaces * numFaces = number of faces/cells on a face of cube
	//	6 = number of sides on cube
	//	2 = 2 triangles per side
	//	3 = 3 indices per triangle
	//
	int numIndices = ((numFaces * numFaces * 6) * 2) * 3;

	// Create mesh data
	MeshData *pMeshData = new MeshData(type, totalVerts, numIndices);

	pMeshData->m_ID = geometryID;

	// Step size between vertices
	float incrementDist = size / numFaces;
	int vertexCounter = 0;

	switch(type)
	{
	case eVertexPC:
		{
			SVertexTypePC *pVertexPC = static_cast<SVertexTypePC*>(pMeshData->pVertices);

			// Front face
			for(int y = 0; y < (int)(numFaces + 1); y++)
			{
				float xStart = -(size / 2);
				float yStart = size / 2;
				float zStart = size / 2;

				for(int x = 0; x < (int)(numFaces + 1); x++)
				{
					pVertexPC[vertexCounter].position.x = xStart + (x * incrementDist);
					pVertexPC[vertexCounter].position.y = yStart - (y * incrementDist);
					pVertexPC[vertexCounter].position.z = zStart;
					pVertexPC[vertexCounter].colour.x = colour.x;
					pVertexPC[vertexCounter].colour.y = colour.y;
					pVertexPC[vertexCounter].colour.z = colour.z;

					vertexCounter++;
				}
			}

			// bottom face
			for(int y = 0; y < (int)(numFaces + 1); y++)
			{
				float xStart = -(size / 2);
				float yStart = -(size / 2);
				float zStart = size / 2;

				for(int x = 0; x < (int)(numFaces + 1); x++)
				{
					pVertexPC[vertexCounter].position.x = xStart + (x * incrementDist);
					pVertexPC[vertexCounter].position.y = yStart;
					pVertexPC[vertexCounter].position.z = zStart - (y * incrementDist);
					pVertexPC[vertexCounter].colour.x = colour.x;
					pVertexPC[vertexCounter].colour.y = colour.y;
					pVertexPC[vertexCounter].colour.z = colour.z;

					vertexCounter++;
				}
			}

			// Left face
			for(int y = 0; y < (int)(numFaces + 1); y++)
			{
				float xStart = -(size / 2);
				float yStart = size / 2;
				float zStart = -(size / 2);

				for(int x = 0; x < (int)(numFaces + 1); x++)
				{
					pVertexPC[vertexCounter].position.x = xStart;
					pVertexPC[vertexCounter].position.y = yStart - (y * incrementDist);
					pVertexPC[vertexCounter].position.z = zStart + (x * incrementDist);
					pVertexPC[vertexCounter].colour.x = colour.x;
					pVertexPC[vertexCounter].colour.y = colour.y;
					pVertexPC[vertexCounter].colour.z = colour.z;

					vertexCounter++;
				}
			}

			// Back face
			for(int y = 0; y < (int)(numFaces + 1); y++)
			{
				float xStart = size / 2;
				float yStart = size / 2;
				float zStart = -(size / 2);

				for(int x = 0; x < (int)(numFaces + 1); x++)
				{
					pVertexPC[vertexCounter].position.x = xStart - (x * incrementDist);
					pVertexPC[vertexCounter].position.y = yStart - (y * incrementDist);
					pVertexPC[vertexCounter].position.z = zStart;
					pVertexPC[vertexCounter].colour.x = colour.x;
					pVertexPC[vertexCounter].colour.y = colour.y;
					pVertexPC[vertexCounter].colour.z = colour.z;

					vertexCounter++;
				}
			}

			// Right face
			for(int y = 0; y < (int)(numFaces + 1); y++)
			{
				float xStart = size / 2;
				float yStart = size / 2;
				float zStart = size / 2;

				for(int x = 0; x < (int)(numFaces + 1); x++)
				{
					pVertexPC[vertexCounter].position.x = xStart;
					pVertexPC[vertexCounter].position.y = yStart - (y * incrementDist);
					pVertexPC[vertexCounter].position.z = zStart - (x * incrementDist);
					pVertexPC[vertexCounter].colour.x = colour.x;
					pVertexPC[vertexCounter].colour.y = colour.y;
					pVertexPC[vertexCounter].colour.z = colour.z;

					vertexCounter++;
				}
			}

			// Top face
			for(int y = 0; y < (int)(numFaces + 1); y++)
			{
				float xStart = -(size / 2);
				float yStart = size / 2;
				float zStart = -(size / 2);

				for(int x = 0; x < (int)(numFaces + 1); x++)
				{
					pVertexPC[vertexCounter].position.x = xStart + (x * incrementDist);
					pVertexPC[vertexCounter].position.y = yStart;
					pVertexPC[vertexCounter].position.z = zStart + (y * incrementDist);
					pVertexPC[vertexCounter].colour.x = colour.x;
					pVertexPC[vertexCounter].colour.y = colour.y;
					pVertexPC[vertexCounter].colour.z = colour.z;

					vertexCounter++;
				}
			}
		}
		break;

	case eVertexPT:
		{
			SVertexTypePT *pVertexPT = static_cast<SVertexTypePT*>(pMeshData->pVertices);

			// Front face
			for(int y = 0; y < (int)(numFaces + 1); y++)
			{
				float xStart = -(size / 2);
				float yStart = size / 2;
				float zStart = size / 2;

				for(int x = 0; x < (int)(numFaces + 1); x++)
				{
					pVertexPT[vertexCounter].position.x = xStart + (x * incrementDist);
					pVertexPT[vertexCounter].position.y = yStart - (y * incrementDist);
					pVertexPT[vertexCounter].position.z = zStart;
					pVertexPT[vertexCounter].textureCoord.x = (float)x / (float)numFaces;
					pVertexPT[vertexCounter].textureCoord.y = ((float)(numFaces) - (float)y) / (float)numFaces;

					vertexCounter++;
				}
			}

			// bottom face
			for(int y = 0; y < (int)(numFaces + 1); y++)
			{
				float xStart = -(size / 2);
				float yStart = -(size / 2);
				float zStart = size / 2;

				for(int x = 0; x < (int)(numFaces + 1); x++)
				{
					pVertexPT[vertexCounter].position.x = xStart + (x * incrementDist);
					pVertexPT[vertexCounter].position.y = yStart;
					pVertexPT[vertexCounter].position.z = zStart - (y * incrementDist);
					pVertexPT[vertexCounter].textureCoord.x = (float)x / (float)numFaces;
					pVertexPT[vertexCounter].textureCoord.y = ((float)(numFaces) - (float)y) / (float)numFaces;

					vertexCounter++;
				}
			}

			// Left face
			for(int y = 0; y < (int)(numFaces + 1); y++)
			{
				float xStart = -(size / 2);
				float yStart = size / 2;
				float zStart = -(size / 2);

				for(int x = 0; x < (int)(numFaces + 1); x++)
				{
					pVertexPT[vertexCounter].position.x = xStart;
					pVertexPT[vertexCounter].position.y = yStart - (y * incrementDist);
					pVertexPT[vertexCounter].position.z = zStart + (x * incrementDist);
					pVertexPT[vertexCounter].textureCoord.x = (float)x / (float)numFaces;
					pVertexPT[vertexCounter].textureCoord.y = ((float)(numFaces) - (float)y) / (float)numFaces;

					vertexCounter++;
				}
			}

			// Back face
			for(int y = 0; y < (int)(numFaces + 1); y++)
			{
				float xStart = size / 2;
				float yStart = size / 2;
				float zStart = -(size / 2);

				for(int x = 0; x < (int)(numFaces + 1); x++)
				{
					pVertexPT[vertexCounter].position.x = xStart - (x * incrementDist);
					pVertexPT[vertexCounter].position.y = yStart - (y * incrementDist);
					pVertexPT[vertexCounter].position.z = zStart;
					pVertexPT[vertexCounter].textureCoord.x = (float)x / (float)numFaces;
					pVertexPT[vertexCounter].textureCoord.y = ((float)(numFaces) - (float)y) / (float)numFaces;

					vertexCounter++;
				}
			}

			// Right face
			for(int y = 0; y < (int)(numFaces + 1); y++)
			{
				float xStart = size / 2;
				float yStart = size / 2;
				float zStart = size / 2;

				for(int x = 0; x < (int)(numFaces + 1); x++)
				{
					pVertexPT[vertexCounter].position.x = xStart;
					pVertexPT[vertexCounter].position.y = yStart - (y * incrementDist);
					pVertexPT[vertexCounter].position.z = zStart - (x * incrementDist);
					pVertexPT[vertexCounter].textureCoord.x = (float)x / (float)numFaces;
					pVertexPT[vertexCounter].textureCoord.y = ((float)(numFaces) - (float)y) / (float)numFaces;

					vertexCounter++;
				}
			}

			// Top face
			for(int y = 0; y < (int)(numFaces + 1); y++)
			{
				float xStart = -(size / 2);
				float yStart = size / 2;
				float zStart = -(size / 2);

				for(int x = 0; x < (int)(numFaces + 1); x++)
				{
					pVertexPT[vertexCounter].position.x = xStart + (x * incrementDist);
					pVertexPT[vertexCounter].position.y = yStart;
					pVertexPT[vertexCounter].position.z = zStart + (y * incrementDist);
					pVertexPT[vertexCounter].textureCoord.x = (float)x / (float)numFaces;
					pVertexPT[vertexCounter].textureCoord.y = ((float)(numFaces) - (float)y) / (float)numFaces;
					vertexCounter++;
				}
			}
		}
		break;

	case eVertexPNC:
		{
			SVertexTypePNC *pVertexPNC = static_cast<SVertexTypePNC*>(pMeshData->pVertices);

			// Front face
			for(int y = 0; y < (int)(numFaces + 1); y++)
			{
				float xStart = -(size / 2);
				float yStart = size / 2;
				float zStart = (size / 2);

				for(int x = 0; x < (int)(numFaces + 1); x++)
				{
					pVertexPNC[vertexCounter].position.x = xStart + (x * incrementDist);
					pVertexPNC[vertexCounter].position.y = yStart - (y * incrementDist);
					pVertexPNC[vertexCounter].position.z = zStart;
					pVertexPNC[vertexCounter].colour.x = colour.x;
					pVertexPNC[vertexCounter].colour.y = colour.y;
					pVertexPNC[vertexCounter].colour.z = colour.z;

					vertexCounter++;
				}
			}

			// bottom face
			for(int y = 0; y < (int)(numFaces + 1); y++)
			{
				float xStart = -(size / 2);
				float yStart = -(size / 2);
				float zStart = size / 2;

				for(int x = 0; x < (int)(numFaces + 1); x++)
				{
					pVertexPNC[vertexCounter].position.x = xStart + (x * incrementDist);
					pVertexPNC[vertexCounter].position.y = yStart;
					pVertexPNC[vertexCounter].position.z = zStart - (y * incrementDist);
					pVertexPNC[vertexCounter].colour.x = colour.x;
					pVertexPNC[vertexCounter].colour.y = colour.y;
					pVertexPNC[vertexCounter].colour.z = colour.z;

					vertexCounter++;
				}
			}

			// Left face
			for(int y = 0; y < (int)(numFaces + 1); y++)
			{
				float xStart = -(size / 2);
				float yStart = size / 2;
				float zStart = -(size / 2);

				for(int x = 0; x < (int)(numFaces + 1); x++)
				{
					pVertexPNC[vertexCounter].position.x = xStart;
					pVertexPNC[vertexCounter].position.y = yStart - (y * incrementDist);
					pVertexPNC[vertexCounter].position.z = zStart + (x * incrementDist);
					pVertexPNC[vertexCounter].colour.x = colour.x;
					pVertexPNC[vertexCounter].colour.y = colour.y;
					pVertexPNC[vertexCounter].colour.z = colour.z;

					vertexCounter++;
				}
			}

			// Back face
			for(int y = 0; y < (int)(numFaces + 1); y++)
			{
				float xStart = size / 2;
				float yStart = size / 2;
				float zStart = -(size / 2);

				for(int x = 0; x < (int)(numFaces + 1); x++)
				{
					pVertexPNC[vertexCounter].position.x = xStart - (x * incrementDist);
					pVertexPNC[vertexCounter].position.y = yStart - (y * incrementDist);
					pVertexPNC[vertexCounter].position.z = zStart;
					pVertexPNC[vertexCounter].colour.x = colour.x;
					pVertexPNC[vertexCounter].colour.y = colour.y;
					pVertexPNC[vertexCounter].colour.z = colour.z;

					vertexCounter++;
				}
			}

			// Right face
			for(int y = 0; y < (int)(numFaces + 1); y++)
			{
				float xStart = size / 2;
				float yStart = size / 2;
				float zStart = size / 2;

				for(int x = 0; x < (int)(numFaces + 1); x++)
				{
					pVertexPNC[vertexCounter].position.x = xStart;
					pVertexPNC[vertexCounter].position.y = yStart - (y * incrementDist);
					pVertexPNC[vertexCounter].position.z = zStart - (x * incrementDist);
					pVertexPNC[vertexCounter].colour.x = colour.x;
					pVertexPNC[vertexCounter].colour.y = colour.y;
					pVertexPNC[vertexCounter].colour.z = colour.z;

					vertexCounter++;
				}
			}

			// Top face
			for(int y = 0; y < (int)(numFaces + 1); y++)
			{
				float xStart = -(size / 2);
				float yStart = size / 2;
				float zStart = -(size / 2);

				for(int x = 0; x < (int)(numFaces + 1); x++)
				{
					pVertexPNC[vertexCounter].position.x = xStart + (x * incrementDist);
					pVertexPNC[vertexCounter].position.y = yStart;
					pVertexPNC[vertexCounter].position.z = zStart + (y * incrementDist);
					pVertexPNC[vertexCounter].colour.x = colour.x;
					pVertexPNC[vertexCounter].colour.y = colour.y;
					pVertexPNC[vertexCounter].colour.z = colour.z;

					vertexCounter++;
				}
			}
		}
		break;

	case eVertexPNT:
		{
			SVertexTypePNT *pVertexPNT = static_cast<SVertexTypePNT*>(pMeshData->pVertices);

			// Front face
			for(int y = 0; y < (int)(numFaces + 1); y++)
			{
				float xStart = -(size / 2);
				float yStart = size / 2;
				float zStart = size / 2;

				for(int x = 0; x < (int)(numFaces + 1); x++)
				{
					pVertexPNT[vertexCounter].position.x = xStart + (x * incrementDist);
					pVertexPNT[vertexCounter].position.y = yStart - (y * incrementDist);
					pVertexPNT[vertexCounter].position.z = zStart;
					pVertexPNT[vertexCounter].textureCoord.x = (float)x / (float)numFaces;
					pVertexPNT[vertexCounter].textureCoord.y = ((float)(numFaces) - (float)y) / (float)numFaces;

					vertexCounter++;
				}
			}

			// bottom face
			for(int y = 0; y < (int)(numFaces + 1); y++)
			{
				float xStart = -(size / 2);
				float yStart = -(size / 2);
				float zStart = size / 2;

				for(int x = 0; x < (int)(numFaces + 1); x++)
				{
					pVertexPNT[vertexCounter].position.x = xStart + (x * incrementDist);
					pVertexPNT[vertexCounter].position.y = yStart;
					pVertexPNT[vertexCounter].position.z = zStart - (y * incrementDist);
					pVertexPNT[vertexCounter].textureCoord.x = (float)x / (float)numFaces;
					pVertexPNT[vertexCounter].textureCoord.y = ((float)(numFaces) - (float)y) / (float)numFaces;

					vertexCounter++;
				}
			}

			// Left face
			for(int y = 0; y < (int)(numFaces + 1); y++)
			{
				float xStart = -(size / 2);
				float yStart = size / 2;
				float zStart = -(size / 2);

				for(int x = 0; x < (int)(numFaces + 1); x++)
				{
					pVertexPNT[vertexCounter].position.x = xStart;
					pVertexPNT[vertexCounter].position.y = yStart - (y * incrementDist);
					pVertexPNT[vertexCounter].position.z = zStart + (x * incrementDist);
					pVertexPNT[vertexCounter].textureCoord.x = (float)x / (float)numFaces;
					pVertexPNT[vertexCounter].textureCoord.y = ((float)(numFaces) - (float)y) / (float)numFaces;

					vertexCounter++;
				}
			}

			// Back face
			for(int y = 0; y < (int)(numFaces + 1); y++)
			{
				float xStart = size / 2;
				float yStart = size / 2;
				float zStart = -(size / 2);

				for(int x = 0; x < (int)(numFaces + 1); x++)
				{
					pVertexPNT[vertexCounter].position.x = xStart - (x * incrementDist);
					pVertexPNT[vertexCounter].position.y = yStart - (y * incrementDist);
					pVertexPNT[vertexCounter].position.z = zStart;
					pVertexPNT[vertexCounter].textureCoord.x = (float)x / (float)numFaces;
					pVertexPNT[vertexCounter].textureCoord.y = ((float)(numFaces) - (float)y) / (float)numFaces;

					vertexCounter++;
				}
			}

			// Right face
			for(int y = 0; y < (int)(numFaces + 1); y++)
			{
				float xStart = size / 2;
				float yStart = size / 2;
				float zStart = size / 2;

				for(int x = 0; x < (int)(numFaces + 1); x++)
				{
					pVertexPNT[vertexCounter].position.x = xStart;
					pVertexPNT[vertexCounter].position.y = yStart - (y * incrementDist);
					pVertexPNT[vertexCounter].position.z = zStart - (x * incrementDist);
					pVertexPNT[vertexCounter].textureCoord.x = (float)x / (float)numFaces;
					pVertexPNT[vertexCounter].textureCoord.y = ((float)(numFaces) - (float)y) / (float)numFaces;

					vertexCounter++;
				}
			}

			// Top face
			for(int y = 0; y < (int)(numFaces + 1); y++)
			{
				float xStart = -(size / 2);
				float yStart = size / 2;
				float zStart = -(size / 2);

				for(int x = 0; x < (int)(numFaces + 1); x++)
				{
					pVertexPNT[vertexCounter].position.x = xStart + (x * incrementDist);
					pVertexPNT[vertexCounter].position.y = yStart;
					pVertexPNT[vertexCounter].position.z = zStart + (y * incrementDist);
					pVertexPNT[vertexCounter].textureCoord.x = (float)x / (float)numFaces;
					pVertexPNT[vertexCounter].textureCoord.y = ((float)(numFaces) - (float)y) / (float)numFaces;
					vertexCounter++;
				}
			}
		}
		break;

	default:
		break;
	}

	// Create the indices
	int indexCounter = 0;
	int vIndex = 0;
	int numVertsX = numFaces + 1;

	// 6 faces in total so loop
	for(int i = 0; i < 6; i++)
	{
		// Loops for generating indices for a face
		for (int y = 0; y < (int)numFaces; y++)
		{
			for (int x = 0; x < (int)numFaces; x++)
			{
				// first triangle
				pMeshData->pIndices[indexCounter++] = vIndex;
				pMeshData->pIndices[indexCounter++] = vIndex + numVertsX;
				pMeshData->pIndices[indexCounter++] = vIndex + numVertsX + 1;


				// second triangle
				pMeshData->pIndices[indexCounter++] = vIndex;
				pMeshData->pIndices[indexCounter++] = vIndex + numVertsX + 1;
				pMeshData->pIndices[indexCounter++] = vIndex + 1;

				vIndex++;
			}

			vIndex++;
		}

		// Skips the 'bottom' row of vertices
		vIndex += (numFaces + 1);
	}

	// Calculate normals
	CalculateNormals(pMeshData);

	return pMeshData;
}



//-------------------------------------------------------------------------------------
//
//	CreateSphere(..)
//
//	Params:
//	geometryID		-	String name stored in MeshData
//	size			-	size of the quad
//	type			-	type of vertices to use
//	subDivisons		-	increases number of divisions, more vertices created. Already assumes 3 as min
//	colour			-	colour of triangle if vertex type supports colour
//
//	Description:
//	Method creates a 2D quad consisting of 2 triangles
//
//-------------------------------------------------------------------------------------
MeshData* CMeshDataGenerator::CreateSphere(const std::string &geometryID, float size, EVertexType type, unsigned int subDivisions,
	const glm::vec4 &colour)
{
	// Minimum of 3 subdivisons to form a sphere
	unsigned int subDivs = 3 + subDivisions;

	int vertSegments = subDivs;
	int horizSegments = subDivs * 2;

	// Add 2 as we add a single point for top and bottom sphere
	int totalVerts = (vertSegments - 1) * horizSegments + 2;

	// Total indies:
	//	2 fan strips (top and bottom) + main body of circle (handle in pairs of triangles)
	int totalIndices = (2 * horizSegments * 3) + (((vertSegments - 2) * horizSegments) * 6);

	// Create empty data
	MeshData *pNewMesh = new MeshData(type, totalVerts, totalIndices);

	pNewMesh->m_ID = geometryID;

	float radius = size / 2;
	int vertCounter = 0;

	// Generate the vertex data
	switch(type)
	{
	case eVertexPC:
		{
			SVertexTypePC *pVertPC = static_cast<SVertexTypePC*>(pNewMesh->pVertices);

			// Start with single vertex at bottom of sphere
			pVertPC[0].position = glm::vec3(0, (radius * -1), 0);
			pVertPC[0].colour = glm::vec3(colour);

			// Already a vertex from above code
			vertCounter = 1;

			// Create rings of vertices at higher latitidues
			for(int i = 0; i < vertSegments - 1; i++) {
				float latitude = ((i + 1) * glm::pi<float>()/
					vertSegments) - (glm::pi<float>()/2);

				float dy = (float)sin(latitude);
				float dxz = (float)cos(latitude);

				// Create a single ring of vertices at this latitude
				for(int j = 0; j < horizSegments; j++) {
					float longitude = j * (2 * glm::pi<float>()) / horizSegments;

					float dx = cos(longitude) * dxz;
					float dz = sin(longitude) * dxz;

					pVertPC[vertCounter].position = glm::vec3((radius * dx), (radius * dy), (radius * dz));
					pVertPC[vertCounter].colour = glm::vec3(colour);

					vertCounter++;
				}
			}

			// Finish with single vertex
			pVertPC[vertCounter].position = glm::vec3(0, (radius * 1), 0);
			pVertPC[vertCounter].colour = glm::vec3(colour);
		}
		break;

	case eVertexPT:
		{
			SVertexTypePT *pVertPT = static_cast<SVertexTypePT*>(pNewMesh->pVertices);

			// Start with single vertex at bottom of sphere
			pVertPT[0].position = glm::vec3(0, (radius * -1), 0);
			pVertPT[0].textureCoord = glm::vec2(0, 0);

			// Already a vertex from above code
			vertCounter = 1;

			// Create rings of vertices at higher latitidues
			for(int i = 0; i < vertSegments - 1; i++) {
				float latitude = ((i + 1) * glm::pi<float>()/
					vertSegments) - (glm::pi<float>()/2);

				float dy = (float)sin(latitude);
				float dxz = (float)cos(latitude);

				// Create a single ring of vertices at this latitude
				for(int j = 0; j < horizSegments; j++) {
					float longitude = j * (2 * glm::pi<float>()) / horizSegments;

					float dx = cos(longitude) * dxz;
					float dz = sin(longitude) * dxz;

					float u = asinf(dx)/glm::pi<float>()+0.5f;
					float v = asinf(dy)/glm::pi<float>()+0.5f;

					pVertPT[vertCounter].position = glm::vec3((radius * dx), (radius * dy), (radius * dz));
					pVertPT[vertCounter].textureCoord = glm::vec2(u, v);

					vertCounter++;
				}
			}

			// Finish with single vertex
			pVertPT[vertCounter].position = glm::vec3(0, (radius * 1), 0);
			pVertPT[vertCounter].textureCoord = glm::vec2(1, 1);
		}
		break;

	case eVertexPNC:
		{
			SVertexTypePNC *pVertPNC = static_cast<SVertexTypePNC*>(pNewMesh->pVertices);

			// Start with single vertex at bottom of sphere
			pVertPNC[0].position = glm::vec3(0, (radius * -1), 0);
			//pVertPNC[0].normal = glm::vec3(0, -1, 0);
			pVertPNC[0].colour = colour;

			// Already a vertex from above code
			vertCounter = 1;

			// Create rings of vertices at higher latitidues
			for(int i = 0; i < vertSegments - 1; i++) {
				float latitude = ((i + 1) * glm::pi<float>()/
					vertSegments) - (glm::pi<float>()/2);

				float dy = (float)sin(latitude);
				float dxz = (float)cos(latitude);

				// Create a single ring of vertices at this latitude
				for(int j = 0; j < horizSegments; j++) {
					float longitude = j * (2 * glm::pi<float>()) / horizSegments;

					float dx = cos(longitude) * dxz;
					float dz = sin(longitude) * dxz;

					pVertPNC[vertCounter].position = glm::vec3((radius * dx), (radius * dy), (radius * dz));
					//pVertPNC[vertCounter].normal = glm::vec3(dx, dy, dz);
					pVertPNC[vertCounter].colour = colour;

					vertCounter++;
				}
			}

			// Finish with single vertex
			pVertPNC[vertCounter].position = glm::vec3(0, (radius * 1), 0);
			//pVertPNC[vertCounter].normal = glm::vec3(0, 1, 0);
			pVertPNC[vertCounter].colour = colour;
		}
		break;

	case eVertexPNT:
		{
			SVertexTypePNT *pVertPNT = static_cast<SVertexTypePNT*>(pNewMesh->pVertices);

			// Start with single vertex at bottom of sphere
			pVertPNT[0].position = glm::vec3(0, (radius * -1), 0);
			//pVertPNT[0].normal = glm::vec3(0, -1, 0);
			pVertPNT[0].textureCoord = glm::vec2(0, 0);

			// Already a vertex from above code
			vertCounter = 1;

			// Create rings of vertices at higher latitidues
			for(int i = 0; i < vertSegments - 1; i++) {
				float latitude = ((i + 1) * glm::pi<float>()/
					vertSegments) - (glm::pi<float>()/2);

				float dy = (float)sin(latitude);
				float dxz = (float)cos(latitude);

				// Create a single ring of vertices at this latitude
				for(int j = 0; j < horizSegments; j++) {
					float longitude = j * (2 * glm::pi<float>()) / horizSegments;

					float dx = cos(longitude) * dxz;
					float dz = sin(longitude) * dxz;

					float u = asinf(dx)/glm::pi<float>()+0.5f;
					float v = asinf(dy)/glm::pi<float>()+0.5f;

					pVertPNT[vertCounter].position = glm::vec3((radius * dx), (radius * dy), (radius * dz));
					//pVertPNT[vertCounter].normal = glm::vec3(dx, dy, dz);
					pVertPNT[vertCounter].textureCoord = glm::vec2(u, v);

					vertCounter++;
				}
			}

			// Finish with single vertex
			pVertPNT[vertCounter].position = glm::vec3(0, (radius * 1), 0);
			//pVertPNT[vertCounter].normal = glm::vec3(0, 1, 0);
			pVertPNT[vertCounter].textureCoord = glm::vec2(1, 1);
		}
		break;

	default:
		// Don't end up here pls.
		break;
	}

	// Generate the index data
	int indexCounter = 0;

	// Create a fan connecting the bottom vertex to the bottom of the latitude ring
	for(int i = 0; i < horizSegments; i++) {
		pNewMesh->pIndices[indexCounter] = 0;
		pNewMesh->pIndices[indexCounter+2] = 1 + (i + 1) % horizSegments;
		pNewMesh->pIndices[indexCounter+1] = 1 + i;

		indexCounter += 3;
	}

	// Fill the sphere body with triangles joining each of latitude rings
	for(int i = 0; i < vertSegments - 2; i ++) {
		for(int j = 0; j < horizSegments; j++) {
			int nextI = i + 1;
			int nextJ = (j + 1) % horizSegments;

			pNewMesh->pIndices[indexCounter] = 1 + i * horizSegments + j;
			pNewMesh->pIndices[indexCounter+2] = 1 + i * horizSegments + nextJ;
			pNewMesh->pIndices[indexCounter+1] = 1 + nextI * horizSegments + j;

			pNewMesh->pIndices[indexCounter+3] = (1 + i * horizSegments + nextJ);
			pNewMesh->pIndices[indexCounter+5] = 1 + nextI * horizSegments + nextJ;
			pNewMesh->pIndices[indexCounter+4] = 1 + nextI * horizSegments + j;

			indexCounter += 6;
		}
	}

	// Create a fan connecting the top vertex to the top latitude ring.
	for(int i = 0; i < horizSegments; i++) { 
		pNewMesh->pIndices[indexCounter] = totalVerts - 1;
		pNewMesh->pIndices[indexCounter+2] = totalVerts - 2 - (i + 1) % horizSegments;
		pNewMesh->pIndices[indexCounter+1] = totalVerts - 2 - i;

		indexCounter += 3;
	}

	CalculateNormals(pNewMesh);

	return pNewMesh;
}

MeshData * CMeshDataGenerator::GenerateChunkMesh(CChunk * pChunk, const std::string & geometryID)
{
	if (pChunk == nullptr)
		return nullptr;

	// Method 1:
	// Count number of active voxels.
	// Assume each one will use a cube
	// Generate array for enough space for all the cubes.
	std::vector<glm::ivec3> voxelList;

	// Find which voxels are required for the mesh generation
	for (int z = 0; z < pChunk->GetVoxelsZ(); z++)
	{
		for (int y = 0; y < pChunk->GetVoxelsY(); y++)
		{
			for (int x = 0; x < pChunk->GetVoxelsX(); x++)
			{
				// If active
				if (pChunk->GetVoxel(x, y, z)->bActive)
				{
					voxelList.push_back(glm::ivec3(x + 1, y + 1, z + 1));
					// Initial optimisation would be to check for surrounding voxels.
					// If completely surrounded, it would be hidden
				}
			}
		}
	}

	MeshData* pNewMesh = new MeshData(EVertexType::eVertexPNT, (voxelList.size() * 24), (voxelList.size() * 36));

	// Now we have all the visible voxels, loop and generate the chunk mesh for them
	float voxelSize = VOXEL_SIZE;
	float minX = ((voxelSize * pChunk->GetVoxelsX()) / 2) * -1;
	float minY = ((voxelSize * pChunk->GetVoxelsY()) / 2) * -1;
	float minZ = ((voxelSize * pChunk->GetVoxelsZ()) / 2) * -1;
	for (int i = 0; i < static_cast<int>(voxelList.size()); i++)
	{
		int vX = voxelList[i].x;
		int vY = voxelList[i].y;
		int vZ = voxelList[i].z;


	}

	return pNewMesh;
}


//-------------------------------------------------------------------------------------
//
//	CalculateNormals(..)
//
//	Params:
//	pMeshData	-	Pointer to mesh data
//
//	Description:
//	Create normals from averaged triangles for each vertex.
//	Assumption that each vertex only has 1 normal (no shared normals)
//
//-------------------------------------------------------------------------------------
void CMeshDataGenerator::CalculateNormals(MeshData* pMeshData)
{
	if (pMeshData != nullptr) {
		int trigCount = pMeshData->indexCount / 3;

		// Calculate triangle normals and accumalate normals for each vertex
		for (int triangle = 0; triangle < trigCount; triangle++) {
			glm::vec3 p0;
			glm::vec3 p1;
			glm::vec3 p2;
			glm::vec3 q0;
			glm::vec3 q1;
			glm::vec3 normal;

			switch (pMeshData->vertexType)
			{
			case eVertexPNC:
				{
					SVertexTypePNC* pVertPNC = (SVertexTypePNC*)(pMeshData->pVertices);
					p0 = pVertPNC[pMeshData->pIndices[(triangle * 3)]].position;
					p1 = pVertPNC[pMeshData->pIndices[(triangle * 3) + 1]].position;
					p2 = pVertPNC[pMeshData->pIndices[(triangle * 3) + 2]].position;

					q0 = p1 - p0;
					q1 = p2 - p0;

					normal = glm::cross(q0, q1);
					normal = glm::normalize(normal);
					
					pVertPNC[pMeshData->pIndices[(triangle * 3)]].normal += normal;
					pVertPNC[pMeshData->pIndices[(triangle * 3) + 1]].normal += normal;
					pVertPNC[pMeshData->pIndices[(triangle * 3) + 2]].normal += normal;
				}
				break;
			case eVertexPNT:
				{
					SVertexTypePNT* pVertPNT = (SVertexTypePNT*)(pMeshData->pVertices);
					p0 = pVertPNT[pMeshData->pIndices[(triangle * 3)]].position;
					p1 = pVertPNT[pMeshData->pIndices[(triangle * 3) + 1]].position;
					p2 = pVertPNT[pMeshData->pIndices[(triangle * 3) + 2]].position;

					q0 = p1 - p0;
					q1 = p2 - p0;

					normal = glm::cross(q0, q1);
					normal = glm::normalize(normal);
					
					pVertPNT[pMeshData->pIndices[(triangle * 3)]].normal += normal;
					pVertPNT[pMeshData->pIndices[(triangle * 3) + 1]].normal += normal;
					pVertPNT[pMeshData->pIndices[(triangle * 3) + 2]].normal += normal;
				}
				break;
			case eVertexPNBTT:
				{
					SVertexTypePNBTT* pVertPNBTT = (SVertexTypePNBTT*)(pMeshData->pVertices);
					p0 = pVertPNBTT[pMeshData->pIndices[(triangle * 3)]].position;
					p1 = pVertPNBTT[pMeshData->pIndices[(triangle * 3) + 1]].position;
					p2 = pVertPNBTT[pMeshData->pIndices[(triangle * 3) + 2]].position;

					q0 = p1 - p0;
					q1 = p2 - p0;

					normal = glm::cross(q0, q1);
					normal = glm::normalize(normal);
					
					pVertPNBTT[pMeshData->pIndices[(triangle * 3)]].normal += normal;
					pVertPNBTT[pMeshData->pIndices[(triangle * 3) + 1]].normal += normal;
					pVertPNBTT[pMeshData->pIndices[(triangle * 3) + 2]].normal += normal;
				}
				break;
			default:
				// Do nothing....
				break;
			}
		}

		// Normalise resultant normals for each vertex
		for (int vert = 0; vert < pMeshData->vertexCount; vert++) {
			switch (pMeshData->vertexType)
			{
			case eVertexPNC:
				{
				   SVertexTypePNC* pVertPNC = (SVertexTypePNC*)(pMeshData->pVertices);
				   pVertPNC[vert].normal = glm::normalize(pVertPNC[vert].normal);
				}
				break;
			case eVertexPNT:
				{
				   SVertexTypePNT* pVertPNT = (SVertexTypePNT*)(pMeshData->pVertices);
				   pVertPNT[vert].normal = glm::normalize(pVertPNT[vert].normal);
				}
				break;
			case eVertexPNBTT:
				{
					SVertexTypePNBTT* pVertPNBTT = (SVertexTypePNBTT*)(pMeshData->pVertices);
					pVertPNBTT[vert].normal = glm::normalize(pVertPNBTT[vert].normal);
				}
				break;
			default:
				// Do nothing....
				break;
			}
		}
	}
}

void CMeshDataGenerator::CalculateTangents(MeshData* pMeshData)
{
}