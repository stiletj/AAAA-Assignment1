#include "LodManager.h"

LodManager::~LodManager()
{
	delete[] m_map;
}

int LodManager::initLodManager(int patchSize, int numPatchesX, int numPatchesZ, float zfar)
{
	m_patchSize = patchSize;
	m_numPatchesX = numPatchesX;
	m_numPatchesZ = numPatchesZ;

	CalcMaxLOD();

	patchLod Zero;
	m_map = new patchLod * [m_numPatchesX];
	for (int i = 0; i < m_numPatchesX; i++)
	{
		m_map[i] = new patchLod[m_numPatchesZ];

		for (int j = 0; j < m_numPatchesZ; j++) {
			m_map[i][j] = Zero;
		}
	}

	m_regions.resize(m_maxLOD + 1);

	CalcLODRegions(zfar);

	return m_maxLOD;
	
}

void LodManager::UpdateLOD(const glm::vec3& camPos)
{
	LODMapPass1(camPos);
	LODMapPass2(camPos);
}

const LodManager::patchLod& LodManager::getPatchLod(int PatchX, int PatchZ)
{
	return m_map[PatchX][PatchZ];
}

void LodManager::CalcLODRegions(float zfar)
{
	int Sum = 0;

	for (int i = 0; i <= m_maxLOD; i++)
	{
		Sum += (i + 1);
	}

	float X = zfar / (float)Sum;

	int Temp = 0;

	for (int i = 0; i < m_maxLOD; i++)
	{
		int currentRange = (int)(X * (i + 1));
		m_regions[i] = Temp + currentRange;
		Temp += currentRange;
	}
}

void LodManager::CalcMaxLOD()
{
	int numSegments = m_patchSize - 1;

	if (std::ceilf(log2f((float)numSegments)) != floorf(log2f((float)numSegments)))
	{
		printf("The number of vertices in the patch minus one must be a power of two\n");
		exit(0);
	}

	int patchSizeLOG2 = (int)log2f((float)numSegments);
	m_maxLOD = patchSizeLOG2 - 1;

}

void LodManager::LODMapPass1(const glm::vec3& camPos)
{
	int CenterStep = m_patchSize / 2;

	for (int LodMapZ = 0; LodMapZ < m_numPatchesZ; LodMapZ++)
	{
		for (int LodMapX = 0; LodMapX < m_numPatchesX; LodMapX++)
		{
			int x = LodMapX * (m_patchSize - 1) + CenterStep;
			int z = LodMapZ * (m_patchSize - 1) + CenterStep;

			glm::vec3 PatchCenter = glm::vec3(x * 1.0f, 0.0f, z * 1.0f);

			float deltaX = camPos.x - PatchCenter.x;
			float deltaY = camPos.y - PatchCenter.y;
			float deltaZ = camPos.z - PatchCenter.z;

			float DistToCam = sqrt(deltaX * deltaX + deltaY * deltaY + deltaZ * deltaZ);

			int CoreLOD = DistanceToLOD(DistToCam);

			patchLod* pPatchLOD = &m_map[LodMapX][LodMapZ];
			pPatchLOD->Core = CoreLOD;

		}
	}

}

void LodManager::LODMapPass2(const glm::vec3& camPos)
{
	int step = m_patchSize / 2;

	for (int LodMapZ = 0; LodMapZ < m_numPatchesZ; LodMapZ++)
	{
		for (int LodMapX = 0; LodMapX < m_numPatchesX; LodMapX++)
		{
			int CoreLOD = m_map[LodMapX][LodMapZ].Core;

			int IndexLeft = LodMapX;
			int IndexRight = LodMapX;
			int IndexTop = LodMapZ;
			int IndexBottom = LodMapZ;

			if (LodMapX > 0)
			{
				IndexLeft--;

				if (m_map[IndexLeft][LodMapZ].Core > CoreLOD)
				{
					m_map[LodMapX][LodMapZ].Left = 1;
				}
				else
				{
					m_map[LodMapX][LodMapZ].Left = 0;
				}
			}

			if (LodMapX < m_numPatchesX - 1)
			{
				IndexRight++;

				if (m_map[IndexRight][LodMapZ].Core > CoreLOD)
				{
					m_map[LodMapX][LodMapZ].Right = 1;
				}
				else
				{
					m_map[LodMapX][LodMapZ].Right = 0;
				}
			}

			if (LodMapZ > 0)
			{
				IndexBottom--;

				if (m_map[LodMapX][IndexBottom].Core > CoreLOD)
				{
					m_map[LodMapX][LodMapZ].Bottom = 1;
				}
				else
				{
					m_map[LodMapX][LodMapZ].Bottom = 0;
				}
			}

			if (LodMapZ < m_numPatchesZ - 1)
			{
				IndexTop++;

				if (m_map[LodMapX][IndexTop].Core > CoreLOD)
				{
					m_map[LodMapX][LodMapZ].Top = 1;
				}
				else
				{
					m_map[LodMapX][LodMapZ].Top = 0;
				}
			}
		}
	}
}

int LodManager::DistanceToLOD(float Distance)
{
	int LOD = m_maxLOD;

	for (int i = 0; i <= m_maxLOD; i++)
	{
		if (Distance < m_regions[i])
		{
			LOD = i;
			break;
		}
	}

	return LOD;
}
