//--------------------------------------------------------------------------
//
//	09/12/2017
//
//	Unit tests for CCameraFPS class
//
//	Author: Matt © 2017
//
//--------------------------------------------------------------------------

#pragma once

#include <gtest\gtest.h>
#include "CCameraFPS.h"

class CCameraFPSUTest : public ::testing::Test
{
public:
	CCameraFPSUTest();
	~CCameraFPSUTest();

	void SetUp();

	void TearDown();

public:
	CCameraFPS m_camera;

	glm::vec3 m_defaultPos;
	glm::vec3 m_defaultLook;
	glm::vec3 m_defaultUp;
};
