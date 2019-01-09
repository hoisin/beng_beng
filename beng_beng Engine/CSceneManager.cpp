//--------------------------------------------------------------------------
//
//	Scene manager
//	- Performs processing of scene to render
//	- Passed new objects handles by this (life time)
//
//--------------------------------------------------------------------------
#include "glm\gtx\quaternion.hpp"
#include "CSceneManager.h"
#include "CCamera.h"
#include "CCameraFPS.h"
#include "CParticleManager.h"

CSceneManager::CSceneManager() : m_pRenderer(nullptr)
{
}

CSceneManager::~CSceneManager()
{
	ShutDown();
}

bool CSceneManager::Initialise(CRenderer * pRenderer)
{
	m_pRenderer = pRenderer;

	return true;
}

void CSceneManager::AddCamera(CCamera* newCamera)
{
	m_cameraArray.push_back(newCamera);
}

CCamera * CSceneManager::GetCamera(int camNo)
{
	CCamera* camera = nullptr;

	if (camNo >= 0 && camNo < (int)m_cameraArray.size()) {
		camera = m_cameraArray[camNo];
	}
	return camera;
}

void CSceneManager::AddLight()
{
}

void CSceneManager::UpdateCamera()
{
	for (int i = 0; i < (int)m_cameraArray.size(); i++)
		m_cameraArray[i]->Update();
}

void CSceneManager::UpdateScene(CWorld* pWorld)
{
	m_objDrawList.clear();

	pWorld->GetDrawObjectList(&m_objDrawList);
	PARTICLEMGR->GetActiveParticles(&m_objDrawList);
}

void CSceneManager::RenderScene(int cameraNo)
{
	ClearDrawList();

	auto drawObjIT = m_objDrawList.begin();
	while (drawObjIT != m_objDrawList.end()) {
		SDrawMesh* newDrawMesh = new SDrawMesh;
		newDrawMesh->m_meshID = (*drawObjIT)->GetModelID();
		newDrawMesh->m_position = (*drawObjIT)->GetPosition();
		newDrawMesh->m_rotation = glm::quat((*drawObjIT)->GetRotation());
		newDrawMesh->m_scale = (*drawObjIT)->GetScale();
		m_drawMeshList.push_back(newDrawMesh);
		++drawObjIT;
	}

	int cam = cameraNo - 1;
	m_pRenderer->UpdateProjMatrix(m_cameraArray[cam]->GetProjectionMatrix());
	m_pRenderer->UpdateViewMatrix(m_cameraArray[cam]->GetViewMatrix());
	m_pRenderer->Render(&m_drawMeshList);
}

void CSceneManager::RenderScene(int cameraNo, float tickInterpValue)
{
	ClearDrawList();

	if (tickInterpValue > 1.0)
		tickInterpValue = 1.0;

	auto drawObjIT = m_objDrawList.begin();
	while (drawObjIT != m_objDrawList.end()) {
		SDrawMesh* newDrawMesh = new SDrawMesh;
		newDrawMesh->m_meshID = (*drawObjIT)->GetModelID();
		glm::vec3 prevRot = (*drawObjIT)->GetPrevRotation();
		glm::vec3 rot = (*drawObjIT)->GetRotation();
		glm::vec3 interp = glm::mix(prevRot, rot, tickInterpValue);

		newDrawMesh->m_rotation = glm::quat(interp);

		glm::vec3 prev = (*drawObjIT)->GetPrevPosition();
		glm::vec3 pos = (*drawObjIT)->GetPosition();
		newDrawMesh->m_position.x = ((pos.x - prev.x) * tickInterpValue) + prev.x;
		newDrawMesh->m_position.y = ((pos.y - prev.y) * tickInterpValue) + prev.y;
		newDrawMesh->m_position.z = ((pos.z - prev.z) * tickInterpValue) + prev.z;

		newDrawMesh->m_scale = (*drawObjIT)->GetScale();

		m_drawMeshList.push_back(newDrawMesh);
		++drawObjIT;
	}

	// Testing
	SDrawMesh* testChunk = new SDrawMesh;
	testChunk->m_meshID = "chunk_model";
	testChunk->m_position.x = 0;
	testChunk->m_position.y = 30;
	testChunk->m_position.z = 0;
	testChunk->m_scale = 1.0;
	m_drawMeshList.push_back(testChunk);

	int cam = cameraNo - 1;
	m_pRenderer->UpdateProjMatrix(m_cameraArray[cam]->GetProjectionMatrix());
	m_pRenderer->UpdateViewMatrix(m_cameraArray[cam]->GetViewMatrix());
	m_pRenderer->Render(&m_drawMeshList);
}

int CSceneManager::GetScreenWidth() const
{
	return m_pRenderer->GetScreenWidth();
}

int CSceneManager::GetScreenHeight() const
{
	return m_pRenderer->GetScreenHeight();
}

void CSceneManager::WireFrameMode(bool bEnable)
{
	m_pRenderer->SetWireFrame(bEnable);
}

void CSceneManager::ShutDown()
{
	// Draw Mesh Items
	auto drawItemIT = m_drawMeshList.begin();
	while (drawItemIT != m_drawMeshList.end()) {
		if ((*drawItemIT)) {
			delete (*drawItemIT);
			(*drawItemIT) = nullptr;	
		}
		++drawItemIT;
	}

	// Cameras
	for (int camera = 0; camera < (int)m_cameraArray.size(); camera++) {
		if (m_cameraArray[camera]) {
			delete m_cameraArray[camera];
			m_cameraArray[camera] = nullptr;
		}
	}
}

void CSceneManager::ClearDrawList()
{
	// Clear the draw item list
	auto drawItemIT = m_drawMeshList.begin();
	while (drawItemIT != m_drawMeshList.end()) {
		if ((*drawItemIT)) {
			delete (*drawItemIT);
			(*drawItemIT) = nullptr;
		}
		++drawItemIT;
	}
	m_drawMeshList.clear();

}

