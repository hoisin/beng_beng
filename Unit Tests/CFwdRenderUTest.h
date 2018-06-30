//--------------------------------------------------------------------------
//
//	04/12/2017
//
//	Unit test for CFwdRender class
//
//--------------------------------------------------------------------------

#pragma once

#include <gtest/gtest.h>
#include "COpenGLTestApp.h"

class CFwdRenderUTest : public ::testing::Test
{
public:
	CFwdRenderUTest();
	~CFwdRenderUTest();

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
