//--------------------------------------------------------------------------
//
//	26/11/2017
//
//	Unit tests for CMeshDataGenerator
//
//	Author: Matt © 2017
//
//--------------------------------------------------------------------------

#pragma once
#include <gtest\gtest.h>
#include "CMeshDataGenerator.h"

class CMeshDataGeneratorUTest : public ::testing::Test
{
public:
	CMeshDataGeneratorUTest();
	~CMeshDataGeneratorUTest();

	void SetUp();

	void TearDown();

public:
	CMeshDataGenerator m_testGenerator;
};
