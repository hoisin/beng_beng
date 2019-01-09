//--------------------------------------------------------------------------
//
//	Renderer class handling rendering operations
//
//--------------------------------------------------------------------------
#include "CRenderer.h"

#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtx\transform.hpp>

#include "CFwdRender.h"
#include "CMesh.h"
#include "CModel.h"
#include "CTexture2D.h"


CRenderer::CRenderer() : m_bWireFrame(false)
{
}

CRenderer::~CRenderer()
{
}

//------------------------------------------------------------------
//
//	Initialise(..)
//
//	Params:
//	hInstance		-	Win32 Instance 
//	hwnd			-	Handle to window
//	windowWidth		-	Window width
//	windowHeight	-	Window height
//	funcCallBack	-   Callback function
//
//	Initialises the renderer
//
//------------------------------------------------------------------
ErrorId CRenderer::Initialise(HINSTANCE hInstance, HWND* hwnd, UINT windowWidth,
	UINT windowHeight, WNDPROC funcCallBack)
{
	// Init the OpenGL
	int majorVer = 3;
	int minorVer = 1;
	ErrorId error = m_openGL.InitOpenGL(hInstance, hwnd, majorVer, minorVer, windowWidth, windowHeight, funcCallBack);
	if (error != ERRORID_NONE) {
		// Failed to initialise OpenGL
		// Return some debug error
		std::cerr << "Failed to initialise OpenGL" << std::endl;
		return error;
	}

	// Update the view port
	ResizeViewPort(windowWidth, windowHeight);

	// 3D drawing
	m_openGL.Set2D(false);

	// Init rest of stuff...

	return error;
}

//------------------------------------------------------------------
//
//	ResizeViewPort(..)
//
//	Params:
//	windowWidth		-	Window width
//	windowHeight	-	Window height
//
//	Resizes the OpenGL viewport
//
//------------------------------------------------------------------
void CRenderer::ResizeViewPort(UINT windowWidth, UINT windowHeight)
{
	glViewport(0, 0, windowWidth, windowHeight);
}

//------------------------------------------------------------------
//
//	Render(..)
//
//	Params:
//	drawMeshList	-	List of meshes to draw
//
//	Render function
//
//------------------------------------------------------------------
void CRenderer::Render(const DrawMeshList* drawMeshList)
{
	ClearScreen();

	// Just know that we use this shader for now
	CFwdRender* pShader = ASSETMGR->GetFwdRenderTech();
	pShader->Enable();

	auto drawMeshIT = drawMeshList->begin();
	while (drawMeshIT != drawMeshList->end()) {
		SDrawMesh* pDrawMesh = (*drawMeshIT);

		CModel* pModel = ASSETMGR->GetModel(pDrawMesh->m_meshID);

		for (int i = 0; i < pModel->GetMeshCount(); i++) {
			CMesh* pMesh = pModel->GetMesh(i);

			// Get material and set textures
			CMaterial* pMaterial = ASSETMGR->GetMaterial(pMesh->GetMaterialID());
			pShader->SetDiffuseTexture(ASSETMGR->GetTexture(pMaterial->m_diffuseTextureID)->GetTexture());
			m_openGL.SetCurrentTexture(ASSETMGR->GetTexture(pMaterial->m_diffuseTextureID)->GetTexture());

			// Setup shader params

			// Scaling uniform in all axes
			float scaleValue = pDrawMesh->m_scale;
			glm::mat4 scaleMat = glm::scale(glm::vec3(scaleValue , scaleValue, scaleValue));

			glm::mat4 rotation;
			rotation = glm::toMat4(pDrawMesh->m_rotation);

			glm::mat4 world;
			world = glm::translate(glm::mat4(1.0), pDrawMesh->m_position);

			// This is actually scale * rotation * translation (SRT) order.
			// Just how matrix multiplication works.
			world = world * rotation * scaleMat;

			glm::mat4 invWorld;
			invWorld = glm::transpose(glm::inverse(world));

			glm::mat4 vpMat = m_projMatrix * m_viewMatrix;
			pShader->SetProjViewMatrix(vpMat);
			pShader->SetInvWorldMatrx(invWorld);
			pShader->SetWorldMatrix(world);

			pShader->SetPointLight(glm::vec3(0, 10, 0), glm::vec3(1, 1, 1), 1, 150);

			m_openGL.RenderBuffer(pMesh->GetVertexBuffer(), pMesh->GetIndexBuffer());

			glBindVertexArray(0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		++drawMeshIT;
	}

	glUseProgram(0);

	UpdateDisplay();
}

//------------------------------------------------------------------
//
//	UpdateProjMatrix(..)
//
//	Params:
//	projMatrix		-	proj matrix to update with
//
//	Updates the projection matrix
//
//------------------------------------------------------------------
void CRenderer::UpdateProjMatrix(const glm::mat4 & projMatrix)
{
	m_projMatrix = projMatrix;
}


//------------------------------------------------------------------
//
//	UpdateViewMatrix(..)
//
//	Params:
//	viewMatrix		-	view matrix to update with
//
//	Updates the view matrix
//
//------------------------------------------------------------------
void CRenderer::UpdateViewMatrix(const glm::mat4& viewMatrix)
{
	m_viewMatrix = viewMatrix;
}

int CRenderer::GetScreenWidth() const
{
	return m_openGL.GetScreenWidth();
}

int CRenderer::GetScreenHeight() const
{
	return m_openGL.GetScreenHeight();
}

void CRenderer::SetWireFrame(bool bEnable)
{
	if (m_bWireFrame != bEnable)
	{
		m_bWireFrame = bEnable;
		m_openGL.SetWireFrame(m_bWireFrame);
	}
}

//------------------------------------------------------------------
//
//	ClearScreen(..)
//
//	Clears the screen...
//
//------------------------------------------------------------------
void CRenderer::ClearScreen()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

//------------------------------------------------------------------
//
//	Render(..)
//
//	Flips drawn buffer
//
//------------------------------------------------------------------
void CRenderer::UpdateDisplay()
{
	m_openGL.FlipBuffers();
}
