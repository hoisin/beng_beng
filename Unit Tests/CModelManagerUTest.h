//--------------------------------------------------------------------------
//
//	03/12/2017
//
//	Unit test for model manager
//	
//	Author: Matt © 2017
//
//--------------------------------------------------------------------------

#pragma once

#include <gtest\gtest.h>
#include "COpenGLTestApp.h"


class CModelManagerUTest : public ::testing::Test
{
public:
	CModelManagerUTest();
	~CModelManagerUTest();

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
