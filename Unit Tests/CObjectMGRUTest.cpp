#include "CObjectMGRUTest.h"
#include "CObject.h"

//--------------------------------------------------------------------------
// UTest class
//--------------------------------------------------------------------------

CObjectMGRUTest::CObjectMGRUTest()
{
}

CObjectMGRUTest::~CObjectMGRUTest()
{
}

void CObjectMGRUTest::SetUp()
{
}

void CObjectMGRUTest::TearDown()
{
}


//--------------------------------------------------------------------------
// Unit tests
//--------------------------------------------------------------------------

TEST_F(CObjectMGRUTest, CreationTests)
{
	EXPECT_EQ(0, m_testMgr.GetObjectCount()) << "Object count should be 0 by default";

	// CObject creation
	EObjectType objType = EType_Object;
	std::string objectName = "object_1";
	CObject* resultObject = m_testMgr.CreateObject(objType, objectName);
	EXPECT_NE(nullptr, resultObject) << "Failed to create CObject";
	
	// CEmitter creation
	objectName = "emitter_1";
	resultObject = m_testMgr.CreateObject(objType, objectName);
	EXPECT_NE(nullptr, resultObject) << "Failed to create CEmitter";

	int count = 2;
	EXPECT_EQ(count, m_testMgr.GetObjectCount()) << "Should be two objects created";
}


TEST_F(CObjectMGRUTest, GetTests)
{
	// Create objects
	std::vector<std::string> objectNames;
	int testObjCount = 100;

	EXPECT_EQ(0, m_testMgr.GetObjectCount()) << "Object count should be 0 by default";

	for (int i = 0; i < testObjCount; i++)
	{
		std::string objectID = "object_" + std::to_string(i);
		objectNames.push_back(objectID);
		EXPECT_NE(nullptr, m_testMgr.CreateObject(EType_Object, objectID)) << "Failed to create object " + objectID;
	}

	// Check object count
	EXPECT_EQ(testObjCount, m_testMgr.GetObjectCount()) << "Unexpected object count returned";

	// Attempt to get all created objects
	for (int j = 0; j < testObjCount; j++)
	{
		std::string objectID = "object_" + std::to_string(j);
		EXPECT_NE(nullptr, m_testMgr.GetObject(objectNames[j])) << "Unexpected nullptr for get object " + objectID;
	}

	// Get object list
	std::list<CObject*> objList;
	EXPECT_EQ(true, m_testMgr.GetObjectList(&objList)) << "Failed to get object list";
	EXPECT_EQ(testObjCount, (int)objList.size()) << "Unexpected object count in returned list";

	// Set first 20 objects to be active with models for draw test
	int drawObjTotal = 20;
	for (int k = 0; k < drawObjTotal; k++)
	{
		std::string objectID = "object_" + std::to_string(k);
		CObject* returnObj = m_testMgr.GetObject(objectID);
		returnObj->SetActive(true);
		returnObj->SetModelID("TestID");	// Doesn't matter that the model ID is the same
	}

	// Test get draw list
	std::list<CObject*> drawObjs;
	EXPECT_EQ(true, m_testMgr.GetDrawObjectList(&drawObjs)) << "Failed to get draw object list";
	EXPECT_EQ(drawObjTotal, (int)drawObjs.size()) << "Unexpected amount of objects returned for draw object list";
}