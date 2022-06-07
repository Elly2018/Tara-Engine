#pragma once
// Import std library
#include <string>
#include <vector>
#include <map>
#include <filesystem>
#include <sys/stat.h>

// Import Tara engine library
#include "config.h"
#include "interface/asset.h"

/*

	Base class of asset

*/
namespace Tara {
	//
	// 
	// ! Structures and classes
	//
	// 
	class TARA_API Scene;
	class TARA_API Component; 
	class TARA_API BuildinManager;
	
	class TARA_API AssetHandle {
	public:
		AssetHandle(ZipContent* _content);
		~AssetHandle();
	private:
		ZipContent* content;
	};

	/// <summary>
	/// Abstact class for pool.
	/// </summary>
	/// <typeparam name="T">Asset type</typeparam>
	template<typename T>
	class PoolBase {
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
	/// Base class for tara object.
	/// </summary>
	class TARA_API ObjectBase {
	public:
		ObjectBase() {}
		ObjectBase(const char* name) : Name(name) {}
		ObjectBase(const char* name, const char* description) : Name(name), Description(description) {}
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

	/*
		Summary:
			Asset collection pool, easier to manage assets.
	*/
	template<typename T>
	class AssetPool final : public PoolBase<T> {
	public:
		friend class EWindow;
		AssetPool()
		{
			static_assert(std::is_base_of<AssetBase, T>::value, "AssetBase's type must be subclass of AssetBase");
			this->data = std::vector<T*>();
		}
		~AssetPool()
		{
			static_assert(std::is_base_of<AssetBase, T>::value, "AssetBase's type must be subclass of AssetBase");
			this->data = std::vector<T*>();
		}
		bool Remove(T* t) override
		{
			return Remove(t, false);
		}
		/*
			Summary:
				Remove object in the pool.
			Argument:
				force: ignore buildin boolean, just delete it.
		*/
		bool Remove(T* t, bool force = false)
		{
			if (!force) {
				if (t->BuildIn()) return false;
			}
			return std::remove_if(this->data.begin(), this->data.end(), [&](T* c)->bool {return t == c; }) != this->data.end();
		}
		/*
			Summary:
				Remove object in the pool by index
			Argument:
				force: ignore buildin boolean, just delete it.
		*/
		bool Remove(int32_t index, bool force = false)
		{
			if (index < 0 || index >= this->data.size()) {
				TARA_ERROR_LEVEL("Index out of range: from asset pool remove", 3);
				TARA_ERROR_LEVEL("\tAsset type: %s", 3, typeid(T).name());
				TARA_ERROR_LEVEL("\tQuery index: %i", 3, index);
				TARA_ERROR_LEVEL("\tPool size: %i", 3, this->data.size());
				return false;
			}
			auto i = this->data.at(index);
			if (!force) {
				if (i->BuildIn()) return false;
			}
			return Remove(i, force);
		}
		/*
			Summary:
				Get instance by index.
		*/
		T* Get(int32_t index) override
		{
			if (index < 0 || index >= this->data.size()) {
				TARA_ERROR_LEVEL("Index out of range: from asset pool get", 3);
				TARA_ERROR_LEVEL("\tAsset type: %s", 3, typeid(T).name());
				TARA_ERROR_LEVEL("\tQuery index: %i", 3, index);
				TARA_ERROR_LEVEL("\tPool size: %i", 3, this->data.size());
				return nullptr;
			}
			return this->data.at(index);
		}
		/*
			Summary:
				Find instance by name.
			Argument:
				n: Asset name.
		*/
		T* FindByName(const char* n)
		{
			typename std::vector<T*>::iterator t = std::find_if(this->data.begin(), this->data.end(), [&](T* c) { return strcmp(c->Name.c_str(), n) == 0; });
			if (t == this->data.end()) return nullptr;
			return *t;
		}
		/*
			Summary:
				Find instance by name and buildin trigger.
			Argument:
				n: Asset name.
				buildin: Is buildin
		*/
		T* FindByName(const char* n, bool buildin)
		{
			typename std::vector<T*>::iterator t = std::find_if(this->data.begin(), this->data.end(), [&](T* c) { return strcmp(c->Name.c_str(), n) == 0 && c->BuildIn() == buildin; });
			if (t == this->data.end()) return nullptr;
			return *t;
		}
		/*
			Summary:
				Find instance by file path.
			Argument:
				n: Asset file path.
		*/
		T* FindByPath(std::filesystem::path n)
		{
			typename std::vector<T*>::iterator t = std::find_if(this->data.begin(), this->data.end(), [&](T* c) { return c->Path == n; });
			if (t == this->data.end()) return nullptr;
			return *t;
		}
		/*
			Summary:
				return multiple instances with same name from pool.
			Argument:
				n: Asset name.
		*/
		const std::vector<T*> FindByNameMultiple(const char* n)
		{
			std::vector<T*> buffer = std::vector<T*>();
			for (auto i : this->data) {
				if (i->Name == i->Name) {
					buffer.push_back(i);
				}
			}
			return buffer;
		}
		/*
			Summary:
				return multiple instances with same name and specified buildin from pool.
			Argument:
				n: Asset name.
				buildin: Is buildin
		*/
		const std::vector<T*> FindByNameMultiple(const char* n, bool buildin)
		{
			std::vector<T*> buffer = std::vector<T*>();
			for (auto i : this->data) {
				if (i->Name == i->Name && i->BuildIn() == buildin) {
					buffer.push_back(i);
				}
			}
			return buffer;
		}
	};


	template<typename T>
	class TARA_API SystemPool final : public PoolBase<T>{
	public:
		SystemPool() {
			static_assert(std::is_base_of<Component, T>::value, "AssetBase's type must be subclass of AssetBase");
			this->data = std::vector<T*>();
		}
		~SystemPool() {
			static_assert(std::is_base_of<Component, T>::value, "AssetBase's type must be subclass of AssetBase");
			this->data = std::vector<T*>();
		}
	};

	/// <summary>
		/// <para> Package database. </para>
		/// <para> Handle all package loaded in engine. </para>
		/// </summary>
	class TARA_API PackageManager final : public IPackage {
	public:
		static PackageManager& Singleton();
		bool AddPackage(std::string name, IPackage* pack, bool replace = false);
		bool RemovePackage(std::string name);
		bool PackageExist(std::string name);
		IPackage* GetPackage(std::string name);

		bool FileExist(std::string filename) override;
		bool DirectroyExist(std::string dir) override;
		std::vector<std::string> GetDirectories(std::string dir) override;
		std::vector<std::string> GetFiles(std::string dir) override;
		std::vector<char> GetFileData_Char(std::string filename) override;
		std::vector<uint8_t> GetFileData_UChar(std::string filename) override;
		std::string GetFileData_String(std::string filename) override;
		void* GetFileData_Void(std::string filename) override;
		size_t GetFileData_Size(std::string filename) override;
		Mesh* GetMesh(std::string filename) override;
		Texture2D* GetTexture(std::string filename) override;
		bool CheckDataIsLoaded(std::string filename) override;
		void LoadData(std::string filename) override;

		BuildinManager* buildin;
	protected:
		PackageManager();
		~PackageManager();

	private:
		static PackageManager* m_Singleton;
		std::map<std::string, IPackage*> packages;
		/// <summary>
		/// Return pair of path <package name, package path>.
		/// </summary>
		/// <param name="path">Fullpath</param>
		std::pair<std::string, std::string> GetPathStructure(std::string path);
	};
}
