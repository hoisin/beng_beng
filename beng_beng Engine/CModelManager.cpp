#include "CModelManager.h"


CModelManager::CModelManager()
{
}

CModelManager::~CModelManager()
{
	CleanUp();
}

//------------------------------------------------------------------
//
//	CreateModel()
//
//	modelID		-	ID to attach created model with
//
//	Creates and returns pointer to created model.
//	Nukll ptr if failed to create.
//
//------------------------------------------------------------------
CModel* CModelManager::CreateModel(const std::string & modelID)
{
	CModel* newModel = nullptr;

	if (!IsModelIDUsed(modelID))
	{
		m_models.push_back(CModel(modelID));
		int index = (int)m_models.size() - 1;
		newModel = &m_models[index];
	}

	return newModel;
}

//------------------------------------------------------------------
//
//	GetModel()
//
//	modelID		-	ID of model to return
//
//	Returns model of specified model ID.
//	Null ptr if invalid or not found ID.
//
//------------------------------------------------------------------
CModel* CModelManager::GetModel(const std::string & modelID)
{
	CModel* model = nullptr;

	for (int i = 0; i < (int)m_models.size(); i++)
	{
		if (m_models[i].GetID() == modelID)
		{
			model = &m_models[i];
			break;
		}
	}

	return model;
}

//------------------------------------------------------------------
//
//	GetModel()
//
//	modelIndex	-	index element of array
//
//	Returns model of specified model index.
//	Null ptr if invalid index.
//
//------------------------------------------------------------------
CModel* CModelManager::GetModel(GLuint modelIndex)
{
	CModel* model = nullptr;

	if (modelIndex < m_models.size())
		model = &m_models[modelIndex];

	return model;
}

int CModelManager::GetModelCount() const
{
	return (int)m_models.size();
}

ErrorId CModelManager::RemoveModel(const std::string & modelID)
{
	for (int i = 0; i < static_cast<int>(m_models.size()); i++)
	{
		if (m_models[i].GetID() == modelID)
		{
			if (i != (static_cast<int>(m_models.size()) - 1))
				std::swap(m_models[i], m_models.back());

			m_models[i].CleanUp();
			m_models.pop_back();
			return ERRORID_NONE;
		}
	}

	return ERRORID_MODEL_REMOVE_MODEL_FAILED;
}

void CModelManager::CleanUp()
{
	for (int i = 0; i < m_models.size(); i++)
		m_models[i].CleanUp();

	m_models.clear();
}

//------------------------------------------------------------------
//
//	IsModelIDUsed()
//
//	modelID	-	ID to check
//
//	Checks if specified ID is already used for a model
//
//------------------------------------------------------------------
bool CModelManager::IsModelIDUsed(const std::string& modelID) const
{
	bool result = false;
	auto it = m_models.begin();

	while (it != m_models.end())
	{
		// If matching ID
		if (modelID == it->GetID())
		{
			result = true;
			break;
		}

		++it;
	}

	return result;
}
