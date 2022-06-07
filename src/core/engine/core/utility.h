#pragma once
// Include std library
#include <string>
#include <filesystem>
#include <nlohmann/json.hpp>
#include <uuid4.h>

// Include tara library
#include "config.h"
#include "interface/asset.h"
#include "shader/shader.h"

namespace Tara {
	const std::map<ShaderType, std::string> shaderTypeExtension = {
		{ShaderType::Vertex, ".vert"},
		{ShaderType::Tessellation, ".tess"},
		{ShaderType::Fragment, ".frag"},
		{ShaderType::Geometry, ".geom"},
		{ShaderType::Compute, ".comp"},
		{ShaderType::Commom, ".glsl"},
	};

	struct TARA_API ZipContent {
	public:
		ZipContent(void* _data, size_t _size) : data(_data), size(_size) {
			uuid4_generate(uuid);
		}
		~ZipContent() {
			free(data);
		}
		void* data;
		char uuid[UUID4_LEN];
		size_t size;
	};

	namespace Utility {
		class TARA_API Argument {
		public:
			static Argument& Singleton();
			void Register(int count, char** argv);

			bool debugMode = false;
			bool recordAllLog = false;
		private:
			Argument() {}
			~Argument() {}
			static Argument* m_Singleton;
		};


		class TARA_API File {
		public:
			/*
				Summary:
					Loading string from file
			*/
			static std::string LoadFromFile(std::filesystem::path filename);
			static bool Exist(std::filesystem::path filename);
		};


		class TARA_API Debug {
		public:
			/*
				Summary:
					Loading string from file
			*/
			static void PrintTrace();
			static std::string CurrentTimeString();
		};


		class TARA_API String {
		public:
			static void RemoveString(std::string& main, std::string find);
			static std::string Replace(std::string& main, std::string from, std::string to);
			static std::string Join(std::vector<std::string>& main, std::string separator);
			static std::string ToLowercase(std::string main);
			static std::string ToUppercase(std::string main);
			static std::vector<std::string> Split(std::string main, std::string d);

			template<typename ... Args>
			static std::string FormatString(std::string main, Args ... args) {
				int size_s = std::snprintf(nullptr, 0, main.c_str(), args ...) + 1; // Extra space for '\0'
				if (size_s <= 0) { throw std::runtime_error("Error during formatting."); }
				auto size = static_cast<size_t>(size_s);
				auto buf = std::make_unique<char[]>(size);
				std::snprintf(buf.get(), size, main.c_str(), args ...);
				return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
			}
		};


		class TARA_API Json {
		public:
			static nlohmann::json ReadJson(const char* filename);
			static nlohmann::json ReadJsonString(const char* data);
			static nlohmann::json ReadBson(const char* filename);
			static std::string SaveJson(const char* dest, nlohmann::json& json, bool beautiful = false);
			static std::vector<uint8_t> SaveBson(const char* dest, nlohmann::json& json);
			static std::string ToJson(nlohmann::json& json, bool beautiful = false);
			static std::vector<uint8_t> ToBson(nlohmann::json& json);
		};


		class TARA_API Zip : public IPackage {
		public:
			static Zip* OpenZip(const char* filename);

			bool FileExist(std::string filename) override;
			bool DirectroyExist(std::string dir) override;
			std::vector<std::string> GetDirectories(std::string dir) override;
			std::vector<std::string> GetFiles(std::string dir) override;
			std::vector<char> GetFileData_Char(std::string filename) override;
			std::vector<uint8_t> GetFileData_UChar(std::string filename) override;
			std::string GetFileData_String(std::string filename) override;
			void* GetFileData_Void(std::string filename) override;
			size_t GetFileData_Size(std::string filename) override;
			/// <summary>
			/// <para> Directly call get mesh from zip will return object with empty path string. </para>
			/// <para> And this won't check loaded from pool. </para>
			/// </summary>
			/// <param name="path">Zip path</param>
			/// <returns>Mesh instance return</returns>
			Mesh* GetMesh(std::string filename) override;
			/// <summary>
			/// <para> Directly call get texture from zip will return object with empty path string. </para>
			/// <para> And this won't check loaded from pool. </para>
			/// </summary>
			/// <param name="path">Zip path</param>
			/// <returns>Texture2D instance return</returns>
			Texture2D* GetTexture(std::string filename) override;
			bool CheckDataIsLoaded(std::string filename) override;
			void LoadData(std::string filename) override;
			bool Contain(ZipContent* content);
			bool Contain(const char* uuid);
			void UnzipContent(std::string dest, std::string dir = "");

		protected:
			Zip(const char* filepath);
			virtual ~Zip();

			void OpenZipFile();
			void LoadZipContent(std::string filename, ZipContent* content);

		private:
			const char* filepath;
			std::map<std::string, ZipContent*> contents = std::map<std::string, ZipContent*>();
			std::streampos size = 0;
			std::vector<uint8_t> data = std::vector<uint8_t>();
			void* mem_stream = nullptr;
			void* zip_handle = nullptr;
		};
	};
}