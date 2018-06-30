//--------------------------------------------------------------------------
//
//	27/11/2017
//
//	Unit tests for CMesh class
//
//	Author: Matt © 2017
//
//--------------------------------------------------------------------------

#pragma once

#include <gtest/gtest.h>
#include "COpenGLTestApp.h"

class CMeshUTest : public ::testing::Test
{
public: 
	CMeshUTest();
	~CMeshUTest();

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
