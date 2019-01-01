//--------------------------------------------------------------------------
//
//	World class
//
//--------------------------------------------------------------------------

#include "CWorld.h"
#include "CCameraFPS.h"
#include "CParticleManager.h"
#include "CEmitter.h"


CWorld::CWorld() : m_pCamera(nullptr), m_lastUpdate(0), m_updateTick(0), m_bUpdated(false)
{
}

CWorld::~CWorld()
{
	ShutDown();
}

//------------------------------------------------------------------
//
//	Initialise(..)
//
//	Params:
//	minBoundary		-	World min boundary
//	maxBoundary		-	World max boundary
//
//	Initialises world, Object creation
//
//------------------------------------------------------------------
bool CWorld::Initialise(const glm::vec3& minBoundary,
	const glm::vec3& maxBoundary)
{

	// World boundary
	m_minBoundary = minBoundary;
	m_maxBoundary = maxBoundary;

	// Create some objects
	// 
	// Setup objects, link graphic to ID (Assume we just know the name)
	//
	// Put objects into list/array

	// Object scene descriptions
	//
	// 1 sphere @ center
	// 4 small cubes random place
	// 2 large cubes random place
	// 1 flag
	//
	// Mesh IDs from CApp::OnLoadAssets
	std::string objSphere = "objectSphere";
	std::string objCubeSmall = "objectCubeSmall";
	std::string objCubeLarge = "objectCubeLarge";
	std::string objFloor = "objectFloor";

	// Spheres, currently only 1
	//for (int sphere = 0; sphere < 1; sphere++) {
	//	CObject* sphereObj = m_objectMGR.CreateObject(EType_Object, objSphere);
	//	sphereObj->SetModelID("sphere_1");
	//	sphereObj->SetLocation(glm::vec3(0, 20, -50));
	//	sphereObj->SetActive(true);
	//	sphereObj->SetFacingDirection(glm::vec3(0, 0, 0));
	//}

	char* l_tempBuffer = new char[10];

	// Small cubes
	// Don't need currently
	/*for (int cubeSmall = 0; cubeSmall < 40; cubeSmall++) {
		_itoa_s(cubeSmall, l_tempBuffer, 10, 10);
		std::string cubeSmallID = objCubeSmall + "_" + l_tempBuffer;
		CObject* cubeSmallObj = m_objectMGR.CreateObject(EType_Object, cubeSmallID);

		glm::vec3 smallCubePos(rand() % 100, rand() % 100, 30);
		cubeSmallObj->SetMeshID("cube_2");
		cubeSmallObj->SetPosition(smallCubePos);
	}*/

	// Large cubes
	for (int largeCube = 0; largeCube < 1; largeCube++) {
		_itoa_s(largeCube, l_tempBuffer, 10, 10);
		std::string cubeLargeID = objCubeLarge + "_" + l_tempBuffer;
		CObject* cubeLargeObject = m_objectMGR.CreateObject(EType_Object, cubeLargeID);
		cubeLargeObject->SetModelID("cube_2");
		cubeLargeObject->SetActive(true);
		cubeLargeObject->SetFacingDirection(glm::vec3(0, 0, 0));
		cubeLargeObject->SetScale(20);
	}

	m_objectMGR.Get(objCubeLarge + "_0")->SetLocation(glm::vec3(-75, 20, 75));
	m_objectMGR.Get(objCubeLarge + "_1")->SetLocation(glm::vec3(75, 20, 75));
	m_objectMGR.Get(objCubeLarge + "_2")->SetLocation(glm::vec3(-75, 20, -75));
	m_objectMGR.Get(objCubeLarge + "_3")->SetLocation(glm::vec3(75, 20, -75));

	CObject* cubeTest = m_objectMGR.CreateObject(EType_Object, "testCube");
	cubeTest->SetModelID("cube_2");
	cubeTest->SetActive(true);
	cubeTest->SetScale(1.0);
	cubeTest->SetDirection(glm::vec3(0, 0, 0));

  // Plane
	CObject* planeObject = m_objectMGR.CreateObject(EType_Object, objFloor);
	planeObject->SetModelID("plane_1");
	planeObject->SetLocation(glm::vec3(0, -10, 0));
	planeObject->SetActive(true);
	planeObject->SetFacingDirection(glm::vec3(0, 0, 0));

	delete[] l_tempBuffer;
	l_tempBuffer = nullptr;

	// Create particles
	//PARTICLEMGR->CacheParticles(4000);
	
	// Create an emitter
	/*CEmitter* pEmitter = (CEmitter*)m_objectMGR.CreateObject(EType_Emitter, "emitter");
	pEmitter->SetParticleSpawnPerTick(6);
	pEmitter->SetParticleSpawnRate(75);
	pEmitter->SetLocation(glm::vec3(0, 50, -75));
	pEmitter->SetFacingDirection(glm::vec3(0, 0, 0));

	chunk.CreateChunk(10, 10, 10);
	chunk.GetVoxel(0, 0, 0)->bActive = false;
	chunk.GetVoxel(9, 9, 9)->bActive = false;
	ASSETMGR->GenerateChunkMesh(&chunk, "my_chunk");
	ASSETMGR->CreateModel("chunk_model");
	ASSETMGR->AddMeshToModel("chunk_model", "my_chunk", "material_1", true);

	return true;
}

#include "glm/gtc/constants.hpp"
float g_angle = 0;

void CWorld::Update(float deltaT)
{
	// World update sim
	m_lastUpdate += deltaT;
	g_angle+=0.01;
	if (g_angle > 360) g_angle = 0;

	if (m_lastUpdate >= m_updateTick) {
		// -------------------------------------------------------------------
		// Test code
		CObject* pObj = m_objectMGR.Get("objectSphere");
		glm::vec3 temp;
		temp.x = g_angle;
		temp.y = g_angle;
		pObj->SetPrevRotation(pObj->GetRotation());
		pObj->SetRotation(temp);*/
		//------------------------------------------------------------------ -

		std::list<CObject*> objList;
		bool bGetList = m_objectMGR.GetObjectList(&objList);
		if (bGetList) {
			auto objIT = objList.begin();
			while (objIT != objList.end()) {
				(*objIT)->Update(m_lastUpdate);
				++objIT;
			}
		}

		m_bUpdated = true;
		m_lastUpdate = 0;

		// Update particles
		PARTICLEMGR->UpdateParticles(deltaT);
	}

	
}

//------------------------------------------------------------------
//
//	GetObjectList(..)
//
//	Params:
//	objectList		-	pointer to object list
//
//	Returns a list of current objects
//
//------------------------------------------------------------------
bool CWorld::GetObjectList(std::list<CObject*>* objectList)
{
	return m_objectMGR.GetObjectList(objectList);
}

//------------------------------------------------------------------
//
//	GetDrawObjectList(..)
//
//	Params:
//	objectList		-	pointer to object list
//
//	Returns objects that are to be 'drawn'
//	Objects have to be active and have a meshID in order to be included
//	 in the list
//
//------------------------------------------------------------------
bool CWorld::GetDrawObjectList(std::list<CObject*>* objectList)
{
	return m_objectMGR.GetDrawObjectList(objectList);
}

//------------------------------------------------------------------
//
//	CreateCameraFPS(..)
//
//	Params:
//	pos				- Camera pos
//	up				- Camera up
//	zNear			- Z near value
//	zFar			- Z far valur
//	aspectRatio		- Aspect ratio
//	fovV			- Field of view angle (degrees)
//
//	Creates camera in world
//
//------------------------------------------------------------------
void CWorld::CreateCameraFPS(const glm::vec3 & pos, const glm::vec3 & up, float zNear, float zFar, float aspectRatio, 
	float fovV)
{
	// Create our camera 
	m_pCamera = new CCameraFPS(glm::vec3(0, 10, 0), glm::vec3(0, 1, 0), 1.f, 1000.f, aspectRatio, 45.f);
}

CCamera * CWorld::GetCamera() const
{
	return m_pCamera;
}

float CWorld::GetLastUpdate() const
{
	return m_lastUpdate;
}

void CWorld::SetUpdateTick(float tick)
{
	m_updateTick = tick;
}

float CWorld::GetUpdateTick() const
{
	return m_updateTick;
}

bool CWorld::IsUpdated() const
{
	return m_bUpdated;
}

void CWorld::EndUpdate()
{
	m_bUpdated = false;
}

void CWorld::ShutDown()
{
	PARTICLEMGR->Release();

	m_objectMGR.CleanUp();

	if (m_pCamera) {
		delete m_pCamera;
		m_pCamera = nullptr;
	}
}
