//--------------------------------------------------------------------------
//
//	27/12/2017
//
//	Unit tests for CMeshDataManager
//
//	Author: Matt © 2017
//
//--------------------------------------------------------------------------

#pragma once
#include <gtest\gtest.h>
#include "CMeshDataManager.h"

class CMeshDataManagerUTest : public ::testing::Test
{
public:
	CMeshDataManagerUTest();
	~CMeshDataManagerUTest();

	void SetUp();

	void TearDown();

public:
	CMeshDataManager m_testManager;
};