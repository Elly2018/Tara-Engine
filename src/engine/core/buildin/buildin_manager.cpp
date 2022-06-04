#include "buildin_manager.h"
#include <map>
#include "../mesh/mesh.h"
#include "../texture/texture.h"
#include "../shader/shader.h"

namespace Tara {
	BuildinManager* BuildinManager::m_Singleton = nullptr;
	BuildinManager& BuildinManager::Singleton()
	{
		if (m_Singleton == nullptr) m_Singleton = new BuildinManager();
		return *m_Singleton;
	}
	void BuildinManager::AssignResource(const char* filename)
	{
		OpenZipFile(filename);
	}

	std::pair<void*, size_t> BuildinManager::GetPrimitiveFontMemory(std::string path)
	{
		std::string n = Utility::String::FormatString("fonts/%s", path.c_str());
		if (!FileExist(n)) return std::pair<void*, size_t>();
		return std::pair<void*, size_t>(GetFileData_Void(n.c_str()), GetFileData_Size(n.c_str()));
	}

	Shader* BuildinManager::PackagingShader(std::string name) {
		auto& splitename = Utility::String::Split(name, "/");
		splitename.erase(splitename.end() - 1);
		std::string dir = splitename.size() > 0 ? Utility::String::FormatString("shader/%s", name.c_str()) : "shader";
		Shader* shader = new Shader(true);
		size_t c = 0;
		for (std::pair<ShaderType, std::string> i : shaderTypeExtension) {
			std::string fullpath = Utility::String::FormatString("%s/%s%s", dir.c_str(), name.c_str(), i.second.c_str());
			if (!FileExist(fullpath)) continue;
			std::string code = GetFileData_String(fullpath.c_str());
			shader->SetShaderFromCode(i.first, code.c_str());
			c++;
		}
		if (c == 0) {
			delete shader;
			return nullptr;
		}
		shader->Name = name;
		shader->Path = Utility::String::FormatString("buildin/shader/%s", name.c_str());
		shader->CompileGLSL();
		return shader;
	}

	std::string BuildinManager::GetShaderString(std::string name, ShaderType type)
	{
		std::string n = Utility::String::FormatString("shader/%s%s", name.c_str(), shaderTypeExtension.at(type).c_str());
		TARA_DEBUG("%s", n.c_str());
		if (!FileExist(n)) return std::string();
		std::string d = GetFileData_String(n.c_str());
		return d;
	}

	Mesh* BuildinManager::GetPrimitiveMesh(std::string name)
	{
		PackageManager& pm = PackageManager::Singleton();
		std::string n = Utility::String::FormatString("buildin/mesh/%s", name.c_str());
		return pm.GetMesh(n);
	}

	Texture2D* BuildinManager::GetPrimitiveTexture(std::string name)
	{
		PackageManager& pm = PackageManager::Singleton();
		std::string n = Utility::String::FormatString("buildin/image/%s", name.c_str());
		return pm.GetTexture(n);
	}

	Texture2D* BuildinManager::GetPrimitiveIcon(std::string name)
	{
		PackageManager& pm = PackageManager::Singleton();
		std::string n = Utility::String::FormatString("buildin/icon/%s", name.c_str());
		return pm.GetTexture(n);
	}

	BuildinManager::BuildinManager() : Utility::Zip() {
		AssignResource("engine.resource");
		std::string jstring = GetFileData_String("Manifest.json");
		Manifest = Utility::Json::ReadJsonString(jstring.c_str());
		if (Manifest.is_null()) {
			TARA_WARNING_LEVEL("Cannot found Manifest.json file", 3);
			return;
		}
		nlohmann::json& shaderConfig = Manifest["shaderConfig"];
		nlohmann::json& fontConfig = Manifest["fontConfig"];
		nlohmann::json& version = Manifest["version"];
		if (shaderConfig.is_null()) {
			Utility::Debug::PrintTrace();
			TARA_RUNTIME_ERROR("Buildin package does not contain shaderConfig property.\nThis is not allow since basic shader need to configure in order to let engine run");
		}
		if (fontConfig.is_null()) {
			Utility::Debug::PrintTrace();
			TARA_WARNING_LEVEL("Buildin package does not contain fontConfig property.\nDefault engine will load default font for everything.", 4);
		}
		if (version.is_string()) {
			TARA_DEBUG("Load buildin package version: %s", Manifest["version"].get<std::string>().c_str());
		}
		else {
			TARA_WARNING_LEVEL("Cannot find version in manifest json file in buildin package", 3);
		}
		PackageManager& pm = PackageManager::Singleton();
		pm.AddPackage("buildin", this);
	}
	BuildinManager::~BuildinManager() {
		
	}
}