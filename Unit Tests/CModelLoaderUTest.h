//--------------------------------------------------------------------------
//
//	16/01/2018
//
//	Unit tests for CModelLoader
//
//	Author: Matt © 2018
//
//--------------------------------------------------------------------------

#pragma once

#include <gtest\gtest.h>
#include "COpenGLTestApp.h"
#include "CModelManager.h"
#include "CMeshDataManager.h"
#include "CTextureManager.h"
#include "CMaterialManager.h"
#include "CModelLoader.h"


class CModelLoaderUTest : public ::testing::Test
{
public:
	CModelLoaderUTest();
	~CModelLoaderUTest();

	void SetUp();

	void TearDown();

public:
	COpenGLTestApp m_app;

	CModelManager m_modelMgr;
	CMeshDataManager m_meshDataMgr;
	CTextureManager m_textureMgr;
	CMaterialManager m_materialMgr;

	CModelLoader m_modelLoader;

	std::string  m_windowName;
	int m_width;
	int m_height;
	int m_majorVer;
	int m_minorVer;
};




