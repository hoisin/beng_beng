//--------------------------------------------------------------------------
//
//	31/12/2017
//
//	Unit test for CObject
//
//	Author: Matt © 2017
//
//--------------------------------------------------------------------------

#pragma once
#include <gtest\gtest.h>
#include "CObject.h"

class CObjectUTest : public ::testing::Test
{
public:
	CObjectUTest();
	~CObjectUTest();

	void SetUp();

	void TearDown();

public:
	CObject m_testObject;
};