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

	const char* ObjectBase::Name()
	{
		return m_name.c_str();
	}
	void ObjectBase::SetName(const char* n)
	{
		m_name = n;
	}
	const char* ObjectBase::Description()
	{
		return m_description.c_str();
	}
	void ObjectBase::SetDescription(const char* n)
	{
		m_description = n;
	}

	AssetBase::AssetBase()
	{
	}
	AssetBase::AssetBase(const char* name)
	{
		m_name = name;
	}
	AssetBase::~AssetBase()
	{

	}
	bool AssetBase::IsBuildIn()
	{
		return m_buildIn;
	}
}