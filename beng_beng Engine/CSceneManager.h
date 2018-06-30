//--------------------------------------------------------------------------
//
//	Scene manager
//	- Performs processing of scene to render
//	- Passed new objects handles by this (life time)
//
//	To add unit tests later
//
//--------------------------------------------------------------------------
#pragma once

#include <string>
#include <list>
#include <vector>
#include "CWorld.h"
#include "CObject.h"
#include "GfxDefs.h"
#include "CRenderer.h"

class CRenderer;

class CCamera;

class CSceneManager
{
public:
	CSceneManager();
	~CSceneManager();

	bool Initialise(CRenderer* pRenderer);

	// Adds a camera to the scene
	void AddCamera(CCamera* newCamera);
	CCamera* GetCamera(int camNo);

	// Adds a light to the scene
	void AddLight();

	// Update the camera properties
	void UpdateCamera();

	// Update the scene properties
	void UpdateScene(CWorld* pWorld);

	// Render scene from 'cameraNo' view point
	void RenderScene(int cameraNo);
	void RenderScene(int cameraNo, float tickInterpValue);

	int GetScreenWidth() const;
	int GetScreenHeight() const;

	void ShutDown();

protected:
	void ClearDrawList();

protected:
	std::vector<CCamera*> m_cameraArray;

	std::list<CObject*> m_objDrawList;		// Pointer list to objects to be drawn
	
	DrawMeshList m_drawMeshList;

	CRenderer* m_pRenderer;
};


