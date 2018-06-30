//--------------------------------------------------------------------------
//
//	08/01/2018
//
//	Unit test for particle object
//
//	Author: Matt © 2018
//
//--------------------------------------------------------------------------

#pragma once

#include <gtest\gtest.h>
#include "CParticle.h"

class CParticleUTest : public ::testing::Test
{
public:
	CParticleUTest();
	~CParticleUTest();

	void SetUp();
	
	void TearDown();

public:
	CParticle m_testParticle;
};
