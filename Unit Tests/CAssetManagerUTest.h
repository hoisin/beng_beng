//--------------------------------------------------------------------------
//
//	31/12/2017
//
//	Unit tests for CAssetManager
//
//	Author: Matt © 2017
//
//--------------------------------------------------------------------------

#pragma once
#include <gtest\gtest.h>
#include "COpenGLTestApp.h"

class CAssetManagerUTest : public ::testing::Test
{
public:
	CAssetManagerUTest();
	~CAssetManagerUTest();

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
