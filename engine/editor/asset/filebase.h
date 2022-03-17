#pragma once
#include <map>
#include <filesystem>
#include "../../engine/core/config.h"
#include "../../engine/core/asset.h"

namespace Tara {
	namespace FileSystem {
		/*
			Summary:
				The file type.
		*/
		enum class TARA_API FileType {
			None,
			Texture,
			Shader,
			Mesh,
			Material,
			Markdown,
			Prefab,
			Scene,
			World,
			PostProcessing
		};


		/*
			Summary:
				File information.
		*/
		struct TARA_API FileInfo {

		};


		/*
			Summary:
				File base class.
		*/
		class TARA_API FileBase : public AssetBase {
		public:
			// Path will default empty string.
			FileBase();
			// Register filebase with path.
			FileBase(std::filesystem::path p);
			~FileBase();
			/*
				Summary:
					Return polymorphism class type.
			*/
			static FileBase* GetFileByPath(std::filesystem::path p);

			// Return binding engine instance.
			virtual AssetBase* BindingFile() = 0;
			// The file name that will display in engine.
			virtual std::string& FileName();
			// The full path of the file.
			virtual std::string& FullPath();
			// Grid element render.
			virtual bool DrawGrid() = 0;
			// Property element render.
			virtual void DrawProp() = 0;

			// Moving file into different directory.
			bool MoveDirectory(const char* dir);
			/*
				Summary:
					Delete this file.
					This will remove the engine instance and remove object from scene.
			*/
			bool Delete();

			static AssetPool<FileBase>& GetFilePool();

		private:
			static AssetPool<FileBase>* m_filePool;
		};


		/// <summary>
		/// <para> Files database. </para>
		/// <para> Handle project file structure. </para>
		/// </summary>
		class TARA_API FileDataBase {
		public:
			static FileDataBase& Singleton();

			std::vector<std::string> GetDirectories(const char* dir);
			std::vector<FileBase*> GetFiles(const char* dir, FileType type = FileType::None);
			/*
				Summary:
					From root, get all the files from it.
			*/
			std::vector<FileBase*> GetFilesRecursive(FileType type = FileType::None);
			/*
				Summary:
					From input directory path, get all the files from it.
			*/
			std::vector<FileBase*> GetFilesRecursive(const char* dir, FileType type = FileType::None);
			std::vector<FileBase*> GetFiles(const char* dir, bool recursive = false, FileType type = FileType::None);
			FileInfo& GetFileInfo(const char* file);
			FileInfo& GetFileInfo(FileBase* file);

		private:
			FileDataBase();
			static FileDataBase* m_Singleton;

			std::map<std::string, FileBase*> storeBuffer;
		};

		inline TARA_API FileDataBase* FileDataBase::m_Singleton = new FileDataBase();
		inline TARA_API AssetPool<FileBase>* FileBase::m_filePool = new AssetPool<FileBase>();
	}
}

