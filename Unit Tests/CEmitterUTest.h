//--------------------------------------------------------------------------
//
//	08/01/2017
//
//	Unit test for emitter object
//
//	Author: Matt © 2018
//
//--------------------------------------------------------------------------

#pragma once

#include <gtest\gtest.h>
#include "CEmitter.h"

class CEmitterUTest : public ::testing::Test
{
public:
	CEmitterUTest();
	~CEmitterUTest();

	void SetUp();
	
	void TearDown();

public:
	CEmitter m_testEmitter;

};