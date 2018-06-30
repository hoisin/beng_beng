//--------------------------------------------------------------------------
//
//	26/11/2017
//
//	Unit tests for COpenGL class
//
//	Author: Matt © 2017
//
//--------------------------------------------------------------------------

#pragma once
#include <gtest\gtest.h>

#include "COpenGLTestApp.h"
#include "COpenGL.h"

class COpenGLUTest : public ::testing::Test
{
public:
	COpenGLUTest();
	~COpenGLUTest();

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

