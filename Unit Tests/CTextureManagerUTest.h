//--------------------------------------------------------------------------
//
//	06/12/2017
//
//	Unit test for texture manager
//
//	Author: Matt © 2017
//
//--------------------------------------------------------------------------

#pragma once

#include <gtest\gtest.h>
#include "COpenGLTestApp.h"


class CTextureManagerUTest : public ::testing::Test
{
public:
	CTextureManagerUTest();
	~CTextureManagerUTest();

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
