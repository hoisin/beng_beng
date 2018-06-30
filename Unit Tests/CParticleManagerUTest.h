//--------------------------------------------------------------------------
//
//	08/01/2017
//
//	Unit test for particle manager
//
//	Author: Matt © 2018
//
//--------------------------------------------------------------------------

#pragma once

#include <gtest\gtest.h>
#include "CParticleManager.h"

class CParticleManagerUTest : public ::testing::Test
{
public:
	CParticleManagerUTest();
	~CParticleManagerUTest();

	void SetUp();

	void TearDown();

public:
	CParticleManager* m_testMgr;
};