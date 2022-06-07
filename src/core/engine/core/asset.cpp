#include "asset.h"
#include "utility.h"
#include "mesh/mesh.h"
#include "texture/texture.h"
#include "buildin/buildin_manager.h"

namespace Tara {
	PackageManager* PackageManager::m_Singleton = nullptr;

	AssetHandle::AssetHandle(ZipContent* _content)
	{
		content = _content;
	}
	AssetHandle::~AssetHandle()
	{
		free(content->data);
		content->size = 0;
	}

	PackageManager& PackageManager::Singleton()
	{
		if (m_Singleton == nullptr) m_Singleton = new PackageManager();
		return *m_Singleton;
	}
	bool PackageManager::AddPackage(std::string name, IPackage* pack, bool replace)
	{
		if (replace) {
			TARA_DEBUG_LEVEL("Add package: %s", 4, name.c_str());
			packages[name] = pack;
			return true;
		}
		else {
			if (packages.count(name)) {
				TARA_ERROR_LEVEL("Package already exist: %s, set the parameter replace to true, if you want to replace it.", 4, name.c_str());
				return false;
			}
			else {
				TARA_DEBUG_LEVEL("Add package: %s", 4, name.c_str());
				packages[name] = pack;
				return true;
			}
		}
	}
	bool PackageManager::RemovePackage(std::string name)
	{
		if (packages.count(name)) {
			packages.erase(packages.find(name));
		}
		return true;
	}
	bool PackageManager::PackageExist(std::string name)
	{
		bool b = packages.count(name);
		if (!b) {
			TARA_WARNING_LEVEL("Package does not exist: %s", 4, name.c_str());
		}
		return b;
	}
	IPackage* PackageManager::GetPackage(std::string name)
	{
		if (!PackageExist(name)) return nullptr;
			return packages.at(name);
	}
	bool PackageManager::FileExist(std::string filename)
	{
		std::pair<std::string, std::string> rpath = GetPathStructure(filename);
		if (!PackageExist(rpath.first)) return false;
		IPackage* package_target = GetPackage(rpath.first);
		return package_target->FileExist(rpath.second);
	}
	bool PackageManager::DirectroyExist(std::string dir)
	{
		std::pair<std::string, std::string> rpath = GetPathStructure(dir);
		if (!PackageExist(rpath.first)) return false;
		IPackage* package_target = GetPackage(rpath.first);
		return package_target->DirectroyExist(rpath.second);
	}
	std::vector<std::string> PackageManager::GetDirectories(std::string dir)
	{
		std::pair<std::string, std::string> rpath = GetPathStructure(dir);
		if (!PackageExist(rpath.first)) return std::vector<std::string>();
		return std::vector<std::string>();
	}
	std::vector<std::string> PackageManager::GetFiles(std::string dir)
	{
		std::pair<std::string, std::string> rpath = GetPathStructure(dir);
		if (!PackageExist(rpath.first)) return std::vector<std::string>();
		return std::vector<std::string>();
	}
	std::vector<char> PackageManager::GetFileData_Char(std::string filename)
	{
		std::pair<std::string, std::string> rpath = GetPathStructure(filename);
		if (!PackageExist(rpath.first)) return std::vector<char>();
		IPackage* package_target = GetPackage(rpath.first);
		return package_target->GetFileData_Char(rpath.second);
	}
	std::vector<uint8_t> PackageManager::GetFileData_UChar(std::string filename)
	{
		std::pair<std::string, std::string> rpath = GetPathStructure(filename);
		if (!PackageExist(rpath.first)) return std::vector<uint8_t>();
		IPackage* package_target = GetPackage(rpath.first);
		return package_target->GetFileData_UChar(rpath.second);
	}
	std::string PackageManager::GetFileData_String(std::string filename)
	{
		std::pair<std::string, std::string> rpath = GetPathStructure(filename);
		if (!PackageExist(rpath.first)) return std::string();
		IPackage* package_target = GetPackage(rpath.first);
		return package_target->GetFileData_String(rpath.second);
	}
	void* PackageManager::GetFileData_Void(std::string filename)
	{
		std::pair<std::string, std::string> rpath = GetPathStructure(filename);
		if (!PackageExist(rpath.first)) return nullptr;
		IPackage* package_target = GetPackage(rpath.first);
		return package_target->GetFileData_Void(rpath.second);
	}
	size_t PackageManager::GetFileData_Size(std::string filename)
	{
		std::pair<std::string, std::string> rpath = GetPathStructure(filename);
		if (!PackageExist(rpath.first)) return 0;
		IPackage* package_target = GetPackage(rpath.first);
		return package_target->GetFileData_Size(rpath.second);
	}
	Mesh* PackageManager::GetMesh(std::string filename)
	{
		std::pair<std::string, std::string> rpath = GetPathStructure(filename);
		if (!PackageExist(rpath.first)) return nullptr;
		auto& meshpool = Mesh::GetAssetPool();
		Mesh* m = meshpool.FindByPath(filename);
		if (m) return m;
		IPackage* package_target = GetPackage(rpath.first);
		if (!package_target->FileExist(rpath.second)) return nullptr;
		const void* data = package_target->GetFileData_Void(rpath.second);
		size_t size = package_target->GetFileData_Size(rpath.second);
		m = Mesh::ImportFromMemory(data, size);
		m->Path = filename;
		m->Name = std::filesystem::path(filename).filename().string();
		return m;
	}
	Texture2D* PackageManager::GetTexture(std::string filename)
	{
		std::pair<std::string, std::string> rpath = GetPathStructure(filename);
		if (!PackageExist(rpath.first)) return nullptr;
		auto& texpool = Texture::GetAssetPool();
		Texture* m = texpool.FindByPath(filename);
		if (m) return dynamic_cast<Texture2D*>(m);
		IPackage* package_target = GetPackage(rpath.first);
		if (!package_target->FileExist(rpath.second)) return nullptr;
		const void* data = package_target->GetFileData_Void(rpath.second);
		size_t size = package_target->GetFileData_Size(rpath.second);
		m = Texture2D::ImportFromMemory(data, size);
		m->Path = filename;
		m->Name = std::filesystem::path(filename).filename().string();
		return dynamic_cast<Texture2D*>(m);
	}
	bool PackageManager::CheckDataIsLoaded(std::string filename) {
		std::pair<std::string, std::string> rpath = GetPathStructure(filename);
		if (!PackageExist(rpath.first)) return 0;
		IPackage* package_target = GetPackage(rpath.first);
		return package_target->CheckDataIsLoaded(rpath.second);
	}
	void PackageManager::LoadData(std::string filename) {
		std::pair<std::string, std::string> rpath = GetPathStructure(filename);
		if (!PackageExist(rpath.first)) return;
		IPackage* package_target = GetPackage(rpath.first);
		return package_target->LoadData(rpath.second);
	}
	PackageManager::PackageManager()
	{
		packages = std::map<std::string, IPackage*>();
		buildin = new BuildinManager("engine.resource");
		packages["buildin"] = buildin;
	}
	PackageManager::~PackageManager()
	{
	}
	std::pair<std::string, std::string> PackageManager::GetPathStructure(std::string path)
	{
		std::string& rpath = Utility::String::Replace(path, "\\", "/");
		std::vector<std::string> splitstring = Utility::String::Split(rpath, "/");
		if (splitstring.size() == 0) return std::pair<std::string, std::string>();
		else if (splitstring.size() == 1) return std::pair<std::string, std::string>(path, "");
		std::string packagename = splitstring[0];
		splitstring.erase(splitstring.begin());
		std::string packagepath = Utility::String::Join(splitstring, "/");
		return std::pair<std::string, std::string>(packagename, packagepath);
	}
}