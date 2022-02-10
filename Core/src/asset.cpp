#include "asset.h"

namespace Tara {
	ObjectBase::ObjectBase()
	{
	}
	ObjectBase::ObjectBase(const char* name)
	{
		m_name = name;
	}
	ObjectBase::~ObjectBase()
	{
	}

	std::string& ObjectBase::Name()
	{
		return m_name;
	}
	std::string& ObjectBase::Description()
	{
		return m_description;
	}

	AssetBase::AssetBase(const char* name)
	{
		m_name = name;
	}
	AssetBase::AssetBase(const char* name, const char* path) : AssetBase(name)
	{
		m_path = path;
	}
	AssetBase::~AssetBase()
	{

	}
	bool& AssetBase::BuildIn()
	{
		return m_buildIn;
	}
	std::string& AssetBase::Path()
	{
		return m_path;
	}
	std::string& AssetBase::Meta()
	{
		return m_meta;
	}
}