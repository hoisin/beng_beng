#include "CTimerUTest.h"

CTimerUTest::CTimerUTest()
{
}


CTimerUTest::~CTimerUTest()
{
}

void CTimerUTest::SetUp()
{
}

void CTimerUTest::TearDown()
{
}

//--------------------------------------------------------------------------
// Unit tests
//--------------------------------------------------------------------------

// Testing initialise
//TEST(CTimer, NoTest)
//{
//	EXPECT_EQ(true, true);
//}

int g_sleepTime = 1000;		// Milliseconds

// Class fixture testing
TEST_F(CTimerUTest, TickTest)
{
	// Reset the timer
	m_testTimer.Reset();

	double checkTime1 = m_testTimer.Time();

	Sleep(g_sleepTime);
	m_testTimer.Tick();

	double checkTime2 = m_testTimer.Time();
	
	// Should not be the same
	EXPECT_NE(checkTime1, checkTime2) << "Tick should have progressed timer";
}

TEST_F(CTimerUTest, ResetTest)
{
	Sleep(g_sleepTime);
	m_testTimer.Tick();
	double checkTime1 = m_testTimer.Time();

	// Reset the timer
	m_testTimer.Reset();
	double checkTime2 = m_testTimer.Time();

	// Time 2 should be less than time 1
	EXPECT_LT(checkTime2, checkTime1) << "'Second' time should be less than the first";
}

TEST_F(CTimerUTest, StartStopTest)
{
	m_testTimer.Tick();
	m_testTimer.Stop();
	m_testTimer.Reset();

	Sleep(g_sleepTime);
	m_testTimer.Tick();
	double checkTimer1 = m_testTimer.Time();
	// Timer should be paused/stopped
	EXPECT_EQ(0, checkTimer1) << "Timer 1 should be 0";

	m_testTimer.Start();
	Sleep(g_sleepTime);
	m_testTimer.Tick();
	double checkTimer2 = m_testTimer.Time();
	// Timer should have progressed
	EXPECT_GT(checkTimer2, 0) << "Timer 2 should be greater than 0";
}

TEST_F(CTimerUTest, DeltaTimeTest)
{
	m_testTimer.Tick();
	Sleep(g_sleepTime);
	m_testTimer.Tick();
	double deltaTime = m_testTimer.DeltaTime();

	double deltaThreshold = 1.002;	// 2 milliseconds grace
	EXPECT_LT(deltaTime, deltaThreshold) << "Delta time should be approx. less than 1.002";

	m_testTimer.Stop();
	m_testTimer.Tick();
	deltaTime = m_testTimer.DeltaTime();
	EXPECT_EQ(0, deltaTime) << "Delta time should be 0 after Stop()";
}

TEST_F(CTimerUTest, TimeTest)
{
	m_testTimer.Reset();
	Sleep(g_sleepTime);
	m_testTimer.Tick();

	double timeError = m_testTimer.Time() - 1.0;
	EXPECT_LT(timeError, 0.0020) << "Expected time with error margin less than 0.002, got: " + std::to_string(timeError);
}