#include <iostream>
#include <gtest/gtest.h> 

// include tests
#include "CBaseAppUTest.h"

int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();

	system("PAUSE");
	return 0;
}