//--------------------------------------------------------------------------
//
//	Base Application framework unit test
//
//	03/11/2017
//
//--------------------------------------------------------------------------
#pragma once

#include <gtest\gtest.h>
#include "COpenGLTestApp.h"

class CBaseAppUTest : public ::testing::Test
{
public:
	CBaseAppUTest();

	~CBaseAppUTest();

	void SetUp();

	void TearDown();

public:
	COpenGLTestApp m_testApp;
};
