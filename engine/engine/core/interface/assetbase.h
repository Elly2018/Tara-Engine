#pragma once
// Import std library
#include <map>
#include <filesystem>

// Import Tara engine library
#include "../config.h"

namespace Tara {
	class TARA_API Mesh;
	class TARA_API Texture2D;


	/// <summary>
	/// Base class for tara object.
	/// </summary>
	class TARA_API ObjectBase {
	public:
		ObjectBase() {}
		ObjectBase(const char* name) : Name(name) {}
		ObjectBase(const char* name, const char* description) : Name(name), Description(description){}
		virtual ~ObjectBase() {}

		// Object name.
		std::string Name = "Default Asset";
		// Object description.
		std::string Description = "Default Description";
	};


	/// <summary>
	/// Base class for asset.
	/// </summary>
	class TARA_API AssetBase : public ObjectBase
	{
	public:
		AssetBase() {}
		AssetBase(const char* name, bool buildin = false) : ObjectBase(name), m_buildIn(buildin) {}
		AssetBase(const char* name, const char* description, bool buildin = false) : ObjectBase(name, description), m_buildIn(buildin) {}
		virtual ~AssetBase() {}
		/*
			Summary:
				Check if shader is build-in.
		*/
		bool BuildIn() { return m_buildIn; }

		// The meta data of this asset
		std::string Meta = "";
		std::filesystem::path Path = "";

	protected:
		// Is asset buildin.
		bool m_buildIn = false;
	};


	/// <summary>
	/// Abstact class for pool.
	/// </summary>
	/// <typeparam name="T">Asset type</typeparam>
	template<typename T>
	class TARA_API PoolBase {
	public:
		virtual bool IsIn(T* t)
		{
			typename std::vector<T*>::iterator k = std::find_if(this->data.begin(), this->data.end(), [&](T* c) { return c == t; });
			return k != this->data.end();
		}
		virtual bool Add(T* t)
		{
			if (IsIn(t)) {
				TARA_ERROR_LEVEL("Pass already exists instance to the pool: %s", 3);
				return false;
			}
			this->data.push_back(t);
			return true;
		}
		virtual bool Remove(T* t) {
			return std::remove_if(this->data.begin(), this->data.end(), [&](T* c)->bool {return t == c; }) != this->data.end();
		}
		virtual bool DeleteAll()
		{
			for (auto i : this->data) {
				if (i) delete i;
			}
			return true;
		}
		virtual T* Get(int32_t index) {
			return this->data.at(index);
		}
		virtual void Clean()
		{
			this->data.clear();
		}
		virtual void CleanNull()
		{
			this->data.erase(std::remove_if(this->data.begin(), this->data.end(), [&](T* c) -> bool { return c == nullptr; }), this->data.end());
		}
		virtual size_t Size()
		{
			return this->data.size();
		}
	protected:
		// All the asset in the pool
		std::vector<T*> data;
	};


	/// <summary>
	/// Package resources query interface
	/// </summary>
	class TARA_API PackageBase {
	public:
		/// <summary>
		/// Check file path is exist.
		/// </summary>
		/// <param name="filename">path</param>
		virtual bool FileExist(std::string filename) = 0;
		/// <summary>
		/// Check dir path is exist.
		/// </summary>
		/// <param name="dir">path</param>
		virtual bool DirectroyExist(std::string dir) = 0;
		virtual std::vector<std::string> GetDirectories(std::string dir) = 0;
		virtual std::vector<std::string> GetFiles(std::string dir) = 0;
		virtual std::vector<char> GetFileData_Char(std::string filename) = 0;
		virtual std::vector<uint8_t> GetFileData_UChar(std::string filename) = 0;
		virtual std::string GetFileData_String(std::string filename) = 0;
		virtual void* GetFileData_Void(std::string filename) = 0;
		virtual size_t GetFileData_Size(std::string filename) = 0;
		/// <summary>
		/// Get the mesh data from package.
		/// </summary>
		/// <param name="path">path</param>
		/// <returns>Null if not found</returns>
		virtual Mesh* GetMesh(std::string path) = 0;
		/// <summary>
		/// Get the texture data from package.
		/// </summary>
		/// <param name="path">path</param>
		/// <returns>Null if not found</returns>
		virtual Texture2D* GetTexture(std::string path) = 0;
	};
}