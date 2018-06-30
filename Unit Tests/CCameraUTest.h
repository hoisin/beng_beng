//--------------------------------------------------------------------------
//
//	09/12/2017
//
//	Unit tests for CCamera class
//
//	Author: Matt © 2017
//
//--------------------------------------------------------------------------

#pragma once

#include <gtest\gtest.h>
#include "CCamera.h"

class CCameraUTest : public ::testing::Test
{
public:
	CCameraUTest();
	~CCameraUTest();

	void SetUp();

	void TearDown();

public:
	CCamera m_camera;
};
