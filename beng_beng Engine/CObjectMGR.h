//--------------------------------------------------------------------------
//
//	Object manager
//
//--------------------------------------------------------------------------
#pragma once

#include <string>
#include <map>
#include <list>
#include <vector>

#include "CObject.h"

class CObjectMGR
{
public:
	CObjectMGR();
	~CObjectMGR();

	CObject* CreateObject(EObjectType objType, const std::string& objID);

	CObject* Get(const std::string& objID);
	bool GetObjectList(std::list<CObject*>* objectList);
	bool GetDrawObjectList(std::list<CObject*>* objectList);

	int GetObjectCount() const;

	void CleanUp();

protected:
	std::map<std::string, CObject*> m_objectMap;

};

