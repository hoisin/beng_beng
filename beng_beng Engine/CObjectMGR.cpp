#include "CObjectMGR.h"
#include "CEmitter.h"


CObjectMGR::CObjectMGR()
{
}

CObjectMGR::~CObjectMGR()
{
	CleanUp();
}


//------------------------------------------------------------------
//
//	CreateObject(..)
//
//	Params:
//	objType		-	object to create
//	objID		-	Assign object ID
//
//	Creates an object in logic/world, returns nullptr on fail
//
//------------------------------------------------------------------
CObject* CObjectMGR::CreateObject(EObjectType objType, const std::string & objID)
{
	CObject* result = nullptr;

	switch (objType) {
	case EType_Object:
		result = new CObject;
		m_objectMap.insert(std::pair<std::string, CObject*>(objID, result));
		break;

	case EType_Emitter:
		result = new CEmitter;
		m_objectMap.insert(std::pair<std::string, CObject*>(objID, result));
		break;

	default:
		// Unknown object type!
		break;
	}

	return result;
}


//------------------------------------------------------------------
//
//	GetObject(..)
//
//	Params:
//	objID		-	ID of object to return
//
//	Returns specified object
//
//------------------------------------------------------------------
CObject * CObjectMGR::GetObject(const std::string & objID)
{
	auto objIT = m_objectMap.find(objID);

	if (objIT != m_objectMap.end()) {
		return objIT->second;
	}

	return nullptr;
}


//------------------------------------------------------------------
//
//	GetObjectList(..)
//
//	Params:
//	objectList		-	Passed in list to fill
//
//	Returns all objects as a list
//
//------------------------------------------------------------------
bool CObjectMGR::GetObjectList(std::list<CObject*>* objectList)
{
	if (!m_objectMap.empty()) {
		auto objIT = m_objectMap.begin();
		while (objIT != m_objectMap.end()) {
			objectList->push_back(objIT->second);
			++objIT;
		}
		return true;
	}

	// no objects
	return false;
}

//------------------------------------------------------------------
//
//	GetObjectList(..)
//
//	Params:
//	objectList		-	Passed in list to fill
//
//	Returns objects that are to be 'drawn'
//	Objects have to be active and have a meshID in order to be included
//	 in the list
//
//------------------------------------------------------------------
bool CObjectMGR::GetDrawObjectList(std::list<CObject*>* objectList)
{
	if (!m_objectMap.empty()) {
		auto objIT = m_objectMap.begin();
		while (objIT != m_objectMap.end()) {
			if (objIT->second->GetActive() && (objIT->second->GetModelID() != "")) {
				objectList->push_back(objIT->second);
			}
			++objIT;
		}
		return true;
	}

	return false;
}

int CObjectMGR::GetObjectCount() const
{
	return (int)m_objectMap.size();
}


//------------------------------------------------------------------
//
//	CleanUp(..)
//
//	Free stuff
//
//------------------------------------------------------------------
void CObjectMGR::CleanUp()
{
	auto objIT = m_objectMap.begin();

	while (objIT != m_objectMap.end()) {
		if (objIT->second) {
			delete objIT->second;
			objIT->second = nullptr;
		}
		++objIT;
	}
	m_objectMap.clear();
}
