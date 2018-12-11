//--------------------------------------------------------------------------
//
//	Voxcel stuff
//
//--------------------------------------------------------------------------
#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <string>

using namespace std;
using namespace glm;

// Defines cube size of all voxels
#define VOXEL_SIZE 10

enum EBlockType
{
	eBlockDirt,
	eBlockGrass,
	eBlockUnknown,
	eBlockTotal,
};

struct SVoxel
{
	EBlockType type;
	bool bActive;
};


class CChunk
{
public:
	CChunk();
	~CChunk();

	void CreateChunk(uint xVoxels, uint yVoxels, uint zVoxels);
	void GenerateMesh();

	float GetVoxelSize() const;

protected:
	SVoxel*** m_pVoxels;

	std::string m_meshID;	// Loaded mesh ID
	glm::vec3 m_pos;		// World position of this chunk
};


//class CChunkMGR
//{
//public:
//	CChunkMGR();
//	~CChunkMGR();
//
//	void CreateChunks(uint xChunks, uint yChunks, uint zChunks, uint xVoxPerChunk, uint yVoxPerChunk, uint zVoxPerChunk);
//
//private:
//	vector<vector<vector<CChunk>>> m_chunks;
//};