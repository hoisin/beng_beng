//--------------------------------------------------------------------------
//
//	World class
//
//	Add unit test later
//
//--------------------------------------------------------------------------
#pragma once

#include "CObjectMGR.h"
#include "CCamera.h"

#include "CVoxel.h"

#include "CAssetManager.h"

class CWorld
{
public:
	CWorld();
	~CWorld();

	bool Initialise(const glm::vec3& minBoundary,
		const glm::vec3& maxBoundary);

	// Pass in deltaT
	void Update(float deltaT);

	// Add objects

	// Remove objects?

	// Access objects

	// Get objects
	bool GetObjectList(std::list<CObject*>* objectList);
	bool GetDrawObjectList(std::list<CObject*>* objectList);

	// Get camera
	void CreateCameraFPS(const glm::vec3 &pos, const glm::vec3 &up, float zNear, float zFar, float aspectRatio,
		float fovV);
	CCamera* GetCamera() const;

	//void SpawnParticleEmitter();

	//DoCommand(const ICommand& command)

	float GetLastUpdate() const;

	void SetUpdateTick(float tick);

	float GetUpdateTick() const;

	bool IsUpdated() const;

	void EndUpdate();

	void ShutDown();

protected:
	// Map of stringID to objects
	CObjectMGR m_objectMGR;

	glm::vec3 m_minBoundary;
	glm::vec3 m_maxBoundary;

	// Got one camera only (First person camera) currently
	CCamera* m_pCamera;

	float m_lastUpdate;
	float m_updateTick;

	bool m_bUpdated;

public:
	CChunk chunk;
};
