//--------------------------------------------------------------------------
//
//	07/12/2017
//
//	Unit tests for CMaterialManager
//
//	Author: Matt © 2017
//
//--------------------------------------------------------------------------

#pragma once

#include <gtest/gtest.h>
#include "CMaterialManager.h"

class CMaterialManagerUTest : public ::testing::Test
{
public:
	CMaterialManagerUTest();
	~CMaterialManagerUTest();

	void SetUp();

	void TearDown();

public:
	CMaterialManager m_materialMgr;
};

