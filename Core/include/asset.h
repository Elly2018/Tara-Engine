#pragma once
#include <string>
#include <vector>
#include <config.h>
#include <utility.h>

namespace Tara {
	class DllExport ObjectBase;
	class DllExport AssetBase;
	template<typename T> class DllExport AssetPool;


	class ObjectBase {
	public:
		ObjectBase();
		ObjectBase(const char* name);
		~ObjectBase();

		const char* Name();
		void SetName(const char* n);
		const char* Description();
		void SetDescription(const char* n);

	protected:
		std::string m_name = "Default Asset";
		std::string m_description = "";
	};

	/*
		Summary:
			Asset base class.
			Contain basic functionality
	*/
	class AssetBase : public ObjectBase
	{
	public:
		AssetBase();
		AssetBase(const char* name);
		~AssetBase();
		/*
			Summary:
				Check if shader is build-in.
		*/
		bool IsBuildIn();
		
	protected:
		bool m_buildIn = false;
	};

	/*
		Summary:
			Asset collection pool, easier to manage assets.
	*/
	template<typename T>
	class AssetPool {
	public:
		AssetPool();
		~AssetPool();

		void Add(T* t);
		void Remove(T* t, bool force = false);
		void Remove(int32_t index, bool force = false);
		void DeleteAll();
		bool IsIn(T* t);
		T* Get(int32_t index);
		T* Find(const char* n);
		T* Find(const char* n, bool buildin);
		std::vector<T*> FindMultiple(const char* n);
		std::vector<T*> FindMultiple(const char* n, bool buildin);
		void Clean();
		void CleanNull();
		size_t Size();
	private:
		std::vector<T*> data;
	};

	template<typename T>
	inline AssetPool<T>::AssetPool()
	{
		static_assert(std::is_base_of<AssetBase, T>::value, "AssetBase's type must be subclass of AssetBase");
		data = std::vector<T*>();
	}
	template<typename T>
	inline AssetPool<T>::~AssetPool()
	{
		Clean();
	}
	template<typename T>
	inline void AssetPool<T>::Add(T* t)
	{
		data.push_back(t);
	}
	template<typename T>
	inline void AssetPool<T>::Remove(T* t, bool force)
	{
		if (!force) {
			if (t->IsBuildIn()) return;
		}
		std::remove(data.begin(), data.end(), t);
	}
	template<typename T>
	inline void AssetPool<T>::DeleteAll()
	{
		for (auto i : data) {
			delete i;
		}
	}
	template<typename T>
	inline void AssetPool<T>::Remove(int32_t index, bool force)
	{
		auto i = data.at(index);
		if (!force) {
			if (i->IsBuildIn()) return;
		}
		Remove(i, force);
	}
	template<typename T>
	inline bool AssetPool<T>::IsIn(T* t)
	{
		typename std::vector<T*>::iterator k = std::find_if(data.begin(), data.end(), [&](T* c) { return c == t; });
		return k != data.end();
	}
	template<typename T>
	inline T* AssetPool<T>::Get(int32_t index)
	{
		return data.at(index);
	}
	template<typename T>
	inline T* AssetPool<T>::Find(const char* n)
	{
		typename std::vector<T*>::iterator t = std::find_if(data.begin(), data.end(), [&](T* c) { return strcmp(c->Name(), n) == 0; });
		if (t == data.end()) return nullptr;
		return *t;
	}
	template<typename T>
	inline T* AssetPool<T>::Find(const char* n, bool buildin)
	{
		typename std::vector<T*>::iterator t = std::find_if(data.begin(), data.end(), [&](T* c) { return strcmp(c->Name(), n) == 0 && c->IsBuildIn() == buildin; });
		if (t == data.end()) return nullptr;
		return *t;
	}
	template<typename T>
	inline std::vector<T*> AssetPool<T>::FindMultiple(const char* n)
	{
		std::vector<T*> buffer = std::vector<T*>();
		for (auto i : data) {
			if (i->Name() == i->Name()) {
				buffer.push_back(i);
			}
		}
		return buffer;
	}
	template<typename T>
	inline std::vector<T*> AssetPool<T>::FindMultiple(const char* n, bool buildin)
	{
		std::vector<T*> buffer = std::vector<T*>();
		for (auto i : data) {
			if (i->Name() == i->Name() && i->IsBuildIn() == buildin) {
				buffer.push_back(i);
			}
		}
		return buffer;
	}
	template<typename T>
	inline void AssetPool<T>::Clean()
	{
		data.clear();
	}
	template<typename T>
	inline void AssetPool<T>::CleanNull()
	{
		data.erase(std::remove(data.begin(), data.end(), nullptr), data.end());
	}
	template<typename T>
	inline size_t AssetPool<T>::Size()
	{
		return data.size();
	}
}
