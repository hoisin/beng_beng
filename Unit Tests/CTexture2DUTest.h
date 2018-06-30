//--------------------------------------------------------------------------
//
//	05/12/2017
//
//	Unit tests for CTexture2D class
//
//	Author: Matt © 2017
//
//--------------------------------------------------------------------------
#pragma once

#include <gtest\gtest.h>
#include "COpenGLTestApp.h"

class CTexture2DUTest : public ::testing::Test
{
public:
	CTexture2DUTest();
	~CTexture2DUTest();

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
