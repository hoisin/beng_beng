//--------------------------------------------------------------------------
//
//	Scene manager
//	- Performs processing of scene to render
//	- Passed new objects handles by this (life time)
//
//--------------------------------------------------------------------------
#pragma once

#include <Windows.h>
#include <list>
#include "glm\gtx\quaternion.hpp"
#include "glm\vec3.hpp"
#include "glm\matrix.hpp"
#include "COpenGL.h"
#include "CAssetManager.h"

struct SDrawMesh {
	std::string m_meshID;
	glm::vec3 m_position;
	glm::quat m_rotation;
	float m_scale;
};

typedef std::list<SDrawMesh*> DrawMeshList;

class CRenderer
{
public:
	CRenderer();
	~CRenderer();

	ErrorId Initialise(HINSTANCE hInstance, HWND* hwnd, UINT windowWidth,
		UINT windowHeight, WNDPROC funcCallBack);

	void ResizeViewPort(UINT windowWidth, UINT windowHeight);

	void Render(const DrawMeshList* drawMeshList);

	void UpdateProjMatrix(const glm::mat4& projMatrix);

	void UpdateViewMatrix(const glm::mat4& viewMatrix);

	int GetScreenWidth() const;
	int GetScreenHeight() const;

	void SetWireFrame(bool bEnable);

protected:
	// Clears the screen to background colour
	void ClearScreen();

	// Swaps drawn buffer
	void UpdateDisplay();

protected:
	COpenGL m_openGL;

	glm::mat4 m_projMatrix;
	glm::mat4 m_viewMatrix;
	bool m_bWireFrame;
};
