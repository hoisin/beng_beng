//--------------------------------------------------------------------------
//
//	CTimer unit test
//
//	03/11/2017
//
//--------------------------------------------------------------------------
#pragma once
#include <gtest\gtest.h>
#include "CTimer.h"


class CTimerUTest : public ::testing::Test
{
public:
	CTimerUTest();
	~CTimerUTest();

	void SetUp();

	void TearDown();

public:
	CTimer m_testTimer;
};

