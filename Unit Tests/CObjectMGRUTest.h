//--------------------------------------------------------------------------
//
//	09/01/2018
//
//	Unit test for particle object
//
//	Author: Matt © 2018
//
//--------------------------------------------------------------------------

#pragma once

#include <gtest/gtest.h>
#include "CObjectMGR.h"

class CObjectMGRUTest : public ::testing::Test
{
public:
	CObjectMGRUTest();
	~CObjectMGRUTest();

	void SetUp();

	void TearDown();

public:
	CObjectMGR m_testMgr;
};