//--------------------------------------------------------------------------
//
//	Voxcel stuff
//
//--------------------------------------------------------------------------
#pragma once

#include <vector>
#include <glm/glm.hpp>

using namespace std;
using namespace glm;

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

protected:
	SVoxel*** m_pVoxels;
};


class CChunkMGR
{
public:
	CChunkMGR();
	~CChunkMGR();

	void CreateChunks(uint xChunks, uint yChunks, uint zChunks, uint xVoxPerChunk, uint yVoxPerChunk, uint zVoxPerChunk);

private:
	vector<vector<vector<CChunk>>> m_chunks;
};