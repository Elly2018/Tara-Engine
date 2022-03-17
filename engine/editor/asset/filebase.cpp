#include "filebase.h"
#include <map>
#include <fstream>
#include <nlohmann/json.hpp>
#include "../../engine/core/utility.h"
#include "../../engine/core/texture/texture.h"
#include "regular_file.h"
#include "special_file.h"

namespace Tara {
	namespace FileSystem {
		const std::vector<std::string> textureExtension = {
			".jpg",
			".png",
		};
		const std::vector<std::string> shaderExtension = {
			".vert",
			".frag",
			".glsl",
		};
		const std::vector<std::string> meshExtension = {
			".obj",
			".fbx",
		};
		const std::vector<std::string> materialExtension = {
			".mat",
			".material",
		};
		const std::vector<std::string> markdownExtension = {
			".md",
			".markdown",
		};
		const std::vector<std::string> prefabExtension = {
			".pb",
			".prefab",
		};
		const std::vector<std::string> sceneExtension = {
			".tara",
			".scene",
		};
		const std::map<FileType, const std::vector<std::string>> fileExtensions = {
			{FileType::Texture, textureExtension},
			{FileType::Shader, shaderExtension},
			{FileType::Mesh, meshExtension},
			{FileType::Material, materialExtension},
			{FileType::Markdown, markdownExtension},
			{FileType::Prefab, prefabExtension},
			{FileType::Scene, sceneExtension},
		};

		FileBase::FileBase()
		{
			GetFilePool().Add(this);
		}
		FileBase::FileBase(std::filesystem::path p) : FileBase()
		{
			Path = p;
		}
		FileBase::~FileBase()
		{
		}
		FileBase* FileBase::GetFileByPath(std::filesystem::path p)
		{
			using namespace nlohmann;
			const std::string ext = p.extension().string();
			for (auto typepair : fileExtensions) {
				for (auto exts : typepair.second) {
					if (Utility::String::ToLowercase(exts) == Utility::String::ToLowercase(ext)) {
						// match
						switch (typepair.first)
						{
						case FileType::Texture:
						{
							Texture* tex = Texture::GetAssetPool().FindByPath(p);
							if (tex) {
								// Load already
								Texture2D* tex2D = dynamic_cast<Texture2D*>(tex);
								if (tex2D) {
									TARA_DEBUG("Cast tex");
									return new TextureFile(tex2D, p);
								}
							}
							else {
								// Not load yet
							}
							break;
						}
						case FileType::Shader:
							break;
						case FileType::Mesh:
							break;
						case FileType::Material:
						{
							TARA_DEBUG("Read mat !");
							std::ifstream st(p.relative_path().string().c_str());
							json jsonRoot;
							st >> jsonRoot;
							break;
							if (jsonRoot.contains("Test")) {
								json test = jsonRoot.find("Test").value();
								if (test.is_number_integer()) {
									test.get<int32_t>();
								}
							}
							st.close();
							break;
						}
						case FileType::Markdown:
							break;
						case FileType::Prefab:
							break;
						case FileType::Scene:
							break;
						}
					}
				}
			}
			TARA_DEBUG("Cast Reg");
			return new RegularFile(p);
		}
		std::string& FileBase::FileName()
		{
			return Path.filename().string();
		}
		std::string& FileBase::FullPath()
		{
			return Path.string();
		}
		bool FileBase::MoveDirectory(const char* dir)
		{
			AssetBase* target = BindingFile();
			if (target != nullptr) {
				target->Path = dir;
			}
			return true;
		}
		bool FileBase::Delete()
		{
			AssetBase* target = BindingFile();
			if (target != nullptr) {
				delete target;
			}
			return true;
		}
		AssetPool<FileBase>& FileBase::GetFilePool()
		{
			return *m_filePool;
		}
		FileDataBase& FileDataBase::Singleton()
		{
			return *m_Singleton;
		}
		std::vector<std::string> FileDataBase::GetDirectories(const char* dir)
		{
			std::vector<std::string> result = std::vector<std::string>();
			for (auto& dire : std::filesystem::directory_iterator(dir)) {
				if (dire.is_directory())
					result.push_back(dire.path().relative_path().string().c_str());
			}
			return result;
		}
		std::vector<FileBase*> FileDataBase::GetFiles(const char* dir, FileType type)
		{
			std::vector<FileBase*> result = std::vector<FileBase*>();
			std::vector<std::string> exts = std::vector<std::string>();
			if (fileExtensions.count(type)) exts = fileExtensions.at(type);

			for (auto& dire : std::filesystem::directory_iterator(dir)) {
				if (dire.is_regular_file()) {
					bool match = false;

					if (type == FileType::None) {
						result.push_back(FileBase::GetFileByPath(dire.path()));
						continue;
					}

					for (auto& ext : exts) {
						if (Utility::String::ToLowercase(dire.path().extension().string()) == Utility::String::ToLowercase(ext)) {
							match = true;
							break;
						}
					}
					if (match)
						result.push_back(FileBase::GetFileByPath(dire.path()));
				}
			}

			return result;
		}
		std::vector<FileBase*> FileDataBase::GetFilesRecursive(FileType type)
		{
			return GetFilesRecursive("", type);
		}
		std::vector<FileBase*> FileDataBase::GetFilesRecursive(const char* dir, FileType type)
		{
			std::vector<FileBase*> result = std::vector<FileBase*>();
			std::vector<std::string> exts = std::vector<std::string>();
			if (fileExtensions.count(type)) exts = fileExtensions.at(type);

			for (auto& dire : std::filesystem::recursive_directory_iterator(dir)) {
				if (dire.is_regular_file()) {
					bool match = false;

					if (type == FileType::None) {
						result.push_back(FileBase::GetFileByPath(dire.path()));
						continue;
					}

					for (auto& ext : exts) {
						if (Utility::String::ToLowercase(dire.path().extension().string()) == Utility::String::ToLowercase(ext)) {
							match = true;
							break;
						}
					}
					if (match)
						result.push_back(FileBase::GetFileByPath(dire.path()));
				}
			}

			return result;
		}
		std::vector<FileBase*> FileDataBase::GetFiles(const char* dir, bool recursive, FileType type)
		{
			return recursive ? GetFilesRecursive(dir, type) : GetFiles(dir, type);
		}
		FileInfo& FileDataBase::GetFileInfo(const char* file)
		{
			return FileInfo();
		}
		FileInfo& FileDataBase::GetFileInfo(FileBase* file)
		{
			return GetFileInfo(file->FullPath().c_str());
		}
		FileDataBase::FileDataBase() {
			storeBuffer = std::map<std::string, FileBase*>();
		}
	}
}