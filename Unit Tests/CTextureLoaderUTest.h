//--------------------------------------------------------------------------
//
//	04/12/2017
//
//	CTextureLoader unit test class
//
//	Author: Matt © 2017
//
//--------------------------------------------------------------------------

#pragma once

#include <gtest/gtest.h>
#include "COpenGLTestApp.h"

class CTextureLoaderUTest : public ::testing::Test
{
public:
	CTextureLoaderUTest();
	~CTextureLoaderUTest();

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

