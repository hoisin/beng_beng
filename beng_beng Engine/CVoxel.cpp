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
	for (int z = 0; z < yVoxels; z++)
	{
		m_pVoxels[z] = new SVoxel*[zVoxels];
		for (int y = 0; y < zVoxels; y++)
		{
			m_pVoxels[z][y] = new SVoxel[xVoxels];
		}
	}
}

void CChunk::GenerateMesh()
{
}

float CChunk::GetVoxelSize() const
{
	return VOXEL_SIZE;
}
