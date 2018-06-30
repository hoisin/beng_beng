//--------------------------------------------------------------------------
//
//	07/12/2017
//
//	Unit tests for CMaterial class
//
//	Author: Matt © 2017
//
//--------------------------------------------------------------------------
#pragma once

#include <gtest\gtest.h>
#include "COpenGLTestApp.h"
#include "CMaterial.h"

class CMaterialUTest : public ::testing::Test
{
public:
	CMaterialUTest();
	~CMaterialUTest();

	void SetUp();
	
	void TearDown();

public:
	CMaterial m_material;
};