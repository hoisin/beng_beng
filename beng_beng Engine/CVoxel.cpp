#include "CVoxel.h"

CChunk::CChunk()
{
}

CChunk::~CChunk()
{
	for (int z = 0; z < m_chunkVoxels.z; z++)
	{
		for (int y = 0; y < m_chunkVoxels.y; y++)
			delete [] m_pVoxels[z][y];
		
		delete [] m_pVoxels[z];
	}

	delete [] m_pVoxels;
}

void CChunk::CreateChunk(uint xVoxels, uint yVoxels, uint zVoxels)
{
	m_chunkVoxels.x = xVoxels;
	m_chunkVoxels.y = yVoxels;
	m_chunkVoxels.z = zVoxels;

	m_pVoxels = new SVoxel**[m_chunkVoxels.z];
	for (int z = 0; z < m_chunkVoxels.z; z++)
	{
		m_pVoxels[z] = new SVoxel*[m_chunkVoxels.y];
		for (int y = 0; y < m_chunkVoxels.y; y++)
		{
			m_pVoxels[z][y] = new SVoxel[m_chunkVoxels.x];
			for (int x = 0; x < m_chunkVoxels.x; x++)
			{
				m_pVoxels[z][y][x].bActive = true;
				m_pVoxels[z][y][x].type = eBlockUnknown;
			}
		}
	}
}


int CChunk::GetVoxelsX()
{
	return m_chunkVoxels.x;
}

int CChunk::GetVoxelsY()
{
	return m_chunkVoxels.y;
}

int CChunk::GetVoxelsZ()
{
	return m_chunkVoxels.z;
}

float CChunk::GetVoxelSize() const
{
	return VOXEL_SIZE;
}

void CChunk::SetPos(const glm::vec3 & pos)
{
	m_pos = pos;
}

SVoxel * CChunk::GetVoxel(int x, int y, int z)
{
	if (z > m_chunkVoxels.z || y > m_chunkVoxels.y || x > m_chunkVoxels.x)
		return nullptr;

	return &m_pVoxels[z][y][x];
}
