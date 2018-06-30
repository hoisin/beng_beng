//--------------------------------------------------------------------------
//
//	Material manager
//
//--------------------------------------------------------------------------

#include "CMaterialManager.h"

CMaterialManager::CMaterialManager(void)
{

}


CMaterialManager::~CMaterialManager(void)
{
	CleanUp();
}

//------------------------------------------------------------------
//
//	AddMaterial(..)
//
//	Params:
//	materialID	-	Assign ID to added material
//	material	-	Material properties to add
//
//	Adds a defined material
//
//------------------------------------------------------------------
bool CMaterialManager::AddMaterial(const std::string& materialID, const CMaterial& material)
{
	auto it = m_materialIndexMap.find(materialID);

	// If no duplicate ID
	if (it == m_materialIndexMap.end()) {
		m_materials.push_back(material);
		m_materialIndexMap.insert(std::pair<std::string, int>(materialID, (int)m_materials.size() - 1));
		return true;
	}

	return false;
}

//------------------------------------------------------------------
//
//	GetMaterial(..)
//
//	Params:
//	materialID	-	ID of material to retrieve
//
//	Gets material
//
//------------------------------------------------------------------
CMaterial* CMaterialManager::GetMaterial(const std::string& materialID)
{
	auto it = m_materialIndexMap.find(materialID);

	if (it != m_materialIndexMap.end()) {
		return &m_materials[it->second];
	}

	return nullptr;
}

//------------------------------------------------------------------
//
//	CleanUp(..)
//
//	Clean up
//
//------------------------------------------------------------------
void CMaterialManager::CleanUp()
{
	m_materials.clear();
	m_materialIndexMap.clear();
}


