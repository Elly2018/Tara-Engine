#pragma once
// Import std library
#include <string>
#include <vector>
// Import Tara engine library
#include <config.h>
#include <utility.h>

/*

	Base class of asset

*/
namespace Tara {
	/*
		Summary:
			Each tara object as basic description.
	*/
	class DllExport ObjectBase {
	public:
		ObjectBase();
		ObjectBase(const char* name);
		~ObjectBase();

		/*
			Summary:
				The property of name.
		*/
		std::string& Name();
		/*
			Summary:
				The property of description.
		*/
		std::string& Description();

	protected:
		// Object name.
		std::string m_name = "Default Asset";
		// Object description.
		std::string m_description = "Default Description";
	};


	/*
		Summary:
			Asset base class.
			Contain basic functionality
	*/
	class DllExport AssetBase : public ObjectBase
	{
	public:
		AssetBase() {}
		AssetBase(const char* name);
		AssetBase(const char* name, const char* path);
		~AssetBase();
		/*
			Summary:
				Check if shader is build-in.
		*/
		bool& BuildIn();
		/*
			Summary:
				Asset file path, application will ignore path if buildin is true.
		*/
		std::string& Path();
		/*
			Summary:
				Extra meta information about this meta.
		*/
		std::string& Meta();
		
	protected:
		// Is asset buildin.
		bool m_buildIn = false;
		// The relative path to the file, ignore if buildin is true.
		std::string m_path = "";
		// The meta data of this asset
		std::string m_meta = "";
	};


	/*
		Summary:
			Asset collection pool, easier to manage assets.
	*/
	template<typename T>
	class DllExport AssetPool final {
	public:
		AssetPool()
		{
			static_assert(std::is_base_of<AssetBase, T>::value, "AssetBase's type must be subclass of AssetBase");
			data = std::vector<T*>();
		}
		~AssetPool()
		{
			static_assert(std::is_base_of<AssetBase, T>::value, "AssetBase's type must be subclass of AssetBase");
			data = std::vector<T*>();
		}

		/*
			Summary:
				Check instance is in the pool.
		*/
		bool IsIn(T* t)
		{
			typename std::vector<T*>::iterator k = std::find_if(data.begin(), data.end(), [&](T* c) { return c == t; });
			return k != data.end();
		}
		/*
			Summary:
				Adding object into the pool.
		*/
		bool Add(T& t)
		{
			if (IsIn(&t)) {
				TARA_ERROR_LEVEL("Pass already exists instance to the pool", 3);
				TARA_ERROR_LEVEL("\tAsset name: %s", 3, t.Name().c_str());
				return false;
			}
			data.push_back(&t);
			return true;
		}
		/*
			Summary:
				Remove object in the pool.
			Argument:
				force: ignore buildin boolean, just delete it.
		*/
		bool Remove(T& t, bool force = false)
		{
			if (!force) {
				if (t.BuildIn()) return false;
			}
			return std::remove(data.begin(), data.end(), &t) != data.end();
		}
		/*
			Summary:
				Remove object in the pool by index
			Argument:
				force: ignore buildin boolean, just delete it.
		*/
		bool Remove(int32_t index, bool force = false)
		{
			if (index < 0 || index >= data.size()) {
				TARA_ERROR_LEVEL("Index out of range: from asset pool remove", 3);
				TARA_ERROR_LEVEL("\tAsset type: %s", 3, typeid(T).name());
				TARA_ERROR_LEVEL("\tQuery index: %i", 3, index);
				TARA_ERROR_LEVEL("\tPool size: %i", 3, data.size());
				return false;
			}
			auto i = data.at(index);
			if (!force) {
				if (i->BuildIn()) return false;
			}
			return Remove(*i, force);
		}
		/*
			Summary:
				Delete all content. This won't clean the pool.
				Prevent pool fullfilled with nullptr, Please call 'Clean()' after delete all content.
		*/
		void DeleteAll()
		{
			for (auto i : data) {
				if(i) delete i;
			}
		}
		/*
			Summary:
				Get instance by index.
		*/
		T* Get(int32_t index)
		{
			if (index < 0 || index >= data.size()) {
				TARA_ERROR_LEVEL("Index out of range: from asset pool get", 3);
				TARA_ERROR_LEVEL("\tAsset type: %s", 3, typeid(T).name());
				TARA_ERROR_LEVEL("\tQuery index: %i", 3, index);
				TARA_ERROR_LEVEL("\tPool size: %i", 3, data.size());
				return nullptr;
			}
			return data.at(index);
		}
		/*
			Summary:
				Find instance by name.
			Argument:
				n: Asset name.
		*/
		T* FindByName(const char* n)
		{
			typename std::vector<T*>::iterator t = std::find_if(data.begin(), data.end(), [&](T* c) { return strcmp(c->Name().c_str(), n) == 0; });
			if (t == data.end()) return nullptr;
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
			typename std::vector<T*>::iterator t = std::find_if(data.begin(), data.end(), [&](T* c) { return strcmp(c->Name().c_str(), n) == 0 && c->BuildIn() == buildin; });
			if (t == data.end()) return nullptr;
			return *t;
		}
		/*
			Summary:
				Find instance by file path.
			Argument:
				n: Asset file path.
		*/
		T* FindByPath(const char* n)
		{
			typename std::vector<T*>::iterator t = std::find_if(data.begin(), data.end(), [&](T* c) { return strcmp(c->Path().c_str(), n) == 0; });
			if (t == data.end()) return nullptr;
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
			for (auto i : data) {
				if (i->Name() == i->Name()) {
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
			for (auto i : data) {
				if (i->Name() == i->Name() && i->BuildIn() == buildin) {
					buffer.push_back(i);
				}
			}
			return buffer;
		}
		/*
			Summary:
				Clean the pool. This action won't delete the contents.
				Before clean the pool, Please call 'DeleteAll()' to delete all the content.
		*/
		void Clean()
		{
			data.clear();
		}
		/*
			Summary:
				Clean the nullptr in the pool.
		*/
		void CleanNull()
		{
			data.erase(std::remove(data.begin(), data.end(), nullptr), data.end());
		}
		/*
			Summary:
				Check the size of the pool.
		*/
		size_t Size()
		{
			return data.size();
		}
	private:
		// All the asset in the pool
		std::vector<T*> data;
	};
}
