//--------------------------------------------------------------------------
//
//	03/12/2017
//
//	Model Manager class
//	Keeps track of created models
//
//--------------------------------------------------------------------------

#pragma once

#include <vector>
#include "GfxDefs.h"
#include "CModel.h"
#include "CMesh.h"

class CModelManager
{
public:
	CModelManager();
	~CModelManager();

	// Creates a new model, adds to the vector and returns pointer reference to it.
	CModel* CreateModel(const std::string& modelID);

	CModel* GetModel(const std::string& modelID);
	CModel* GetModel(GLuint modelIndex);

	int GetModelCount() const;

	ErrorId RemoveModel(const std::string& modelID);

	void CleanUp();

protected:
	bool IsModelIDUsed(const std::string& modelID) const;

protected:
	std::vector<CModel> m_models;

};


