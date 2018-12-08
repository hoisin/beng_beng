#include "CVoxel.h"

CChunk::CChunk()
{
}

CChunk::~CChunk()
{
}

void CChunk::CreateChunk(uint xVoxels, uint yVoxels, uint zVoxels)
{
	m_pVoxels = new SVoxel**[yVoxels];
	for (int y = 0; y < yVoxels; y++)
	{
		m_pVoxels[y] = new SVoxel*[zVoxels];
		for (int z = 0; z < zVoxels; z++)
		{
			m_pVoxels[y][z] = new SVoxel[xVoxels];
		}
	}
}

void CChunk::GenerateMesh()
{
}
