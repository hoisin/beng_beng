//--------------------------------------------------------------------------
//
//	27/12/2017
//
//	Unit tests for CMeshDataManager
//
//	Author: Matt © 2017
//
//--------------------------------------------------------------------------

#pragma once
#include <gtest\gtest.h>
#include "COpenGLTestApp.h"

class CRendererUTest : public ::testing::Test
{
public:
	CRendererUTest();
	~CRendererUTest();

	void SetUp();

	void TearDown();

public:
	COpenGLTestApp m_testApp;

	std::string m_windowName;
	int m_width;
	int m_height;
	int m_majorVer;
	int m_minorVer;
};