//--------------------------------------------------------------------------
//
//	Material manager
//
//--------------------------------------------------------------------------
#pragma once

#include <string>
#include <map>
#include <vector>
#include "CMaterial.h"
#include "Errors.h"

class CMaterialManager
{
public:
	CMaterialManager(void);
	~CMaterialManager(void);

	ErrorId AddMaterial(const std::string& materialID, const CMaterial& material);

	CMaterial* GetMaterial(const std::string& materialID);

	void CleanUp();

protected:
	std::map<std::string, int> m_materialIndexMap;
	std::vector<CMaterial> m_materials;
};
