//--------------------------------------------------------------------------
//
//	26/11/2017
//
//	Unit tests for CVertexBuffer class
//  There is a number of different vertex types where the loading of
//		vertex data differs depending on the type.
//	Current unit tests only check for PNT type.
//	To expand this.
//
//	Author: Matt © 2017
//
//--------------------------------------------------------------------------

#pragma once

#include <gtest/gtest.h>
#include "COpenGLTestApp.h"

class CVertexBufferUTest : public ::testing::Test
{
public:
	CVertexBufferUTest();
	~CVertexBufferUTest();

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