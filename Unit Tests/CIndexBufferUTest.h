//--------------------------------------------------------------------------
//
//	26/11/2017
//
//	Unit tests for CIndexBuffer class
//
//	Author: Matt © 2017
//
//--------------------------------------------------------------------------

#pragma once
#include <gtest\gtest.h>

#include "COpenGLTestApp.h"

class CIndexBufferUTest : public ::testing::Test
{
public:
	CIndexBufferUTest();
	~CIndexBufferUTest();

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

